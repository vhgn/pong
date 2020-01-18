/**
 * 
 * LICENSE: MIT
 * 
 */

#ifndef _RENDERER
#define _RENDERER

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
 * Screen with matrix of pixels
 */
typedef struct screen screen;

/** 
 * Initialize a screen with char[width][height] then fill
 */
screen*
init_screen
	(unsigned width,
	unsigned height,
	char pixel);

/** 
 * Set the screen's [line_num][col_num] to pixel
 */
void
set_screen_index
	(screen *screen_ref,
	unsigned line_num,
	unsigned col_num,
	char pixel);

/** 
 * Get the screen's [line_num][col_num]
 */
char
get_screen_index
	(screen *screen_ref,
	unsigned line_num,
	unsigned col_num);

/** 
 * Render the screen's all characters
 */
void
render_screen_matrix
	(screen *screen_ref);

#endif
