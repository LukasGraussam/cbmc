/*******************************************************************\

Module: Slicing

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/

/// \file
/// Slicing

#ifndef CPROVER_GOTO_INSTRUMENT_REACHABILITY_SLICER_H
#define CPROVER_GOTO_INSTRUMENT_REACHABILITY_SLICER_H

#include <list>
#include <string>

class goto_modelt;
class message_handlert;

void reachability_slicer(goto_modelt &, message_handlert &);

void reachability_slicer(
  goto_modelt &,
  const std::list<std::string> &properties,
  message_handlert &);

void function_path_reachability_slicer(
  goto_modelt &goto_model,
  const std::list<std::string> &functions_list,
  message_handlert &);

void reachability_slicer(
  goto_modelt &,
  const bool include_forward_reachability,
  message_handlert &);

void reachability_slicer(
  goto_modelt &,
  const std::list<std::string> &properties,
  const bool include_forward_reachability,
  message_handlert &);

#define OPT_FP_REACHABILITY_SLICER "(fp-reachability-slice):"
#define OPT_REACHABILITY_SLICER "(reachability-slice)(reachability-slice-fb)"

#define HELP_FP_REACHABILITY_SLICER                                            \
  " {y--fp-reachability-slice} {uf} \t "                                       \
  "remove instructions that cannot appear on a trace that visits all given "   \
  "functions. The list of functions has to be given as a comma separated "     \
  "list {uf}.\n"                                                               \
  " {y--reachability-slice} \t "                                               \
  "remove instructions that cannot appear on a trace from entry point to a "   \
  "property\n"
#define HELP_REACHABILITY_SLICER                                               \
  " {y--reachability-slice-fb} \t "                                            \
  "remove instructions that cannot appear on a trace from entry point "        \
  "through a property\n"

#endif // CPROVER_GOTO_INSTRUMENT_REACHABILITY_SLICER_H
