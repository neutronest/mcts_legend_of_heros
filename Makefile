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
	legend_mcts.cc \
	main.cc


CCFLAGS = -g -Wall -std=c++11 -I $(HEADER)

OBJS = player.o \
	skill.o \
	legend_state.o \
	legend_mcts.o \
	main.o

$(PROG) : $(OBJS)
	$(CLANG) $(OBJS) -o $(PROG) 

main.o :
	$(CLANG) $(CCFLAGS) -c main.cc

player.o :
	$(CLANG) $(CCFLAGS) -c player.cc

skill.o :
	$(CLANG) $(CCFLAGS) -c skill.cc

legend_state.o :
	$(CLANG) $(CCFLAGS) -c legend_state.cc

legend_mcts.o :
	$(CLANG) $(CCFLAGS) -c legend_mcts.cc

clean:
	rm core $(PROG) $(OBJS)