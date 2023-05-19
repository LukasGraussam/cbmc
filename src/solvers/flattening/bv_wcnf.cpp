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

  std::cout << "\n~~~~~~~~~~~~~~~~~~~~LUGR: start of write_wcnf"  << "\n";

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

  //  BEGING OBSERVATION OUTPUT~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
  std::cout << "\n~~~~~~~~~~~~~~~~~~~~LUGR: bv_lastObsIndex=" << std::to_string(bv_lastObsIndex) << "\n";
  // If we have a bitvector observation:
  if(bv_lastObsIndex >= 0) {

    // The key of following two maps is the variable name without instance numbers at the end:
    // e.g. the key of destination main::1::bravo!0@1#5 becomes main::1::bravo!0@1#
    std::map<std::string,bvt> bv_destDimacsLiterals; // get destination dimacs literals of a observation varible
    std::map<std::string, std::string> bv_destFullVarName; // get dest. full variabel name from un-instanced variable

    // get corresponding destination variable mapping for our observation variables:
    for(const auto &m : get_map().get_mapping())
    {
      // Look at last observation variables:
      if(id2string(m.first).rfind("WCNF_OBS_" + std::to_string(bv_lastObsIndex)) == 0) {

        // get name of destination variable (without WCNF_OBS prefix but with instance numbering):
        int startPos = id2string(m.first).find("_",9)+1; // "WCNF_OBS_".length() = 9
        std::string destVarName = id2string(m.first).substr(startPos);

        // get name of destination variable without instance numbering:
        int endPos = destVarName.rfind("#"); // Without "#NUM" at end
        std::string curVarKey = destVarName.substr(0,endPos);

        std::cout << "\n~~~~~~~~~~~~~~~~~~~~LUGR: curVarKey=" << curVarKey << "; destVarName=" << destVarName << "\n";

        // Look for corresponing destination variable:
        for(const auto &n : get_map().get_mapping())
        {
          if(id2string(n.first).compare(destVarName) == 0) {
            std::cout << "\n~~~~~~~~~~~~~~~~~~~~LUGR: Found! adding to maps...." << "\n";
            bv_destFullVarName[curVarKey] = destVarName; // add destination variable name
            bv_destDimacsLiterals[curVarKey] = n.second.literal_map; // add literal map of destination variable
          }
        }
      }
    }

    // Create array for observation strings
    std::vector<std::string> observationStrings(bv_lastObsIndex+1,"o"); // all observation strings start with "o"

    // Finally loop again over all observation variables and
    // add each assigned value to the observation output string
    for(const auto &m : get_map().get_mapping())
    {
      if(id2string(m.first).rfind("WCNF_OBS_") == 0) {
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
        

        // LUGR TODO: need this? (and also for dest var literal map???):
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
    }

    // print observation strings:
    out << "c # observ: " << std::to_string(bv_lastObsIndex+1) << "\n";
    for (auto & curObsString : observationStrings) {
      out << curObsString << " 0\n";
    }
  } // END if(bv_lastObsIndex >= 0)

  // LUGR TODO for symbols

  // END OBSERVATION OUTPUT~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
