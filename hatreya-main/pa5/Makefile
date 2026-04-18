#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 5
# Hansa Atreya(hatreya)#
# make                         makes WordFrequency
# make DictionaryClient        makes DictionaryClient
# make clean                   removes all binaries
# make checkWordFrequency      runs WordFrequency under valgrind on INFILE to OUTFILE
# make checkDictionaryClient   runs DictionaryClient under valgrind
#
#------------------------------------------------------------------------------


MAIN           = WordFrequency
MAINOBJ        = $(MAIN).o
MAINSRC        = $(MAIN).c
TEST           = DictionaryClient
TESTOBJ        = $(TEST).o
TESTSRC        = $(TEST).c
ADT            = Dictionary
ADTOBJ         = $(ADT).o
ADTSRC         = $(ADT).c
ADT_H          = $(ADT).h
COMPILE        = gcc -std=c17 -Wall -c
LINK           = gcc -std=c17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full
INFILE         = in5
OUTFILE        = myout5


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
	$(MEMCHECK) $(MAIN) $(INFILE) $(OUTFILE)

check$(TEST) : $(TEST)
	$(MEMCHECK) $(TEST)
