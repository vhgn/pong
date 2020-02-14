# Variables

cc=gcc
lib=-Iinc
flags=-Wall
objects=$(shell ls -p src | grep -v / | sed -e s/.c//g | while read name; do echo obj/$$name.o; done < /dev/stdin | paste -sd ' ' -)
sources=$(shell ls -p src/tst | grep -v / | sed -e s/.check//g | while read name; do echo src/$$name.c; done < /dev/stdin | paste -sd ' ' -)
checks=$(shell ls -p src/tst | grep -v / | while read name; do echo src/tst/$$name; done < /dev/stdin | paste -sd ' ' -)
includes=$(shell ls -p inc | grep -v / | while read name; do echo inc/$$name; done < /dev/stdin | paste -sd ' ' -)
params=$(flags) $(lib)

# Targets

all: obj bin main

test: bin obj bintest runtest

main: $(objects)
	@$(cc) $? -o bin/pong -lm

bintest: $(checks)
	@checkmk $? | cat $(sources) - | $(cc) -x c $(params) -Isrc -o bin/test - -lcheck

runtest:
	@bin/test

obj:
	@mkdir -p obj/tests

bin:
	@mkdir -p bin

# Helpers

run:
	@bin/pong

debug: all run

clean:
	@rm $(objects)

# Sources

obj/%.o: src/%.c $(includes)
	@$(cc) $(params) -c $< -o $@
