# Compiler settings
CC          = gcc
CFLAGS      = -g -Wall -pedantic -Wextra -std=c18
TESTFLAGS   = -lcunit -lm

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
FLAT_MEM_DIR 	= flatMem
SET_DIR   		= flatSet
AF_DIR    		= af

TEST_DIRS 		= $(SET_DIR) $(FLAT_TYPES_DIR) $(UTILS_DIR) $(FLAT_MEM_DIR)

SRC       		= $(wildcard $(SRC_DIR)/*.c)
UTILS_SRC 		= $(wildcard $(SRC_DIR)/$(UTILS_DIR)/*.c)
FLAT_TYPES_SRC	= $(wildcard $(SRC_DIR)/$(FLAT_TYPES_DIR)/*.c)
FLAT_MEM_SRC	= $(wildcard $(SRC_DIR)/$(FLAT_MEM_DIR)/*.c)
SET_SRC   		= $(wildcard $(SRC_DIR)/$(SET_DIR)/*.c)

OBJ_UTILS 		= $(UTILS_SRC:$(SRC_DIR)/$(UTILS_DIR)/%.c=$(OBJ_DIR)/$(UTILS_DIR)/%.o)
OBJ_FLAT_TYPES 	= $(FLAT_TYPES_SRC:$(SRC_DIR)/$(FLAT_TYPES_DIR)/%.c=$(OBJ_DIR)/$(FLAT_TYPES_DIR)/%.o)
OBJ_FLAT_MEM 	= $(FLAT_MEM_SRC:$(SRC_DIR)/$(FLAT_MEM_DIR)/%.c=$(OBJ_DIR)/$(FLAT_MEM_DIR)/%.o)
OBJ_SET   		= $(SET_SRC:$(SRC_DIR)/$(SET_DIR)/%.c=$(OBJ_DIR)/$(SET_DIR)/%.o)

INCLUDES 		= -I$(INCLUDE_DIR) -I$(SRC_DIR)/$(INCLUDE_DIR)

MAIN_TRGT 		= main
LIB_TRGT  		= $(FLAT_TYPES_DIR) $(FLAT_MEM_DIR) $(SET_DIR) $(UTILS_DIR)
SUBDIRS 		= $(SET_DIR) $(UTILS_DIR) $(FLAT_TYPES_DIR) $(FLAT_MEM_DIR)

.PHONY: all clean runTest runSetTest

all: $(LIB_TRGT)

$(OBJ_DIR):
	mkdir -p $@
	$(foreach dir,$(LIB_TRGT),mkdir -p $@/$(dir);)

$(SUBDIRS): % : $(OBJ_UTILS) $(OBJ_SET) $(OBJ_FLAT_TYPES) $(OBJ_FLAT_MEM)
	$(CC) $(wildcard $(TEST_SRC_DIR)/$(@F)/*.c) $^ -o $(TEST_OUT_DIR)/$(@F)Test $(INCLUDES) $(TESTFLAGS)


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
