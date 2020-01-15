#include <GL/glut.h>
#include "game.h"

int main(int argc, char **argv){
	
	/*GLUT initialization. */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

	/* creating new window */
	glutInitWindowSize(900, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(argv[0]);

	glClearColor(1, 1, 1, 0);
	glEnable(GL_DEPTH_TEST);

	/* game initialize */
	initialize_light();
	initialize();

	glutMainLoop();

	return 0;
}















