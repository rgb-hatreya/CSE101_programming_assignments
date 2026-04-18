#------------------------------------------------------------------------------
# Makefile for CSE 101 pa2
# Hansa Atreya (hatreya)
#
# make                builds FindPath
# make GraphTest      builds GraphTest
# make clean          removes all binaries and object files
# make checkFindPath  runs FindPath under valgrind
# make checkGraphTest runs GraphTest under valgrind
#------------------------------------------------------------------------------

MAIN        = FindPath
MAINOBJ     = FindPath.o
MAINSRC     = FindPath.c

TEST        = GraphTest
TESTOBJ     = GraphTest.o
TESTSRC     = GraphTest.c

ADT1        = Graph
ADT1OBJ     = Graph.o
ADT1SRC     = Graph.c
ADT1H       = Graph.h

ADT2        = List
ADT2OBJ     = List.o
ADT2SRC     = List.c
ADT2H       = List.h

CC          = gcc
CFLAGS      = -std=c17 -Wall -Wextra -g
COMPILE     = $(CC) $(CFLAGS) -c
LINK        = $(CC) $(CFLAGS) -o
REMOVE      = rm -f

MEMCHECK    = valgrind --leak-check=full --show-leak-kinds=all

# Default target
all: $(MAIN)

# Build FindPath
$(MAIN): $(MAINOBJ) $(ADT1OBJ) $(ADT2OBJ)
	$(LINK) $(MAIN) $(MAINOBJ) $(ADT1OBJ) $(ADT2OBJ)

# Build GraphTest
$(TEST): $(TESTOBJ) $(ADT1OBJ) $(ADT2OBJ)
	$(LINK) $(TEST) $(TESTOBJ) $(ADT1OBJ) $(ADT2OBJ)

# Compile object files
$(MAINOBJ): $(MAINSRC) $(ADT1H) $(ADT2H)
	$(COMPILE) $(MAINSRC)

$(TESTOBJ): $(TESTSRC) $(ADT1H) $(ADT2H)
	$(COMPILE) $(TESTSRC)

$(ADT1OBJ): $(ADT1SRC) $(ADT1H) $(ADT2H)
	$(COMPILE) $(ADT1SRC)

$(ADT2OBJ): $(ADT2SRC) $(ADT2H)
	$(COMPILE) $(ADT2SRC)

# Clean
clean:
	$(REMOVE) $(MAIN) $(TEST) *.o

# Valgrind targets
checkFindPath: $(MAIN)
	$(MEMCHECK) ./$(MAIN) in out

checkGraphTest: $(TEST)
	$(MEMCHECK) ./$(TEST)

