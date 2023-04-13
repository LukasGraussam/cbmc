/*******************************************************************\

Module:

Author: Lukas Graussam, l.g@lukas-graussam.at

\*******************************************************************/


#ifndef CPROVER_SOLVERS_SAT_WCNF_CNF_H
#define CPROVER_SOLVERS_SAT_WCNF_CNF_H

#include <iosfwd>

#include "cnf_clause_list.h"

class wcnf_cnft:public cnf_clause_listt
{
public:
  explicit wcnf_cnft(message_handlert &);
  virtual ~wcnf_cnft() { }

  virtual void write_wcnf_cnf(std::ostream &out, std::string activationVarString, int countActVars);

  // dummy functions

  std::string solver_text() const override
  {
    return "WCNF CNF";
  }

  void set_assignment(literalt a, bool value) override;
  bool is_in_conflict(literalt l) const override;

  static void
  write_wcnf_clause(const bvt &, std::ostream &, bool break_lines, int topWeight);

protected:
  void write_problem_line(std::ostream &out, int topWeight);
  void write_clauses(std::ostream &out, int topWeight);

  bool break_lines;
};

class wcnf_cnf_dumpt:public cnft
{
public:
  wcnf_cnf_dumpt(std::ostream &_out, message_handlert &message_handler);
  virtual ~wcnf_cnf_dumpt() { }

  std::string solver_text() const override
  {
    return "WCNF CNF Dumper";
  }

  void lcnf(const bvt &bv) override;

  tvt l_get(literalt) const override
  {
    return tvt::unknown();
  }

  size_t no_clauses() const override
  {
    return 0;
  }

protected:
  resultt do_prop_solve() override
  {
    return resultt::P_ERROR;
  }

  std::ostream &out;
};

#endif // CPROVER_SOLVERS_SAT_WCNF_CNF_H
