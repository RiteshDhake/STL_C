# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -Iinclude

# Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
LIB_NAME = libstl.a

# Source files (all .c except test files)
SRC = $(filter-out $(SRC_DIR)/test_%.c, $(wildcard $(SRC_DIR)/*.c))
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

# Test sources
TEST_SRC = $(wildcard $(SRC_DIR)/test_*.c)
TEST_OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(TEST_SRC))

# Targets
TARGET = test_vector

all: $(LIB_NAME) $(TARGET)

# Build static library
$(LIB_NAME): $(OBJ)
	ar rcs $@ $^

# Build test executables (links with libstl)
$(TARGET): $(LIB_NAME) $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJ) -L. -lstl

# Rule to compile source into build directory
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory if missing
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean
clean:
	rm -rf $(BUILD_DIR) *.a $(TARGET)

# Run test
run: $(TARGET)
	./$(TARGET)
