DIRS = analyses \
       ansi-c \
       assembler \
       big-int \
       cbmc \
       cpp \
       cprover \
       crangler \
       goto-analyzer \
       goto-bmc \
       goto-cc \
       goto-checker \
       goto-diff \
       goto-inspect \
       goto-instrument \
       goto-harness \
       goto-programs \
       goto-symex \
       goto-synthesizer \
       json \
       json-symtab-language \
       langapi \
       libcprover-cpp \
       linking \
       memory-analyzer \
       pointer-analysis \
       solvers \
       statement-list \
       symtab2gb \
       util \
       xmllang \
       # Empty last line

all: cbmc.dir \
     cprover.dir \
     crangler.dir \
     goto-analyzer.dir \
     goto-bmc.dir \
     goto-cc.dir \
     goto-diff.dir \
     goto-instrument.dir \
     goto-inspect.dir \
     goto-harness.dir \
     goto-synthesizer.dir \
     symtab2gb.dir \
     # Empty last line

ifndef WITH_MEMORY_ANALYZER
  ifeq ($(OS),Windows_NT)
    WITH_MEMORY_ANALYZER = 0
  else
    detected_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
    detected_ARCH := $(shell sh -c 'uname -m 2>/dev/null || echo Unknown')
    ifeq ($(filter-out Linux_x86_64 Linux_i386,$(detected_OS)_$(detected_ARCH)),)
      WITH_MEMORY_ANALYZER = 1
    else
      WITH_MEMORY_ANALYZER = 0
    endif
  endif
endif

ifeq ($(WITH_MEMORY_ANALYZER),1)
  all: memory-analyzer.dir
endif

###############################################################################

util.dir: big-int.dir

# everything but big-int depends on util
$(patsubst %, %.dir, $(filter-out big-int util, $(DIRS))): util.dir

.PHONY: languages
.PHONY: clean

ansi-c.dir: analyses.dir

cpp.dir: ansi-c.dir linking.dir

crangler.dir: util.dir json.dir

languages: util.dir langapi.dir \
           cpp.dir ansi-c.dir xmllang.dir assembler.dir \
           json.dir json-symtab-language.dir statement-list.dir

solvers.dir: util.dir

goto-harness.dir: util.dir goto-programs.dir langapi.dir linking.dir \
                  json.dir json-symtab-language.dir \
                  goto-instrument.dir

goto-instrument.dir: languages goto-programs.dir pointer-analysis.dir \
                     goto-symex.dir linking.dir analyses.dir solvers.dir

goto-inspect.dir: util.dir goto-programs.dir languages linking.dir

goto-checker.dir: solvers.dir goto-symex.dir goto-programs.dir

cbmc.dir: languages solvers.dir goto-symex.dir analyses.dir \
          pointer-analysis.dir goto-programs.dir linking.dir \
          goto-instrument.dir goto-checker.dir

cprover.dir: ansi-c.dir langapi.dir solvers.dir goto-programs.dir \
             linking.dir analyses.dir

goto-analyzer.dir: languages analyses.dir goto-programs.dir linking.dir \
                   goto-instrument.dir goto-checker.dir

goto-diff.dir: languages goto-programs.dir pointer-analysis.dir \
               linking.dir analyses.dir goto-instrument.dir \
               solvers.dir goto-symex.dir

goto-cc.dir: languages goto-programs.dir linking.dir

memory-analyzer.dir: util.dir goto-programs.dir langapi.dir linking.dir \
	                   ansi-c.dir

symtab2gb.dir: util.dir goto-programs.dir langapi.dir linking.dir \
               json.dir json-symtab-language.dir ansi-c.dir

goto-synthesizer.dir: languages util.dir goto-programs.dir langapi.dir \
                    json.dir goto-checker.dir \
                    goto-instrument.dir

goto-bmc.dir: libcprover-cpp.dir

libcprover-cpp.dir: cbmc.dir

# building for a particular directory

$(patsubst %, %.dir, $(DIRS)):
	## Entering $(basename $@)
	$(MAKE) $(MAKEARGS) -C $(basename $@)

# generate source files

$(patsubst %, %_generated_files, $(DIRS)):
	$(MAKE) $(MAKEARGS) -C $(patsubst %_generated_files, %, $@) generated_files

generated_files: $(patsubst %, %_generated_files, $(DIRS))

# cleaning

clean: $(patsubst %, %_clean, $(DIRS))

$(patsubst %, %_clean, $(DIRS)):
	$(MAKE) $(MAKEARGS) -C $(patsubst %_clean, %, $@) clean ; \

# minisat2 and glucose download, for your convenience

DOWNLOADER = curl -L --remote-name
TAR = tar

minisat2-download:
	@echo "Downloading Minisat 2.2.1"
	@for i in $$(seq 1 3) ; do \
	  $(DOWNLOADER) \
	    http://ftp.debian.org/debian/pool/main/m/minisat2/minisat2_2.2.1.orig.tar.gz && \
	    exit 0 ; \
		$(RM) minisat2_2.2.1.orig.tar.gz ; \
	  if [ $$i -lt 3 ] ; then echo "Re-trying in 10 seconds" 1>&2 ; sleep 10 ; fi ; \
	done ; exit 1
	@$(TAR) xfz minisat2_2.2.1.orig.tar.gz
	@rm -Rf ../minisat-2.2.1
	@mv minisat2-2.2.1 ../minisat-2.2.1
	@(cd ../minisat-2.2.1; patch -p1 < ../scripts/minisat-2.2.1-patch)
	@rm minisat2_2.2.1.orig.tar.gz

cudd-download:
	@echo "Downloading Cudd 3.0.0"
	@$(DOWNLOADER) https://sourceforge.net/projects/cudd-mirror/files/cudd-3.0.0.tar.gz/download cudd-3.0.0.tar.gz
	@$(TAR) xfz cudd-3.0.0.tar.gz
	@$(RM) -r ../cudd-3.0.0
	@mv cudd-3.0.0 ../
	@$(RM) cudd-3.0.0.tar.gz
	@echo "Compiling Cudd 3.0.0"
	@(cd ../cudd-3.0.0; ./configure; $(MAKE))

glucose_rev = 0bb2afd3b9baace6981cbb8b4a1c7683c44968b7
glucose-download:
	@echo "Downloading glucose-syrup"
	@$(DOWNLOADER) https://github.com/BrunoDutertre/glucose-syrup/archive/$(glucose_rev).tar.gz
	@$(TAR) xfz $(glucose_rev).tar.gz
	@rm -Rf ../glucose-syrup
	@mv glucose-syrup-$(glucose_rev) ../glucose-syrup
	@(cd ../glucose-syrup; patch -p1 < ../scripts/glucose-syrup-patch)
	@$(RM) $(glucose_rev).tar.gz

cadical_release = rel-2.0.0
cadical-download:
	@echo "Downloading CaDiCaL $(cadical_release)"
	@$(DOWNLOADER) https://github.com/arminbiere/cadical/archive/$(cadical_release).tar.gz
	@$(TAR) xfz $(cadical_release).tar.gz
	@rm -Rf ../cadical
	@mv cadical-$(cadical_release) ../cadical
	@(cd ../cadical; patch -p1 < ../scripts/cadical-2.0.0-patch)
	@(cd ../cadical && ./configure CXX="$(CXX)")
	# Need to rename VERSION so that it isn't picked up by `#include<version>` on
	# macOS which is case insensitive
	@(cd ../cadical && mv VERSION VERSION.txt)
	@$(RM) $(cadical_release).tar.gz

doc :
	doxygen

install: all
	for b in \
		cbmc crangler \
		goto-analyzer goto-cc goto-diff goto-instrument goto-inspect goto-harness \
    goto-synthesizer symtab2gb ; do \
		  cp $$b/$$b $(PREFIX)/bin/ ; \
			cp ../doc/man/$$b.1 $(PREFIX)/doc/man/man1/ ; \
	done
	ln -sf $(PREFIX)/bin/goto-cc $(PREFIX)/bin/goto-gcc
	ln -sf $(PREFIX)/bin/goto-cc $(PREFIX)/bin/goto-ld
	cp ../scripts/ls_parse.py $(PREFIX)/bin/

.PHONY: minisat2-download cudd-download glucose-download cadical-download install
