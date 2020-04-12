name = pong
includes = $(wildcard inc/*)
sourcefiles = $(wildcard src/*)
sources = $(sourcefiles:%.c=obj/%.o)

compiler = gcc
flags = -Iinc -std=c89 -pedantic -Wall

quick: sub all

sub:	
	git submodule init
	git submodule update

all: obj bin run

obj: obj/src

obj/%:
	mkdir -p $@

bin:
	mkdir -p $@

run: bin/$(name)
	$<

clean:
	rm -f $(sources) bin/$(name)

bin/$(name): $(sources)
	$(compiler) -o $@ $^

obj/src/%.o: src/%.c $(includes)
	$(compiler) -o $@ -c $< $(flags)
