#include "main.h"
#include "compass.cpp"

float DISPLAY_INTERVAL = 100;

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

void plotPoint(Coord point, Coord offset) {
	glVertex3f(point.x + offset.x, point.y + offset.y, point.z + offset.z);
}

Coord rotateAlongY(Coord point, float angle) {
	angle = angle * M_PI / 180;
	Coord result;
	result.y = point.y;
	result.z = point.z * cos(angle) + point.x * sin(angle);
	result.x = point.x * cos(angle) - point.z * sin(angle);
	return result;
}

//Draws the 3D scene
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective

	//glRotatef(-_angle, 0.0f, 0.0f, 1.0f); //Rotate about the z-axis

	Coord head = rotateAlongY(_head, _angle);
	Coord tail1 = rotateAlongY(_tail1, _angle);
	Coord tail2 = rotateAlongY(_tail2, _angle);
	Coord tail3 = rotateAlongY(_tail3, _angle);
	Coord tail4 = rotateAlongY(_tail4, _angle);
	Coord offset = _offset;

	glBegin(GL_TRIANGLES); // Four sides
	
	//Triangle
	plotPoint(head, offset);
	plotPoint(tail1, offset);
	plotPoint(tail3, offset);

	plotPoint(head, offset);
	plotPoint(tail1, offset);
	plotPoint(tail2, offset);

	plotPoint(head, offset);
	plotPoint(tail2, offset);
	plotPoint(tail4, offset);

	plotPoint(head, offset);
	plotPoint(tail3, offset);
	plotPoint(tail4, offset);  

	glEnd();

   	glBegin(GL_QUADS); // Bottom face
    
	plotPoint(tail1, offset);
	plotPoint(tail2, offset);  
	plotPoint(tail3, offset);
	plotPoint(tail4, offset);  
    
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



