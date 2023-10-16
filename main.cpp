//
//  main.cpp
//  rc_converter
//
//  Created by Faizan Bhagat on 6/29/22.
//

#include <stdio.h>
#include "Pixel.h"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void printImage(vector<Pixel> toPrint , int size, int width, int height, ostream& os){
    os << "P3\n";
    os << width << " " << height << "\n";
    os << 255 << "\n";
    
    for (int i = 0; i < size; i++){
        os << toPrint[i].getRed() << " " << toPrint[i].getGreen() << " " << toPrint[i].getBlue() << " ";
    }
}

int matrixAt(int row, int col, int width){
    return (row * width) + col;
}

int amtCubes(int width, int height){
    int tempWidth = width / 3.0;
    int tempHeight = height / 3.0;
    return tempWidth * tempHeight;
}

Pixel getPixelAround(vector<Pixel> currImg, int mainPoint, int howManyAround, int imgWidth){
    double realAverageRed = 0;
    double realAverageGreen = 0;
    double realAverageBlue = 0;

    int intAverageRed;
    int intAverageGreen;
    int intAverageBlue;
    
    for (int j = 0; j < howManyAround; j++){
        for (int i = 0; i < howManyAround; i++){
            realAverageRed = realAverageRed + currImg[mainPoint + i + (j * imgWidth)].getRed();
            realAverageGreen = realAverageGreen + currImg[mainPoint + i + (j * imgWidth)].getGreen();
            realAverageBlue = realAverageBlue + currImg[mainPoint + i + (j * imgWidth)].getBlue();
        }
    }
    
    realAverageRed = realAverageRed / (howManyAround * howManyAround);
    realAverageGreen = realAverageGreen / (howManyAround * howManyAround);
    realAverageBlue = realAverageBlue / (howManyAround * howManyAround);
    
    intAverageRed = realAverageRed;
    intAverageGreen = realAverageGreen;
    intAverageBlue = realAverageBlue;
    
    Pixel rVal(intAverageRed, intAverageBlue, intAverageGreen);
    return rVal;
}

int main(int argc, char* argv[]){
    cout << "Using image : " << argv[1] << " as input, outputting to " << argv[2] << endl;
    string imgName;
    
    int imgHeight;
    int imgWidth;
    int imgIntensity;
    int totalPixels;
    int totalPixelsNew;
    int pixelsPerPixel = atoi(argv[3]);
    
    int tempRed;
    int tempGreen;
    int tempBlue;
    
    ifstream ins;
    ins.open(argv[1]);
    
    ofstream ons;
    ons.open(argv[2]);
    
    ins >> imgName;
    ins >> imgWidth;
    ins >> imgHeight;
    ins >> imgIntensity;
    
    totalPixels = imgWidth * imgHeight;
    vector<Pixel> currImg(totalPixels);
    
    int newImgWidth = imgWidth / atoi(argv[3]);
    int newImgHeight = imgHeight / atoi(argv[3]);
    totalPixelsNew = newImgWidth * newImgHeight;
        
    cout << "Will require " << amtCubes(newImgWidth, newImgHeight) << " Rubik's cubes to make image." << endl;
    
    vector<Pixel> rubikImg(totalPixelsNew);
    
    for (int i = 0; i < totalPixels; i++){
        ins >> tempRed;
        ins >> tempGreen;
        ins >> tempBlue;
        currImg[i].setRed(tempRed);
        currImg[i].setGreen(tempGreen);
        currImg[i].setBlue(tempBlue);
    }
    
    
    int mainPoint;
    

    int rubikImgCounter = 0;
    
    for (int j = 0; j <= imgHeight - pixelsPerPixel; j = j + pixelsPerPixel){
        for (int i = 0; i <= imgWidth - pixelsPerPixel; i = i + pixelsPerPixel){
            mainPoint = matrixAt(j, i, imgWidth);
            Pixel tempVal;
            tempVal = getPixelAround(currImg, mainPoint, pixelsPerPixel, imgWidth);
            rubikImg[rubikImgCounter] = tempVal;
            rubikImgCounter++;
        }
    }

    for (int i = 0; i < totalPixelsNew; i++){
        rubikImg[i].setColor(findClosestRubikColorByDarkness(rubikImg[i]));
    }

    printImage(rubikImg, totalPixelsNew, newImgWidth, newImgHeight, ons);
    
    ins.close();
    ons.close();
    return 0;
}

void printImage(Pixel toPrint[], int size, int width, int height, ostream& os);

int matrixAt(int row, int col, int width);

int amtCubes(int width, int height);

Pixel getPixelAround(vector<Pixel> currImg, int mainPoint, int howManyAround, int imgWidth);
