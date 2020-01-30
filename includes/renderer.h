/**
 * 
 * LICENSE: MIT
 * 
 */

#ifndef _RENDERER_H
#define _RENDERER_H

/**
 * Screen with matrix of pixels
 */
struct
screen
{
	/**
	 * Width of the matrix
	 */
	unsigned width;

	/**
	 * Height of the matrix
	 */
	unsigned height;

	/**
	 * Matrix of chacaters
	 */
	char *matrix;
};

/**
 * Initialize a screen with char[width][height] then fill
 */
struct screen*
init_screen
	(unsigned width,
	unsigned height,
	char pixel);

/**
 * Clear the screen filling with specified pixels
*/
void
clear_screen
	(struct screen *screen,
	char pixel);

/**
 * Set the screen's [line_num][col_num] to pixel
 */
void
set_screen_index
	(struct screen *screen_ref,
	unsigned line_num,
	unsigned col_num,
	char pixel);

/**
 * Get the screen's [line_num][col_num]
 */
char
get_screen_index
	(struct screen *screen_ref,
	unsigned line_num,
	unsigned col_num);

/**
 * Render the screen's all characters
 */
void
render_screen_matrix
	(struct screen *screen_ref);

/**
 * Exits program and resets terminal attributes
 */
void
exit_renderer
	(void);

#endif
