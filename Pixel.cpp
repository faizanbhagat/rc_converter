//
//  Pixel.cpp
//  rc_converter
//
//  Created by Faizan Bhagat on 6/29/22.
//

#include <stdio.h>
#include "Pixel.h"
#include <iostream>
#include <cmath>

using namespace std;

Pixel red (183, 18, 52);
Pixel blue (0, 70, 173);
Pixel green (0, 155, 72);
Pixel yellow (255, 213, 0);
Pixel white (255, 255, 255);
Pixel orange (255, 88, 0);

Pixel::Pixel(){
    r = 0;
    g = 0;
    b = 0;
}

Pixel::Pixel(int rIn, int gIn, int bIn){
    r = rIn;
    b = bIn;
    g = gIn;
}

int Pixel::getRed(){
    return r;
}

int Pixel::getBlue(){
    return b;
}

int Pixel::getGreen(){
    return g;
}

void Pixel::setRed(int rValue){
    r = rValue;
}

void Pixel::setBlue(int bValue){
    b = bValue;
}

void Pixel::setGreen(int gValue){
    g = gValue;
}
    
void Pixel::setColor(Pixel colorSet){
    setRed(colorSet.getRed());
    setGreen(colorSet.getGreen());
    setBlue(colorSet.getBlue());
}

double findDistanceFrom(Pixel &mainImage, Pixel &rubikColor){
    double redDistance = ((mainImage.getRed() - rubikColor.getRed()) * 2.0);
    redDistance = redDistance * redDistance;
    
    double blueDistance = ((mainImage.getBlue() - rubikColor.getBlue()) * 0.5);
    blueDistance = blueDistance * blueDistance;
    
    double greenDistance = ((mainImage.getGreen() - rubikColor.getGreen()) * 1.5);
    greenDistance = greenDistance * greenDistance;
    
    return redDistance + blueDistance + greenDistance;
};

//first attempted method, not as effective
Pixel findClosestRubikColorByColor(Pixel &mainImage){
    Pixel colorPixels [6];
    double colors [6];
    
    colors[0] = findDistanceFrom(mainImage, red);
    colorPixels[0] = red;
    colors[1] = findDistanceFrom(mainImage, blue);
    colorPixels[1] = blue;
    colors[2] = findDistanceFrom(mainImage, green);
    colorPixels[2] = green;
    colors[3] = findDistanceFrom(mainImage, orange);
    colorPixels[3] = orange;
    colors[4] = findDistanceFrom(mainImage, white);
    colorPixels[4] = white;
    colors[5] = findDistanceFrom(mainImage, yellow);
    colorPixels[5] = yellow;
    
    double currentMin = colors[0];
    int currentMinIndex = 0;
    
    for (int i = 0; i < 6; i++){
        if (currentMin > colors[i]){
            currentMin = colors[i];
            currentMinIndex = i;
        }
    }
    
    return colorPixels[currentMinIndex];
}

//second attempted method, much more effective
Pixel findClosestRubikColorByDarkness(Pixel &mainImage){
    double brightness = sqrt((mainImage.getRed() * mainImage.getRed() * .241) +
                             (mainImage.getGreen() * mainImage.getGreen() * .691) +
                             (mainImage.getBlue() * mainImage.getBlue() * .068));
    if (brightness < 90){
        return blue;
    }
    else if (brightness < 125){
        return red;
    }
    else if (brightness < 145){
        return orange;
    }
    else if (brightness < 165){
        return yellow;
    } 
    
    return white;
}

