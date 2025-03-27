CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
LDFLAGS =

SRC_DIR = src
BUILD_DIR = build
TEST_DIR = tests
DOC_DIR = docs

MATRIX_SRC = $(SRC_DIR)/matrix/matrix.c
OUTPUT_SRC = $(SRC_DIR)/output/output.c
MAIN_SRC = $(SRC_DIR)/main.c

TEST_MATRIX_SRC = $(TEST_DIR)/tests_matrix.c
TEST_OUTPUT_SRC = $(TEST_DIR)/tests_output.c
TEST_RUNNER_SRC = $(TEST_DIR)/test_runner.c

MATRIX_OBJ = $(BUILD_DIR)/matrix.o
OUTPUT_OBJ = $(BUILD_DIR)/output.o
MAIN_OBJ = $(BUILD_DIR)/main.o

TEST_MATRIX_OBJ = $(BUILD_DIR)/tests_matrix.o
TEST_OUTPUT_OBJ = $(BUILD_DIR)/tests_output.o
TEST_RUNNER_OBJ = $(BUILD_DIR)/test_runner.o

EXECUTABLE = matrix_calculator
TEST_EXECUTABLE = test_runner

# CUnit library
CUNIT_PATH = /usr/local
CUNIT_INC = -I$(CUNIT_PATH)/include
CUNIT_LIB = -L$(CUNIT_PATH)/lib -lcunit

all: build executable docs

build:
	mkdir -p $(BUILD_DIR)

executable: $(MATRIX_OBJ) $(OUTPUT_OBJ) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(BUILD_DIR)/$(EXECUTABLE) $(MATRIX_OBJ) $(OUTPUT_OBJ) $(MAIN_OBJ)

test: build test_executable
	$(BUILD_DIR)/$(TEST_EXECUTABLE)

test_executable: $(MATRIX_OBJ) $(OUTPUT_OBJ) $(TEST_MATRIX_OBJ) $(TEST_OUTPUT_OBJ) $(TEST_RUNNER_OBJ)
	$(CC) $(CFLAGS) $(CUNIT_INC) $(LDFLAGS) -o $(BUILD_DIR)/$(TEST_EXECUTABLE) $(TEST_MATRIX_OBJ) $(TEST_OUTPUT_OBJ) $(TEST_RUNNER_OBJ) $(MATRIX_OBJ) $(OUTPUT_OBJ) $(CUNIT_LIB)

docs:
	mkdir -p $(DOC_DIR)
	doxygen

# Компиляция объектных файлов
$(MATRIX_OBJ): $(MATRIX_SRC)
	$(CC) $(CFLAGS) -c $(MATRIX_SRC) -o $(MATRIX_OBJ)

$(OUTPUT_OBJ): $(OUTPUT_SRC)
	$(CC) $(CFLAGS) -c $(OUTPUT_SRC) -o $(OUTPUT_OBJ)

$(MAIN_OBJ): $(MAIN_SRC)
	$(CC) $(CFLAGS) -c $(MAIN_SRC) -o $(MAIN_OBJ)

$(TEST_MATRIX_OBJ): $(TEST_MATRIX_SRC)
	$(CC) $(CFLAGS) $(CUNIT_INC) -c $(TEST_MATRIX_SRC) -o $(TEST_MATRIX_OBJ)

$(TEST_OUTPUT_OBJ): $(TEST_OUTPUT_SRC)
	$(CC) $(CFLAGS) $(CUNIT_INC) -c $(TEST_OUTPUT_SRC) -o $(TEST_OUTPUT_OBJ)

$(TEST_RUNNER_OBJ): $(TEST_RUNNER_SRC)
	$(CC) $(CFLAGS) $(CUNIT_INC) -c $(TEST_RUNNER_SRC) -o $(TEST_RUNNER_OBJ)

clean:
	rm -rf $(BUILD_DIR) $(DOC_DIR)

run: executable
	$(BUILD_DIR)/$(EXECUTABLE)

.PHONY: all build executable test test_executable docs clean run