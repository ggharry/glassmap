all:
	g++ main.cpp -o glassmap -lX11 -lglut -lGL -lGLU -lm -lphidget21

mac: 
	g++ -Wall main.cpp -o glassmap -framework OpenGL -framework GLUT -framework Phidget21 -I/Library/Frameworks/Phidget21.framework/Headers

rm:
	rm glassmap

run:
	sudo ./glassmap
