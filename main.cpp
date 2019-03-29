#include <iostream>
#include <fstream>
#include "functions.h"
using namespace std;

// Normally you should not use global variables. However, the stack is
//   limited in size and will not allow arrays of this size. We'll learn
//   later how to put these arrays on the heap instead. Regardless, for now
//   we'll use these and treat them as if they were declared in main. So
//   when used in functions, we'll pass them as we would any other array.
static int elevations[MAX_ROWS][MAX_COLS];
static Pixel image[MAX_ROWS][MAX_COLS];

int main() {
	ifstream inData;
	int rows,cols,max,min;
	string fileName; 


/**
The statements below tests if appropriate values are entered for the amount of
rows and columns
*/
	cout<<"Enter the number of rows : ";
	cin>>rows;
	if(!cin.good()|| rows<1){
		cout <<"Error: Problem reading in rows and columns. "<< endl;
		return 1;
	}
	cout<<"Enter the number of columns :";
	cin>>cols;
	if(!cin.good()||cols<1){
		cout << "Error: Problem reading in rows and columns. " << endl;
		return 1;
	}

	cin>>fileName;
	inData.open(fileName);
	if (!inData.is_open()) {//checks to see if the file was able to open
		cout << "Error: Unable to open file <"<<fileName<<">" << endl;
		return 1;
	}

	//loads elevation array with integers
	loadData(elevations,rows,cols,inData);
	//the max and min of array is calculated
	findMaxMin(elevations,rows,cols,max,min);
	//elelvation values are converted to RGB values in the Pixel array
	loadGreyscale(image, elevations, rows, cols, max, min);

	Pixel colR = {252,25,63};
	Pixel colG = {31,253,13};
	int path=0;
	int firstDist=colorPath(elevations,image, rows, cols, colR,0);
	for(int i=0;i<rows;i++){
		int total=colorPath(elevations,image, rows, cols, colR,i);
		if(total<firstDist){
			firstDist=total;
			path=i;
		}
	}
	colorPath(elevations,image, rows, cols, colG,path);

	ofstream outData;//ofstream variable declared here
	outData.open(fileName+".ppm");//ofstream opens the file 
	//writes to our ppm file supplying the write info in a given format
	outputImage(image, rows, cols, outData);
}