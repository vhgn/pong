/**
 * 
 * LICENSE: MIT
 * 
 */

#ifndef _GAMEPLAY
#define _GAMEPLAY

#include "renderer.h"
#include "prefload.h"

/**
 * Player object with position and look
 */
struct
player
{
	/**
	 * Y coordinate of the top character
	 */
	unsigned height;

	/**
	 * Count of middle characters
	 */
	unsigned length;

	/**
	 * Appearance of the player
	 */
	struct appearance *look;
};

struct screen *screen;
struct player *left;
struct player *right;

/**
 * Calculate coordinates using delta and input
 */
void
calculate_frame
	(int delta,
	int input);

/**
 * Start game loop with artificial delay for stable fps
 */
void
start_gameplay
	(struct screen *game_screen,
	struct appearance *left_player,
	struct appearance *right_player,
	int delay);

/**
 * Render player with given properties
 */
void
render_player
	(struct player *player,
	struct screen *screen,
	int side);

#endif
