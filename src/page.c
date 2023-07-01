#include "headers/page.h"
#define NULL 0

struct ppage physical_page_array[128]; // 128 pages, each 2mb in length covers 256 megs of memory

struct ppage *free_physical_pages;

extern int _end_kernel;


/*
 * function to initialize physical page array struct
 */
void init_pfa_list(void) {
   free_physical_pages = &physical_page_array[0];
   struct ppage* curr = free_physical_pages;
   curr->physical_addr = 0x100000;
   curr->next = &physical_page_array[1];
   curr = curr->next;
   for (int i = 1; i < 127; i++) {
        curr->prev = &physical_page_array[i - 1];
        curr->next = &physical_page_array[i + 1];
	curr->physical_addr = curr->prev->physical_addr + 0x1000;
       	curr = (*curr).next;
    }
    curr->prev = &physical_page_array[126];
    curr->physical_addr = physical_page_array[126].physical_addr + 0x1000;
}


/*
 * function to allocate npages pages from the free physical pages
 */
struct ppage *allocate_physical_pages(unsigned int npages) {

}


/*
 * function to free the allocated pages
 * The freed pages will be linked back to the free physical pages array
 */
void free_pages(struct ppage *ppage_list){

}
