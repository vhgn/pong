# Variables

cc=gcc
lib=-Ilibraries -Iincludes
flags=-Wall
objects=objects/main.o objects/renderer.o objects/prefload.o

params=$(flags) $(lib)

# Targets

all: obj bin main

main: $(objects)
	@$(cc) $? -o binaries/pong

obj:
	@mkdir -p objects

bin:
	@mkdir -p binaries

# Helpers

run:
	@binaries/pong

debug: all run

clean:
	@rm $(objects)

# Sources

objects/%.o: sources/%.c
	@$(cc) $(params) -c $? -o $@
