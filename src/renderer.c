#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <termios.h>

#include "renderer.h"

struct screen *init_screen(unsigned width,
                           unsigned height, char pixel) {
	struct screen *screen_ref;

	screen_ref = malloc(sizeof(struct screen));

	screen_ref->width = width;
	screen_ref->height = height;

	screen_ref->matrix = malloc((size_t)width * height);

	clear_screen(screen_ref, pixel);

	return screen_ref;
}

void clear_screen(struct screen *screen, char pixel) {
	unsigned i, j;

	for (i = 0; i < screen->height; i++) {
		for (j = 0; j < screen->width; j++) {
			set_screen_index(screen, i, j, pixel);
		}
	}
}

void set_screen_index(struct screen *screen_ref, unsigned line_num,
                      unsigned col_num, char pixel) {
	char *line_ref;
	char *col_ref;

	line_ref = screen_ref->matrix +
	           line_num * screen_ref->width;

	col_ref = line_ref + col_num;
	*col_ref = pixel;
}

char get_screen_index(struct screen *screen_ref,
                      unsigned line_num, unsigned col_num) {
	char *line_ref;
	char *col_ref;

	line_ref = screen_ref->matrix +
	           line_num * screen_ref->width;

	col_ref = line_ref + col_num;

	return *col_ref;
}

void render_screen_matrix(struct screen *screen_ref) {
	int i, j;
	for (i = 0; i < screen_ref->height; i++) {
		for (j = 0; j < screen_ref->width; j++) {
			char pixel = get_screen_index(screen_ref, i, j);
			printf("%c", pixel);
		}
		printf("%c", '\n');
	}
}

void exit_renderer() {
	static const int STDIN = 0;
	struct termios term;
	tcgetattr(STDIN, &term);
	term.c_lflag |= ICANON;
	term.c_lflag |= ECHO;
	tcsetattr(STDIN, TCSANOW, &term);
	exit(0);
}
