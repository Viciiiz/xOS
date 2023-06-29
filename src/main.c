
#include <stdint.h>
#include "headers/main.h"

#define MULTIBOOT2_HEADER_MAGIC         0xe85250d6

const unsigned int multiboot_header[]  = {MULTIBOOT2_HEADER_MAGIC, 0, 16, -(16+MULTIBOOT2_HEADER_MAGIC), 0, 12};

uint8_t inb (uint16_t _port) {
    uint8_t rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}


void outb (uint16_t _port, uint8_t val) {
    __asm__ __volatile__ ("outb %0, %1" : : "a" (val), "dN" (_port) );
}

void main() {
    unsigned short *vram = (unsigned short*)0xb8000; // Base address of video mem
    const unsigned char color = 7; // gray text on black background

    esp_printf(putc, "hello world");

    while(1) {
	// read from port 0x64
        uint8_t status = inb(0x64);
	if(status & 1){
	   uint8_t scancode = inb(0x60);
           if(keyboard_map[scancode] >= 1 && keyboard_map[scancode]!=0){
	   	if((scancode & 0x80) == 0){ 
	   	   esp_printf(putc, "%c", keyboard_map[scancode]);
		}
	   }
	}
    }
}
