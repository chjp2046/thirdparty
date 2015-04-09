RL_LIBRARY_VERSION = 6.1
READLINE_LIB = ../libreadline.a
HISTORY_LIB = ../libhistory.a
TERMCAP_LIB = -lncurses

project.defines := \
	-DREADLINE_LIBRARY \
	-DRL_LIBRARY_VERSION='"$(RL_LIBRARY_VERSION)"' \
	-DHAVE_CONFIG_H

project.includes := ..

# trun off all default warnings for this third party library
project.warning :=

project.targets += rl
rl.sources := rl.c
rl.ldadd := $(READLINE_LIB) $(TERMCAP_LIB)

project.targets += rlcat
rlcat.sources := rlcat.c
rlcat.ldadd := $(READLINE_LIB) $(TERMCAP_LIB)

project.targets += rlevent
rlevent.sources := rlevent.c
rlevent.ldadd := $(READLINE_LIB) $(TERMCAP_LIB)

project.targets += fileman
fileman.sources := fileman.c
fileman.ldadd := $(READLINE_LIB) $(TERMCAP_LIB)

project.targets += rltest
rltest.sources := rltest.c
rltest.ldadd := $(READLINE_LIB) $(TERMCAP_LIB)

project.targets += rlptytest
rlptytest.sources := rlptytest.c
rlptytest.ldadd := $(READLINE_LIB) $(TERMCAP_LIB) -lutil

project.targets += rlversion
rlversion.sources := rlversion.c
rlversion.ldadd := $(READLINE_LIB) $(TERMCAP_LIB)

project.targets += histexamp
histexamp.sources := histexamp.c
histexamp.ldadd := $(READLINE_LIB) $(HISTORY_LIB) $(TERMCAP_LIB)

include ../../builder/Generic.mak

