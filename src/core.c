#include <stdio.h>

#include "renderer.h"

int
main
	(void)
{
	screen *game_screen;
	game_screen = init_screen(4, 4, ' ');

	set_screen_index
		(game_screen, 1, 3, '0');

	render_screen_matrix(game_screen);

	return 0;
}
