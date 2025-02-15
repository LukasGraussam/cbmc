/*******************************************************************\

Module: Symbolic Execution

Author: Lukas Graussam (LUGR), l.g@lukas-graussam.at

Description: Symbolically execute OBSERVATION_[BEGIN/END] instructions

\*******************************************************************/

/// \file
/// Symbolic Execution

#include "goto_symex.h"

#include <util/exception_utils.h>
  
  // TODO: maybe keep track of inObservation and observation IDs here,
  // similar to atomic section?
  // for now we do this only when converting assignments (for solver)

// Symbolically execute an OBSERVATION_BEGIN instructions
void goto_symext::symex_observation_begin(statet &state)
{
  if(!state.reachable)
    return;

  target.observation_begin(
      state.guard.as_expr(),
      state.source);
}

// Symbolically execute an OBSERVATION_END instructions
void goto_symext::symex_observation_end(statet &state)
{
  if(!state.reachable)
    return;

  target.observation_end(
    state.guard.as_expr(),
    state.source);
}
