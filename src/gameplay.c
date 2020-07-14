#include <curses.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include "gameplay.h"
#include "kbhit.h"

int calculate_frame(int delta, char input) {
	double new_x, new_y;
	unsigned x, y;

	if (input == '1') {
		if (left->height + left->length + 2 < screen->height) {
			left->height++;
		}
	} else if (input == '2') {
		if (left->height > 0) {
			left->height--;
		}
	} else if (input == '9') {
		if (right->height + right->length + 2 < screen->height) {
			right->height++;
		}
	} else if (input == '0') {
		if (right->height > 0) {
			right->height--;
		}
	}

	new_x = ball->pos_x + ball->vel_x;
	new_y = ball->pos_y + ball->vel_y;

	if (new_y < 0 || new_y >= screen->height)
		ball->vel_y *= -1;

	if (new_x < -1 || new_x > screen->width)
		return 1;

	x = round(new_x);
	y = round(new_y);

	if (x <= 0 && left->height <= y && left->height + left->length + 1 >= y)
		ball->vel_x *= -1;

	if ((unsigned)x >= screen->width - 1 && right->height <= y && right->height + right->length + 1 >= y)
		ball->vel_x *= -1;

	ball->pos_x = new_x;
	ball->pos_y = new_y;

	return 0;
}

void start_gameplay(struct screen *game_screen, struct appearance *left_player,
                    struct appearance *right_player, int delay) {
	struct timeval this_frame, prev_frame;
	int input, total_delayed, diff;
	double degrees, radians;

	gettimeofday(&prev_frame, NULL);
	srand(prev_frame.tv_sec);

	left = malloc(sizeof(struct player));
	left->height = 0u;
	left->length = 2u;
	left->look = malloc(sizeof(struct appearance));
	left->look = left_player;

	right = malloc(sizeof(struct player));
	right->height = 0u;
	right->length = 2u;
	right->look = malloc(sizeof(struct appearance));
	right->look = right_player;

	ball = malloc(sizeof(struct ball));
	ball->pos_x = (screen->width - 1) / 2;
	ball->pos_y = (screen->height - 1) / 2;

	degrees = rand() % 90 - 45;
	radians = degrees * M_PI / 180;

	ball->vel_x = cos(radians) * INITIAL_SPEED;
	ball->vel_y = sin(radians) * INITIAL_SPEED;

	while (1) {
		gettimeofday(&this_frame, NULL);

		if (_kbhit()) {
			input = fgetc(stdin);
			if (input == 127) {
				system("clear");
				break;
			}
		}

		diff = (this_frame.tv_usec - prev_frame.tv_usec) + (this_frame.tv_sec - prev_frame.tv_sec) * 1000000;

		total_delayed += diff;

		if (total_delayed > delay) {
			if (calculate_frame(diff, input) != 0) {
				system("clear");
				break;
			}
			clear_screen(screen, ' ');
			render_ball(ball, screen);
			render_player(left, screen, 0);
			render_player(right, screen, 1);
			system("clear");
			render_screen_matrix(game_screen);
			total_delayed = 0;
			input = 0;
		}

		gettimeofday(&prev_frame, NULL);
	}
}

void render_player(struct player *player, struct screen *screen, int side) {
	int i;

	set_screen_index(screen, player->height, side * (screen->width - 1),
	                 player->look->top_char);

	for (i = player->height + 1;
	     i < player->height + player->length + 1; i++)
		set_screen_index(screen, i, side * (screen->width - 1),
		                 player->look->middle_char);

	set_screen_index(screen, player->height + player->length + 1,
	                 side * (screen->width - 1), player->look->bottom_char);
}

void render_ball(struct ball *ball, struct screen *screen) {
	set_screen_index(screen, (unsigned)ball->pos_y,
	                 (unsigned)ball->pos_x, 'o');
}
