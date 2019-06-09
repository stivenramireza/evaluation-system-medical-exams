SRCDIR   := src
BUILDDIR := build
INCLUDE  := include
BINDIR   := bin
LDFLAGS  := -lrt -pthread -std=c++11
CXXFLAGS := -pedantic-errors -Wall -Wextra -std=c++11 -lrt -pthread -I include

all: dirs $(BINDIR)/evaluator
VPATH := src include build

$(BINDIR)/evaluator: evaluator.o init_command.o reg_command.o
	$(CXX) -o $@ $^ $(LDFLAGS)

$(BUILDDIR)/evaluator.o: evaluator.cpp share_memory.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<
	
$(BUILDDIR)/init_command.o: init_command.cpp init_command.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILDDIR)/reg_command.o: reg_command.cpp reg_command.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

.PHONY: clean

clean:
	rm -f  $(SRCDIR)/*.cpp~ $(INCLUDE)/*.h~ makefile~
	rm -f -R $(BUILDDIR)
	rm -f -R $(BINDIR)

.PHONY: dirs
dirs:
	@test -d build || mkdir build
	@test -d bin || mkdir bin