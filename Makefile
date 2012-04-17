PMKGCC = PMK_GCC	#use the GCC optimizations.  Comment this line out if you don't want GCC optimizations
COMP_OPTS = -Wall
BIN_DIR = bin
OBJ_DIR = $(BIN_DIR)/objects
SRC_ROOT = src
SRC_DIR = $(SRC_ROOT)/src
HDR_DIR = $(SRC_ROOT)/header


$(BIN_DIR)/motor: $(BIN_DIR) $(OBJ_DIR)/util.o $(SRC_DIR)/motor.c $(HDR_DIR)/motor.h
	gcc -D$(PMKGCC) -lm  -I $(HDR_DIR) $(OBJ_DIR)/util.o $(SRC_DIR)/motor.c $(COMP_OPTS) -o $(BIN_DIR)/motor

$(OBJ_DIR)/util.o: $(OBJ_DIR) $(HDR_DIR)/util.h $(SRC_DIR)/util.c 
	gcc -c -D$(PMKGCC) -I $(HDR_DIR) $(SRC_DIR)/util.c $(COMP_OPTS) -o $(OBJ_DIR)/util.o

clean:
	rm -rf $(BIN_DIR)

remake: clean $(BIN_DIR)/motor

$(BIN_DIR):
	mkdir $(BIN_DIR)

$(OBJ_DIR): $(BIN_DIR)
	mkdir $(OBJ_DIR)
