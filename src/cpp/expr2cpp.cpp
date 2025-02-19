/*******************************************************************\

Module:

Author: Daniel Kroening, kroening@cs.cmu.edu

\*******************************************************************/

#include "expr2cpp.h"

#include <util/c_types.h>
#include <util/lispexpr.h>
#include <util/lispirep.h>
#include <util/namespace.h>
#include <util/pointer_expr.h>
#include <util/std_expr.h>

#include <ansi-c/c_misc.h>
#include <ansi-c/c_qualifiers.h>
#include <ansi-c/expr2c_class.h>

#include "cpp_name.h"
#include "cpp_template_type.h"

class expr2cppt:public expr2ct
{
public:
  explicit expr2cppt(const namespacet &_ns):expr2ct(_ns) { }

protected:
  std::string convert_with_precedence(
    const exprt &src, unsigned &precedence) override;
  std::string convert_cpp_this();
  std::string convert_cpp_new(const exprt &src);
  std::string convert_extractbit(const exprt &src);
  std::string convert_code_cpp_delete(const exprt &src, unsigned indent);
  std::string convert_code_cpp_new(const exprt &src, unsigned indent);
  std::string convert_struct(const exprt &src, unsigned &precedence) override;
  std::string convert_code(const codet &src, unsigned indent) override;
  // NOLINTNEXTLINE(whitespace/line_length)
  std::string convert_constant(const constant_exprt &src, unsigned &precedence) override;

  std::string convert_rec(
    const typet &src,
    const c_qualifierst &qualifiers,
    const std::string &declarator) override;
};

std::string expr2cppt::convert_struct(
  const exprt &src,
  unsigned &precedence)
{
  if(src.type().id() != ID_struct && src.type().id() != ID_struct_tag)
    return convert_norep(src, precedence);

  const struct_typet &struct_type =
    src.type().id() == ID_struct_tag
      ? ns.follow_tag(to_struct_tag_type(src.type()))
      : to_struct_type(src.type());

  std::string dest="{ ";

  const struct_typet::componentst &components=
    struct_type.components();

  DATA_INVARIANT(
    components.size() == src.operands().size(), "component count mismatch");

  exprt::operandst::const_iterator o_it=src.operands().begin();

  bool first=true;
  size_t last_size=0;

  for(const auto &c : components)
  {
    if(c.type().id() == ID_code)
    {
    }
    else
    {
      std::string tmp=convert(*o_it);
      std::string sep;

      if(first)
        first=false;
      else
      {
        if(last_size+40<dest.size())
        {
          sep=",\n    ";
          last_size=dest.size();
        }
        else
          sep=", ";
      }

      dest+=sep;
      dest+='.';
      if(!c.get_pretty_name().empty())
        dest += id2string(c.get_pretty_name());
      else
        dest += id2string(c.get_name());
      dest+='=';
      dest+=tmp;
    }

    o_it++;
  }

  dest+=" }";

  return dest;
}

std::string expr2cppt::convert_constant(
  const constant_exprt &src,
  unsigned &precedence)
{
  if(src.type().id() == ID_c_bool)
  {
    // C++ has built-in Boolean constants, in contrast to C
    if(src.is_true())
      return "true";
    else if(src.is_false())
      return "false";
  }

  return expr2ct::convert_constant(src, precedence);
}

std::string expr2cppt::convert_rec(
  const typet &src,
  const c_qualifierst &qualifiers,
  const std::string &declarator)
{
  std::unique_ptr<c_qualifierst> clone = qualifiers.clone();
  c_qualifierst &new_qualifiers = *clone;
  new_qualifiers.read(src);

  const std::string d = declarator.empty() ? declarator : (" " + declarator);

  const std::string q=
    new_qualifiers.as_string();

  if(is_reference(src))
  {
    return q + convert(to_reference_type(src).base_type()) + " &" + d;
  }
  else if(is_rvalue_reference(src))
  {
    return q + convert(to_pointer_type(src).base_type()) + " &&" + d;
  }
  else if(!src.get(ID_C_c_type).empty())
  {
    const irep_idt c_type=src.get(ID_C_c_type);

    if(c_type == ID_bool)
      return q+"bool"+d;
    else
      return expr2ct::convert_rec(src, qualifiers, declarator);
  }
  else if(src.id() == ID_struct)
  {
    std::string dest=q;

    if(src.get_bool(ID_C_class))
      dest+="class";
    else if(src.get_bool(ID_C_interface))
      dest+="__interface"; // MS-specific
    else
      dest+="struct";

    dest+=d;

    return dest;
  }
  else if(src.id() == ID_struct_tag)
  {
    const struct_typet &struct_type = ns.follow_tag(to_struct_tag_type(src));

    std::string dest = q;

    if(src.get_bool(ID_C_class))
      dest += "class";
    else if(src.get_bool(ID_C_interface))
      dest += "__interface"; // MS-specific
    else
      dest += "struct";

    const irept &tag = struct_type.find(ID_tag);
    if(!tag.id().empty())
    {
      if(tag.id() == ID_cpp_name)
        dest += " " + to_cpp_name(tag).to_string();
      else
        dest += " " + id2string(tag.id());
    }

    dest += d;

    return dest;
  }
  else if(src.id() == ID_union_tag)
  {
    const union_typet &union_type = ns.follow_tag(to_union_tag_type(src));

    std::string dest = q + "union";

    const irept &tag = union_type.find(ID_tag);
    if(!tag.id().empty())
    {
      if(tag.id() == ID_cpp_name)
        dest += " " + to_cpp_name(tag).to_string();
      else
        dest += " " + id2string(tag.id());
    }

    dest += d;

    return dest;
  }
  else if(src.id()==ID_constructor)
  {
    return "constructor ";
  }
  else if(src.id()==ID_destructor)
  {
    return "destructor ";
  }
  else if(src.id()=="cpp-template-type")
  {
    return "typename";
  }
  else if(src.id()==ID_template)
  {
    std::string dest="template<";

    const irept::subt &arguments=src.find(ID_arguments).get_sub();

    for(auto it = arguments.begin(); it != arguments.end(); ++it)
    {
      if(it!=arguments.begin())
        dest+=", ";

      const exprt &argument=(const exprt &)*it;

      if(argument.id()==ID_symbol)
      {
        dest+=convert(argument.type())+" ";
        dest+=convert(argument);
      }
      else if(argument.id()==ID_type)
        dest+=convert(argument.type());
      else
      {
        lispexprt lisp;
        irep2lisp(argument, lisp);
        dest+="irep(\""+MetaString(lisp.expr2string())+"\")";
      }
    }

    dest += "> " + convert(to_template_type(src).subtype());
    return dest;
  }
  else if(
    src.id() == ID_pointer &&
    to_pointer_type(src).base_type().id() == ID_nullptr)
  {
    return "std::nullptr_t";
  }
  else if(src.id() == ID_pointer && src.find(ID_to_member).is_not_nil())
  {
    typet tmp=src;
    typet member;
    member.swap(tmp.add(ID_to_member));

    std::string dest = "(" + convert(member) + ":: *)";

    const auto &base_type = to_pointer_type(src).base_type();

    if(base_type.id() == ID_code)
    {
      const code_typet &code_type = to_code_type(base_type);
      const typet &return_type = code_type.return_type();
      dest = convert(return_type) + " " + dest;

      const code_typet::parameterst &args = code_type.parameters();
      dest+="(";

      for(code_typet::parameterst::const_iterator it=args.begin();
          it!=args.end();
          ++it)
      {
        if(it!=args.begin())
          dest+=", ";
        dest += convert(it->type());
      }

      dest+=")";
      dest+=d;
    }
    else
      dest = convert(base_type) + " " + dest + d;

    return dest;
  }
  else if(src.id()==ID_verilog_signedbv ||
          src.id()==ID_verilog_unsignedbv)
    return "sc_lv[" + std::to_string(to_bitvector_type(src).get_width()) + "]" +
           d;
  else if(src.id()==ID_unassigned)
    return "?";
  else if(src.id()==ID_code)
  {
    const code_typet &code_type=to_code_type(src);

    // C doesn't really have syntax for function types,
    // so we use C++11 trailing return types!

    std::string dest="auto";

    // qualifiers, declarator?
    if(d.empty())
      dest+=' ';
    else
      dest+=d;

    dest+='(';
    const code_typet::parameterst &parameters=code_type.parameters();

    for(code_typet::parameterst::const_iterator
        it=parameters.begin();
        it!=parameters.end();
        it++)
    {
      if(it!=parameters.begin())
        dest+=", ";

      dest+=convert(it->type());
    }

    if(code_type.has_ellipsis())
    {
      if(!parameters.empty())
        dest+=", ";
      dest+="...";
    }

    dest+=')';

    const typet &return_type=code_type.return_type();
    dest+=" -> "+convert(return_type);

    return dest;
  }
  else if(src.id()==ID_initializer_list)
  {
    // only really used in error messages
    return "{ ... }";
  }
  else if(src.id() == ID_c_bool)
  {
    return q + "bool" + d;
  }
  else
    return expr2ct::convert_rec(src, qualifiers, declarator);
}

std::string expr2cppt::convert_cpp_this()
{
  return id2string(ID_this);
}

std::string expr2cppt::convert_cpp_new(const exprt &src)
{
  std::string dest;

  if(src.get(ID_statement)==ID_cpp_new_array)
  {
    dest="new";

    std::string tmp_size=
      convert(static_cast<const exprt &>(src.find(ID_size)));

    dest+=' ';
    dest += convert(to_pointer_type(src.type()).base_type());
    dest+='[';
    dest+=tmp_size;
    dest+=']';
  }
  else
    dest = "new " + convert(to_pointer_type(src.type()).base_type());

  return dest;
}

std::string expr2cppt::convert_code_cpp_new(const exprt &src, unsigned indent)
{
  return indent_str(indent) + convert_cpp_new(src) + ";\n";
}

std::string expr2cppt::convert_code_cpp_delete(
  const exprt &src,
  unsigned indent)
{
  std::string dest=indent_str(indent)+"delete ";

  if(src.operands().size()!=1)
  {
    unsigned precedence;
    return convert_norep(src, precedence);
  }

  std::string tmp = convert(to_unary_expr(src).op());

  dest+=tmp+";\n";

  return dest;
}

std::string expr2cppt::convert_with_precedence(
  const exprt &src,
  unsigned &precedence)
{
  if(src.id()=="cpp-this")
  {
    precedence = 15;
    return convert_cpp_this();
  }
  if(src.id()==ID_extractbit)
  {
    precedence = 15;
    return convert_extractbit(src);
  }
  else if(src.id()==ID_side_effect &&
          (src.get(ID_statement)==ID_cpp_new ||
           src.get(ID_statement)==ID_cpp_new_array))
  {
    precedence = 15;
    return convert_cpp_new(src);
  }
  else if(src.id()==ID_side_effect &&
          src.get(ID_statement)==ID_throw)
  {
    precedence = 16;
    return convert_function(src, "throw");
  }
  else if(src.is_constant() && src.type().id()==ID_verilog_signedbv)
    return "'"+id2string(src.get(ID_value))+"'";
  else if(src.is_constant() && src.type().id()==ID_verilog_unsignedbv)
    return "'"+id2string(src.get(ID_value))+"'";
  else if(src.is_constant() && to_constant_expr(src).get_value()==ID_nullptr)
    return "nullptr";
  else if(src.id()==ID_unassigned)
    return "?";
  else if(src.id() == ID_pod_constructor)
    return "pod_constructor";
  else
    return expr2ct::convert_with_precedence(src, precedence);
}

std::string expr2cppt::convert_code(
  const codet &src,
  unsigned indent)
{
  const irep_idt &statement=src.get(ID_statement);

  if(statement==ID_cpp_delete ||
     statement==ID_cpp_delete_array)
    return convert_code_cpp_delete(src, indent);

  if(statement==ID_cpp_new ||
     statement==ID_cpp_new_array)
    return convert_code_cpp_new(src, indent);

  return expr2ct::convert_code(src, indent);
}

std::string expr2cppt::convert_extractbit(const exprt &src)
{
  const auto &extractbit_expr = to_extractbit_expr(src);
  return convert(extractbit_expr.op0()) + "[" + convert(extractbit_expr.op1()) +
         "]";
}

std::string expr2cpp(const exprt &expr, const namespacet &ns)
{
  expr2cppt expr2cpp(ns);
  expr2cpp.get_shorthands(expr);
  return expr2cpp.convert(expr);
}

std::string type2cpp(const typet &type, const namespacet &ns)
{
  expr2cppt expr2cpp(ns);
  return expr2cpp.convert(type);
}
