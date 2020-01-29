# Variables

cc=gcc
lib=-Ilibraries -Iincludes
flags=-Wall
objects=$(shell ls -p sources | grep -v / | sed -e s/.c//g | while read name; do echo objects/$$name.o; done < /dev/stdin | paste -sd ' ' -)
sources=$(shell ls -p sources/tests | grep -v / | sed -e s/.check//g | while read name; do echo sources/$$name.c; done < /dev/stdin | paste -sd ' ' -)
checks=$(shell ls -p sources/tests | grep -v / | while read name; do echo sources/tests/$$name; done < /dev/stdin | paste -sd ' ' -)
includes=$(shell ls -p includes | grep -v / | while read name; do echo includes/$$name; done < /dev/stdin | paste -sd ' ' -)
params=$(flags) $(lib)

# Targets

all: obj bin main

test: bin obj bintest runtest

main: $(objects)
	@$(cc) $? -o binaries/pong -lm

bintest: $(checks)
	@checkmk $? | cat $(sources) - | $(cc) -x c $(params) -lcheck -Isources -o binaries/test -

runtest:
	@binaries/test

obj:
	@mkdir -p objects/tests

bin:
	@mkdir -p binaries

# Helpers

run:
	@binaries/pong

debug: all run

clean:
	@rm $(objects)

# Sources

objects/%.o: sources/%.c $(includes)
	@$(cc) $(params) -c $< -o $@
