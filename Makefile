# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -Iinclude

# Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
TARGET = app   # final output executable

# Source files (all .c except test files)
SRC = $(filter-out $(SRC_DIR)/test_%.c, $(wildcard $(SRC_DIR)/*.c))
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

# Default target
all: $(TARGET)

# Link executable from object files
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile source into build directory
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory if missing
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Run
run: $(TARGET)
	./$(TARGET)
