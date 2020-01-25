# Variables

cc=gcc
lib=-Ilibraries -Iincludes
flags=-Wall
objects=$(shell ls -p sources | grep -v / | sed -e s/.c//g | while read name; do echo objects/$$name.o; done < /dev/stdin | paste -sd ' ' -)
includes=$(shell ls -p includes | grep -v / | while read name; do echo includes/$$name; done < /dev/stdin | paste -sd ' ' -)
params=$(flags) $(lib)

# Targets

all: obj bin main

main: $(objects)
	@$(cc) $? -o binaries/pong

obj:
	@mkdir -p objects/tests

bin:
	@mkdir -p binaries/tests

# Helpers

run:
	@binaries/pong

debug: all run

clean:
	@rm $(objects)

# Sources

objects/%.o: sources/%.c $(includes)
	@$(cc) $(params) -c $< -o $@
