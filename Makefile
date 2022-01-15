#compilers for c and c++
#CC = gcc
CXX = g++

SRC_DIR  = src
OBJ_DIR = obj
BIN_DIR = bin
TARGET_EXEC = main

#FLAGS
# CXXFLAGS = -Wall -Werror -pedantic -g --std=c++2a
CXXFLAGS = -Wall -Werror -pedantic -O2 --std=c++2a


SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

DEPS := $(OBJS:.o=.d)

# INC_DIRS := $(shell find $(SRC_DIR) -type d)
# INC_FLAGS := $(addprefix -I,$(INC_DIRS))

#linker flags
LDFLAGS = -pthread

#preprocesor flags
CPPFLAGS = -Iinclude -MP -MMD

.PHONY: clean print

$(BIN_DIR)/$(TARGET_EXEC): $(OBJS) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@ 

# Build step for C source
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<  


$(BIN_DIR):
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@

run: $(BIN_DIR)/$(TARGET_EXEC) 
	@$(BIN_DIR)/$(TARGET_EXEC)

print:
	echo $(OBJS)
	echo $(SRCS)

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(DEPS)