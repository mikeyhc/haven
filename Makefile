# Makefile
# Simple makefile for initial development, will be replaced with automake 
# script when I find time
#
# author: mikeyhc <mikeyhc@atmosia.net>

GCC   := gcc
ECHO  := echo
MKDIR := mkdir -p
RMR   := rm -r

BUILD_DIR         := build
INCLUDE_DIR       := include
TEST_DIR          := t
TEST_OUT_DIR      := $(BUILD_DIR)/$(TEST_DIR)
UNIT_TEST_DIR     := $(TEST_DIR)/unit
UNIT_TEST_OUT_DIR := $(BUILD_DIR)/$(UNIT_TEST_DIR)

CFLAGS := -I$(INCLUDE_DIR)
QUIET  ?= @

all:

test: run_arraylist_unit_test
	$(QUIET)$(ECHO)

$(UNIT_TEST_OUT_DIR)/arraylist: $(UNIT_TEST_DIR)/arraylist.c \
	                            $(INCLUDE_DIR)/arraylist.h
	$(QUIET)$(MKDIR) $(UNIT_TEST_OUT_DIR)
	$(QUIET)$(GCC) $(CFLAGS) -o $@ $<

run_arraylist_unit_test: $(UNIT_TEST_OUT_DIR)/arraylist
	$(QUIET)$(ECHO)
	$(QUIET)$(UNIT_TEST_OUT_DIR)/arraylist

clean:
	$(RMR) $(BUILD_DIR)
