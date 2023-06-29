
#include <stdint.h>
#include "headers/main.h"


/*
 * multiboot header
 *
 */
const unsigned int multiboot_header[]  = {MULTIBOOT2_HEADER_MAGIC, 0, 16, -(16+MULTIBOOT2_HEADER_MAGIC), 0, 12};




void main() {


    while(1) {
	// read from port 0x64 (status register)
        uint8_t status = inb(0x64);

	// if LSB is 1, then the is a scancode to read
	if(status & 1){
	   // read port 0x60 (status register) to get scancode
	   uint8_t scancode = inb(0x60);

	   // conversion to ascii & print to qemu
           if(keyboard_map[scancode] >= 1 && keyboard_map[scancode]!=0){
	   	if((scancode & 0x80) == 0){ 
	   	   esp_printf(putc, "%c", keyboard_map[scancode]);
		}
	   }
	}
    }
}
