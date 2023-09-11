#ifndef GFX_H
#define GFX_H

#include "Vga/Vga.h"
 
class GFX
{
    public:
    static void DrawRectangle(uint_16 x, uint_16 y, uint_16 width, uint_16 height, uint_8 borderSize = 1, uint_8 fillColor = VGA::BLACK, uint_8 BorderColor = VGA::WHITE);
    static void DrawSphere(uint_16 x, uint_16 y, uint_16 radius = 3, uint_8 color = VGA::WHITE);
    static void DrawText(const char *text, uint_16 x, uint_16 y, uint_8 color = VGA::WHITE);
    static void SetChar(uint_8 c, uint_32 x, uint_32 y, uint_8 color = VGA::WHITE);

};

#endif