# Terminal.mk

# Version Details
APP_MAJ		:=	$(shell grep MAJOR_RELEASE ./src/version.h | tr -d '"' | awk '{print $$3'} )
APP_MIN		:=	$(shell grep MINOR_RELEASE ./src/version.h | tr -d '"' | awk '{print $$3'} )
PATCH		:=	$(shell grep PATCH ./src/version.h | tr -d '"' | awk '{print $$3'} )

# Executable filename details
EXEC_BASE 	= 	Terminal
EXEC		= 	$(BIN_DIR)$(EXEC_BASE)-$(APP_MAJ).$(APP_MIN).$(PATCH)$(DEBUG_NAME)
EXEC_MD5	= 	$(addsuffix .md5, $(EXEC))

# Directories
GAME_DIR 		= ../game/
BUILD_DIR		= ./
SRC_DIR			= $(BUILD_DIR)src/
BIN_DIR			= $(BUILD_DIR)bin/
GAME_BIN_DIR	= $(GAME_DIR)/bin/
INI_DIR			= $(BUILD_DIR)LeksysINI/
JSON_DIR		= $(BUILD_DIR)json/include/

# Sources
CPPSOURCES += $(SRC_DIR)main.cpp
CPPSOURCES += $(SRC_DIR)Registry.cpp
CPPSOURCES += $(SRC_DIR)Level.cpp
CPPSOURCES += $(SRC_DIR)LevelManager.cpp
CPPSOURCES += $(SRC_DIR)EventManager.cpp
CPPSOURCES += $(SRC_DIR)LinuxUtils.cpp


# Object files
COBJ = $(patsubst %.cpp, $(OBJ_DIR)%.o, $(notdir $(CPPSOURCES)))

# Compiler and flags
CXX = /usr/bin/g++
CFLAGS += -I$(SRC_DIR)
CFLAGS += -I$(INI_DIR)
CFLAGS += -I$(JSON_DIR)
CFLAGS += -std=c++17

ifeq ($(DEBUG), 1)
	CFLAGS += -g
	DEBUG_NAME = .dbg
	CFLAGS += -DDEBUG
	OBJ_DIR = $(BUILD_DIR)obj/debug/
else
	OBJ_DIR = $(BUILD_DIR)obj/release/
endif

# Virtual paths for building .cpp->.o files
vpath %.cpp $(SRC_DIR)
vpath %.h $(SRC_DIR)

# Make Targets
.PHONY: all test clean clobber

$(EXEC_MD5): $(EXEC)

$(EXEC): $(OBJ_DIR) $(COBJ) $(BIN_DIR) $(GAME_BIN_DIR)
	$(CXX) $(CFLAGS) $(LDFLAGS) $(COBJ) -o $@
	md5sum $(EXEC) > $(addsuffix .md5, $(EXEC))
	cp $@ $(GAME_BIN_DIR)$(EXEC_BASE)$(DEBUG_NAME)

$(GAME_BIN_DIR):
	@mkdir -p $@

$(BIN_DIR):
	@mkdir -p $@

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)%.o: %.cpp
	$(CXX) $(CFLAGS) -MMD -c $< -o $@

all:
	@$(MAKE) DEBUG=0
	@$(MAKE) DEBUG=1

include $(wildcard $(OBJ_DIR)*.d)

