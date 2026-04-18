#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 
# Hansa Atreya (hatreya)
#------------------------------------------------------------------------------

MAIN           = Words
MAINOBJ        = $(MAIN).o
MAINSRC        = $(MAIN).c

TEST           = ListTest
TESTOBJ        = $(TEST).o
TESTSRC        = $(TEST).c

ADT            = List
ADTOBJ         = $(ADT).o
ADTSRC         = $(ADT).c
ADT_H          = $(ADT).h

COMPILE        = gcc -std=c17 -Wall -Wextra -g -c
LINK           = gcc -std=c17 -Wall -Wextra -g -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full --show-leak-kinds=all

INFILE         = in4
OUTFILE        = myout4

all: $(MAIN) $(TEST)

$(MAIN) : $(MAINOBJ) $(ADTOBJ)
	$(LINK) $(MAIN) $(MAINOBJ) $(ADTOBJ)

$(TEST) : $(TESTOBJ) $(ADTOBJ)
	$(LINK) $(TEST) $(TESTOBJ) $(ADTOBJ)

$(MAINOBJ) : $(ADT_H) $(MAINSRC)
	$(COMPILE) $(MAINSRC)

$(TESTOBJ) : $(ADT_H) $(TESTSRC)
	$(COMPILE) $(TESTSRC)

$(ADTOBJ) : $(ADT_H) $(ADTSRC)
	$(COMPILE) $(ADTSRC)

clean :
	$(REMOVE) $(MAIN) $(MAINOBJ) $(TEST) $(TESTOBJ) $(ADTOBJ)

check$(MAIN) : $(MAIN)
	$(MEMCHECK) ./$(MAIN) $(INFILE) $(OUTFILE)

check$(TEST) : $(TEST)
	$(MEMCHECK) ./$(TEST)

