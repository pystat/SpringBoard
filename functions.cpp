#include <iostream>
#include <fstream>
#include <cmath>
#include "functions.h"
using namespace std;

void findMaxMin(const int elevations[MAX_ROWS][MAX_COLS], int rows, int cols, int& max, int& min) {
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			if(max<elevations[i][j]){
				max=elevations[i][j];
			}
			if(min>elevations[i][j]){
				min=elevations[i][j];
			}
		}
	}
}

void loadData(int elevations[MAX_ROWS][MAX_COLS], int rows, int cols, istream& inData) {
	if(inData.good()){
		for(int i=0;i<rows;i++){
			for(int j=0;j<cols;j++){
				inData >> elevations[i][j];
			}
		}
	}
}

int scaleValue(int value, int max, int min){
	value=int(round(((value-min)*255)/((max-min)*1.0)));
    return value;
}

void loadGreyscale(Pixel image[MAX_ROWS][MAX_COLS], const int elevations[MAX_ROWS][MAX_COLS], 
                    int rows, int cols, int max, int min){ 
	int temp=0;
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			temp=scaleValue(elevations[i][j],max,min);
			image[i][j].red=temp;
			image[i][j].green=temp;
			image[i][j].blue=temp;

		}
	}
}

void outputImage(const Pixel image[MAX_ROWS][MAX_COLS], int rows, int cols, ostream& outData) {

}

