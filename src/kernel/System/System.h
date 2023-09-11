#ifndef SYSTEM_H
#define SYSTEM_H

#include "Util.h"
#include "Console.h"
#include "Interrupt/isr.h"
#include "Keyboard/Keyboard.h"
#include "Timer/Timer.h"
#include "Vga/Vga.h"

// start interrupt
#define sti() asm volatile("sti")
// clear interrupt
#define cli() asm volatile("cli")

class System
{
    public:
    static void ErrorPanel(const char *error);
    static void InitSystemComponents();
    static void Sleep(uint_32 milliseconds);
    static float GetTimer();
};
#endif