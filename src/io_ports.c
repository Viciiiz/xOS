#include <stdint.h>
#include "headers/io_ports.h"

/*
* inb
*
* Reads from I/O port _port, and returns a one byte value
*/

uint8_t inb (uint16_t _port) {
    uint8_t rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}


/*
* outb
*
* Writes val to I/O port _port
*/
void outb (uint16_t _port, uint8_t val) {
    __asm__ __volatile__ ("outb %0, %1" : : "a" (val), "dN" (_port) );
}

