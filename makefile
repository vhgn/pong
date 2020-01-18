all: obj bin main

main: obj/core.o obj/renderer.o
	@gcc obj/core.o obj/renderer.o -o bin/pong

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
	@gcc -c src/core.c -o obj/core.o

obj/renderer.o: src/renderer.c
	@gcc -c src/renderer.c -o obj/renderer.o
