# src/Makefile — Feature 4: build static AND dynamic libraries

CC       = gcc
CFLAGS   = -Wall -Wextra -g -I../include
OBJ_DIR  = ../obj
BIN_DIR  = ../bin
LIB_DIR  = ../lib

LIB_NAME       = myutils
STATIC_LIB     = $(LIB_DIR)/lib$(LIB_NAME).a
DYNAMIC_LIB    = $(LIB_DIR)/lib$(LIB_NAME).so
TARGET_STATIC  = $(BIN_DIR)/client_static
TARGET_DYNAMIC = $(BIN_DIR)/client_dynamic

LIB_SRCS = mystrfunctions.c myfilefunctions.c
LIB_OBJS      = $(LIB_SRCS:%.c=$(OBJ_DIR)/%.o)
LIB_OBJS_PIC  = $(LIB_SRCS:%.c=$(OBJ_DIR)/%.pic.o)

MAIN_SRC = main.c
MAIN_OBJ = $(OBJ_DIR)/main.o

.PHONY: all static dynamic clean

all: static dynamic

## ---------- STATIC ----------
static: $(TARGET_STATIC)

$(STATIC_LIB): $(LIB_OBJS)
	@mkdir -p $(LIB_DIR)
	ar rcs $(STATIC_LIB) $(LIB_OBJS)

$(TARGET_STATIC): $(MAIN_OBJ) $(STATIC_LIB)
	@mkdir -p $(BIN_DIR)
	$(CC) $(MAIN_OBJ) -L$(LIB_DIR) -l$(LIB_NAME) -o $(TARGET_STATIC)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

## ---------- DYNAMIC ----------
dynamic: $(TARGET_DYNAMIC)

# Position-independent objects, needed for a shared library
$(OBJ_DIR)/%.pic.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

$(DYNAMIC_LIB): $(LIB_OBJS_PIC)
	@mkdir -p $(LIB_DIR)
	$(CC) -shared -o $(DYNAMIC_LIB) $(LIB_OBJS_PIC)

$(TARGET_DYNAMIC): $(MAIN_OBJ) $(DYNAMIC_LIB)
	@mkdir -p $(BIN_DIR)
	$(CC) $(MAIN_OBJ) -L$(LIB_DIR) -l$(LIB_NAME) -o $(TARGET_DYNAMIC)

clean:
	rm -f $(OBJ_DIR)/*.o $(STATIC_LIB) $(DYNAMIC_LIB) $(TARGET_STATIC) $(TARGET_DYNAMIC)
