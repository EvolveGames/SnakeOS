#ifndef CONSOLE_H
#define CONSOLE_H

#include "Keyboard/Keyboard.h"
#include "Util.h"
#include "Math.h"

struct ForegroundColor
{
    public:
    //all console text colors
    static const uint_8 Black = 0x00; 
    static const uint_8 Blue = 0x01; 
    static const uint_8 Green = 0x02; 
    static const uint_8 Cyan = 0x03; 
    static const uint_8 Red = 0x04; 
    static const uint_8 Magenta = 0x05; 
    static const uint_8 Brown = 0x06; 
    static const uint_8 LightGray = 0x07; 
    static const uint_8 DarkGray = 0x08; 
    static const uint_8 LightBlue = 0x09; 
    static const uint_8 LightGreen = 0x0A; 
    static const uint_8 LightCyan = 0x0B;
    static const uint_8 LightRed = 0x0C; 
    static const uint_8 LightMagenta = 0x0D; 
    static const uint_8 Yellow = 0x0E; 
    static const uint_8 White = 0x0F; 
};
struct BackgroundColor
{
    public:
    //all console text colors
    static const uint_8 Black = 0x00; 
    static const uint_8 Blue = 0x01; 
    static const uint_8 Green = 0x02; 
    static const uint_8 Cyan = 0x03; 
    static const uint_8 Red = 0x04; 
    static const uint_8 Magenta = 0x05; 
    static const uint_8 Brown = 0x06; 
    static const uint_8 LightGray = 0x07; 
    static const uint_8 DarkGray = 0x08; 
    static const uint_8 LightBlue = 0x09; 
    static const uint_8 LightGreen = 0x0A; 
    static const uint_8 LightCyan = 0x0B;
    static const uint_8 LightRed = 0x0C; 
    static const uint_8 LightMagenta = 0x0D; 
    static const uint_8 Yellow = 0x0E; 
    static const uint_8 White = 0x0F; 
};

//main console functions
class Console
{
    public:
    static void SetCursorPosition(unsigned int x = 0, unsigned int y = 0);
    static void ClearScreen();
    static void WriteLine(const char *text, uint_8 color = ForegroundColor::White);
    static void Write(const char *text, uint_8 color = ForegroundColor::White);
    static void WriteChar(const char _char, uint_8 color = ForegroundColor::White);
    static char* ReadLine(uint_8 color = ForegroundColor::White);
    //cursor class
    class Cursor
    {
        public:
        //Get Cursor Pos X
        static const int GetX();
        //Get Cursor Pos Y
        static const int GetY();
        //Set Cursor Pos X
        static void SetX(const int x = 0);
        //Set Cursor Pos Y
        static void SetY(const int y = 0);
    };
};

#endif