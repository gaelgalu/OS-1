
all: release

release:
	gcc main.c functions.c -o laboratorio1 -lm -Wall

run:
	./laboratorio1 -h 5 - m
