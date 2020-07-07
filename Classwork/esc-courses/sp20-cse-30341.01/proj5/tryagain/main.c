/*
Main program for the virtual memory project.
Make all of your modifications to this file.
You may add or rearrange any code or data as you need.
The header files page_table.h and disk.h explain
how to use the page table and disk interfaces.
*/

#include "page_table.h"
#include "disk.h"
#include "program.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

//globals
int npages;
int nframes;
const char *pf_replacement_alg;
const char *program;
int *frametable;
int *ft_chances;
int ft_entries = 0;
int tot_entries = 0;
struct disk *disk;
int pagefaults=0;
int diskreads=0;
int diskwrites=0;

void rand_replace_alg(int * frame){
	*frame = rand() % (nframes);
}

void fifo_replace_alg(int * frame){
	*frame = tot_entries % nframes;
} 

void custom_replace_alg(int * frame){
	int curr_frame = tot_entries % nframes;
	while (1) {
		if (ft_chances[curr_frame]) {
            //replaced next time unless it's accessed again
			ft_chances[curr_frame] = 0; //set curr entry to chance of 0
		} else {
			*frame = curr_frame; //fifo
			break;
		}
		curr_frame += 1;
		if (curr_frame == nframes) { //if at end
			curr_frame = 0; //go back to start
		}
	}
}

void initialize_frame_table() {
	frametable = malloc(nframes*sizeof(int *));
	int i;
	for (i = 0; i < nframes; i++) {
		frametable[i] = -1;
	}
}

void initialize_chance_table() {
	ft_chances = malloc(nframes*sizeof(int *));
	int i;
	for (i = 0; i < npages; i++) {
		ft_chances[i] = 0;
	}
}

void page_fault_handler( struct page_table *pt, int page)
{
	int frame;
	int bits;
	unsigned char *physmem = page_table_get_physmem(pt);
	pagefaults += 1; //another page fault happening
    
	page_table_get_entry(pt, page, &frame, &bits); //read a page from virt mem

    //if frame table has empty slots, fill linearly
	if (ft_entries < nframes && frametable[frame] != page) {
		int i;
		for (i = 0; i < nframes; i++) {
			if (frametable[i] == -1) { //-1 to check if frame is empty
				page_table_set_entry(pt, page, i, PROT_READ);
				frametable[i] = page; //fill frame table spot
				ft_entries += 1; //another entry in table
				tot_entries += 1; //increment total entries added
				ft_chances[i] = 0; //set number of chances to 0
				return;
			}
		}
	}
	page_table_get_entry(pt, page, &frame, &bits);
	
	if (bits != PROT_READ) {
        //get frames from alg chosen
		if(!strcmp(pf_replacement_alg,"rand")) {
			rand_replace_alg(&frame);
		} else if(!strcmp(pf_replacement_alg,"fifo")) {
			fifo_replace_alg(&frame);
		} else if(!strcmp(pf_replacement_alg,"custom")) {
			custom_replace_alg(&frame);
		} else {
			fprintf(stderr,"unknown algorithm: %s\n",pf_replacement_alg);
			return;
		}

		int trash_bits;
		int trash_frame;
		int trash_page = frametable[frame]; //page number to be removed
		
        //bits from frame to see if dirty
        page_table_get_entry(pt, trash_page, &trash_frame, &trash_bits);
        
		//if alpha, write to disk
        if (!strcmp(program,"alpha")) {
			disk_write(disk, trash_page, &physmem[frame*PAGE_SIZE]);
			diskwrites += 1;
    
		} else if (trash_bits == 3) { //if dirty, write to disk
			disk_write(disk, trash_page, &physmem[frame*PAGE_SIZE]);
			diskwrites += 1;
		}
        
		disk_read(disk, page, &physmem[frame*PAGE_SIZE]);
		diskreads += 1;
        
		page_table_set_entry(pt, page, frame, PROT_READ); //set new entry
		page_table_set_entry(pt, trash_page, frame, 0); //rewrite old entry
		
        ft_chances[frame] = 0; //new entry gets chance 0
		frametable[frame] = page; //update page pointing to frame
		tot_entries += 1;
        
	} else if (frametable[frame] == page) { //make read bit a write bit
		page_table_set_entry(pt, page, frame, PROT_READ|PROT_WRITE);
		ft_chances[frame] = 1; //it is accessed so add another chance bit
	} 
}

int main( int argc, char *argv[] )
{
	if(argc!=5) {
		printf("use: virtmem <npages> <nframes> <rand|fifo|lru|custom> <sort|scan|focus>\n");
		return 1;
	}

	npages = atoi(argv[1]);
	nframes = atoi(argv[2]);
	pf_replacement_alg = argv[3];
	program = argv[4];

	initialize_frame_table();
	initialize_chance_table();
   /* frametable = malloc(nframes*sizeof(int *)); //initialize frame table to all -1
    for (int i = 0; i < nframes; i++) {
        frametable[i] = -1; //all empty slots
    }
    ft_chances = malloc(nframes * sizeof(int *)); //initialize chance table to all 0
    for (int i= 0; i < npages; i++){
        ft_chances[i] = 0; //empty slots
    }*/
    
	disk = disk_open("myvirtualdisk", npages);
	if(!disk) {
		fprintf(stderr,"couldn't create virtual disk: %s\n", strerror(errno));
		return 1;
	}

	struct page_table *pt = page_table_create( npages, nframes, page_fault_handler );
	if(!pt) {
		fprintf(stderr,"couldn't create page table: %s\n", strerror(errno));
		return 1;
	}

	unsigned char *virtmem = page_table_get_virtmem(pt);

	if(!strcmp(program,"alpha")) {
		alpha_program(virtmem, npages*PAGE_SIZE);

	} else if(!strcmp(program,"beta")) {
		beta_program(virtmem, npages*PAGE_SIZE);

	} else if(!strcmp(program,"gamma")) {
		gamma_program(virtmem, npages*PAGE_SIZE);
        
	} else if(!strcmp(program,"delta")) {
		delta_program(virtmem, npages*PAGE_SIZE);

	} else {
		fprintf(stderr,"unknown program: %s\n",argv[4]);
		return 1;
	}

	printf("Page Faults:\t%d\nDisk Reads:\t%d\nDisk Writes:\t%d\n", pagefaults, diskreads, diskwrites);
    
	page_table_delete(pt);
	disk_close(disk);

	return 0;
}
