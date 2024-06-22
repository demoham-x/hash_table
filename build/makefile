# Makefile

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall    \
         -g
#		 -Werror

# Source Path
SRC_PATH = ../source

# Source files
SRCS = hash_table.c \
	   utils.c      \
       appl_main.c

# Include directories
INCLUDES = -I../source

# Object files
OBJS = $(SRCS:.c=.o)


# Executable
TARGET = HT_test

# Target directory for executable
TARGET_DIR = bin

# Build log file
BUILD_LOG = build_ht.log

# Default target
all: $(TARGET)

# Rule to create the executable
$(TARGET): $(OBJS)
	@echo "Linking..."
	$(CC) $(CFLAGS) -o $(TARGET_DIR)/$(TARGET) $(OBJS)
	@echo "Build successful!"

# Rule to compile source files into object files
%.o: $(SRC_PATH)/%.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC_PATH)/$< -o $@

# Clean up object files and executable
clean:
	@echo "Cleaning up..."
	rm -f $(OBJS) $(TARGET) $(BUILD_LOG)
	@echo "Clean complete!"

# Log the build process
log: 
	@echo "Building project and logging output to $(BUILD_LOG)..."
	$(MAKE) all > $(BUILD_LOG) 2>&1

.PHONY: all clean log
