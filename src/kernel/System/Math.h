#ifndef MATH_H
#define MATH_H

#include "Util.h"

#define PI 3.14

class Math
{
    public:
    
    static int IntDivision(const int input, const int divisor = 2);
    static int Abs(int x);
    static float Smooth(float src, float dest, int time = 100);
    static double Sin(double x);
    static double Cos(double x);
};
class Random
{
    public:
    Random();
    unsigned int Next();
    unsigned int Next(int from, int to);
    void SetSeed(int Seed);
};
#endif