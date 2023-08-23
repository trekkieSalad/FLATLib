# Compiler settings
CC          = gcc
CFLAGS      = -g -Wall -Wextra -Wpedantic

# ===============================  DIRECTORIES  ===============================

# Base directories
INCLUDE_DIR 	= include
SRC_DIR  		= src
OBJ_DIR  		= build
TEST_DIR 		= test
TEST_SRC_DIR 	= $(TEST_DIR)
TEST_OUT_DIR 	= $(TEST_DIR)/out

# Source directories
UTILS_DIR 		= flatutils
FLAT_TYPES_DIR 	= flattypes
FLAT_MEM_DIR 	= flatmemory
STRUCTS_DIR		= flatdatastructures
SRC_DIRS 		= $(UTILS_DIR) $(FLAT_TYPES_DIR) $(FLAT_MEM_DIR) $(STRUCTS_DIR)

# Test directories
SET_DIR    		= flatset
TUPLE_DIR 		= flattuple
TEST_DIRS 		= $(SET_DIR) $(FLAT_TYPES_DIR) $(UTILS_DIR) $(TUPLE_DIR)

# ==================================  FILES  ==================================

# Source files
SRC       		= $(wildcard $(SRC_DIR)/*.c)
UTILS_SRC 		= $(wildcard $(SRC_DIR)/$(UTILS_DIR)/*.c)
FLAT_TYPES_SRC	= $(wildcard $(SRC_DIR)/$(FLAT_TYPES_DIR)/*.c)
FLAT_MEM_SRC	= $(wildcard $(SRC_DIR)/$(FLAT_MEM_DIR)/*.c)
STRUCTS_SRC   	= $(wildcard $(SRC_DIR)/$(STRUCTS_DIR)/*.c)

# Object files
OBJ_UTILS 		= $(UTILS_SRC:$(SRC_DIR)/$(UTILS_DIR)/%.c=$(OBJ_DIR)/$(UTILS_DIR)/%.o)
OBJ_FLAT_TYPES 	= $(FLAT_TYPES_SRC:$(SRC_DIR)/$(FLAT_TYPES_DIR)/%.c=$(OBJ_DIR)/$(FLAT_TYPES_DIR)/%.o)
OBJ_FLAT_MEM 	= $(FLAT_MEM_SRC:$(SRC_DIR)/$(FLAT_MEM_DIR)/%.c=$(OBJ_DIR)/$(FLAT_MEM_DIR)/%.o)
OBJ_SET   		= $(STRUCTS_SRC:$(SRC_DIR)/$(STRUCTS_DIR)/%.c=$(OBJ_DIR)/$(STRUCTS_DIR)/%.o)

OBJS 			= $(OBJ_UTILS) $(OBJ_FLAT_TYPES) $(OBJ_FLAT_MEM) $(OBJ_SET)

# ==================================  FLAGS  ==================================

# Includes flags
INCLUDES_FLAGS 		= -I$(INCLUDE_DIR) -I$(SRC_DIR)/private_$(INCLUDE_DIR)

# Test flags
TESTFLAGS   = -lcunit -lm

# ==================================  RULES  ==================================

.PHONY: all clean build build_test runTest runSetTest runUtilsTest runTypesTest

all: build_tests runTest clean

build: build_out_dirs $(OBJS)
build_tests: build_test_out_dirs $(TEST_DIRS)

build_out_dirs:
	mkdir -p $(OBJ_DIR)
	$(foreach dir,$(SRC_DIRS),mkdir -p $(OBJ_DIR)/$(dir);)

build_test_out_dirs:
	mkdir -p $(TEST_OUT_DIR)


$(TEST_DIRS): % : build
	@echo ">>> Building $@ tests..."
	$(CC) $(CFLAGS) $(wildcard $(TEST_SRC_DIR)/$(@F)/*.c) $(OBJS) -o $(TEST_OUT_DIR)/$(@F)Test $(INCLUDES_FLAGS) $(TESTFLAGS)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES_FLAGS) -c $< -o $@

runTest:
	$(foreach dir,$(TEST_DIRS),$(TEST_OUT_DIR)/$(dir)Test;)

runSetTest:
	$(TEST_OUT_DIR)/$(STRUCTS_DIR)Test

runUtilsTest:
	$(TEST_OUT_DIR)/$(UTILS_DIR)Test

runTypesTest:
	$(TEST_OUT_DIR)/$(FLAT_TYPES_DIR)Test

clean: 
	rm -rf $(OBJ_DIR)
	rm -rf $(TEST_OUT_DIR)
