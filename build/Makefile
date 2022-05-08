# Makefile

export OBJ_DIR 		= $(BUILD_DIR)obj/
export BIN_DIR		= $(BUILD_DIR)bin/

# MKSOURCES += EventManager.mk Deprecated for now (BAR): 5/7/2021
MKSOURCES += Terminal.mk

.PHONY: all clean

release:
	$(foreach mkfile,$(MKSOURCES),\
	$(MAKE) -f $(mkfile) ;)

debug:
	$(foreach mkfile,$(MKSOURCES),\
	$(MAKE) DEBUG=1 -f $(mkfile) ;)

all: release debug

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)