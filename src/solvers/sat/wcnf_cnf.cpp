/*******************************************************************\

Module:

Author: Lukas Graussam, l.g@lukas-graussam.at

\*******************************************************************/


#include "wcnf_cnf.h"

#include <util/invariant.h>
#include <util/magic.h>

#include <iostream>

wcnf_cnft::wcnf_cnft(message_handlert &message_handler)
  : cnf_clause_listt(message_handler), break_lines(false)
{
}

void wcnf_cnft::set_assignment(literalt, bool)
{
  UNIMPLEMENTED;
}

bool wcnf_cnft::is_in_conflict(literalt) const
{
  UNREACHABLE;
  return false;
}

wcnf_cnf_dumpt::wcnf_cnf_dumpt(
  std::ostream &_out,
  message_handlert &message_handler)
  : cnft(message_handler), out(_out)
{
}

void wcnf_cnft::write_wcnf_cnf(std::ostream &out, std::string softClausesString, int countHealthyPreds)
{
  int topWeight = countHealthyPreds + 1;
  write_problem_line(out, topWeight);
  out << softClausesString;
  write_clauses(out, topWeight);
}

void wcnf_cnft::write_problem_line(std::ostream &out, int topWeight)
{
  // We start counting at 1, thus there is one variable fewer.
  out << "p wcnf " << (no_variables()-1) << " "
      << clauses.size() << " " << topWeight << "\n";
}

// if topWeight is positive, we start each clause with it
// otherwise, we ommit the weight (used in the wcnf_cnf_dumpt::lcnf function)
void wcnf_cnft::write_wcnf_clause(
  const bvt &clause,
  std::ostream &out,
  bool break_lines,
  int topWeight)
{

  // The DIMACS CNF format allows line breaks in clauses:
  // "Each clauses is terminated by the value 0. Unlike many formats
  // that represent the end of a clause by a new-line character,
  // this format allows clauses to be on multiple lines."
  // Some historic solvers (zchaff e.g.) have silently swallowed
  // literals in clauses that exceed some fixed buffer size.

  // However, the SAT competition format does not allow line
  // breaks in clauses, so we offer both options.
  if(topWeight > 0)
    out << topWeight << " "; // we make all hard clauses have top weight

  for(size_t j=0; j<clause.size(); j++)
  {
    out << clause[j].dimacs() << " ";
    // newline to avoid overflow in sat checkers
    if((j&15)==0 && j!=0 && break_lines)
      out << "\n";
  }

  out << "0" << "\n";
}

// Write standard DIMACS clauses -> tranistion relation
void wcnf_cnft::write_clauses(std::ostream &out, int topWeight)
{
  std::size_t count = 0;
  std::stringstream output_block;
  for(clausest::const_iterator it=clauses.begin();
      it!=clauses.end(); it++)
  {
    write_wcnf_clause(*it, output_block, break_lines, topWeight);

    // print the block once in a while
    if(++count % CNF_DUMP_BLOCK_SIZE == 0)
    {
      out << output_block.str();
      output_block.str("");
    }
  }

  // make sure the final block is printed as well
  out << output_block.str();
}

void wcnf_cnf_dumpt::lcnf(const bvt &bv)
{
  wcnf_cnft::write_wcnf_clause(bv, out, true, -1);
}
