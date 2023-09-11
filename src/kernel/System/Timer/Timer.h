#ifndef TIMER_H
#define TIMER_H

#include "../Util.h"
#include "../Interrupt/isr.h"
#include "../Console.h"

static struct
{
    uint_64 divisor = 0;
    uint_64 ticks = 0;
    uint_32 freq = 0;
} timer_state;

class Timer
{
    public:
    static void timer_init(uint_32 frequency);
    static void print_ticks();
    static uint_64 GetTimerTicks();
    static uint_64 GetTimerFreq();
};


#endif