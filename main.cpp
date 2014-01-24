#include "main.h"
#include "compass.cpp"

float DISPLAY_INTERVAL = 40;

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
	}
}

//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
}

//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

float _cameraAngle = 0.0f;

//Draws the 3D scene
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective

	glRotatef(-_angle, 0.0f, 0.0f, 1.0f); //Rotate about the z-axis

	glBegin(GL_TRIANGLES);
	
	//Triangle
	glVertex3f(0.3f, -0.5f, -3.0f);
	glVertex3f(0.0f, 0.5f, -2.85f);
	glVertex3f(-0.3f, -0.5f, -3.0f);

	//Triangle
	glVertex3f(0.3f, -0.5f, -2.7f);
	glVertex3f(0.0f, 0.5f, -2.85f);
	glVertex3f(-0.3f, -0.5f, -2.7f);
	
	glEnd();
	
	glutSwapBuffers();
}



void update(int value) {
	glutPostRedisplay(); //Tell GLUT that the display has changed
	
	//Tell GLUT to call update again in 25 milliseconds
	glutTimerFunc(DISPLAY_INTERVAL, update, 0);
}


int main(int argc, char** argv) {

	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	
	//Create the window
	glutCreateWindow("Transformations and Timers - videotutorialsrock.com");
	initRendering();
	
	//Set handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);

	glutTimerFunc(DISPLAY_INTERVAL, update, 0); //Add a timer

	spatial_simple();	
	
	glutMainLoop();
	return 0;
}



