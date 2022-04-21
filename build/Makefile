# Makefile

export OBJ_DIR 		= $(BUILD_DIR)obj/
export BIN_DIR		= $(BUILD_DIR)bin/

MKSOURCES += RegistryEngine.mk
MKSOURCES += GameEngine.mk

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