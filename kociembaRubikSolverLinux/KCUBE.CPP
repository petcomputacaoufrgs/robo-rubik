// kcube.cpp - Kociemba Cube Solver main program
//
// This program implements an algorithm devised by Herbert
// Kociemba to solve Rubik's Cube.
//
// This program was written for educational purposes and
// may be freely distributed provided this header remains
// intact.  The author assumes no responsibility for its
// use.
//
#include "SOLVER.H"     // Solver
#include "KOCICUBE.H"	// KociembaCube
#include "FACECUBE.H"	// FaceletCube
#include "CUBEPARS.H"	// CubeParser

#include <stdlib.h>     // For exit()
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <unistd.h>

#include "CubeView.h"
//
// Command line format:
//
// >cube FaceSpecifier1, FaceSpecifier2, ... FaceSpecifier6
//
// where each face specifier is of the form f:mmmmmmmmm
//
// and f (face) must be one of {U,D,F,B,L,R} and m (marker)
// can be any printable ASCII character.  Grasp the left or
// right side of the cube with one hand and rotate it so that
// the face under consideration is in front of you.  The order
// of the markers is left-to-right, top-to-bottom with respect
// to each face.  For example, consider the following "unfolded"
// cube:
//              Red Red Wht
//              Yel Wht Wht
//              Wht Red Red
//
// Wht Wht Grn  Org Yel Yel  Blu Red Org  Yel Grn Grn
// Red Org Org  Yel Yel Yel  Blu Red Org  Blu Grn Blu
// Yel Wht Grn  Org Wht Org  Yel Blu Blu  Red Grn Red
//
//              Blu Org Blu
//              Grn Blu Grn
//              Wht Org Grn
//
// With the faces above corresponding to:
//
//      Up
// Left Front Right Back
//      Down
//
// Then one possible way to enter this configuration is:
//
// >cube L:WWGROOYWG R:BROBROYBB U:RRWYWWWRR D:BOBGBGWOG F:OYYYYYOWO B:YGGBGBRGR
//
// Note: that the choice of marker characters is completely
// arbitrary, one must only use them consistently within
// any given cube configuration specification.  Also, the
// order of each face specification is arbitrary.
//
// When run, the program will first load the move mapping
// and pruning tables (it will regenerate them if not found)
// then perform the search.  Successively shorter solutions
// will be printed out until an optimal solution is found
// (that may take a very long time) and the program terminates,
// or the program is aborted by the user.
//
int cubePos = 0;
FILE *arduinoStream;
void initialRotateCube() {
    switch(cubePos){
        case 0:
            usleep(100000);
        fprintf(arduinoStream,"%c", LEFTTOGGLE); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", RIGHTUP90); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        cubePos++;
        //cin.get();
        //photo(); //orientação certa
        break;
        case 1:
        usleep(100000);
        fprintf(arduinoStream,"%c", RIGHTUP90); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        cubePos++;
        //cin.get();
        //photo(); //orietação invertida
        break;
        case 2:
        usleep(100000);
        fprintf(arduinoStream,"%c", LEFTTOGGLE); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", RIGHTTOGGLE); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", RIGHTDOWN90); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", RIGHTTOGGLE); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", LEFTTOGGLE); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", RIGHTUP90); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        cubePos++;
        //cin.get();
        //photo(); //orientação certa
        break;
        case 3:
        usleep(100000);
        fprintf(arduinoStream,"%c", LEFTTOGGLE); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", RIGHTTOGGLE); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", LEFTUP90); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", RIGHTTOGGLE); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", LEFTTOGGLE); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", LEFTDOWN90); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", RIGHTDOWN90); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        cubePos++;
        //cin.get();
        //photo(); //orientação invertida
        break;
        case 4:
        usleep(100000);
        fprintf(arduinoStream,"%c", RIGHTDOWN90); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", LEFTTOGGLE); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", RIGHTTOGGLE); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", RIGHTUP90); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", RIGHTTOGGLE); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", LEFTTOGGLE); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", RIGHTDOWN90); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        cubePos++;
        //cin.get();
        //photo();; //orientação certa
        break;
        case 5:
        usleep(100000);
        fprintf(arduinoStream,"%c", RIGHTUP90); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", LEFTTOGGLE); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", RIGHTTOGGLE); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", RIGHTDOWN90); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", LEFTUP90); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", RIGHTTOGGLE); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", LEFTTOGGLE); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", LEFTDOWN90); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", LEFTTOGGLE); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", RIGHTTOGGLE); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", RIGHTUP90); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", RIGHTTOGGLE); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", LEFTTOGGLE); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", RIGHTDOWN90); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        fprintf(arduinoStream,"%c", LEFTTOGGLE); //Writing to the file
        fflush(arduinoStream);
        usleep(600000);
        cubePos = 0;
    }
}

int main(int argc, char* argv[])
{

	 CubeView camera;
//    namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
//    int key=0;
//

	if(arduinoStream = fopen("/dev/ttyACM0","w")) {

	    if(true){  //Opening device file
//        cout<< "aperte enter entre cada foto..." << endl;
//        while(key!=27)
//    {
//        camera.updateFrame();
//        key = cv::waitKey(40);
//        if(key != -1)
//            key = key % 256;
//        //printf("%d\n", key);
//        if(key == 'a')
//        {
//            camera.printColors();
//            string tmp = camera.getColors();
//        }
//        else
//        {
//            camera.printRectangles();
//        }
//
//        imshow("MyVideo", *(camera.currentFrame)); //show the frame in "MyVideo" window
//    }
        //photo(); //orientação correta

//aqui go zueira
       }
		unsigned int status;

		// Parse the input and initialize a "FaceletCube".
		// The FaceletCube represents the cube by the markings
		//   of the 54 individual facelets.

		FaceletCube faceletCube;
		CubeParser cubeParser;
		if ((status = cubeParser.ParseInput(argc, argv, faceletCube)) != CubeParser::VALID)
		{
			cout << cubeParser.ErrorText(status) << endl;
			cout << "bla bla bla" << endl;
			exit(1);
		}

		// Validate the facelet representation in terms	of
		//   legal cubie markings, permutation, and parity
		//   and initialize a "standard" cube.  The standard
		//   cube represents the cube state in terms of cubie
		//   permutation and parity.

		KociembaCube cube;
		if ((status = faceletCube.Validate(cube)) != FaceletCube::VALID)
		{
			cout << faceletCube.ErrorText(status) << endl;
			int ok = system("pause");
			exit(ok);
		}

		// Create a solver, initialize the move mapping and
		//   pruning tables, and invoke the search for a
		//   solution.  Since the cube is in a valid configuration
		//   at this point, a solution should always be found.

		Solver solver;
		solver.InitializeTables();
		(void)solver.Solve(cube);
		solver.sendToArduino(solver.Moves, 1, arduinoStream);
    }
	return 0;
}

extern "C"
{
//  __declspec(dllexport) char * SolveRubikCube(const char* cubeAsString)
//  {
//    unsigned int status;
//	char str_argv[7][100], **argv = new char*[7], *pch;
//
//	for(int i=0; i<7; i++)
//		argv[i] = &str_argv[i][0];
//
//	std::strcpy(argv[0],"kcube");
//
//	int argc=1;
//
//	pch = strtok((char*)cubeAsString," ");
//	while (pch != NULL)
//	{
//		std::strcpy(argv[argc],pch);
//		if(argc<=6)
//			argc++;
//		pch = strtok(NULL, " ");
//	}
//
//	FaceletCube faceletCube;
//	CubeParser cubeParser;
//
//	if ((status = cubeParser.ParseInput(argc,argv, faceletCube)) != CubeParser::VALID)
//	{
//		return (char*) "Invalid input";
//	}
//	// Validate the facelet representation in terms	of
//	//   legal cubie markings, permutation, and parity
//	//   and initialize a "standard" cube.  The standard
//	//   cube represents the cube state in terms of cubie
//	//   permutation and parity.
//
//	KociembaCube cube;
//	if ((status = faceletCube.Validate(cube)) != FaceletCube::VALID)
//	{
//		return (char*) "Invalid cube definition";
//	}
//
//	// Create a solver, initialize the move mapping and
//	//   pruning tables, and invoke the search for a
//	//   solution.  Since the cube is in a valid configuration
//	//   at this point, a solution should always be found.
//
//	Solver solver;
//	solver.InitializeTables();
//	solver.Moves = new char[170];
//	for(int i=0; i<170; i++) solver.Moves[i] = 0;
//	(void)solver.Solve(cube);
//	return solver.Moves;
//  }

}
