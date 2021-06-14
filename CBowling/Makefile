# CppUtest must be installed for this project to run
bowling : bowling.c
	cc bowling.c -o bowling

# Points to the root of CppUTest, relative to where this file is.
CPPUTEST_HOME = ../cpputest

# Where to find user code.
USER_DIR = .

# Flags passed to the preprocessor.
CPPFLAGS += -I$(CPPUTEST_HOME)/include

# Flags passed to the C++ compiler.
CFLAGS += -g -Wall -Wextra

LD_LIBRARIES = -L$(CPPUTEST_HOME)/lib -lCppUTest
unit : tests.c
	g++ $(CPPFLAGS) $(CFLAGS) -o unittests $(USER_DIR)/tests.c $(LD_LIBRARIES)
	./unittests

clean : 
	rm bowling; rm -R unittests.dSYM
	
