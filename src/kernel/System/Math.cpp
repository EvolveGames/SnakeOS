#include "Math.h"

unsigned int rndvalue = 4367;

int Math::IntDivision(const int input, const int divisor)
{
    float dv = input % divisor;
    float d = input / divisor;
    return (int)(d - dv);
}
int Math::Abs(int x)
{
    return (x < 0) ? -x : x;
}
float Math::Smooth(float src, float dest, int time)
{
    float val = ((float)Abs(dest - src)) / (float)time;
    return src < dest ? src + val : src - val;
}

double factorial(int n)
{
    double fact = 1.0;
    for(int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

double power(double x, int n)
{
    double result = 1.0;
    for(int i = 0; i < n; i++) {
        result *= x;
    }
    return result;
}

double Math::Sin(double x)
{
    double result = 0.0;
    for(int i = 0; i <= 10; i++) {
        double term = power(-1, i) * power(x, 2 * i + 1) / factorial(2 * i + 1);
        result += term;
    }
    return result;
}

double Math::Cos(double x)
{
    double result = 0.0;
    for(int i = 0; i <= 10; i++) {
        double term = power(-1, i) * power(x, 2 * i) / factorial(2 * i);
        result += term;
    }
    return result;
}

Random::Random()
{
    //unsigned int value = 8092748;
    //value = (1664525 * rndvalue + 1013904223) % 4294967296;
    //int load = value;
    
    //int seed = value;
    //for (int i = 0; i < load; i++)
    //{
    //    unsigned int val = 8092 * i;
    //    val = (1664525 * rndvalue + 1013904223) % 4294967296;
    //    load = val;
    //}
    //SetSeed(seed);
}

unsigned int Random::Next()
{
    rndvalue = (1664525 * rndvalue + 1013904223) % 4294967296;
    return rndvalue;
}
unsigned int Random::Next(int from, int to)
{
    rndvalue = (1664525 * rndvalue + 1013904223) % 4294967296;
    return (from + (rndvalue % (to - from + 1)));
}
void Random::SetSeed(int seed)
{
    rndvalue = seed;
}