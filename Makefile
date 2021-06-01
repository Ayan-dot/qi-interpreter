# Usage:
# make 					compile all binary
# make clean		remove all binaries and objects

.PHONY = all compile clean

SRC := src
OUT := build

CXX := g++
FLAGS := -std=c++11
NAME := qi

.DEFAULT_GOAL := compile

compile:
	@echo [INFO] Compiling objects...
	${CXX} ${FLAGS} ${SRC}/*.cpp -o ${OUT}/${NAME}

run:
	./${OUT}/${NAME}

clean:
	@echo [INFO] Cleaning the build directory...
	@rm ${OUT}/*
