#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>

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

typedef struct {
  float x;
  float y;
  float z;
} Coord;

Coord _current_angle = {0.0f, 0.0f, 0.0f};

float DISPLAY_INTERVAL = 200;
int READ_COMPASS_INTERVAL = 200;

float _side = 0.3f;
Coord _tail1 = {_side, _side, -_side};
Coord _tail2 = {_side, -_side, -_side};
Coord _tail3 = {_side, -_side, _side};
Coord _tail4 = {_side, _side, _side};
Coord _tail5 = {-_side, _side, -_side};
Coord _tail6 = {-_side, -_side, -_side};
Coord _tail7 = {-_side, -_side, _side};
Coord _tail8 = {-_side, _side, _side};

Coord _offset = {0.0f, -0.5f, -5.0f};

void handleKeypress(unsigned char key, int x, int y);
void handleResize(int w, int h);
void plotPoint(Coord point, Coord offset);
Coord rotateAlongXYZ(Coord point, Coord angle);
void drawScene();
void update(int value);
int main(int argc, char** argv);


