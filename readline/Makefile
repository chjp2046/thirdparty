SRC=../../

RL_LIBRARY_VERSION = 6.1
RL_LIBRARY_NAME = readline

PACKAGE_BUGREPORT = bug-readline@gnu.org
PACKAGE_VERSION = 6.1

# project.subdirs = . examples

project.defines := -DHAVE_CONFIG_H  -DRL_LIBRARY_VERSION=\"$(RL_LIBRARY_VERSION)\"
project.includes := .

# trun off all default warnings for this third party library
project.warning :=

# could add -Werror here
GCC_LINT_FLAGS = -ansi -Wall -Wshadow -Wpointer-arith -Wcast-qual \
		 -Wwrite-strings -Wstrict-prototypes \
		 -Wmissing-prototypes -Wno-implicit -pedantic

histoty_sources := history.c histexpand.c histfile.c histsearch.c shell.c mbutil.c
tilde_sources := tilde.c
all_sources := readline.c vi_mode.c funmap.c keymaps.c parens.c search.c \
	  rltty.c complete.c bind.c isearch.c display.c signals.c \
	  util.c kill.c undo.c macro.c input.c callback.c terminal.c \
	  text.c nls.c misc.c compat.c xmalloc.c $(histoty_sources) $(tilde_sources)

CREATED_MAKEFILES = Makefile doc/Makefile examples/Makefile shlib/Makefile
INSTALLED_HEADERS = readline.h chardefs.h keymaps.h history.h tilde.h \
		    rlstdc.h rlconf.h rltypedefs.h

tilde.c.extra_flags = -DREADLINE_LIBRARY

project.targets += libreadline.a
libreadline.a.type = library
libreadline.a.sources := $(all_sources)

project.targets += libreadline.so
libreadline.so.type = shared
libreadline.so.sources := $(all_sources)
libreadline.so.ldadd = -lncurses

project.targets += libhistory.a
libhistory.a.type = library
libhistory.a.sources := $(history_sources) xmalloc.c

project.targets += readline
readline.sources := examples/rl.c
readline.defines := -DREADLINE_LIBRARY
readline.ldadd = $(if $(SOSO_BUILD),@libroot@/common/readline/)libreadline.a -lncurses

include $(SRC)/common/builder/Generic.mak

