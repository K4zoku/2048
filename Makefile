CC=gcc
CFLAGS=-fPIC -g -O2 -Wall -Wextra -std=gnu11
LD=-lm

SRC=src
INC=-I$(SRC)
DIST=dist
OBJ=$(DIST)/obj
BIN=$(DIST)/bin

NAME=2048

SOURCES=$(shell find $(SRC) -name '*.c')
OBJECTS=$(SOURCES:$(SRC)/%.c=$(OBJ)/%.o)

default: clean prepare compile

prepare:
	@echo Preparing...
	@mkdir -p $(OBJ)
	@mkdir -p $(BIN)

clean:
	@echo Cleaning...
	@rm -rf $(OBJ)/*
	@rm -rf $(BIN)/*

compile: $(OBJECTS)
	@echo Linking...
	@$(CC) $(INC) $(CFLAGS) $^ -o $(BIN)/$(NAME) $(LD)

$(OBJ)/%.o: $(SRC)/%.c
	@echo Compiling $<
	@mkdir -p $$(dirname $@)
	@$(CC) $(INC) $(CFLAGS) -c $< -o $@ $(LD) 
