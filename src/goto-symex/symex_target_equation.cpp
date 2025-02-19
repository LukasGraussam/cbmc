/*******************************************************************\

Module: Symbolic Execution

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/

/// \file
/// Symbolic Execution
/// Implementation of functions to build SSA equation.

#include "symex_target_equation.h"

#include <util/std_expr.h>

#include "solver_hardness.h"
#include "ssa_step.h"

#include <chrono> // IWYU pragma: keep

#include <util/options.h> // Introduced for WCNF option (fault-localization)

static std::function<void(solver_hardnesst &)>
hardness_register_ssa(std::size_t step_index, const SSA_stept &step)
{
  return [step_index, &step](solver_hardnesst &hardness) {
    hardness.register_ssa(step_index, step.cond_expr, step.source.pc);
  };
}

void symex_target_equationt::shared_read(
  const exprt &guard,
  const ssa_exprt &ssa_object,
  unsigned atomic_section_id,
  const sourcet &source)
{
  SSA_steps.emplace_back(source, goto_trace_stept::typet::SHARED_READ);
  SSA_stept &SSA_step=SSA_steps.back();

  SSA_step.guard=guard;
  SSA_step.ssa_lhs=ssa_object;
  SSA_step.atomic_section_id=atomic_section_id;

  merge_ireps(SSA_step);
}

void symex_target_equationt::shared_write(
  const exprt &guard,
  const ssa_exprt &ssa_object,
  unsigned atomic_section_id,
  const sourcet &source)
{
  SSA_steps.emplace_back(source, goto_trace_stept::typet::SHARED_WRITE);
  SSA_stept &SSA_step=SSA_steps.back();

  SSA_step.guard=guard;
  SSA_step.ssa_lhs=ssa_object;
  SSA_step.atomic_section_id=atomic_section_id;

  merge_ireps(SSA_step);
}

/// spawn a new thread
void symex_target_equationt::spawn(
  const exprt &guard,
  const sourcet &source)
{
  SSA_steps.emplace_back(source, goto_trace_stept::typet::SPAWN);
  SSA_stept &SSA_step=SSA_steps.back();
  SSA_step.guard=guard;

  merge_ireps(SSA_step);
}

void symex_target_equationt::memory_barrier(
  const exprt &guard,
  const sourcet &source)
{
  SSA_steps.emplace_back(source, goto_trace_stept::typet::MEMORY_BARRIER);
  SSA_stept &SSA_step=SSA_steps.back();
  SSA_step.guard=guard;

  merge_ireps(SSA_step);
}

/// start an atomic section
void symex_target_equationt::atomic_begin(
  const exprt &guard,
  unsigned atomic_section_id,
  const sourcet &source)
{
  SSA_steps.emplace_back(source, goto_trace_stept::typet::ATOMIC_BEGIN);
  SSA_stept &SSA_step=SSA_steps.back();
  SSA_step.guard=guard;
  SSA_step.atomic_section_id=atomic_section_id;

  merge_ireps(SSA_step);
}

/// end an atomic section
void symex_target_equationt::atomic_end(
  const exprt &guard,
  unsigned atomic_section_id,
  const sourcet &source)
{
  SSA_steps.emplace_back(source, goto_trace_stept::typet::ATOMIC_END);
  SSA_stept &SSA_step=SSA_steps.back();
  SSA_step.guard=guard;
  SSA_step.atomic_section_id=atomic_section_id;

  merge_ireps(SSA_step);
}

/// start of an observation block, for WCNF option (fault-localization)
void symex_target_equationt::observation_begin(
  const exprt &guard,
  const sourcet &source)
{
  SSA_steps.emplace_back(source, goto_trace_stept::typet::OBSERVATION_BEGIN);
  SSA_stept &SSA_step=SSA_steps.back();
  SSA_step.guard=guard;

  merge_ireps(SSA_step);
}

/// end of an observation block, for WCNF option (fault-localization)
void symex_target_equationt::observation_end(
  const exprt &guard,
  const sourcet &source)
{
  SSA_steps.emplace_back(source, goto_trace_stept::typet::OBSERVATION_END);
  SSA_stept &SSA_step=SSA_steps.back();
  SSA_step.guard=guard;

  merge_ireps(SSA_step);
}

void symex_target_equationt::assignment(
  const exprt &guard,
  const ssa_exprt &ssa_lhs,
  const exprt &ssa_full_lhs,
  const exprt &original_full_lhs,
  const exprt &ssa_rhs,
  const sourcet &source,
  assignment_typet assignment_type)
{
  PRECONDITION(ssa_lhs.is_not_nil());

  SSA_steps.emplace_back(SSA_assignment_stept{source,
                                              guard,
                                              ssa_lhs,
                                              ssa_full_lhs,
                                              original_full_lhs,
                                              ssa_rhs,
                                              assignment_type});

  merge_ireps(SSA_steps.back());
}

void symex_target_equationt::decl(
  const exprt &guard,
  const ssa_exprt &ssa_lhs,
  const exprt &initializer,
  const sourcet &source,
  assignment_typet assignment_type)
{
  PRECONDITION(ssa_lhs.is_not_nil());

  SSA_steps.emplace_back(source, goto_trace_stept::typet::DECL);
  SSA_stept &SSA_step=SSA_steps.back();

  SSA_step.guard=guard;
  SSA_step.ssa_lhs=ssa_lhs;
  SSA_step.ssa_full_lhs = initializer;
  SSA_step.original_full_lhs=ssa_lhs.get_original_expr();
  SSA_step.hidden=(assignment_type!=assignment_typet::STATE);

  // the condition is trivially true, and only
  // there so we see the symbols
  SSA_step.cond_expr=equal_exprt(SSA_step.ssa_lhs, SSA_step.ssa_lhs);

  merge_ireps(SSA_step);
}

/// declare a fresh variable
void symex_target_equationt::dead(
  const exprt &,
  const ssa_exprt &,
  const sourcet &)
{
  // we currently don't record these
}

void symex_target_equationt::location(
  const exprt &guard,
  const sourcet &source)
{
  SSA_steps.emplace_back(source, goto_trace_stept::typet::LOCATION);
  SSA_stept &SSA_step=SSA_steps.back();

  SSA_step.guard=guard;

  merge_ireps(SSA_step);
}

void symex_target_equationt::function_call(
  const exprt &guard,
  const irep_idt &function_id,
  const std::vector<renamedt<exprt, L2>> &function_arguments,
  const sourcet &source,
  const bool hidden)
{
  SSA_steps.emplace_back(source, goto_trace_stept::typet::FUNCTION_CALL);
  SSA_stept &SSA_step=SSA_steps.back();

  SSA_step.guard = guard;
  SSA_step.called_function = function_id;
  for(const auto &arg : function_arguments)
    SSA_step.ssa_function_arguments.emplace_back(arg.get());
  SSA_step.hidden = hidden;

  merge_ireps(SSA_step);
}

void symex_target_equationt::function_return(
  const exprt &guard,
  const irep_idt &function_id,
  const sourcet &source,
  const bool hidden)
{
  SSA_steps.emplace_back(source, goto_trace_stept::typet::FUNCTION_RETURN);
  SSA_stept &SSA_step=SSA_steps.back();

  SSA_step.guard = guard;
  SSA_step.called_function = function_id;
  SSA_step.hidden = hidden;

  merge_ireps(SSA_step);
}

void symex_target_equationt::output(
  const exprt &guard,
  const sourcet &source,
  const irep_idt &output_id,
  const std::list<renamedt<exprt, L2>> &args)
{
  SSA_steps.emplace_back(source, goto_trace_stept::typet::OUTPUT);
  SSA_stept &SSA_step=SSA_steps.back();

  SSA_step.guard=guard;
  for(const auto &arg : args)
    SSA_step.io_args.emplace_back(arg.get());
  SSA_step.io_id=output_id;

  merge_ireps(SSA_step);
}

void symex_target_equationt::output_fmt(
  const exprt &guard,
  const sourcet &source,
  const irep_idt &output_id,
  const irep_idt &fmt,
  const std::list<exprt> &args)
{
  SSA_steps.emplace_back(source, goto_trace_stept::typet::OUTPUT);
  SSA_stept &SSA_step=SSA_steps.back();

  SSA_step.guard=guard;
  SSA_step.io_args=args;
  SSA_step.io_id=output_id;
  SSA_step.formatted=true;
  SSA_step.format_string=fmt;

  merge_ireps(SSA_step);
}

void symex_target_equationt::input(
  const exprt &guard,
  const sourcet &source,
  const irep_idt &input_id,
  const std::list<exprt> &args)
{
  SSA_steps.emplace_back(source, goto_trace_stept::typet::INPUT);
  SSA_stept &SSA_step=SSA_steps.back();

  SSA_step.guard=guard;
  SSA_step.io_args=args;
  SSA_step.io_id=input_id;

  merge_ireps(SSA_step);
}

void symex_target_equationt::assumption(
  const exprt &guard,
  const exprt &cond,
  const sourcet &source)
{
  SSA_steps.emplace_back(source, goto_trace_stept::typet::ASSUME);
  SSA_stept &SSA_step=SSA_steps.back();

  SSA_step.guard=guard;
  SSA_step.cond_expr=cond;

  merge_ireps(SSA_step);
}

void symex_target_equationt::assertion(
  const exprt &guard,
  const exprt &cond,
  const irep_idt &property_id,
  const std::string &msg,
  const sourcet &source)
{
  SSA_steps.emplace_back(source, goto_trace_stept::typet::ASSERT);
  SSA_stept &SSA_step=SSA_steps.back();

  SSA_step.guard=guard;
  SSA_step.cond_expr=cond;
  SSA_step.comment=msg;
  SSA_step.property_id = property_id;

  merge_ireps(SSA_step);
}

void symex_target_equationt::goto_instruction(
  const exprt &guard,
  const renamedt<exprt, L2> &cond,
  const sourcet &source)
{
  SSA_steps.emplace_back(source, goto_trace_stept::typet::GOTO);
  SSA_stept &SSA_step=SSA_steps.back();

  SSA_step.guard=guard;
  SSA_step.cond_expr = cond.get();

  merge_ireps(SSA_step);
}

void symex_target_equationt::constraint(
  const exprt &cond,
  const std::string &msg,
  const sourcet &source)
{
  // like assumption, but with global effect
  SSA_steps.emplace_back(source, goto_trace_stept::typet::CONSTRAINT);
  SSA_stept &SSA_step=SSA_steps.back();

  SSA_step.guard=true_exprt();
  SSA_step.cond_expr=cond;
  SSA_step.comment=msg;

  merge_ireps(SSA_step);
}

void symex_target_equationt::convert_without_assertions(
  decision_proceduret &decision_procedure,
  bool wcnfIsSet)
{
  with_solver_hardness(decision_procedure, [&](solver_hardnesst &hardness) {
    hardness.register_ssa_size(SSA_steps.size());
  });

  convert_guards(decision_procedure);
  if(wcnfIsSet) {
    convert_assignments_wcnf(decision_procedure);
  }
  else {
    convert_assignments(decision_procedure);
  }
  convert_decls(decision_procedure);
  convert_assumptions(decision_procedure);
  convert_goto_instructions(decision_procedure);
  convert_function_calls(decision_procedure);
  convert_io(decision_procedure);
  convert_constraints(decision_procedure);
}

void symex_target_equationt::convert(
  decision_proceduret &decision_procedure,
  bool wcnfIsSet)
{
  const auto convert_SSA_start = std::chrono::steady_clock::now();

  convert_without_assertions(decision_procedure, wcnfIsSet);
  convert_assertions(decision_procedure, true,  wcnfIsSet);

  const auto convert_SSA_stop = std::chrono::steady_clock::now();
  std::chrono::duration<double> convert_SSA_runtime =
    std::chrono::duration<double>(convert_SSA_stop - convert_SSA_start);
  log.statistics() << "Runtime Convert SSA: " << convert_SSA_runtime.count()
                   << "s" << messaget::eom;
}

void symex_target_equationt::convert_assignments(
  decision_proceduret &decision_procedure)
{
  std::size_t step_index = 0;
  for(auto &step : SSA_steps)
  {
    if(step.is_assignment() && !step.ignore && !step.converted)
    {
      log.conditional_output(log.debug(), [&step](messaget::mstreamt &mstream) {
        step.output(mstream);
        mstream << messaget::eom;
      });

      decision_procedure.set_to_true(step.cond_expr);
      step.converted = true;
      with_solver_hardness(
        decision_procedure, hardness_register_ssa(step_index, step));
    }
    ++step_index;
  }
}

bool symex_target_equationt::convert_observation_step(SSA_stept &step,
  std::size_t observation_index)
{
  if(step.source.pc->source_location().is_built_in())  {
    log.warning() << "built in location not expected within Observation"
          << messaget::eom;
    return false;
  }
  if(step.assignment_type != symex_targett::assignment_typet::STATE) {
    log.warning() << "Non STATE Assignment not expected within observation"
        << messaget::eom;
    return false;
  }
  // Check whether we have a equality expression:
  if(!can_cast_expr<equal_exprt>(step.cond_expr)) {
    log.warning() << "Non Equality expression not expected within observation"
        << messaget::eom;
    return false;
  }

  // Cast condition expression of current step to a equality expression:
  equal_exprt curAssignment = to_equal_expr(step.cond_expr);

  if(!curAssignment.rhs().is_constant()) {
    log.warning() << "RHS must be constant in observation"
        << messaget::eom;
    return false;
  }
  if(!can_cast_expr<symbol_exprt>(curAssignment.lhs())) {
    log.warning() << "LHS must be a symbol in observation"
        << messaget::eom;
    return false;
  }

  // Cast lhs of assignment to symbol:
  symbol_exprt curAssignVar = to_symbol_expr(curAssignment.lhs());

  // Give the symbol the new name:
  const irep_idt newVarName = "WCNF_OBS_" + std::to_string(observation_index) + "_" + id2string(curAssignVar.get_identifier());
  curAssignVar.set_identifier(newVarName);

  // build new equality expression with replaced variable name:
  equal_exprt newCond(curAssignVar,curAssignment.rhs());
  step.cond_expr = newCond;

  return true;
}

void symex_target_equationt::convert_wcnf_assignment_step(SSA_stept &step)
{
  // decide whether to insert a healthy variable for fault-localization,
  // i.e. check whether this assignment really corresponds to a line of code we want to enable/disble:
  bool insertFaultLoc = false;
  // check if not a built-in step:
  if(!step.source.pc->source_location().is_built_in()) {
    // check types of assignments:
    switch(step.assignment_type)
    {
    case symex_targett::assignment_typet::STATE:
      // TODO: In this newer CBMC version, there are assignment steps created for function calls
      // even when they appear within a CPROVER_assert. Thus, such lines - as in the TCAS benchmark -
      // can now also get havoced as opposed to the initial CBMC version where the wcnf feature was introduced.
      // This cannot be fixed by NOT havocing function calls (step.source.pc->is_function_call()) since
      // a "normal" line can consist of only such an assignment step of type function call
      insertFaultLoc = true;
      break;
    case symex_targett::assignment_typet::GUARD:
      insertFaultLoc = true;
      break;
    case symex_targett::assignment_typet::PHI:
      insertFaultLoc = false; // this is a path merge
      break;
    case symex_targett::assignment_typet::HIDDEN:
      insertFaultLoc = false; // hidden assignments, e.g. for mapping return values when calling a function and using the return value...
      // true if it is a return statement itself:
      if(step.source.pc->type() == SET_RETURN_VALUE) {
        insertFaultLoc = true;
      }
      break;
    case symex_targett::assignment_typet::VISIBLE_ACTUAL_PARAMETER:
      insertFaultLoc = false; // used somehow in function calls
      break;
    // TODO: check if handling for other assignment types is necessary:
    case symex_targett::assignment_typet::HIDDEN_ACTUAL_PARAMETER:
      log.error() << "Assignment type not considered so far (for WCNF option)"
            << messaget::eom;
      break;
    default:
      log.error() << "Assignment type not considered so far (for WCNF option)"
            << messaget::eom;
    }
  }

  if(insertFaultLoc) {
    // create and insert healthy variable for fault-loc:
    std::string myFile = id2string(step.source.pc->source_location().get_file());
    std::string myLine = id2string(step.source.pc->source_location().get_line());
    const irep_idt identifier = "compHealthy::" + myFile + "::" + myLine;
    symbol_exprt healthySymbol(identifier,bool_typet());

    implies_exprt implication(
      healthySymbol,
      step.cond_expr);
    
    step.cond_expr = implication;
  }
}

void symex_target_equationt::convert_assignments_wcnf(
  decision_proceduret &decision_procedure)
{
  std::size_t step_index = 0;
  std::size_t observation_index = 0; // keep track of observations
  bool inObservation = false; // whether we are in an observation block
  for(auto &step : SSA_steps)
  {
    if(step.is_assignment() && !step.ignore && !step.converted)
    {
      log.conditional_output(log.debug(), [&step](messaget::mstreamt &mstream) {
        step.output(mstream);
        mstream << messaget::eom;
      });

      // Parse observations:
      if(inObservation) {
        if(convert_observation_step(step,observation_index)) {
          decision_procedure.set_to_true(step.cond_expr);
          step.converted = true;
          with_solver_hardness(
            decision_procedure, hardness_register_ssa(step_index, step));
        }
        ++step_index;
        continue; // Go to next iteration of for-loop
      }

      convert_wcnf_assignment_step(step);

      decision_procedure.set_to_true(step.cond_expr);
      step.converted = true;
      with_solver_hardness(
        decision_procedure, hardness_register_ssa(step_index, step));
    }
    else if (step.is_observation_begin() && !step.ignore && !step.converted) {
      if(inObservation) {
        log.error() << "convert_assignments_wcnf: Nesting of OBSERVATION_BEGIN not allowed"
               << messaget::eom;
      }
      inObservation=true;
      step.converted = true;
    }
    else if (step.is_observation_end() && !step.ignore && !step.converted) {
      if(!inObservation) {
        log.error() << "convert_assignments_wcnf: OBSERVATION_END requires preceeding OBSERVATION_BEGIN"
               << messaget::eom;
      }
      inObservation=false;
      observation_index++;
      step.converted = true;
    }
    ++step_index;
  }
}

void symex_target_equationt::convert_decls(
  decision_proceduret &decision_procedure)
{
  std::size_t step_index = 0;
  for(auto &step : SSA_steps)
  {
    if(step.is_decl() && !step.ignore && !step.converted)
    {
      // The result is not used, these have no impact on
      // the satisfiability of the formula.
      decision_procedure.handle(step.cond_expr);
      decision_procedure.handle(
        equal_exprt{step.ssa_full_lhs, step.ssa_full_lhs});
      step.converted = true;
      with_solver_hardness(
        decision_procedure, hardness_register_ssa(step_index, step));
    }
    ++step_index;
  }
}

void symex_target_equationt::convert_guards(
  decision_proceduret &decision_procedure)
{
  std::size_t step_index = 0;
  for(auto &step : SSA_steps)
  {
    if(step.ignore)
      step.guard_handle = false_exprt();
    else
    {
      log.conditional_output(log.debug(), [&step](messaget::mstreamt &mstream) {
        step.output(mstream);
        mstream << messaget::eom;
      });

      step.guard_handle = decision_procedure.handle(step.guard);
      with_solver_hardness(
        decision_procedure, [step_index, &step](solver_hardnesst &hardness) {
          hardness.register_ssa(step_index, step.guard, step.source.pc);
        });
    }
    ++step_index;
  }
}

void symex_target_equationt::convert_assumptions(
  decision_proceduret &decision_procedure)
{
  std::size_t step_index = 0;
  for(auto &step : SSA_steps)
  {
    if(step.is_assume())
    {
      if(step.ignore)
        step.cond_handle = true_exprt();
      else
      {
        log.conditional_output(
          log.debug(), [&step](messaget::mstreamt &mstream) {
            step.output(mstream);
            mstream << messaget::eom;
          });

        step.cond_handle = decision_procedure.handle(step.cond_expr);

        with_solver_hardness(
          decision_procedure, hardness_register_ssa(step_index, step));
      }
    }
    ++step_index;
  }
}

void symex_target_equationt::convert_goto_instructions(
  decision_proceduret &decision_procedure)
{
  std::size_t step_index = 0;
  for(auto &step : SSA_steps)
  {
    if(step.is_goto())
    {
      if(step.ignore)
        step.cond_handle = true_exprt();
      else
      {
        log.conditional_output(
          log.debug(), [&step](messaget::mstreamt &mstream) {
            step.output(mstream);
            mstream << messaget::eom;
          });

        step.cond_handle = decision_procedure.handle(step.cond_expr);
        with_solver_hardness(
          decision_procedure, hardness_register_ssa(step_index, step));
      }
    }
    ++step_index;
  }
}

void symex_target_equationt::convert_constraints(
  decision_proceduret &decision_procedure)
{
  std::size_t step_index = 0;
  for(auto &step : SSA_steps)
  {
    if(step.is_constraint() && !step.ignore && !step.converted)
    {
      log.conditional_output(log.debug(), [&step](messaget::mstreamt &mstream) {
        step.output(mstream);
        mstream << messaget::eom;
      });

      decision_procedure.set_to_true(step.cond_expr);
      step.converted = true;

      with_solver_hardness(
        decision_procedure, hardness_register_ssa(step_index, step));
    }
    ++step_index;
  }
}

void symex_target_equationt::convert_assertions(
  decision_proceduret &decision_procedure,
  bool optimized_for_single_assertions,
  bool wcnfIsSet)
{
  // we find out if there is only _one_ assertion,
  // which allows for a simpler formula

  std::size_t number_of_assertions=count_assertions();

  if(number_of_assertions==0)
    return;

  if(number_of_assertions == 1 && optimized_for_single_assertions)
  {
    std::size_t step_index = 0;
    for(auto &step : SSA_steps)
    {
      // hide already converted assertions in the error trace
      if(step.is_assert() && step.converted)
        step.hidden = true;

      if(step.is_assert() && !step.ignore && !step.converted)
      {
        step.converted = true;
        if(wcnfIsSet) {
          // If WCNF (fault-localization) option is set, we have to insert a Healthy variable
          // also for Assertions, that were created by goto_check_c, so they get havoced together with the actual
          // assignment step of the source location:
          if(id2string(step.source.pc->source_location().get_property_class()).rfind("WCNF_GOTO_CHECK ") == 0) {
            // create healthy variable:
            std::string myFile = id2string(step.source.pc->source_location().get_file());
            std::string myLine = id2string(step.source.pc->source_location().get_line());
            const irep_idt identifier = "compHealthy::" + myFile + "::" + myLine;
            symbol_exprt healthySymbol(identifier,bool_typet());

            implies_exprt implicationWcnf(
              healthySymbol,
              step.cond_expr);
            step.cond_expr = implicationWcnf;
          }
          
          // for fault-localization the assertion needs to be positive:
          decision_procedure.set_to_true(step.cond_expr);
        }
        else {
          decision_procedure.set_to_false(step.cond_expr);
        }
        
        step.cond_handle = false_exprt();

        with_solver_hardness(
          decision_procedure, hardness_register_ssa(step_index, step));
        return; // prevent further assumptions!
      }
      else if(step.is_assume())
      {
        decision_procedure.set_to_true(step.cond_expr);

        with_solver_hardness(
          decision_procedure, hardness_register_ssa(step_index, step));
      }
      ++step_index;
    }

    UNREACHABLE; // unreachable
  }

  // We do (NOT a1) OR (NOT a2) ...
  // where the a's are the assertions
  or_exprt::operandst disjuncts;
  disjuncts.reserve(number_of_assertions);

  exprt assumption=true_exprt();

  std::vector<goto_programt::const_targett> involved_steps;

  std::size_t step_index = 0; // Needed for WCNF
  for(auto &step : SSA_steps)
  {
    // hide already converted assertions in the error trace
    if(step.is_assert() && step.converted)
      step.hidden = true;

    if(step.is_assert() && !step.ignore && !step.converted)
    {
      step.converted = true;

      log.conditional_output(log.debug(), [&step](messaget::mstreamt &mstream) {
        step.output(mstream);
        mstream << messaget::eom;
      });

      if(wcnfIsSet) {
        // If WCNF (fault-localization) option is set, we have to insert a Healthy variable
        // also for Assertions, that were created by goto_check_c, so they get havoced together with the actual
        // assignment step of the source location:
        if(id2string(step.source.pc->source_location().get_property_class()).rfind("WCNF_GOTO_CHECK ") == 0) {
          // create healthy variable:
          std::string myFile = id2string(step.source.pc->source_location().get_file());
          std::string myLine = id2string(step.source.pc->source_location().get_line());
          const irep_idt identifier = "compHealthy::" + myFile + "::" + myLine;
          symbol_exprt healthySymbol(identifier,bool_typet());

          implies_exprt implicationWcnf(
            healthySymbol,
            step.cond_expr);
          step.cond_expr = implicationWcnf;
        }

        // ASSUME is currently not implemented for WCNF, we just care for the cond_expr:
        decision_procedure.set_to_true(step.cond_expr);
        with_solver_hardness(
          decision_procedure, hardness_register_ssa(step_index, step));
        
        step_index++;
        continue;
      }

      implies_exprt implication(
        assumption,
        step.cond_expr);

      // do the conversion
      step.cond_handle = decision_procedure.handle(implication);

      with_solver_hardness(
        decision_procedure,
        [&involved_steps, &step](solver_hardnesst &hardness) {
          involved_steps.push_back(step.source.pc);
        });

      // store disjunct
      disjuncts.push_back(not_exprt(step.cond_handle));
    }
    else if(step.is_assume())
    {
      if(wcnfIsSet) {
        log.warning() << "ASSUME not implemented for WCNF option" << messaget::eom;
      }
      // the assumptions have been converted before
      // avoid deep nesting of ID_and expressions
      if(assumption.id()==ID_and)
        assumption.copy_to_operands(step.cond_handle);
      else
        assumption = and_exprt(assumption, step.cond_handle);

      with_solver_hardness(
        decision_procedure,
        [&involved_steps, &step](solver_hardnesst &hardness) {
          involved_steps.push_back(step.source.pc);
        });
    }
    step_index++; // WCNF
  }

  if(wcnfIsSet) {
    // In WCNF mode we already asserted all assertions directly
    return;
  }

  const auto assertion_disjunction = disjunction(disjuncts);
  // the below is 'true' if there are no assertions
  decision_procedure.set_to_true(assertion_disjunction);

  with_solver_hardness(
    decision_procedure,
    [&assertion_disjunction, &involved_steps](solver_hardnesst &hardness) {
      hardness.register_assertion_ssas(assertion_disjunction, involved_steps);
    });
}

void symex_target_equationt::convert_function_calls(
  decision_proceduret &decision_procedure)
{
  std::size_t step_index = 0;
  for(auto &step : SSA_steps)
  {
    if(!step.ignore)
    {
      and_exprt::operandst conjuncts;
      step.converted_function_arguments.reserve(step.ssa_function_arguments.size());

      for(const auto &arg : step.ssa_function_arguments)
      {
        if(arg.is_constant() ||
           arg.id()==ID_string_constant)
          step.converted_function_arguments.push_back(arg);
        else
        {
          const irep_idt identifier="symex::args::"+std::to_string(argument_count++);
          symbol_exprt symbol(identifier, arg.type());

          equal_exprt eq(arg, symbol);
          merge_irep(eq);

          decision_procedure.set_to(eq, true);
          conjuncts.push_back(eq);
          step.converted_function_arguments.push_back(symbol);
        }
      }
      with_solver_hardness(
        decision_procedure,
        [step_index, &conjuncts, &step](solver_hardnesst &hardness) {
          hardness.register_ssa(
            step_index, conjunction(conjuncts), step.source.pc);
        });
    }
    ++step_index;
  }
}

void symex_target_equationt::convert_io(decision_proceduret &decision_procedure)
{
  std::size_t step_index = 0;
  for(auto &step : SSA_steps)
  {
    if(!step.ignore)
    {
      and_exprt::operandst conjuncts;
      for(const auto &arg : step.io_args)
      {
        if(arg.is_constant() ||
           arg.id()==ID_string_constant)
          step.converted_io_args.push_back(arg);
        else
        {
          const irep_idt identifier =
            "symex::io::" + std::to_string(io_count++);
          symbol_exprt symbol(identifier, arg.type());

          equal_exprt eq(arg, symbol);
          merge_irep(eq);

          decision_procedure.set_to(eq, true);
          conjuncts.push_back(eq);
          step.converted_io_args.push_back(symbol);
        }
      }
      with_solver_hardness(
        decision_procedure,
        [step_index, &conjuncts, &step](solver_hardnesst &hardness) {
          hardness.register_ssa(
            step_index, conjunction(conjuncts), step.source.pc);
        });
    }
    ++step_index;
  }
}

/// Merging causes identical ireps to be shared.
/// This is only enabled if the definition SHARING is defined.
/// \param SSA_step The step you want to have shared values.
void symex_target_equationt::merge_ireps(SSA_stept &SSA_step)
{
  merge_irep(SSA_step.guard);

  merge_irep(SSA_step.ssa_lhs);
  merge_irep(SSA_step.ssa_full_lhs);
  merge_irep(SSA_step.original_full_lhs);
  merge_irep(SSA_step.ssa_rhs);

  merge_irep(SSA_step.cond_expr);

  for(auto &step : SSA_step.io_args)
    merge_irep(step);

  for(auto &arg : SSA_step.ssa_function_arguments)
    merge_irep(arg);

  // converted_io_args is merged in convert_io
}

void symex_target_equationt::output(std::ostream &out) const
{
  for(const auto &step : SSA_steps)
  {
    step.output(out);
    out << "--------------\n";
  }
}
