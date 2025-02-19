SRC = allocate_objects.cpp \
      anonymous_member.cpp \
      ansi_c_convert_type.cpp \
      ansi_c_declaration.cpp \
      ansi_c_entry_point.cpp \
      ansi_c_internal_additions.cpp \
      ansi_c_language.cpp \
      ansi_c_lex.yy.cpp \
      ansi_c_parse_tree.cpp \
      ansi_c_parser.cpp \
      ansi_c_scope.cpp \
      ansi_c_typecheck.cpp \
      ansi_c_y.tab.cpp \
      builtin_factory.cpp \
      printf_formatter.cpp \
      c_expr.cpp \
      c_misc.cpp \
      c_nondet_symbol_factory.cpp \
      c_object_factory_parameters.cpp \
      c_preprocess.cpp \
      c_qualifiers.cpp \
      c_storage_spec.cpp \
      c_typecast.cpp \
      c_typecheck_base.cpp \
      c_typecheck_code.cpp \
      c_typecheck_expr.cpp \
      c_typecheck_gcc_polymorphic_builtins.cpp \
      c_typecheck_shadow_memory_builtin.cpp \
      c_typecheck_initializer.cpp \
      c_typecheck_type.cpp \
      c_typecheck_typecast.cpp \
      cprover_library.cpp \
      designator.cpp \
      expr2c.cpp \
      gcc_types.cpp \
      gcc_version.cpp \
      goto-conversion/builtin_functions.cpp \
      goto-conversion/goto_asm.cpp \
      goto-conversion/destructor.cpp \
      goto-conversion/format_strings.cpp \
      goto-conversion/goto_convert.cpp \
      goto-conversion/goto_check_c.cpp \
      goto-conversion/goto_convert_exceptions.cpp \
      goto-conversion/goto_clean_expr.cpp \
      goto-conversion/goto_convert_functions.cpp \
      goto-conversion/goto_convert_function_call.cpp \
      goto-conversion/goto_convert_side_effect.cpp \
      goto-conversion/link_to_library.cpp \
      goto-conversion/scope_tree.cpp \
      goto-conversion/string_instrumentation.cpp \
      literals/convert_character_literal.cpp \
      literals/convert_float_literal.cpp \
      literals/convert_integer_literal.cpp \
      literals/convert_string_literal.cpp \
      literals/parse_float.cpp \
      literals/unescape_string.cpp \
      padding.cpp \
      preprocessor_line.cpp \
      type2name.cpp \
      # Empty last line

INCLUDES= -I ..

include ../config.inc
include ../common

BUILTIN_FILES = \
  cprover_builtin_headers.inc \
  compiler_headers/arm_builtin_headers.inc \
  compiler_headers/clang_builtin_headers.inc \
  compiler_headers/cw_builtin_headers.inc \
  compiler_headers/gcc_builtin_headers_alpha.inc \
  compiler_headers/gcc_builtin_headers_arm.inc \
  compiler_headers/gcc_builtin_headers_generic.inc \
  compiler_headers/gcc_builtin_headers_ia32-2.inc \
  compiler_headers/gcc_builtin_headers_ia32-3.inc \
  compiler_headers/gcc_builtin_headers_ia32-4.inc \
  compiler_headers/gcc_builtin_headers_ia32-5.inc \
  compiler_headers/gcc_builtin_headers_ia32-6.inc \
  compiler_headers/gcc_builtin_headers_ia32-7.inc \
  compiler_headers/gcc_builtin_headers_ia32-8.inc \
  compiler_headers/gcc_builtin_headers_ia32-9.inc \
  compiler_headers/gcc_builtin_headers_ia32.inc \
  compiler_headers/gcc_builtin_headers_math.inc \
  compiler_headers/gcc_builtin_headers_mem_string.inc \
  compiler_headers/gcc_builtin_headers_mips.inc \
  compiler_headers/gcc_builtin_headers_omp.inc \
  compiler_headers/gcc_builtin_headers_power.inc \
  compiler_headers/gcc_builtin_headers_tm.inc \
  compiler_headers/gcc_builtin_headers_types.inc \
  compiler_headers/gcc_builtin_headers_ubsan.inc \
  compiler_headers/windows_builtin_headers.inc

CLEANFILES = ansi-c$(LIBEXT) \
  ansi_c_y.tab.h ansi_c_y.tab.cpp ansi_c_lex.yy.cpp ansi_c_y.tab.cpp.output \
  ansi_c_y.output \
  library/converter$(EXEEXT) cprover_library.inc \
  file_converter$(EXEEXT) library_check \
  $(BUILTIN_FILES)

all: ansi-c$(LIBEXT)

###############################################################################

ansi_c_y.tab.cpp: parser.y
	$(YACC) $(YFLAGS) -pyyansi_c parser.y --defines=ansi_c_y.tab.h -o $@

ansi_c_y.tab.h: ansi_c_y.tab.cpp

ansi_c_lex.yy.cpp: scanner.l
	$(LEX) -Pyyansi_c -o$@ scanner.l

# extra dependencies
ansi_c_y.tab$(OBJEXT): ansi_c_y.tab.cpp ansi_c_y.tab.h
ansi_c_lex.yy$(OBJEXT): ansi_c_y.tab.cpp ansi_c_lex.yy.cpp ansi_c_y.tab.h
cprover_library$(OBJEXT): cprover_library.inc

###############################################################################

library/converter$(EXEEXT): library/converter.cpp
	$(LINKNATIVE)

file_converter$(EXEEXT): file_converter.cpp
	$(LINKNATIVE)

ifeq ($(BUILD_ENV_),MinGW)
  platform_unavail = library/java.io.c library/err.c library/threads.c
else ifeq ($(BUILD_ENV_),FreeBSD)
  platform_unavail = library/fenv.c library/java.io.c library/threads.c
else
  platform_unavail = library/java.io.c library/threads.c
endif
library_check: library/*.c
	./library_check.sh "$(CC)" $(filter-out $(platform_unavail), $^)
	touch $@

cprover_library.inc: library/converter$(EXEEXT) library/*.c
	library/converter$(EXEEXT) library/*.c > $@

%.inc: %.h file_converter$(EXEEXT)
	./file_converter$(EXEEXT) $< > $@

ansi_c_internal_additions$(OBJEXT): $(BUILTIN_FILES)

generated_files: \
        ansi_c_y.tab.cpp ansi_c_lex.yy.cpp ansi_c_y.tab.h \
        cprover_library.inc \
        $(BUILTIN_FILES)

###############################################################################

ansi-c$(LIBEXT): $(OBJ)
	$(LINKLIB)
