# Usage:
#  - make			compile to build dir
#  - make clean		clear build dir (delete executables)
#  - make test		test with target as arg

.PHONY = all compile clean test

# Directory addresses
SOURCE := src
BUILD := build
TARGET := test/test.qi

# Command directives
CXX := g++
FLAGS := -std=c++17
OUTPUT := qi
COMMAND = -o

# Set default goal
.DEFAULT_GOAL := compile

compile:
	@echo [info] compiling...
	@${CXX} ${FLAGS} ${SOURCE}/*.cpp ${COMMAND} ${BUILD}/${OUTPUT}
	@echo [info] compiled to ${BUILD}/${OUTPUT}

clean:
	@echo [info] cleaning build dir...
	@rm ${BUILD}/*
	@echo [info] build dir cleaned

test:
	@echo [info] testing program with target ${TARGET}
	@${TARGET}
