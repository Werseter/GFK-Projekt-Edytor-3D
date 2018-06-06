CXX=g++
CXXFLAGS+=--O0 $(GXX_FLAGS)
CXXFLAGS+=-g -ggdb -std=c++11
CXXFLAGS+=`wx-config --cxxflags --libs std`

DEP_FLAGS=-MMD

EXECNAME=Projekt21

DEP_FLAGS+=-MP

CXXFLAGS+=$(DEP_FLAGS)

SRC=$(wildcard *.cpp) $(wildcard Commands/*.cpp) $(wildcard Objects3D/*.cpp)
OBJ=$(SRC:.cpp=.o)
DEP=$(SRC:.cpp=.d)

all: $(EXECNAME)

$(EXECNAME): $(OBJ)
	+$(MAKE) -C Objects3D
	+$(MAKE) -C Commands
	$(CXX) $(CXXFLAGS) $(LFLAGS) $? -o $@

.PHONY: clean run

clean:
	+$(MAKE) -C Objects3D clean
	+$(MAKE) -C Commands clean
	rm -f $(EXECNAME) $(OBJ) $(DEP)

run: $(EXECNAME)
	./$(EXECNAME)

-include $(DEP)


