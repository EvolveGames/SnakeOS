#ifndef VGA_H
#define VGA_H

#include "../Util.h"
#include "../Timer/Timer.h"

static uint_8 *vga_addr = (uint_8 *)0xA0000;

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define SCREEN_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT)
#define CURRENT (buffers[back])

class VGA
{
    public:

    enum Color
    {
        WHITE = 0xFF,
        BLACK = 0x00,
    };

    static void Init();
    static void Clear(uint_8 color = 0);
    static void Swap();
    static void SetPixel(uint_16 x, uint_16 y, uint_8 color);
    static char GetPixel(uint_16 x, uint_16 y);
};

#endif
