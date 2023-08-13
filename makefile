# Created by: DGP_DEV aka trekkieSalad

# Global variables
# Compiler flags and options
CC       		= gcc -g
CFLAGS   		= -Wall -pedantic -Wextra -std=c18
TESTFLAGS 		= -lcunit -lm

# Directories
# Base directories
INCLUDE_DIR 	= include
SRC_DIR  		= src
OBJ_DIR  		= build
TEST_DIR 		= test
TEST_SRC_DIR 	= $(TEST_DIR)
TEST_OUT_DIR 	= $(TEST_DIR)/out


UTILS_DIR 		= flatUtils
FLAT_TYPES_DIR 	= flatTypes
SET_DIR   		= flatSet
AF_DIR    		= af

TEST_DIRS 		= $(SET_DIR) $(FLAT_TYPES_DIR) $(UTILS_DIR)

SRC       		= $(wildcard $(SRC_DIR)/*.c)
UTILS_SRC 		= $(wildcard $(SRC_DIR)/$(UTILS_DIR)/*.c)
FLAT_TYPES_SRC	= $(wildcard $(SRC_DIR)/$(FLAT_TYPES_DIR)/*.c)
SET_SRC   		= $(wildcard $(SRC_DIR)/$(SET_DIR)/*.c)

TEST	  		= $(wildcard $(TEST_SRC_DIR)/*.c)
SET_TEST  		= $(wildcard $(TEST_SRC_DIR)/$(SET_DIR)/*.c)
FLAT_TYPES_TEST	= $(wildcard $(TEST_SRC_DIR)/$(FLAT_TYPES_DIR)/*.c)
UTILS_TEST		= $(wildcard $(TEST_SRC_DIR)/$(UTILS_DIR)/*.c)

OBJ_UTILS 		= $(UTILS_SRC:$(SRC_DIR)/$(UTILS_DIR)/%.c=$(OBJ_DIR)/$(UTILS_DIR)/%.o)
OBJ_FLAT_TYPES 	= $(FLAT_TYPES_SRC:$(SRC_DIR)/$(FLAT_TYPES_DIR)/%.c=$(OBJ_DIR)/$(FLAT_TYPES_DIR)/%.o)
OBJ_SET   		= $(SET_SRC:$(SRC_DIR)/$(SET_DIR)/%.c=$(OBJ_DIR)/$(SET_DIR)/%.o)

OUT_SET_TEST 	= $(SET_TEST:$(TEST_SRC_DIR)/$(SET_DIR)/%.c=$(TEST_OUT_DIR)/$(SET_DIR)/%)

INCLUDES 		= -I$(INCLUDE_DIR) -I$(SRC_DIR)/$(INCLUDE_DIR)

MAIN_TRGT 		= main
LIB_TRGT  		= $(FLAT_TYPES_DIR)  $(SET_DIR) $(UTILS_DIR)

.PHONY: all clean runTest runSetTest

all: $(LIB_TRGT)

$(OBJ_DIR):
	mkdir -p $@
	$(foreach dir,$(LIB_TRGT),mkdir -p $@/$(dir);)

$(SET_DIR): $(OBJ_UTILS) $(OBJ_SET) $(OBJ_FLAT_TYPES)
	$(CC) $(SET_TEST) $^ -o $(TEST_OUT_DIR)/$@Test $(INCLUDES) $(TESTFLAGS)

$(UTILS_DIR): $(OBJ_UTILS) $(OBJ_SET) $(OBJ_FLAT_TYPES)
	$(CC) $(UTILS_TEST) $^ -o $(TEST_OUT_DIR)/$@Test $(INCLUDES) $(TESTFLAGS)

$(FLAT_TYPES_DIR): $(OBJ_UTILS) $(OBJ_SET) $(OBJ_FLAT_TYPES)
	$(CC) $(FLAT_TYPES_TEST) $^ -o $(TEST_OUT_DIR)/$@Test $(INCLUDES) $(TESTFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

runTest:
	$(foreach dir,$(TEST_DIRS),$(TEST_OUT_DIR)/$(dir)Test;)

runSetTest:
	$(TEST_OUT_DIR)/$(SET_DIR)Test

runUtilsTest:
	$(TEST_OUT_DIR)/$(UTILS_DIR)Test

runTypesTest:
	$(TEST_OUT_DIR)/$(FLAT_TYPES_DIR)Test

clean: 
	rm -rf $(OBJ_DIR)
	rm -rf $(TEST_OUT_DIR)/*