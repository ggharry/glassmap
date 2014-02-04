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

float _dest_to_current_angle = 0.0f;
float _current_angle = 0.0f;
float _destination_angle = 0.0f;

float DISPLAY_INTERVAL = 200;
int READ_COMPASS_INTERVAL = 200;

float _width = 0.05f;
float _length = 2.0f;
Coord _head = {0.0f, 0.0f, -_length/2};
Coord _tail1 = {-_width, _width, _length/2};
Coord _tail2 = {-_width, -_width, _length/2};
Coord _tail3 = {_width, _width, _length/2};
Coord _tail4 = {_width, -_width, _length/2};
Coord _offset = {0.0f, -0.5f, -5.0f};

void handleKeypress(unsigned char key, int x, int y);
void handleResize(int w, int h);
void plotPoint(Coord point, Coord offset);
Coord rotateAlongY(Coord point, float angle);
void drawScene();
void update(int value);
float dest_relative_to_current(float dest, float current);
int main(int argc, char** argv);


