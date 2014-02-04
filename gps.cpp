#include "gps.h"

float read_direction(string filename) {
	string line;
	ifstream direction_file (filename.c_str());
	getline(direction_file, line);
	direction_file.close();	
	
	float direction;
	char *ptr = (char*)line.c_str();
	direction = strtof (ptr, NULL);
	return direction;
}
