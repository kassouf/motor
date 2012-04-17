PMKGCC = PMK_GCC	#use the GCC optimizations.  Comment this line out if you don't want GCC optimizations
COMP_OPTS = -Wall
BIN_DIR = bin
OBJ_DIR = $(BIN_DIR)/objects
SRC_ROOT = src
SRC_DIR = $(SRC_ROOT)/src
HDR_DIR = $(SRC_ROOT)/header

MAIN_APP_DEPS = $(OBJ_DIR)/util_obj.o
.SECONDARY: 

$(OBJ_DIR)/%_obj.o: $(SRC_DIR)/%_obj.c $(HDR_DIR)/%_obj.h 
	gcc -c -D$(PMKGCC) -I$(HDR_DIR) $< $(COMP_OPTS) -o $@

$(BIN_DIR)/%_bin: $(SRC_DIR)/%.c $(HDR_DIR)/%.h $(MAIN_APP_DEPS) 
	gcc -lm -D$(PMKGCC) -I$(HDR_DIR) $< $(MAIN_APP_DEPS) $(COMP_OPTS) -o $@


clean:
	rm -rf $(BIN_DIR)&& mkdir $(BIN_DIR) && mkdir $(OBJ_DIR)

remake: clean $(BIN_DIR)/main_bin

config: $(BIN_DIR)

$(BIN_DIR):
	mkdir $(BIN_DIR) &&  mkdir $(OBJ_DIR)

