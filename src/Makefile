# src/Makefile — compiles all .c files directly and links into bin/client
# (Feature 2: baseline, no library yet)

CC       = gcc
CFLAGS   = -Wall -Wextra -g -I../include
SRC_DIR  = .
OBJ_DIR  = ../obj
BIN_DIR  = ../bin
TARGET   = $(BIN_DIR)/client

SRCS = mystrfunctions.c myfilefunctions.c main.c
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

.PHONY: all clean

all: $(TARGET)

# Linking rule: link ALL object files directly into the executable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $(TARGET)
	@echo "Build complete: $(TARGET)"

# Pattern rule: compile any .c into a .o inside obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
