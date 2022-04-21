# Makefile

export OBJ_DIR 		= $(BUILD_DIR)obj/
export BIN_DIR		= $(BUILD_DIR)bin/

BINSOURCES += RegistryEngine.mk

.PHONY: all clean

release:
	$(MAKE) -f $(BINSOURCES)

debug:
	$(MAKE) DEBUG=1 -f $(BINSOURCES)

all:
	$(MAKE) DEBUG=0 -f $(BINSOURCES)
	$(MAKE) DEBUG=1 -f $(BINSOURCES)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)