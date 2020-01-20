/**
 * 
 * LICENSE: MIT
 * 
 */

#ifndef _PREFLOAD
#define _PREFLOAD

#define MAX_TOKENS 16

/**
 * Player appearance
 */
struct
appearance
{
	/**
	 * Top character of the player
	 */
	char top_char;

	/**
	 * Middle characters of the player
	 */
	char middle_char;

	/**
	 * Bottom character of the player
	 */
	char bottom_char;

	/**
	 * Length of middle characters
	 */ 
	unsigned length;
};

/**
 * Get preferences of player[index]
 */
struct appearance*
get_player_prefs
	(unsigned index);

/**
 * Load file by name and return content
 */
char*
load_file
	(char *file_name);

#endif
