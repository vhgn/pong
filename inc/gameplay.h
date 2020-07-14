#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "prefload.h"
#include "renderer.h"

#define INITIAL_SPEED 0.5

/**
 * Player object with position and look
 */
struct player {
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

struct ball {
  /**
   * Position of the ball
   */
  double pos_x, pos_y;

  /**
   * Velocity of the ball
   */
  double vel_x, vel_y;
};

struct screen *screen;
struct player *left;
struct player *right;
struct ball *ball;

/**
 * Calculate coordinates using delta and input
 */
int calculate_frame(int delta, char input);

/**
 * Start game loop with artificial delay for stable fps
 */
void start_gameplay(struct screen *game_screen, struct appearance *left_player,
                    struct appearance *right_player, int delay);

/**
 * Render player with given properties
 */
void render_player(struct player *player, struct screen *screen, int side);

/**
 * Render ball on screen
 */
void render_ball(struct ball *ball, struct screen *screen);

#endif /* GAMEPLAY_H*/
