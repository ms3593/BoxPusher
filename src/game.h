#ifndef _H_GAME_H_
#define _H_GAME_H_

#include <math.h>
#include <GL/glut.h>
#include <string.h>
#include "draw.h"


int level;	//current level
int move;	//move direction
int move_count;	//move counter
int push;	//indicator of player pushing box
int box_same_color; //box color dependin on position
int direction;	//character direction
int animation_active; 
int animation_parameter;
int animation_moving;
int animation_moving_phase;
int x_player_position;	// x position of character
int z_player_position;	// y position of character

int arena[10][10][10]; //arena [level][x][y]

void initialize_light();
void initialize();
void on_keyboard(unsigned char key, int x, int y);
void on_reshape(int width, int height);
void on_timer(int value);
void on_display(void);
int level_finished();
void next_level();
void restart();
int next_move(int right, int down, int left, int up);

#endif
