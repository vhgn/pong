#include <stdio.h>
#include <stdlib.h>

#include "renderer.h"
	
struct screen*
init_screen
	(unsigned width,
	unsigned height,
	char pixel)
{
	struct screen *screen_ref;
	
	screen_ref = malloc
		(sizeof width +
		sizeof height +
		sizeof pixel * width * height);
	
	screen_ref->width = width;
	screen_ref->height = height;

	screen_ref->matrix = malloc(width * height);

	for
		(unsigned i = 0; i < height; i++)
	{
		for
			(unsigned j = 0; j < width; j++)
		{
			set_screen_index(screen_ref, i, j, pixel);
		}
	}

	return screen_ref;
}

void
set_screen_index
	(struct screen *screen_ref,
	unsigned line_num,
	unsigned col_num,
	char pixel)
{
	char *line_ref,
		*col_ref;

	line_ref = screen_ref->matrix +
		line_num * screen_ref->width;
	
	col_ref = line_ref + col_num;
	*col_ref = pixel;

	return;
}

char
get_screen_index
	(struct screen *screen_ref,
	unsigned line_num,
	unsigned col_num)
{
	char *line_ref,
		*col_ref;

	line_ref = screen_ref->matrix +
		line_num * screen_ref->height;
	
	col_ref = line_ref + col_num;

	return *col_ref;
}

void
render_screen_matrix
	(struct screen *screen_ref)
{
	for
		(int i = 0; i < screen_ref->height; i++)
	{
		for
			(int j = 0; j < screen_ref->width; j++)
		{
			char pixel = get_screen_index(screen_ref, i, j);
			printf("%c", pixel);
		}
		printf("%c",'\n');
	}

	return;
}
