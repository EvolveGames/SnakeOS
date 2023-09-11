#ifndef PIC_H
#define PIC_H

#include "../Util.h"

#define PIC1 0x20
#define PIC2 0xA0
#define PIC_EOI 0x20 // end of interrupt

void pic_remap();
#endif