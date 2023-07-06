#include "headers/pgtbl.h"

struct page_directory_entry pd[1024] __attribute__((aligned(4096)));   // each page directory entry is 4kb aligned
struct page_table_entry pt[1024] __attribute__((aligned(4096)));  // each page table entry is 4kb aligned
struct page_table_entry pt2[1024] __attribute__((aligned(4096)));

void map_pages_init() {
	for(int i=0;i<1024; i++){
		pd[i].present=0;
		pd[i].rw=0;
		pd[i].user=0;
		pd[i].writethru=0;
		pd[i].cachedisabled=0;
		pd[i].accessed=0;
		pd[i].pagesize=0;
		pd[i].ignored=0;
		pd[i].os_specific=0;
		pd[i].frame=0; //address of pt at index i
	}

	for(int i =0; i<=1023;i++){
		pt[i].user = 0;
                pt[i].accessed = 0;
                pt[i].dirty = 0;
                pt[i].unused = 0;
                pt[i].frame =i; //physical address
                pt[i].present =1;
                pt[i].rw=1;
        }
}


void *map_pages(void *vaddr, struct page *ppage, struct page_directory_entry *paged) {

}


