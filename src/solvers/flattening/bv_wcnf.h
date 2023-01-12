/*******************************************************************\

Module: Writing WCNF Files

Author: Lukas Graussam, l.g@lukas-graussam.at

\*******************************************************************/

/// \file
/// Writing WCNF Files

#ifndef CPROVER_SOLVERS_FLATTENING_BV_WCNF_H
#define CPROVER_SOLVERS_FLATTENING_BV_WCNF_H

#include "bv_pointers.h"

class bv_wcnft : public bv_pointerst
{
public:
  bv_wcnft(
    const namespacet &_ns,
    propt &_prop,
    message_handlert &message_handler,
    const std::string &_filename)
    : bv_pointerst(_ns, _prop, message_handler), filename(_filename)
  {
  }

  virtual ~bv_wcnft()
  {
    write_wcnf();
  }

protected:
  const std::string filename;
  bool write_wcnf();
  bool write_wcnf(std::ostream &);
};

#endif // CPROVER_SOLVERS_FLATTENING_BV_WCNF_H
