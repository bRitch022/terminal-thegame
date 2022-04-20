# cli_game Makefile

# Version Details
APP_MAJ		:=	$(shell grep MAJOR_RELEASE ./gamesrc/version.h | tr -d '"' | awk '{print $$3'} )
APP_MIN		:=	$(shell grep MINOR_RELEASE ./gamesrc/version.h | tr -d '"' | awk '{print $$3'} )
PATCH		:=	$(shell grep PATCH ./gamesrc/version.h | tr -d '"' | awk '{print $$3'} )

# Executable filename details
EXEC_BASE 	= 	cli_game
EXEC		= 	$(BIN_DIR)$(EXEC_BASE)-$(APP_MAJ).$(APP_MIN).$(PATCH)$(DEBUG_NAME)
EXEC_MD5	= 	$(addsuffix .md5, $(EXEC))

# Directories
BUILD_DIR		= ./
SRC_DIR			= $(BUILD_DIR)gamesrc/
JSON_DIR		= $(BUILD_DIR)json/include/
TEST_DIR		= $(BUILD_DIR)test/
OBJ_DIR 		= $(BUILD_DIR)obj/
BIN_DIR			= $(BUILD_DIR)bin/
CLI_DIR 		= $(BUILD_DIR)cli/include/

# Sources
CPPSOURCES += $(TEST_DIR)clitest.cpp
# CPPSOURCES += $(GAME_DIR)busyboxtest.cpp
# CPPSOURCES += $(GAMEPLAY_DIR)stage.cpp
# CPPSOURCES += $(GAMEPLAY_DIR)level.cpp

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
	rm -rf $(OBJ_DIR) $(BIN_DIR)
