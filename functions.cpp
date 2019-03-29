#include <iostream>
#include <fstream>
#include <cmath>
#include "functions.h"
using namespace std;

/**
This findMaxMin function does not return anything but calculates the highest and lowest 
elevation in the array
*/
void findMaxMin(const int elevations[MAX_ROWS][MAX_COLS], int rows, int cols, int& max, int& min) {
	max=elevations[0][0];
	min=elevations[0][0];
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
/**
The loadata function does not return anything but it fils our elevation 
array with integer values using the fstream package
*/
void loadData(int elevations[MAX_ROWS][MAX_COLS], int rows, int cols, istream& inData) {
	if(inData.good()){
		for(int i=0;i<rows;i++){
			for(int j=0;j<cols;j++){
				if(inData.fail()){
					cout<<"Error: Read a non-integer value."<<endl;
				}
				if(inData.eof()){
					cout<<"Error: End of file reached prior to getting all the required data."<<endl;
				}
				else{
					inData >> elevations[i][j];
				}
			}
		}
	if(!inData.eof()){
		cout<<"Error: Too many data points.";
	}

	}
}
/**
The scaleValue funtion converts a given elevation value to a greyscale value and
retrns the converted value
*/
int scaleValue(int value, int max, int min){
	value=int(round(((value-min)*255.0)/(max-min)));
    return value;
}
/**
The loadGreyScale function assigns each index in the parallel array to a rgb 
value of the greyscale value returned by the scaleValue function
*/
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
/**
The outputImage function writes to our file and generates a ppm file
which will allow us to see our finished image with the appropriate 
shading
*/
void outputImage(const Pixel image[MAX_ROWS][MAX_COLS], int rows, int cols, ostream& outData) {
	outData<<"P3"<<endl;
	outData<<cols<<" "<<rows<<endl;
	outData<<"255"<<endl;
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			outData<<image[i][j].red<<" "<<image[i][j].green<<" "<<image[i][j].blue<<" ";
		}
	}
}
int colorPath(const int elevations[MAX_ROWS][MAX_COLS], Pixel 
				image[MAX_ROWS][MAX_COLS], int rows, int cols, Pixel color, int start_row){
	int dist1,dist2,dist3;
	image[start_row][0]=color;
	int totalDist=0;
	for(int j=0;j<cols;j++){
		if(start_row==0){
			int dist1=abs(elevations[start_row][j]-elevations[start_row][j+1]);
			int dist2=abs(elevations[start_row][j]-elevations[start_row+1][j+1]);
			if(dist1<=dist2){
				totalDist+=dist1;
				image[start_row][j+1]=color;
			}
			else{
				totalDist+=dist2;
				image[start_row+1][j+1]=color;
			}
		}
		if(start_row==rows-1){
			int dist1=abs(elevations[start_row][j]-elevations[start_row][start_row+1]);
			int dist2=abs(elevations[start_row][j]-elevations[start_row-1][start_row+1]);
			if(dist1<=dist2){
				totalDist+=dist1;
				image[start_row][j+1]=color;
			}
			else{
				totalDist+=dist2;
				image[start_row-1][j+1]=color;
			}
		}
		else{
			int dist1=abs(elevations[start_row][j]-elevations[start_row][j+1]);
			int dist2=abs(elevations[start_row][j]-elevations[start_row+1][start_row+1]);
			int dist3=abs(elevations[start_row][j]-elevations[start_row-1][j+1]);
			if(dist1<=dist2&&dist1<=dist3){
				totalDist+=dist1;
				image[start_row][j+1]=color;
			}
			else if(dist2<=dist3&&dist2<dist1){
				totalDist+=dist2;
				image[start_row+1][j+1]=color;
			}
			else{
				totalDist+=dist2;
				image[start_row-1][j+1]=color;
			}
		}
	}
	return totalDist;	
}

