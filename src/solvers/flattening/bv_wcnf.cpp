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
  // First the observations are encoded in the WCNF:
  if(!writeObservationOutput(out)) {
    return false;
  }

  symbolst healthyPreds; // map containing healthy variables only
  std::string softClausesString = ""; // build string that will output activation variables
  int countHealthyPreds = 0; // save number of activation variables

  // Write activation variables (Soft clauses):
  for(const auto &s : get_symbols())
  {
    if(id2string(s.first).rfind("compHealthy::") == 0) {
      softClausesString = softClausesString + "1 " + std::to_string(s.second.dimacs()) + " 0" + "\n";

      countHealthyPreds++;

      std::pair<symbolst::iterator, bool> result =
      healthyPreds.insert(std::pair<irep_idt, literalt>(s.first, s.second));
      if(!result.second)
        out << "c WARNING: Did not insert activation variable: " << s.first << "\n";
    }
  }

  // This will write the problem line, soft and hard clauses:
  dynamic_cast<wcnf_cnft &>(prop).write_wcnf_cnf(out, softClausesString, countHealthyPreds);

  // The Strings "ACTIVATION_VARIABLES_BEGIN/END" are used by fault-location scripts
  // to identify this section in the wcnf file for mapping the variables to line numbers
  out << "\n";
  out << "c ACTIVATION_VARIABLES_BEGIN" << "\n";
  for(const auto &s : healthyPreds)
  {
    out << "c " << s.first << " " << s.second.dimacs() << "\n";
  }
  out << "c ACTIVATION_VARIABLES_END" << "\n";

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

bool bv_wcnft::writeObservationOutput(std::ostream &out)
{
  int bv_lastObsIndex = -1; // index of last observation (highest observation index)

  // get last observation index:
  for(const auto &m : get_map().get_mapping())
  {
    if(id2string(m.first).rfind("WCNF_OBS_") == 0) {
      // get observation index from variable name:
      int curIndex = stoi(id2string(m.first).substr(9,id2string(m.first).find("_",9))); // "WCNF_OBS_".length() = 9
      if(curIndex>bv_lastObsIndex) {
        bv_lastObsIndex = curIndex;
      }
    }
  }
  
  // If we do not have a bitvector observation:
  if(bv_lastObsIndex < 0) {
    return true;
    // TODO do we need to do the same logic of this whole method also for symbols (get_symbols())?
  }

  // The key of following two maps is the variable name without instance numbers at the end:
  // e.g. the key of destination main::1::bravo!0@1#5 becomes main::1::bravo!0@1#
  std::map<std::string,bvt> bv_destDimacsLiterals; // get destination dimacs literals of a observation varible
  std::map<std::string, std::string> bv_destFullVarName; // get dest. full variabel name from un-instanced variable

  // This loop is only for filling the maps, i.e.,
  // getting mapping for all observation variables to their destination variable:
  for(const auto &m : get_map().get_mapping())
  {
    // Continue if it is NOT at last observation variable:
    if(id2string(m.first).rfind("WCNF_OBS_" + std::to_string(bv_lastObsIndex)) != 0) {
      continue;
    }

    // get name of destination variable (without WCNF_OBS prefix but with instance numbering):
    int startPos = id2string(m.first).find("_",9)+1; // "WCNF_OBS_".length() = 9
    std::string destVarName = id2string(m.first).substr(startPos);

    // get name of destination variable without instance numbering:
    int endPos = destVarName.rfind("#"); // Without "#NUM" at end
    std::string curVarKey = destVarName.substr(0,endPos);

    // Look for corresponing destination variable (actually used variable without the WCNF_OBS prefix):
    for(const auto &n : get_map().get_mapping())
    {
      if(id2string(n.first).compare(destVarName) == 0) {
        bv_destFullVarName[curVarKey] = destVarName; // add destination variable name
        bv_destDimacsLiterals[curVarKey] = n.second.literal_map; // add literal map of destination variable
      }
    }
  }

  // Create array for observation strings
  std::vector<std::string> observationStrings(bv_lastObsIndex+1,"o"); // all observation strings start with "o"

  // Finally loop again over all observation variables and
  // add each assigned value to the observation output string
  for(const auto &m : get_map().get_mapping())
  {
    if(id2string(m.first).rfind("WCNF_OBS_") != 0) {
      continue;
    }

    // get observation index from variable name:
    int curObsIndex = stoi(id2string(m.first).substr(9,id2string(m.first).find("_",9))); // "WCNF_OBS_".length() = 9
    auto &curObsString = observationStrings[curObsIndex]; // Current observation string

    // get name of current variable (without WCNF_OBS prefix but with instance numbering):
    int startPos = id2string(m.first).find("_",9)+1; // "WCNF_OBS_".length() = 9
    std::string tmpThisVarName = id2string(m.first).substr(startPos);

    // get name of current variable without instance numbering:
    int endPos = tmpThisVarName.rfind("#"); // Without "#NUM"
    std::string curVarKey = tmpThisVarName.substr(0,endPos);

    const auto &curLiteralMap = m.second.literal_map; // literal map of current variable
    const auto &destLiteralMap = bv_destDimacsLiterals[curVarKey]; // literal map of current variable

    // Sanity check, which should not happen:
    if(curLiteralMap.empty() || destLiteralMap.empty() || curLiteralMap.size() != destLiteralMap.size()) {
      out << "c WARNING: Found empty or unequal-length literal maps for : " << m.first << ", " << bv_destFullVarName[curVarKey] << "\n";
      continue;
    }

    for(unsigned int i = 0; i < curLiteralMap.size(); i++)
    {
      if(!curLiteralMap[i].is_constant()) {
        log.error() << "literal map of " << m.first << " has non-constant literal" << messaget::eom;
        return false;
      }
      if(destLiteralMap[i].is_constant()) {
        log.error() << "literal map of " << bv_destFullVarName[curVarKey] << " has constant literal" << messaget::eom;
        return false;
      }
      curObsString.append(" ");
      if(curLiteralMap[i].is_true()) {
        curObsString.append(std::to_string(destLiteralMap[i].dimacs())); // append pos. dimacs to curObsString
      }
      else {
        curObsString.append(std::to_string(-destLiteralMap[i].dimacs())); // append neg. dimacs to curObsString
      }
    }
  }

  // print observation strings:
  out << "c # observ: " << std::to_string(bv_lastObsIndex+1) << "\n";
  for (auto & curObsString : observationStrings) {
    out << curObsString << " 0\n";
  }

  return true;
}
