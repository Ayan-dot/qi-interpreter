# Usage:
# make 				compile all binary
# make clean		remove all binaries and objects

.PHONY = all compile clean

SRC := src
OUT := build

CXX := g++
FLAGS := -std=c++11
NAME := qi
ARGS := test.qi

.DEFAULT_GOAL := compile

compile:
	${CXX} ${FLAGS} ${SRC}/*.cpp -o ${OUT}/${NAME}
	@echo [info] compiled to ./${OUT}/${NAME}

run:
	./${OUT}/${NAME} ${ARGS}

clean:
	@echo [info] cleaning build directory
	@rm ${OUT}/*
