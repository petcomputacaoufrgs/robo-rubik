CVLIBS = -lopencv_core -lopencv_highgui

SRC_PATH = ./src
OBJ_PATH = ./obj
SOURCES = ./src/CameraView.cpp ./src/CubeView.cpp ./src/CubeSquare.cpp
OBJECTS = ./obj/CameraView.o ./obj/CubeView.o ./obj/CubeSquare.o

INCLUDES = -I include
MAINFILE = main.cpp

CC = g++
CFLAGS = -Wall

rubikcv:
	$(CC) $(MAINFILE) $(OBJ_PATH)/*.o $(CVLIBS) $(CFLAGS) -o rubikcv.out
debug:
	$(CC) -g $(MAINFILE) $(SRC_PATH)/*.cpp $(CVLIBS) $(CFLAGS) -o debug.out
cameraview:
	$(CC) $(SRC_PATH)/CameraView.cpp -c -o $(OBJ_PATH)/CameraView.o $(CVLIBS) $(CFLAGS)
cubeview:
	$(CC) $(SRC_PATH)/CubeView.cpp -c -o $(OBJ_PATH)/CubeView.o $(CVLIBS) $(CFLAGS)
cubesquare: 
	$(CC) $(SRC_PATH)/CubeSquare.cpp -c -o $(OBJ_PATH)/CubeSquare.o $(CVLIBS) $(CFLAGS)
clean:
	rm -f $(OBJECTS) *.out 
