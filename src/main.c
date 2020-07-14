#include <stdio.h>

#include "gameplay.h"
#include "prefload.h"
#include "renderer.h"

#define WIDTH 64u
#define HEIGHT 16u
#define FPS 1

int main(void) {
	struct appearance *left;
	struct appearance *right;
	screen = init_screen(WIDTH, HEIGHT, ' ');
	render_screen_matrix(screen);
	left = get_player_prefs(0);
	right = get_player_prefs(1);
	start_gameplay(screen, left, right, 1000 / FPS);

	exit_renderer();
	return 0;
}
