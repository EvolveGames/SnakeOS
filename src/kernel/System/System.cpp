#include "System.h"

void System::ErrorPanel(const char *error)
{
    if (error != NULL)
    {
        Console::ClearScreen();
        Console::WriteLine("Main System Exeption:\n", ForegroundColor::LightRed);
        Console::Write("Error: ", ForegroundColor::LightRed);
        Console::WriteLine(error, ForegroundColor::Red);
    }

    for(;;);
}

void System::InitSystemComponents()
{
    isr_init();
    sti();
    Timer::timer_init(60);
    Keyboard::KeyboardInit();
    VGA::Init();
}

void System::Sleep(uint_32 milliseconds)
{
    uint_64 ticks = Timer::GetTimerTicks();
    uint_32 freq = Timer::GetTimerFreq();
    uint_64 end = ticks + (milliseconds * freq) / 1000;
    while (Timer::GetTimerTicks() < end);
}

float System::GetTimer()
{
    uint_64 ticks = Timer::GetTimerTicks();
    uint_32 freq = Timer::GetTimerFreq();
    return (ticks * freq) / 1000;
}
