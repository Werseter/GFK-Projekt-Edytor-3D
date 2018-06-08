CXX=g++
CXX_FLAGS+=-O0 $(GXX_FLAGS)
CXX_FLAGS+=-g -ggdb -std=c++11
CXX_FLAGS+=`wx-config --cxxflags --libs std`
DEP_FLAGS=-MMD -MP

EXECNAME=Projekt45
BUILD_DIR=./build

SRC=$(wildcard *.cpp) $(wildcard Commands/*.cpp) $(wildcard Objects3D/*.cpp)
OBJ=$(SRC:%.cpp=$(BUILD_DIR)/%.o)
DEP=$(OBJ:%.o=%.d)

all: $(EXECNAME)

$(EXECNAME) : $(BUILD_DIR)/$(EXECNAME)

$(BUILD_DIR)/$(EXECNAME) : $(OBJ)
	mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) $^ -o $@

-include $(DEP)

$(BUILD_DIR)/%.o : %.cpp
	mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) $(DEP_FLAGS) -c $< -o $@

.PHONY: clean run

clean:
	rm -f $(BUILD_DIR)/$(EXECNAME) $(OBJ) $(DEP)

run: $(EXECNAME)
	$(BUILD_DIR)/$(EXECNAME)



