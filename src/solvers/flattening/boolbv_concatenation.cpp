/*******************************************************************\

Module:

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/

#include "boolbv.h"

#include <util/bitvector_expr.h>
#include <util/invariant.h>

bvt boolbvt::convert_concatenation(const concatenation_exprt &expr)
{
  std::size_t width=boolbv_width(expr.type());

  const exprt::operandst &operands=expr.operands();

  DATA_INVARIANT(
    !operands.empty(), "concatenation shall have at least one operand");

  std::size_t offset=width;
  bvt bv;
  bv.resize(width);

  for(const auto &operand : operands)
  {
    const bvt &op = convert_bv(operand);

    INVARIANT(
      op.size() <= offset,
      "concatenation operand must fit into the result bitvector");

    offset-=op.size();

    for(std::size_t i=0; i<op.size(); i++)
      bv[offset+i]=op[i];
  }

  INVARIANT(
    offset == 0,
    "all bits in the result bitvector must have been filled up by the "
    "concatenation operands");

  return bv;
}
