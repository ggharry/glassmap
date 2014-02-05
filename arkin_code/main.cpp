#include "main.h"
#include "compass.cpp"

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


/*
 * We rotate the point clockwise by angle in the following plane
 * ------->x
 * |
 * |
 * |
 * |
 * z
 */
Coord rotateAlongY(Coord point, float angle) {
	angle = angle * M_PI / 180;
	Coord result;
	result.y = point.y;
	result.z = point.z * cos(angle) + point.x * sin(angle);
	result.x = point.x * cos(angle) - point.z * sin(angle);
	return result;
}

/* clockwise rotation */
Coord rotateAlongZ(Coord point, float angle) {
	angle = angle * M_PI / 180;
	Coord result;
	result.z = point.z;
	result.x = point.x * cos(angle) + point.y * sin(angle);
	result.y = point.y * cos(angle) - point.x * sin(angle);
	return result;
}

/* clockwise rotation */
Coord rotateAlongX(Coord point, float angle) {
	angle = angle * M_PI / 180;
	Coord result;
	result.x = point.x;
	result.y = point.y * cos(angle) + point.z * sin(angle);
	result.z = point.z * cos(angle) - point.y * sin(angle);
	return result;
}


Coord rotateAlongXYZ(Coord point, Coord angle) {
	Coord result;
	//angle = {45.0f, 0.0f, 0.0f};
	result = rotateAlongX(point, -angle.x);
	result = rotateAlongY(result, -angle.y);
	result = rotateAlongZ(result, -angle.z);
	return result;
}

/* 
 * Given the destination angle (clockwise to North) and the current angle
 * (clockwise to North), find the angle of destination relative to
 * the current angle (clockwise)
 */
float dest_relative_to_current(float dest, float current) {
	return 360 - dest - current;
	
}

//Draws the 3D scene
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
	
	Coord tail1 = rotateAlongXYZ(_tail1, _current_angle);
	Coord tail2 = rotateAlongXYZ(_tail2, _current_angle);
	Coord tail3 = rotateAlongXYZ(_tail3, _current_angle);
	Coord tail4 = rotateAlongXYZ(_tail4, _current_angle);
	Coord tail5 = rotateAlongXYZ(_tail5, _current_angle);
	Coord tail6 = rotateAlongXYZ(_tail6, _current_angle);
	Coord tail7 = rotateAlongXYZ(_tail7, _current_angle);
	Coord tail8 = rotateAlongXYZ(_tail8, _current_angle);
	Coord offset = _offset;

			
   	glBegin(GL_QUADS); // Bottom face
    
	glColor4f(0,0,1,1);
	plotPoint(tail1, offset);
	plotPoint(tail2, offset);  
	plotPoint(tail3, offset);
	plotPoint(tail4, offset);
	
	glColor4f(0,1,0,1);
	plotPoint(tail5, offset);
	plotPoint(tail6, offset);  
	plotPoint(tail7, offset);
	plotPoint(tail8, offset);  
	
	glColor4f(0,1,1,1);
	plotPoint(tail1, offset);
	plotPoint(tail2, offset);  
	plotPoint(tail5, offset);
	plotPoint(tail6, offset);  
    
	glColor4f(1,0,0,1);
	plotPoint(tail1, offset);
	plotPoint(tail4, offset);  
	plotPoint(tail5, offset);
	plotPoint(tail8, offset);  
	
	glColor4f(1,0,1,1);
	plotPoint(tail2, offset);
	plotPoint(tail3, offset);  
	plotPoint(tail6, offset);
	plotPoint(tail7, offset); 
	
	glColor4f(1,1,0,1);
	plotPoint(tail3, offset);
	plotPoint(tail4, offset);  
	plotPoint(tail7, offset);
	plotPoint(tail8, offset);  
	
	glEnd(); 
	
	glutSwapBuffers();
}



void update(int value) {
	glutPostRedisplay(); //Tell GLUT that the display has changed
	
	//Tell GLUT to call update again in DISPLAY_INTERVAL milliseconds
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



