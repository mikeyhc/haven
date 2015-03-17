# Makefile
# Simple makefile for initial development, will be replaced with automake 
# script when I find time
#
# author: mikeyhc <mikeyhc@atmosia.net>

GCC   := gcc
ECHO  := echo
FIND  := find
MKDIR := mkdir -p
SED   := sed
RM    := rm -f
RMR   := $(RM) -r

BUILD_DIR         := build
BIN_DIR           := $(BUILD_DIR)/bin
INCLUDE_DIR       := include
OBJ_DIR           := $(BUILD_DIR)/obj
SRC_DIR           := src
TEST_DIR          := t
TEST_OUT_DIR      := $(BUILD_DIR)/$(TEST_DIR)
UNIT_TEST_DIR     := $(TEST_DIR)/unit
UNIT_TEST_OUT_DIR := $(BUILD_DIR)/$(UNIT_TEST_DIR)

VPATH             := $(SRC_DIR)

DEBUG  := -g
CFLAGS := -I$(INCLUDE_DIR) $(DEBUG) -Wall -Wextra -pedantic -I/usr/include/SDL2
LDLIBS := -L/usr/lib64/SDL2 -lSDL2 -lSDL2_image
QUIET  ?= @

all: $(BIN_DIR)/haven

no-gui:

$(BIN_DIR)/haven: $(OBJ_DIR)/gui.o $(OBJ_DIR)/game.o $(OBJ_DIR)/main.o 
	$(QUIET)$(MKDIR) $(BIN_DIR)
	$(GCC) $(CFLAGS) $(LDLIBS) -o $@ $^

$(OBJ_DIR)/main.o: main.c $(INCLUDE_DIR)/gui.h $(INCLUDE_DIR)/game.h
	$(QUIET)$(MKDIR) $(OBJ_DIR)
	$(GCC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/gui.o: gui.c $(INCLUDE_DIR)/gui.h
	$(QUIET)$(MKDIR) $(OBJ_DIR)
	$(GCC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/game.o: game.c $(INCLUDE_DIR)/game.h $(INCLUDE_DIR)/gui.h
	$(QUIET)$(MKDIR) $(OBJ_DIR)
	$(GCC) $(CFLAGS) -c -o $@ $<

test: run_arraylist_unit_test run_entity_unit_test run_chunk_unit_test
	$(QUIET)$(ECHO)

test-debug-files: $(UNIT_TEST_OUT_DIR)/arraylist-debug \
	              $(UNIT_TEST_OUT_DIR)/chunk-debug

$(UNIT_TEST_OUT_DIR)/arraylist-debug: $(UNIT_TEST_DIR)/arraylist.c \
	                                  $(INCLUDE_DIR)/arraylist.h
	$(QUIET)$(MKDIR) $(UNIT_TEST_OUT_DIR)
	$(GCC) $(CFLAGS) -E -P -o $(patsubst %.c,%.i,$<) $<
	$(SED) -i 's/\(;\|{\|}\)/\1\n/g' $(patsubst %.c,%.i,$<)
	$(GCC) $(DEBUG) -o $@ $(patsubst %c,%i,$<)

$(UNIT_TEST_OUT_DIR)/chunk-debug: $(UNIT_TEST_DIR)/chunk.c \
	                              $(OBJ_DIR)/entity.o $(INCLUDE_DIR)/entity.h \
								  $(INCLUDE_DIR)/component/chunk.h
	$(QUIET)$(MKDIR) $(UNIT_TEST_OUT_DIR)
	$(GCC) $(CFLAGS) -E -P -o $(patsubst %.c,%.i,$<) $<
	$(SED) -i 's/\(;\|{\|}\)/\1\n/g' $(patsubst %.c,%.i,$<)
	$(GCC) $(DEBUG) -o $@ $(patsubst %c,%i,$<) $(OBJ_DIR)/entity.o
	

$(UNIT_TEST_OUT_DIR)/arraylist: $(UNIT_TEST_DIR)/arraylist.c \
	                            $(INCLUDE_DIR)/arraylist.h
	$(QUIET)$(MKDIR) $(UNIT_TEST_OUT_DIR)
	$(QUIET)$(GCC) $(CFLAGS) -o $@ $<

run_arraylist_unit_test: $(UNIT_TEST_OUT_DIR)/arraylist
	$(QUIET)$(ECHO)
	$(QUIET)$(UNIT_TEST_OUT_DIR)/arraylist

run_entity_unit_test: $(UNIT_TEST_OUT_DIR)/entity
	$(QUIET)$(ECHO)
	$(QUIET)$(UNIT_TEST_OUT_DIR)/entity

run_chunk_unit_test: $(UNIT_TEST_OUT_DIR)/chunk
	$(QUIET)$(ECHO)
	$(QUIET)$(UNIT_TEST_OUT_DIR)/chunk

$(UNIT_TEST_OUT_DIR)/entity: $(UNIT_TEST_DIR)/entity.c $(OBJ_DIR)/entity.o \
	                         $(INCLUDE_DIR)/entity.h
	$(QUIET)$(MKDIR) $(UNIT_TEST_OUT_DIR)
	$(QUIET)$(GCC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/entity.o: entity.c $(INCLUDE_DIR)/entity.h \
	                 $(INCLUDE_DIR)/arraylist.h
	$(QUIET)$(MKDIR) $(OBJ_DIR)
	$(QUIET)$(GCC) $(CFLAGS) -c -o $@ $<

$(UNIT_TEST_OUT_DIR)/chunk: $(UNIT_TEST_DIR)/chunk.c \
							$(OBJ_DIR)/entity.o \
							$(INCLUDE_DIR)/entity.h \
	                        $(INCLUDE_DIR)/component/chunk.h
	$(QUIET)$(MKDIR) $(UNIT_TEST_OUT_DIR)
	$(QUIET)$(GCC) $(CFLAGS) -o $@ $^

clean: clean-debug
	$(RMR) $(BUILD_DIR)

clean-debug:
	$(RM) $(UNIT_TEST_DIR)/*.i
