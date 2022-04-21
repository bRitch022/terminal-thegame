# Makefile

export OBJ_DIR 		= $(BUILD_DIR)obj/
export BIN_DIR		= $(BUILD_DIR)bin/

BINSOURCES += RegistryEngine.mk
BINSOURCES += GameEngine.mk

.PHONY: all clean

release:
	$(foreach bin,$(BINSOURCES),\
	$(MAKE) -f $(bin) ;)

debug:
	$(foreach bin,$(BINSOURCES),\
	$(MAKE) DEBUG=1 -f $(bin) ;)

all: release debug

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)