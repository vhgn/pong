#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

#include "gameplay.h"
#include "kbhit.h"

void
calculate_frame
	(int delta,
	int input)
{
	if(input == '1')
	{
		if(left->height + left->length + 2 < screen->height)
		{
			left->height++;
		}
	}
	else if(input == '2')
	{
		if(left->height > 0)
		{
			left->height--;
		}
	}
	else if(input == '9')
	{
		if(right->height + right->length + 2 < screen->height)
		{
			right->height++;
		}
	}
	else if(input == '0')
	{
		if(right->height > 0)
		{
			right->height--;
		}
	}
}

void
start_gameplay
	(struct screen *game_screen,
	struct appearance *left_player,
	struct appearance *right_player,
	int delay)
{
	struct timeval this_frame, prev_frame;
	gettimeofday(&prev_frame, NULL);

	int total_delayed;

	while(1)
	{
		gettimeofday(&this_frame, NULL);

		int input = 0;
		if(_kbhit())
		{
			input = fgetc(stdin);
			if(input == 127) /* delete key */
			{
				break;
			}
		}

		int diff = (this_frame.tv_usec - prev_frame.tv_usec)
			+ (this_frame.tv_sec - prev_frame.tv_sec) * 1000000;

		total_delayed += diff;

		if(total_delayed > delay)
		{
			calculate_frame(diff, input);
			render_player(left, screen, 0);
			render_player(right, screen, 1);
			system("clear");
			render_screen_matrix(game_screen);
			total_delayed = 0;
		}

		gettimeofday(&prev_frame, NULL);
	}

	return;
}

void
render_player
	(struct player *player,
	struct screen *screen,
	int side)
{
	set_screen_index
		(screen,
		player->height,
		side * (screen->width - 1),
		player->look->top_char);

	for
		(int i = player->height + 1;
		i < player->height + player->length + 1;
		i++)
	{
		set_screen_index
			(screen, 
			i,
			side * (screen->width - 1),
			player->look->middle_char);
	}

	set_screen_index
		(screen,
		player->height + player->length + 1,
		side * (screen->width - 1),
		player->look->bottom_char);

	return;
}
