#include "Keyboard.h"

#define KEYBOARD_PORT 0x60

uint_8 keyboard_layout_us[2][128] = {
    {NULL, KEY_ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
     '-', '=', KEY_BACKSPACE, KEY_TAB, 'q', 'w', 'e', 'r', 't', 'y', 'u',
     'i', 'o', 'p', '[', ']', KEY_ENTER, KEY_LCTRL, 'a', 's', 'd', 'f', 'g', 'h', 'j',
     'k', 'l', ';', '\'', '`', KEY_LSHIFT, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm',
     ',', '.', '/', KEY_RSHIFT, 0, KEY_LALT, ' ', KEY_CAPS_LOCK, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5,
     KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_NUM_LOCK, KEY_SCROLL_LOCK, KEY_HOME, KEY_UP,
     KEY_PAGE_UP, '-', KEY_LEFT, '5', KEY_RIGHT, '+', KEY_END, KEY_DOWN,
     KEY_PAGE_DOWN, KEY_INSERT, KEY_DELETE, KEY_F11, KEY_F12, KEY_LGUI, KEY_RGUI},
    {NULL, KEY_ESC, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
     '_', '+', KEY_BACKSPACE, KEY_TAB, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U',
     'I', 'O', 'P', '{', '}', KEY_ENTER, KEY_LCTRL, 'A', 'S', 'D', 'F', 'G', 'H',
     'J', 'K', 'L', ':', '\"', '~', KEY_LSHIFT, '|', 'Z', 'X', 'C', 'V', 'B', 'N',
     'M', '<', '>', '?', KEY_RSHIFT, 0, KEY_LALT, ' ', 0, KEY_F1, KEY_F2, KEY_F3, KEY_F4,
     KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, 0, 0, KEY_HOME, KEY_UP,
     KEY_PAGE_UP, '-', KEY_LEFT, '5', KEY_RIGHT, '+', KEY_END, KEY_DOWN,
     KEY_PAGE_DOWN, KEY_INSERT, KEY_DELETE, KEY_F11, KEY_F12, KEY_LGUI, KEY_RGUI}};

uint_8 keyboard_codes[128] = {
     0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x0A, 0x0B,
     0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
     0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24,
     0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 
     0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
     0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
     0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,
     0x50, 0x52, 0x53, 0x57, 0x58, 0x5B, 0x5C
};

uint_8 scancode, hex, static_hex;


uint_32 codesLength = 0;

bool shift_code = false;

char KeyboardToChar(char input)
{
    char char_index = 0;

    // if(input == 0x2A && input == 0x36) {shift_code = true;}
    // else if(input == 0x2A + 0x80 && input == 0x36 + 0x80) shift_code = false;

    int d = shift_code ? 1 : 0;

    for(int i = 0; i < 128; i++)
    {
        if(input == keyboard_codes[i]) {char_index = i; break;};
    }

    uint_8 _char = keyboard_layout_us[d][char_index];
    return _char;
}

static void keyboard_callback(registers_t regs)
{
    static_hex, hex = inb(KEYBOARD_PORT);
    if(hex < 0x80)
    {
        scancode = KeyboardToChar(hex);
    }
    else
    {
        scancode = NULL;
        hex = NULL;
    }

    codesLength++;
}

void Keyboard::KeyboardInit()
{
    scancode = 0;
    isr_install(IRQ1, keyboard_callback);
}
bool Keyboard::IsKeyPressed(uint_8 key)
{
    return hex == key;
}
bool Keyboard::IsKeyCharPressed(uint_8 keychar)
{
    return scancode == keychar;
}
uint_8 Keyboard::GetKeyCode()
{
    return hex;
}
uint_8 Keyboard::GetKeyCodeStatic()
{
    return hex;
}
uint_8 Keyboard::GetChar()
{
    for(int i = 0; i < Keycode::Length; i++)
    {
        Keycode key = static_cast<Keycode>(i);
        if(scancode == key) return NULL;
    }
    return scancode;
}
