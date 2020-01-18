# Variables

cc=gcc
lib=-Ilib
flags=-Wall

params=$(flags) $(lib)

# Targets

all: obj bin main

main: obj/core.o obj/renderer.o obj/prefload.o
	@$(cc) $? -o bin/pong

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

obj/%.o: src/%.c
	@$(cc) $(params) -c $? -o $@
