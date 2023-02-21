# Usage:
#  - make			compile to build dir
#  - make clean		clear build dir (delete executables)
#  - make test		test program

.PHONY = all compile clean test

# Directory addresses
SOURCE := src
BUILD := build
TARGET := test/test.qi

# Command directives
CXX := g++
FLAGS := -std=c++17
OUTPUT := q
COMMAND = -o

# Set default goal
.DEFAULT_GOAL := compile

compile:
	@echo [info] compiling...
	@mkdir -p ${BUILD}
	@${CXX} ${FLAGS} ${SOURCE}/*.cpp ${COMMAND} ${BUILD}/${OUTPUT}
	@echo [info] compiled to ${BUILD}/${OUTPUT}

clean:
	@echo [info] cleaning build dir...
	@rm ${BUILD}/*
	@echo [info] build dir cleaned

test: 
	@bash ./tests/test.sh
