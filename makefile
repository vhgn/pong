# Variables

cc=gcc
lib=-Ilib
flags=-Wall

params=$(flags) $(lib)

# Targets

all: obj bin main

main: obj/core.o obj/renderer.o
	@$(cc) obj/core.o obj/renderer.o -o bin/pong

obj:
	@mkdir -p obj

bin:
	@mkdir -p bin

# Helpers

run:
	@bin/pong

debug: all run

clean:
	@rm obj/core.o obj/renderer.o bin/pong

# Sources

obj/core.o: src/core.c
	@$(cc) $(params) -c src/core.c -o obj/core.o

obj/renderer.o: src/renderer.c
	@$(cc) $(params) -c src/renderer.c -o obj/renderer.o
