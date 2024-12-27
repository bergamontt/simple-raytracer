//#include <iostream>
//#include <fstream>
//#include "canvas.h"
//#include "const_colors.h"
//
//using namespace std;
//
//int main(void) {
//	ofstream outputFile("test.ppm");
//
//	if (!outputFile.is_open())
//		return 1;
//
//	Canvas canvas(20, 20);
//	canvas.writePixel(5, 5, RED);
//	canvas.writePixel(5, 6, RED);
//	canvas.writePixel(5, 7, RED);
//	canvas.writePixel(5, 8, RED);
//	
//	outputFile << canvas.toPPM();
//
//}