/*******************************************************************\

Module: Remove the 'vector' data type by compilation into arrays

Author: Daniel Kroening

Date:   September 2014

\*******************************************************************/

/// \file
/// Remove the 'vector' data type by compilation into arrays

#ifndef CPROVER_GOTO_PROGRAMS_REMOVE_VECTOR_H
#define CPROVER_GOTO_PROGRAMS_REMOVE_VECTOR_H

class goto_functionst;
class goto_modelt;
class symbol_table_baset;

void remove_vector(symbol_table_baset &, goto_functionst &);

void remove_vector(goto_modelt &);

/// returns true iff any of the given goto functions has instructions that use
/// the vector type
bool has_vector(const goto_functionst &);

/// returns true iff the given goto model has instructions that use
/// the vector type
bool has_vector(const goto_modelt &);

#endif // CPROVER_GOTO_PROGRAMS_REMOVE_VECTOR_H
