#specify the compiler
CLANG = clang++
PROG = legend

HEADER = \
	state.h \
	player.h \
	skill.h \
	legend_state.h \
	legend_mcts.h

MAIN = player.cc \
	skill.cc \
	legend_state.cc \
	legend_mcts.cc


CCFLAGS = -g -Wall -std=c++11 -I $(HEADER)

OBJS = player.o \
	skill.o \
	legend_state.o

$(PROG) : $(OBJS)
	$(CLANG) $(CCFLAGS) -o $(PROG) $(OBJS)

player.o :
	$(CLANG) $(CCFLAGS) -c player.cc

skill.o :
	$(CLANG) $(CCFLAGS) -c skill.cc

legend_state.o :
	$(CLANG) $(CCFLAGS) -c legend_state.cc

legend_mcts.o :
	$(CLANG) $(CCFLAGS) -c legend_mcts.o

