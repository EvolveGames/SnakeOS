#include "Vga.h"

#define PALETTE_MASK 0x3C6
#define PALETTE_READ 0x3C7
#define PALETTE_WRITE 0x3C8
#define PALETTE_DATA 0x3C9

char idk[SCREEN_SIZE];

// double buffering
uint_8 buffers[2][SCREEN_SIZE];
uint_8 back = 0;

#define SWAP() (back = 1 - back)

void VGA::Clear(uint_8 color)
{
  // memset(CURRENT, color, SCREEN_SIZE);
  memset(vga_addr, color, SCREEN_SIZE);
}

void VGA::Swap()
{
  memcpy(vga_addr, CURRENT, SCREEN_SIZE);
  SWAP();
}

void VGA::SetPixel(uint_16 x, uint_16 y, uint_8 color)
{
  uint_16 offset = y * SCREEN_WIDTH + x; // specifying position
  // CURRENT[offset] = color;               // draw color on back buffer
  vga_addr[offset] = color;
}
char VGA::GetPixel(uint_16 x, uint_16 y)
{
  return vga_addr[((y * 320) + x)];
}

void VGA::Init()
{
  // 8-bit RRRGGGBB
  outb(PALETTE_MASK, 0xFF); // enable all bits for update
  outb(PALETTE_WRITE, 0);   // update first entry
  for (uint_8 i = 0; i < 255; i++)
  {
    outb(PALETTE_DATA, (((i >> 5) & 0x7) * (256 / 8)) / 4); // extract red   11111110 >> 5 = 00000111, last 3 red   & 0x7 = 00000111
    outb(PALETTE_DATA, (((i >> 2) & 0x7) * (256 / 8)) / 4); // extract green 11111110 >> 2 = 00111111, last 3 green & 0x7 = 00000111
    outb(PALETTE_DATA, (((i >> 0) & 0x3) * (256 / 4)) / 4); // extract blue  11111110 >> 0 = 11111110, last 2 blue  & 0x3 = 00000010
    // 7 * 32 = 224, 224 / 4 = 56, range 0 - 56
  }
  // set color 255 = white
  outb(PALETTE_DATA, 0x3F);
  outb(PALETTE_DATA, 0x3F);
  outb(PALETTE_DATA, 0x3F);
}

static struct
{
  uint_16 line = 0;
  uint_16 c = 0;
} current;

void scroll_screen()
{
  for (size_t i = 0; i < SCREEN_HEIGHT; i++)
  {
    memset((uint_8 *)vga_addr + (i * SCREEN_WIDTH), ((uint_32)System::GetTimer() - i) % 256, SCREEN_WIDTH);
  }
}
