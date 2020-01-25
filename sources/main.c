#include <stdio.h>

#include "renderer.h"
#include "prefload.h"
#include "gameplay.h"

#define WIDTH 64u
#define HEIGHT 16u
#define FPS 1

int
main
	(void)
{
	screen = init_screen(WIDTH, HEIGHT, ' ');
	render_screen_matrix(screen);
	struct appearance *left, *right;
	left = get_player_prefs(0);
	right = get_player_prefs(1);
	start_gameplay(screen, left, right, 1000 / FPS);
	
	return 0;
}
