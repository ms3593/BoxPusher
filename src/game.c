#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "game.h"

/* lightings and meterials */
void initialize_light(){
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat light_position[] = {0.1, 0, 1, 0};
	GLfloat light_ambient[]	= {0.1, 0.1, 0.1, 1};
	GLfloat light_diffuse[]	= {1, 1, 1, 1};
	GLfloat light_specular[] = {0.8, 0.8, 0.8, 1};
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	GLfloat shiness = 20;
	glMaterialf(GL_FRONT, GL_SHININESS, shiness);	
}

/* initialization of callback functions and variales */
void initialize(){
	glutKeyboardFunc(on_keyboard);
	glutReshapeFunc(on_reshape);
	glutDisplayFunc(on_display);
	
	level = 1;
	move = 0;
	move_count = 0;
	push = 0;
	box_same_color = 0;
	direction = 0;
	animation_active = 0;
	animation_moving = 0;
	animation_parameter = 0;
	animation_moving_phase = 0;

	/* drawing arena from file */
	FILE *fajl;

	if ((fajl = fopen("ulaz.txt", "r")) == NULL){
		printf("Error! opening file");
		exit(1);         
	}
	int i, j, z;
	for(z=1; z<3; z++){
		for(i=0; i<10; i++){
			for(j=0; j<10; j++){
				fscanf(fajl, "%d", &arena[z][i][j]);
				
				if(arena[level][i][j] == 1){
					x_player_position = i;
					z_player_position = -j;
					arena[level][i][j] = 0;
				}
			}
		}
	}
}

/* keyboard inputs */
void on_keyboard(unsigned char key, int x, int y){
	switch (key) {
	case 27:
		/* close the game */
		exit(0);
		break;
	/* character movements */
 	case 'd':
   	case 'D':
		if(!animation_active && next_move(1,0,0,0)){
			animation_active = 1;
			move = 1;
			move_count++;
			direction = 90;
			glutTimerFunc(25, on_timer, 0);		
		}
       	break;
	case 's':
   	case 'S':
        if(!animation_active && next_move(0,1,0,0)){
			animation_active = 1;
			move = 2;
			move_count++;
			direction = 0;
			glutTimerFunc(25, on_timer, 0);		
		}
       	break;
	
	case 'a':
   	case 'A':
        if(!animation_active && next_move(0,0,1,0)){
			animation_active = 1;
			move = 3;
			move_count++;
			direction = -90;
			glutTimerFunc(25, on_timer, 0);
		}
       	break;
	
	case 'w':
   	case 'W':
        if(!animation_active && next_move(0,0,0,1)){
			animation_active=1;
			move=4;
			move_count++;
			direction = 180;
			glutTimerFunc(25, on_timer, 0);
		}
       	break;
	/* level reset */
	case 'r':
   	case 'R':
		if(!animation_active){
        	restart();
			glutTimerFunc(25, on_timer, 0);
		}
       	break;
	}
}



void on_timer(int value){
	if (value != 0)
        return;
	animation_parameter += 5;

	/* legs animation */
	if(animation_moving_phase == 0)
		animation_moving++;
	else animation_moving--;

	if(animation_moving >= 3) 
		animation_moving_phase = 1;
	if(animation_moving <= -3)
		animation_moving_phase = 0;	
	
	/* end of step, animation stops and we check what should we draw and current and spot before step */
	if(animation_parameter > 50){
		animation_active = 0;
		animation_parameter = 0;
		animation_moving_phase = 0;
		animation_moving = 0;
		
		switch(move){
			case 1 : x_player_position += 1;
				 if(push){
					if(arena[level][x_player_position][z_player_position*(-1)] == 6)
						arena[level][x_player_position][z_player_position*(-1)] = 5;
					else arena[level][x_player_position][z_player_position*(-1)] = 0;
					if(arena[level][x_player_position+1][z_player_position*(-1)] == 5)
						arena[level][x_player_position+1][z_player_position*(-1)] = 4;
					else arena[level][x_player_position+1][z_player_position*(-1)] = 2;					
				}			
				break;
			case 2 : z_player_position += 1;
				if(push){
					if(arena[level][x_player_position][z_player_position*(-1)] == 6)
						arena[level][x_player_position][z_player_position*(-1)] = 5;
					else arena[level][x_player_position][z_player_position*(-1)] = 0;
					if(arena[level][x_player_position][(z_player_position+1)*(-1)] == 5)
						arena[level][x_player_position][(z_player_position+1)*(-1)] = 4;
					else arena[level][x_player_position][(z_player_position+1)*(-1)] = 2;				
				}
				break;
			case 3 : x_player_position -= 1;
				if(push){
					if(arena[level][x_player_position][z_player_position*(-1)] == 6)
						arena[level][x_player_position][z_player_position*(-1)] = 5;
					else arena[level][x_player_position][z_player_position*(-1)] = 0;
					if(arena[level][x_player_position-1][z_player_position*(-1)] == 5)
						arena[level][x_player_position-1][z_player_position*(-1)] = 4;
					else arena[level][x_player_position-1][z_player_position*(-1)] = 2;					
				}
				break;
			case 4 : z_player_position -= 1;
				if(push){
					if(arena[level][x_player_position][z_player_position*(-1)] == 6)
						arena[level][x_player_position][z_player_position*(-1)] = 5;
					else arena[level][x_player_position][z_player_position*(-1)] = 0;
					if(arena[level][x_player_position][(z_player_position-1)*(-1)] == 5)
						arena[level][x_player_position][(z_player_position-1)*(-1)] = 4;
					else arena[level][x_player_position][(z_player_position-1)*(-1)] = 2;				
				}
				break;
		}
		
		move = 0;
		next_level();
		push = 0;
		box_same_color = 0;
		glutPostRedisplay();
	 	return;
	}

	glutPostRedisplay();
	/* if its not end of the move animation continues */
	if (animation_active){
	if(push==1) glutTimerFunc(50, on_timer, 0);
       	else glutTimerFunc(25, on_timer, 0);
	}
}


// checking if next move is possible and setting values of arena fields.
//0-empty spot
//2-box
//3-player pushing box
//4-box on right spot
//5-spot for box
//6-player pushing box on right spot

int next_move(int right,int down, int left, int up){
	
	int x = x_player_position + right - left;
	int z = (z_player_position-up + down)*(-1);

	// if field is empty, player moves there
	if(arena[level][x][z] == 0 || arena[level][x][z] == 5) 
		return 1;

	/* if there is a box on field, and next field is empty or spot, player push a box */
	else if((arena[level][x][z] == 2 || arena[level][x][z] == 4) 
	&& (arena[level][x + right - left][z - down + up] == 0 
	|| arena[level][x + right - left][z - down + up] == 5)){
		if(arena[level][x][z] == 2)
			arena[level][x][z] = 3;
		else arena[level][x][z] = 6;

		if(arena[level][x + right - left][z - down + up] == 5)
			box_same_color = 1;
		push = 1;
		return 1; 
	}

	return 0;
}

// if all boxes are on their places level ends.
int level_finished(){
	int i, j;
	for(i = 0; i < 10; i++){
		for(j = 0; j < 10; j++){
			if(arena[level][i][j] == 2 || arena[level][i][j] == 3 || arena[level][i][j] == 6) return 0;
		}
	}
	return 1;
}

// load next level
void next_level(){
	if(level_finished()){
		if(level < 2){
			int i,j;
			level++;
			move_count = 0;
				for(i = 0; i < 10; i++){
					for(j = 0; j < 10; j++){
						if(arena[level][i][j]==1){
							x_player_position=i;
							z_player_position=-j;
							arena[level][i][j]=0;
						}
					}
				}
		}
	}
}

void restart(){
	initialize();
}

/* draw screen and setting up camera */
void on_display(void){
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(350, 450, 350, 250, 0, -250, 0, 1, 0);

	draw_character();
	draw_arena();

	glutSwapBuffers();
}

/* window reshape */
void on_reshape(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float) width / height, 1, 1500);
}

