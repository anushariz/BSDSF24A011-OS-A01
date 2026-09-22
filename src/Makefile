# src/Makefile — Feature 3: build a static library and link against it

CC       = gcc
CFLAGS   = -Wall -Wextra -g -I../include
OBJ_DIR  = ../obj
BIN_DIR  = ../bin
LIB_DIR  = ../lib

LIB_NAME    = myutils
STATIC_LIB  = $(LIB_DIR)/lib$(LIB_NAME).a
TARGET_STATIC = $(BIN_DIR)/client_static

LIB_SRCS = mystrfunctions.c myfilefunctions.c
LIB_OBJS = $(LIB_SRCS:%.c=$(OBJ_DIR)/%.o)

MAIN_SRC = main.c
MAIN_OBJ = $(OBJ_DIR)/main.o

.PHONY: all static clean

all: static

static: $(TARGET_STATIC)

# 1. Build the static library from the library object files
$(STATIC_LIB): $(LIB_OBJS)
	@mkdir -p $(LIB_DIR)
	ar rcs $(STATIC_LIB) $(LIB_OBJS)
	@echo "Static library built: $(STATIC_LIB)"

# 2. Link main.o against the static library
$(TARGET_STATIC): $(MAIN_OBJ) $(STATIC_LIB)
	@mkdir -p $(BIN_DIR)
	$(CC) $(MAIN_OBJ) -L$(LIB_DIR) -l$(LIB_NAME) -o $(TARGET_STATIC)
	@echo "Static executable built: $(TARGET_STATIC)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(STATIC_LIB) $(TARGET_STATIC)
