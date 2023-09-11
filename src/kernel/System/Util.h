#ifndef UTIL_H
#define UTIL_H

#define NEW_LINE 10
#define RETURN 13
#define NULL 0

typedef unsigned char uint_8;
typedef unsigned short uint_16;
typedef unsigned int uint_32;
typedef unsigned long long uint_64;
typedef uint_32 size_t;

typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;
typedef char* string;

template<typename T>
T var() {
    T value;
    return value;
}

// 0xFFFF = 11111111 8bit mask
#define low_16(address) (uint_16)((address) & 0xFFFF)  
// shift to right 
#define high_16(address) (uint_16)(((address) >> 16) & 0xFFFF)

char *to_string(size_t num, bool hexadecimal = false);
//write i/o port
void outb(unsigned short port, unsigned char val);
//read i/o port
unsigned char inb(unsigned short port);
//fill memory
void memset(void *ptr, uint_8 value, size_t num);
//memory copy
void *memcpy(void *dst, const void *src, size_t n);
//memory move
void memmove(void *dest, void *src, size_t n);
//from rgb to byte
uint_8 fromRGB(uint_8 R, uint_8 G, uint_8 B);
//string length
int string_length(const char *str);
//get any array length

// template <typename T>
// static size_t getArrayLength(T (&array));

class EventSystem {
public:
    typedef void (*EventHandler)(uint_8);

    EventSystem() : numHandlers(0) {}

    void addHandler(EventHandler handler) {
        handlers[numHandlers++] = handler;
    }

    void invokeAll(uint_8 eventData) {
        for (int i = 0; i < numHandlers; i++) {
            handlers[i](eventData);
        }
    }

private:
    EventHandler *handlers;
    int numHandlers;
};

#endif