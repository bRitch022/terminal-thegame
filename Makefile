# cli_game Makefile

# Version Details
APP_MAJ		:=	$(shell grep MAJOR_RELEASE ./src/version.h | tr -d '"' | awk '{print $$3'} )
APP_MIN		:=	$(shell grep MINOR_RELEASE ./src/version.h | tr -d '"' | awk '{print $$3'} )
PATCH		:=	$(shell grep PATCH ./src/version.h | tr -d '"' | awk '{print $$3'} )

# Executable filename details
EXEC_BASE 	= 	cli_game
EXEC		= 	$(BIN_DIR)$(EXEC_BASE)-$(APP_MAJ).$(APP_MIN).$(PATCH)$(DEBUG_NAME)
EXEC_MD5	= 	$(addsuffix .md5, $(EXEC))

# Directories
GAME_DIR 		= ./
SRC_DIR			= $(GAME_DIR)src/
JSON_DIR		= $(SRC_DIR)json/include/
TEST_DIR		= $(GAME_DIR)test/
BUILD_DIR 		= $(GAME_DIR)build/
OBJ_DIR 		= $(BUILD_DIR)obj/
BIN_DIR			= $(BUILD_DIR)bin/
CLI_DIR 		= $(SRC_DIR)cli/include/

# Sources
CPPSOURCES += $(GAME_DIR)clitest.cpp

# Object files
COBJ = $(patsubst %.cpp, $(OBJ_DIR)%.o, $(notdir $(CPPSOURCES)))

# Compiler and flags
CXX = /usr/bin/g++
CFLAGS += -I$(CLI_DIR)
CFLAGS += -I$(JSON_DIR)
CFLAGS += -std=c++17

ifeq ($(DEBUG), 1)
	CFLAGS += -g
	DEBUG_NAME = .dbg
endif

# Virtual paths for building .cpp->.o files
vpath %.cpp $(TEST_DIR)
vpath %.cpp $(SRC_DIR)

# Make Targets
.PHONY: all test clean clobber

$(EXEC_MD5): $(EXEC)

$(EXEC): $(OBJ_DIR) $(COBJ) $(BIN_DIR) 
	$(CXX) $(CFLAGS) $(LDFLAGS) $(COBJ) -o $@
	md5sum $(EXEC) > $(addsuffix .md5, $(EXEC))

$(BIN_DIR):
	@mkdir -p $@

$(OBJ_DIR): 
	@mkdir -p $@

$(OBJ_DIR)%.o: %.cpp
	$(CXX) $(CFLAGS) -MMD -c $< -o $@

all:
	@$(MAKE) DEBUG=0
	@$(MAKE) DEBUG=1

clean:
	rm -rf $(BUILD_DIR)
