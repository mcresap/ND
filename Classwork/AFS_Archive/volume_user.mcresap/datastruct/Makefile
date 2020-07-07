CXX=		g++
CXXFLAGS=	-g -Wall -std=gnu++11
SHELL=		bash
MEASURE=	../common/measure

all:		new

new:	new.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f new

test:		test-output test-memory test-time

test-output:	new
	@echo Testing output...
	@diff --suppress-common-lines -y <(./new < input) output

test-memory:	new
	@echo Testing memory...
	@[ `valgrind --leak-check=full ./new < input 2>&1 | grep ERROR | awk '{print $$4}'` = 0 ]

test-time:	$(MEASURE) new
	@echo Testing time...
	@$(MEASURE) ./new < input | tail -n 1 | awk '{ if ($$1 > 1.0) { print "Time limit exceeded"; exit 1} }'
