export PATH="$PATH:/usr/local/i386elfgcc/bin"

i386-elf-gcc -ffreestanding -g -c -fno-common "src/kernel/kernel.cpp" -o "build/kernel.o"

i386-elf-gcc -ffreestanding -g -c -fno-common "src/kernel/System/Console.cpp" -o "build/Console.o"
i386-elf-gcc -ffreestanding -g -c -fno-common "src/kernel/System/Util.cpp" -o "build/Util.o"
i386-elf-gcc -ffreestanding -g -c -fno-common "src/kernel/System/Math.cpp" -o "build/Math.o"

i386-elf-gcc -ffreestanding -g -c -fno-common "src/kernel/System/Interrupt/idt.cpp" -o "build/idt.o"
i386-elf-gcc -ffreestanding -g -c -fno-common "src/kernel/System/Interrupt/isr.cpp" -o "build/isr.o"
i386-elf-gcc -ffreestanding -g -c -fno-common "src/kernel/System/Interrupt/pic.cpp" -o "build/pic.o"
i386-elf-gcc -ffreestanding -g -c -fno-common "src/kernel/System/System.cpp" -o "build/System.o"
i386-elf-gcc -ffreestanding -g -c -fno-common "src/kernel/System/Keyboard/Keyboard.cpp" -o "build/Keyboard.o"
i386-elf-gcc -ffreestanding -g -c -fno-common "src/kernel/System/Timer/Timer.cpp" -o "build/Timer.o"
i386-elf-gcc -ffreestanding -g -c -fno-common "src/kernel/System/Vga/Vga.cpp" -o "build/Vga.o"
i386-elf-gcc -ffreestanding -g -c -fno-common "src/kernel/System/Gfx.cpp" -o "build/Gfx.o"


nasm "src/boot/boot.asm" -f bin -o "build/boot.bin"
nasm "src/kernel/System/Interrupt/idt.asm" -f elf -o "build/idt_asm.o"
nasm "src/kernel/System/Interrupt/irq.asm" -f elf -o "build/irq_asm.o"
nasm "src/kernel/System/Interrupt/isr.asm" -f elf -o "build/isr_asm.o"
nasm "src/boot/kernelEntry.asm" -f elf -o "build/kernelEntry_asm.o"
nasm "src/boot/zero.asm" -f bin -o "build/zero.bin"

i386-elf-ld -o "build/kernel.bin" -T link.ld "build/kernel.o" "build/kernelEntry_asm.o" "build/Console.o" "build/Util.o" "build/Math.o" "build/idt_asm.o" "build/irq_asm.o" "build/isr_asm.o" "build/idt.o" "build/isr.o" "build/pic.o" "build/System.o" "build/Keyboard.o" "build/Timer.o" "build/Vga.o" "build/Gfx.o" -g -L/usr/local/i386elfgcc/lib/gcc/i386-elf/12.2.0 -lgcc --oformat binary 

cat "build/boot.bin" "build/kernel.bin" "build/zero.bin" > "build/os.bin"

mkdir iso
# brew genisoimage -b os.bin -o iso/SnakeOS.iso

qemu-system-x86_64 -drive format=raw,file=build/os.bin