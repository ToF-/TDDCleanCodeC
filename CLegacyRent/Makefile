rent : rent.c
	cc rent.c -o rent

test : rent tests.txt
	sed -n -e 's/\(< \)\(.*\)/\2/pw test.dat'     tests.txt >/dev/null
	sed -n -e 's/\(> \)\(.*\)/\2/pw expected.dat' tests.txt >/dev/null
	./rent <test.dat >result.dat
	diff expected.dat result.dat

large: rent
	./rent <largedata.dat >result.dat
	diff largeresult.dat result.dat

# Points to the root of CppUTest, relative to where this file is.
# Remember to tweak this if you move this file.
CPPUTEST_HOME = ~/dev/cpputest

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
	rm rent; rm unittests; rm -R unittests.dSYM; rm temp*
	
