#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 6
#
# Hansa Atreya (hatreya)
# 
# make                     makes Shuffle
# make ListTest          makes ListTest
# make clean               removes all binaries
# make checkShuffle        runs Shuffle under valgrind with arg 100, output to myout100
# make checkListTest     runs ListClient under valgrind
#
#------------------------------------------------------------------------------


MAIN           = Shuffle
MAINOBJ        = $(MAIN).o
MAINSRC        = $(MAIN).cpp
TEST           = ListTest
TESTOBJ        = $(TEST).o
TESTSRC        = $(TEST).cpp
ADT            = List
ADTOBJ         = $(ADT).o
ADTSRC         = $(ADT).cpp
ADT_H          = $(ADT).h
COMPILE        = g++ -std=c++17 -Wall -c
LINK           = g++ -std=c++17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full
OUTFILE        = myout100


$(MAIN) : $(MAINOBJ) $(ADTOBJ)
	$(LINK) $(MAIN) $(MAINOBJ) $(ADTOBJ)

$(MAINOBJ) : $(ADT_H) $(MAINSRC)
	$(COMPILE) $(MAINSRC)

$(TEST) : $(TESTOBJ) $(ADTOBJ)
	$(LINK) $(TEST) $(TESTOBJ) $(ADTOBJ)

$(TESTOBJ) : $(ADT_H) $(TESTSRC)
	$(COMPILE) $(TESTSRC)

$(ADTOBJ) : $(ADT_H) $(ADTSRC)
	$(COMPILE) $(ADTSRC)

clean :
	$(REMOVE) $(MAIN) $(MAINOBJ) $(TEST) $(TESTOBJ) $(ADTOBJ)

check$(MAIN) : $(MAIN)
	$(MEMCHECK) $(MAIN) 100 > $(OUTFILE)

check$(TEST) : $(TEST)
	$(MEMCHECK) $(TEST)

