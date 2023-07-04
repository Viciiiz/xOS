
#include "headers/main.h"


uint8_t p_init_txt(){
    esp_printf(putc, "Hello, World!\n\n\n\t\t\t\t\t\t\t Welcome to my OS!\n\n\n\n");
    return 0;
}




void main() {

    p_init_txt();

    init_pfa_list();

    struct ppage *page = allocate_physical_pages(2);

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
