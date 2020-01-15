#include "draw.h"

GLfloat ambient_coeffs_red[] 	= {0.2,0,0,1};
GLfloat diffuse_coeffs_red[] 	= {1,0,0,1};
GLfloat ambient_coeffs_gray[]   = {0,0,0,1};
GLfloat diffuse_coeffs_gray[]	= {0.7,0.7,0.7,1};
GLfloat ambient_coeffs_dblue[] 	= {0,0,0.2,1};
GLfloat diffuse_coeffs_dblue[] 	= {0,0,0.6,1};
GLfloat ambient_coeffs_blue[] 	= {0,0,0.2,1};
GLfloat diffuse_coeffs_blue[] 	= {0,0,1,1};
GLfloat ambient_coeffs_green[] 	= {0,0.2,0,1};
GLfloat diffuse_coeffs_green[] 	= {0,1,0,1};
GLfloat ambient_coeffs_yellow[] = {0,0,0,1};
GLfloat diffuse_coeffs_yellow[]	= {1,1,0,1};



void draw_arena(void){
	int i,j;

	//move count and level text
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs_red);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs_red);
	text();
	
	//grid draw
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs_gray);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs_gray);
	glBegin(GL_LINES);
		for(i = 0; i <= 10; i++){
			glVertex3f(i * 50, 0, 0);
        		glVertex3f(i * 50, 0, -500);
			glVertex3f(0, 0, i * (-50));
        		glVertex3f(500, 0, i * (-50));
		}
   	glEnd();

	//arena draw
	for(i = 0; i < 10; i++){
		for(j = 0; j < 10; j++){
			if(arena[level][i][j] == 9){
				glPushMatrix();
				glTranslatef(i * 50, 0, j * (-50));
				draw_fixed_block();
				glPopMatrix();
			}
			if(arena[level][i][j] == 2 || arena[level][i][j] == 3 
			|| arena[level][i][j] == 4 || arena[level][i][j] == 6){
				glPushMatrix();
				glTranslatef(i * 50, 0, j * (-50));
				if(arena[level][i][j] == 2) draw_box(0);
				else if(arena[level][i][j] == 4 ) draw_box(2);
				else if(arena[level][i][j] == 6 && box_same_color == 1) draw_box(3);
				else draw_box(1);
				glPopMatrix();
			}
			if(arena[level][i][j] == 5 || arena[level][i][j] == 6){
				glPushMatrix();
				glTranslatef(i * 50, 0, j * (-50));
				draw_spot();
				glPopMatrix();
			}
		}
	}
}



// blue box draw, green on right spot
void draw_box(int x){
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs_dblue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs_dblue);

	if(x == 2 || x == 3){
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs_green);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs_green);
	}
	glPushMatrix();
	
	if(x == 1 || x == 3){
		switch(move){
			case 1 : glTranslatef(animation_parameter, 0, 0); break;
			case 2 : glTranslatef(0, 0, animation_parameter);  break;
			case 3 : glTranslatef(-animation_parameter, 0, 0);  break;
			case 4 : glTranslatef(0, 0,-animation_parameter);  break;
		}
	}
	glTranslatef(25, 26, -25);
	glutSolidCube(49);
	glPopMatrix();

}
// right spot
void draw_spot(void){

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs_yellow);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs_yellow);
	
	glPushMatrix();
	glBegin(GL_QUADS);
		
		glNormal3f(0, 1, 0);

		glVertex3f(1, 1, -1);
		glVertex3f(1, 1, -49);
		glVertex3f(49, 1, -49);
		glVertex3f(49, 1, -1);
	glEnd();
	glPopMatrix();
}

//walls
void draw_fixed_block(void){
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs_gray);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs_gray);
	//front
	glBegin(GL_QUADS);
		glNormal3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 20, 0);
		glVertex3f(50, 20, 0);
		glVertex3f(50, 0, 0);
	glEnd();
	//left
	glBegin(GL_QUADS);
		glNormal3f(-1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 20, 0);
		glVertex3f(0, 20, -50);
		glVertex3f(0, 0, -50);
	glEnd();
	//back
	glBegin(GL_QUADS);
		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, -50);
		glVertex3f(0, 20, -50);
		glVertex3f(50, 20, -50);
		glVertex3f(50, 0, -50);
	glEnd();
	//right
	glBegin(GL_QUADS);
		glNormal3f(1, 0, 0);
		glVertex3f(50, 0, 0);
		glVertex3f(50, 20, 0);
		glVertex3f(50, 20, -50);
		glVertex3f(50, 0, -50);
	glEnd();
	//top
	glBegin(GL_QUADS);
		glNormal3f(0, 1, 0);
		glVertex3f(0, 20, 0);
		glVertex3f(0, 20, -50);
		glVertex3f(50, 20, -50);
		glVertex3f(50, 20, 0);
	glEnd();

}



//caracter
void draw_character(void){

	
	glPushMatrix();
	switch(move){
		case 1 : glTranslatef(x_player_position * 50 + animation_parameter, 0, z_player_position * 50); break;
		case 2 : glTranslatef(x_player_position * 50, 0, z_player_position * 50 + animation_parameter); break;
		case 3 : glTranslatef(x_player_position*50 - animation_parameter, 0, z_player_position * 50); break;
		case 4 : glTranslatef(x_player_position * 50, 0, z_player_position * 50 - animation_parameter); break;
		default : glTranslatef(x_player_position * 50, 0, z_player_position * 50); break;
	}
	
	//rotation
	
	glTranslatef(25, 0, -25);
	glRotatef(direction, 0, 1, 0);
	glTranslatef(-11, 0, 5);

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs_red);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs_red);
	

	//legs
	glTranslatef(0, 30, -5);	
	glRotatef(animation_moving * 10, 1, 0, 0);
	glTranslatef(0, -30, 5);
	
	glBegin(GL_QUADS);
		glNormal3f(-1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 30, 0);
		glVertex3f(0, 30, -10);
		glVertex3f(0, 0, -10);
		
		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, -10);
		glVertex3f(0, 30, -10);
		glVertex3f(10, 30, -10);
		glVertex3f(10, 0, -10);

		glNormal3f(1, 0, 0);
		glVertex3f(10, 0, -10);
		glVertex3f(10, 30, -10);
		glVertex3f(10, 30, 0);
		glVertex3f(10, 0, 0);

		glNormal3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 30, 0);
		glVertex3f(10, 30, 0);
		glVertex3f(10, 0, 0);
	glEnd();
	glTranslatef(0,	30,	-5);
	glRotatef(-animation_moving * 20, 1, 0, 0);
	glTranslatef(0, -30, 5);

	glTranslatef(12, 0, 0);
	glBegin(GL_QUADS);
		glNormal3f(-1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 30, 0);
		glVertex3f(0, 30, -10);
		glVertex3f(0, 0, -10);
		
		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, -10);
		glVertex3f(0, 30, -10);
		glVertex3f(10, 30, -10);
		glVertex3f(10, 0, -10);

		glNormal3f(1, 0, 0);
		glVertex3f(10, 0, -10);
		glVertex3f(10, 30, -10);
		glVertex3f(10, 30, 0);
		glVertex3f(10, 0, 0);

		glNormal3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 30, 0);
		glVertex3f(10, 30, 0);
		glVertex3f(10, 0, 0);
	glEnd();
	glTranslatef(-12, 30, -5);
	glRotatef(animation_moving * 10, 1, 0, 0);
	glTranslatef(12, -30, 5);

	//body

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs_blue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs_blue);
	
	glTranslatef(-12, 30, 2);
	glBegin(GL_QUADS);
		glNormal3f(0, -1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, -14);
		glVertex3f(22, 0, -14);
		glVertex3f(22, 0, 0);

		glNormal3f(-1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 20, 0);
		glVertex3f(0, 20, -14);
		glVertex3f(0, 0, -14);
		
		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, -14);
		glVertex3f(0, 20, -14);
		glVertex3f(22, 20, -14);
		glVertex3f(22, 0, -14);

		glNormal3f(1, 0, 0);
		glVertex3f(22, 0, -14);
		glVertex3f(22, 20, -14);
		glVertex3f(22, 20, 0);
		glVertex3f(22, 0, 0);
		
		glNormal3f(0, 0, 1);
		glVertex3f(22, 0, 0);
		glVertex3f(22, 20, 0);
		glVertex3f(0, 20, 0);
		glVertex3f(0, 0, 0);

		glNormal3f(0, 1, 0);
		glVertex3f(0, 20, 0);
		glVertex3f(0, 20, -14);
		glVertex3f(22, 20, -14);
		glVertex3f(22, 20, 0);
	glEnd();
	
	//head
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs_yellow);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs_yellow);

	glTranslatef(11, 26, -7);
	glutSolidSphere(8, 30, 30);	

	//arms
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs_blue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs_blue);
	
	glTranslatef(11, -8, 3);
	if(push == 1)
		glRotatef(-90, 1, 0, 0);
	glBegin(GL_QUADS);
		
		glNormal3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, -8);
		glVertex3f(5, 0, -8);
		glVertex3f(5, 0, 0);	

		glNormal3f(-1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, -8);
		glVertex3f(0, -25, -8);
		glVertex3f(0, -25, 0);

		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, -8);
		glVertex3f(5, 0, -8);
		glVertex3f(5, -25, -8);
		glVertex3f(0, -25, -8);

		glNormal3f(1, 0, 0);
		glVertex3f(5, 0, -8);
		glVertex3f(5, -25, -8);
		glVertex3f(5, -25, 0);
		glVertex3f(5, 0, 0);

		glNormal3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(5, 0, 0);
		glVertex3f(5, -25, 0);
		glVertex3f(0, -25, 0);

	glEnd();
	glTranslatef(-27, 0, 0);
	glBegin(GL_QUADS);

		glNormal3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, -8);
		glVertex3f(5, 0, -8);
		glVertex3f(5, 0, 0);	

		glNormal3f(-1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, -8);
		glVertex3f(0, -25, -8);
		glVertex3f(0, -25, 0);

		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, -8);
		glVertex3f(5, 0, -8);
		glVertex3f(5, -25, -8);
		glVertex3f(0, -25, -8);

		glNormal3f(1, 0, 0);
		glVertex3f(5, 0, -8);
		glVertex3f(5, -25, -8);
		glVertex3f(5, -25, 0);
		glVertex3f(5, 0, 0);

		glNormal3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(5, 0, 0);
		glVertex3f(5, -25, 0);
		glVertex3f(0, -25, 0);
		
	glEnd();
	glPopMatrix();
}

//text draw
void text() {

	int i;
	char s[] = "Level:";
	char s1[] = "Moves:";
	char str[10];

	sprintf(str, "%d", move_count);
	strcat(s1, str);
	sprintf(str, "%d", level);
	strcat(s, str);
	strcat(s, " ");

	glPushMatrix();
	glTranslatef(-30, 0, -600);
	glScalef(0.5, 0.5, 0.5);
	for ( i = 0; s[i] != '\0'; i++ ) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, s[i]);
	}
	for ( i = 0; s1[i] != '\0'; i++ ) {
      		glutStrokeCharacter(GLUT_STROKE_ROMAN, s1[i]);
	}
	glPopMatrix();
}
