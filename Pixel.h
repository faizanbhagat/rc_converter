//
//  Pixel.h
//  rc_converter
//
//  Created by Faizan Bhagat on 6/29/22.
//

#ifndef Pixel_h
#define Pixel_h
#include <iostream>

class Pixel{
public:
    Pixel();
    
    Pixel(int r_in, int g_in, int b_in);
    
    int getRed();
    
    int getBlue();
    
    int getGreen();
    
    void setRed(int rValue);
    
    void setBlue(int bValue);
    
    void setGreen(int gValue);
    
    void setColor(Pixel colorSet);
    
private:
    int r;
    int g;
    int b;
};

double findDistanceFrom(Pixel &mainImage, Pixel &rubikColor);

Pixel findClosestRubikColorByColor(Pixel &mainImage);

Pixel findClosestRubikColorByDarkness(Pixel &mainImage);

#endif /* Pixel_h */
