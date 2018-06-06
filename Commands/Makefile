CXX=g++
CXXFLAGS+=-O0 $(GXX_FLAGS)
CXXFLAGS+=-g -ggdb -std=c++11
CXXFLAGS+=`wx-config --cxxflags --libs std`

DEP_FLAGS=-MMD

DEP_FLAGS+=-MP

CXXFLAGS+=$(DEP_FLAGS)

SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
DEP=$(SRC:.cpp=.d)

all: $(OBJ)
	$(CXX) -c $?

.PHONY: clean run

clean:
	rm -f $(OBJ) $(DEP)

-include $(DEP)


