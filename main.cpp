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
	ofstream outData;
	int rows,cols;
	string fileName; 
 	int min=elevations[0][0];
	int max=elevations[0][0];

	cin>>rows;
	if(!cin||rows<0){
		cout << "Incorrect input" << endl;
		return 1;
	}
	cin>>cols;
	if(!cin||cols<0){
		cout << "Incorrect input" << endl;
		return 1;
	}
	cin>>fileName;
	inData.open(fileName);
	if (!inData.is_open()) {
		cout << "Could not open file" << endl;
		return 1;
	}

	
	loadData(elevations,rows,cols,inData);
	findMaxMin(elevations,rows,cols,max,min);
	loadGreyscale(image, elevations, rows, cols, max, min);
	outputImage(image, rows, cols, outData);
}