/*******************************************************************\

Module: Writing WCNF Files

Author: Lukas Graussam, l.g@lukas-graussam.at

\*******************************************************************/

/// \file
/// Writing WCNF Files

#include "bv_wcnf.h"

#include <solvers/sat/wcnf_cnf.h>

#include <fstream> // IWYU pragma: keep
#include <iostream>

bool bv_wcnft::write_wcnf()
{
  if(filename.empty() || filename == "-")
    return write_wcnf(std::cout);

  std::ofstream out(filename);

  if(!out)
  {
    log.error() << "failed to open " << filename << messaget::eom;
    return false;
  }

  return write_wcnf(out);
}

bool bv_wcnft::write_wcnf(std::ostream &out)
{

  symbolst activationVars; // map containing activation variables only
  std::string activationVarString = ""; // build string that will output activation variables
  int countActVars = 0; // save number of activation variables

  // Write activation variables (Soft clauses):
  for(const auto &s : get_symbols())
  {
    if(id2string(s.first).rfind("compHealthy::") == 0) {
      activationVarString = activationVarString + "1 " + std::to_string(s.second.dimacs()) + " 0" + "\n";

      countActVars++;

      std::pair<symbolst::iterator, bool> result =
      activationVars.insert(std::pair<irep_idt, literalt>(s.first, s.second));
      if(!result.second)
        out << "c WARNING: Did not insert activation variable: " << s.first << "\n";
    }
  }

  out << "\n\n";

  // This will write the problem line, soft and hard clauses:
  dynamic_cast<wcnf_cnft &>(prop).write_wcnf_cnf(out, activationVarString, countActVars);


  out << "\n";
  out << "c Activation variables:" << "\n";
  for(const auto &s : activationVars)
  {
    out << "c " << s.first << " " << s.second.dimacs() << "\n";
  }

  // we dump the mapping variable<->literals
  out << "\n";
  out << "c Other variables:" << "\n";
  for(const auto &s : get_symbols())
  {
    // We do not dump activation variables again, since we already dumped them before.
    if(id2string(s.first).rfind("compHealthy::") == 0) {
      continue;
    }

    if(s.second.is_constant())
      out << "c " << s.first << " " << (s.second.is_true() ? "TRUE" : "FALSE")
          << "\n";
    else
      out << "c " << s.first << " " << s.second.dimacs() << "\n";
  }

  

  // dump mapping for selected bit-vectors
  for(const auto &m : get_map().get_mapping())
  {
    const auto &literal_map = m.second.literal_map;

    if(literal_map.empty())
      continue;

    out << "c " << m.first;

    for(const auto &lit : literal_map)
    {
      out << ' ';

      if(lit.is_constant())
        out << (lit.is_true() ? "TRUE" : "FALSE");
      else
        out << lit.dimacs();
    }

    out << "\n";
  }

  return false;
}
