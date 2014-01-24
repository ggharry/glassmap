#include <iostream>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <OPENGL/gl.h>
#include <OPENGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

using namespace std;


void handleKeypress(unsigned char key, int x, int y);
void handleResize(int w, int h);
void drawScene();
void update(int value);
int main(int argc, char** argv);


