#include "Console.h"

int current_x = 0;
int current_y = 0;

uint_16 memindex = 0;

void SetIndexPos(uint_16 pos)
{
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint_8)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint_8)((pos >> 8) & 0xFF));
    //calculate x and y
    current_x = pos % 80;
    current_y = pos / 80;
    memindex = pos;
}

void Console::SetCursorPosition(unsigned int x, unsigned int y)
{
    //x max 80 and y max 24
    if(x <= 80 && y <= 24)
    {
        uint_16 i = (y * 80) + x;
        // current_x = x;
        // current_y = y;
        SetIndexPos(i);
    }
}

void Console::WriteLine(const char *text, uint_8 color)
{
    char* vidmem = (char*)0xb8000;
    int i = 0;
    while (text[i] != NULL) 
    {
        switch(text[i])
        {
            case NEW_LINE:
                //new line
                SetCursorPosition(0, current_y + 1);
                i++;
                break;
            case RETURN:
                //return
                SetCursorPosition(0, current_y);
                i++;
                break;
            default:
                //write char
                vidmem[memindex * 2] = text[i];
                vidmem[memindex * 2 + 1] = color;
                i++;
                SetIndexPos(memindex + 1);
                break;
        }
    }
    SetCursorPosition(0, current_y + 1);
}

void Console::Write(const char *text, uint_8 color)
{
    char* vidmem = (char*)0xb8000;

    int load_text_length = 0;
    //int text_length = sizeof(text);

    while (*text != '\0') {
        uint_8 _char = *text;

        switch(_char)
        {
            case NEW_LINE:
                //new line
                SetCursorPosition(0, current_y + 1);
                break;
            case RETURN:
                //return
                SetCursorPosition(0, current_y);
                break;
            default:
                //write char
                vidmem[memindex * 2] = _char;
                vidmem[memindex * 2 + 1] = color;
                text++;
                load_text_length++;
                SetIndexPos(memindex + 1);
                break;
        }
    }
}
void Console::WriteChar(const char _char, uint_8 color)
{
    char* vidmem = (char*)0xb8000;
    switch(_char)
    {
        case NEW_LINE:
            //new line
            SetCursorPosition(0, current_y + 1);
            break;
        case RETURN:
            //return
            SetCursorPosition(0, current_y);
            break;
        default:
            //write char
            vidmem[memindex * 2] = _char;
            vidmem[memindex * 2 + 1] = color;
            SetIndexPos(memindex + 1);
            break;
    }
}

void Console::ClearScreen(){
    char* vidmem = (char*)0xb8000;
    
    for (int i = 0; i < 80 * 25; i++) {
        vidmem[i * 2] = ' ';
        vidmem[i * 2 + 1] = 0x07;
    }
    SetIndexPos(0);
}

void DownClick(uint_8 _char)
{
    Console::WriteChar(_char);
}

char* Console::ReadLine(uint_8 color)
{
    char *read;

    uint_16 length = 0;
    uint_16 start_offset = current_x;

    char old_char = Keyboard::GetChar();
    char old_key = Keyboard::GetKeyCode();

    char _char = old_char;
    char _key = old_key;

    do
    {
        _char = Keyboard::GetChar();
        _key = Keyboard::GetKeyCode();

        if(old_char != _char)
        {
            old_char = _char;
            if(_char != NULL)
            {
                read[length] = _char;
                WriteChar(_char, color);
                length++;
            }
        }

        if(old_key != _key)
        {
            old_key = _key;

            switch(_key)
            {
                case Keycode::KEY_BACKSPACE:
                    if(current_x > start_offset)
                    {
                        SetCursorPosition(current_x - 1, current_y);
                        WriteChar(NULL);
                        SetCursorPosition(current_x - 1, current_y);
                        length--;
                        read[length] = NULL;
                    }
                    break;
                case Keycode::KEY_SPACE:
                    read[length] = Keycode::KEY_SPACE;
                    WriteChar(0x20);
                    length++;
                    break;                    
            }
        }
    }
    while(_key != Keycode::KEY_ENTER);
    read[length] = NULL;
    SetCursorPosition(0, current_y + 1);
    return read;
}

const int Console::Cursor::GetX()
{
    return current_x;
}
const int Console::Cursor::GetY()
{
    return current_y;
}

void Console::Cursor::SetX(int x)
{
    SetCursorPosition(x, current_y);
}
void Console::Cursor::SetY(int y)
{
    SetCursorPosition(current_x, y);
}

