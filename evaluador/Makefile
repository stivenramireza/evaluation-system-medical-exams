SRCDIR   := src
BUILDDIR := build
INCLUDE  := include
BINDIR   := bin
LDFLAGS  := -pthread
CXXFLAGS := -pedantic-errors -Wall -Wextra -std=c++11 -I include

all: dirs $(BINDIR)/evaluator
VPATH := src include build

$(BINDIR)/evaluator: evaluator.o 
	$(CXX) -o $@ $(LDFLAGS) $^

$(BUILDDIR)/evaluator.o: evaluator.cpp 
	$(CXX) $(CXXFLAGS) -o $@ -c $<
	
.PHONY: clean

clean:
	rm -f $(SRCDIR)/*.cpp~ $(INCLUDE)/*.h~ makefile~
	rm -f -R $(BUILDDIR)
	rm -f -R $(BINDIR)

.PHONY: dirs
dirs:
	@test -d build || mkdir build
	@test -d bin || mkdir bin