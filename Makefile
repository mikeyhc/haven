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
INCLUDE_DIR       := include
OBJ_DIR           := $(BUILD_DIR)/obj
SRC_DIR           := src
TEST_DIR          := t
TEST_OUT_DIR      := $(BUILD_DIR)/$(TEST_DIR)
UNIT_TEST_DIR     := $(TEST_DIR)/unit
UNIT_TEST_OUT_DIR := $(BUILD_DIR)/$(UNIT_TEST_DIR)

VPATH             := $(SRC_DIR)

DEBUG  := -g
CFLAGS := -I$(INCLUDE_DIR) $(DEBUG) -Wall -Wextra -pedantic
QUIET  ?= @

all: 

test: run_arraylist_unit_test run_entity_unit_test
	$(QUIET)$(ECHO)

test-debug-files: $(UNIT_TEST_OUT_DIR)/arraylist-debug

$(UNIT_TEST_OUT_DIR)/arraylist-debug: $(UNIT_TEST_DIR)/arraylist.c \
	                                  $(INCLUDE_DIR)/arraylist.h
	$(QUIET)$(MKDIR) $(UNIT_TEST_OUT_DIR)
	$(GCC) $(CFLAGS) -E -P -o $(patsubst %.c,%.i,$<) $<
	$(SED) -i 's/\(;\|{\|}\)/\1\n/g' $(patsubst %.c,%.i,$<)
	$(GCC) $(DEBUG) -o $@ $(patsubst %c,%i,$<)
	

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

$(UNIT_TEST_OUT_DIR)/entity: $(UNIT_TEST_DIR)/entity.c $(OBJ_DIR)/entity.o \
	                         $(INCLUDE_DIR)/entity.h
	$(QUIET)$(MKDIR) $(UNIT_TEST_OUT_DIR)
	$(QUIET)$(GCC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/entity.o: entity.c $(INCLUDE_DIR)/entity.h \
	                 $(INCLUDE_DIR)/arraylist.h
	$(QUIET)$(MKDIR) $(OBJ_DIR)
	$(QUIET)$(GCC) $(CFLAGS) -c -o $@ $<

clean: clean-debug
	$(RMR) $(BUILD_DIR)

clean-debug:
	$(RM) $(UNIT_TEST_DIR)/*.i
