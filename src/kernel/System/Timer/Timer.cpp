#include "Timer.h"

#define PIT_HZ 1193180

void print_ticks()
{
    Console::Write("[");
    Console::Write(to_string(timer_state.ticks));
    Console::Write("]");
}

void timer_callback(registers_t regs)
{
    timer_state.ticks++;
    //print_ticks();
}

uint_64 Timer::GetTimerTicks()
{
    return timer_state.ticks;
}

uint_64 Timer::GetTimerFreq()
{
    return timer_state.freq;
}

void Timer::timer_init(uint_32 frequency)
{
    timer_state.freq = frequency;
    timer_state.ticks = 0;
    isr_install(IRQ0, timer_callback);

    /* hardware clock at 1193180 Hz*/
    timer_state.divisor = PIT_HZ / frequency;
    uint_8 low = (uint_8)(timer_state.divisor & 0xFF); // extract the lowest 8 bits of the divisor
    uint_8 high = (uint_8)((timer_state.divisor >> 8) & 0xFF);

    /* Send the command */
    outb(0x43, 0x36); // Command register port
    outb(0x40, low);  // Channel 0 data port
    outb(0x40, high); // Channel 0 data port
}

