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

int npages;
int nframes;
int OLDEST_FRAME = 0;
const char *algorithm;
int diskReads, diskWrites, pageFaults;
int *frameTable = NULL;
int *lruTable = NULL;
struct disk *disk; 
unsigned char *physmem;

void initialize_frame_table(){
    int i;
    for(i=0; i < nframes; i++){
        frameTable[i] = -1;
    }
}
int table_full(){
    int i;
    int tableFull = 1;
    for(i = 0; i < nframes; i++){
        if(frameTable[i] == -1){
            tableFull = 0;
        }
    }
    return tableFull;
}
int in_frame_table(int page){
    int i;
    for(i = 0; i < nframes; i++){
        if(frameTable[i] == page) return 1;
    }
    return 0;
}

void rand_handler(struct page_table *pt, int page){
    pageFaults++;
    int fr = rand() % nframes;
	int pg = frameTable[fr];
    disk_write(disk, pg, &physmem[fr*npages]);
    diskWrites++;
    disk_read(disk, page, &physmem[fr*npages]);
    diskReads++;
    page_table_set_entry(pt, page, fr, PROT_READ);
    frameTable[fr] = page;
    page_table_set_entry(pt, pg, 0, 0);
}

void fifo_handler(struct page_table *pt, int page) {
    pageFaults++;
    int fr = OLDEST_FRAME;
    int pg = frameTable[fr];
    disk_write(disk, pg, &physmem[fr*npages]);
    diskWrites++;
    disk_read(disk, page, &physmem[fr*npages]);
    diskReads++;
    page_table_set_entry(pt, page, fr, PROT_READ);
    frameTable[fr] = page;
    page_table_set_entry(pt, pg, 0, 0);
    OLDEST_FRAME++;
    if (OLDEST_FRAME == nframes) {
        OLDEST_FRAME = 0;
    }
}

void custom_handler(struct page_table *pt, int page){
    pageFaults++;
    int i, fr, val;
    int max = 0;
	for(i = 0; i < nframes; i++){
        if(lruTable[i] > max){
            max = lruTable[i];
            fr = i;
        }
    }
    int pg = frameTable[fr];
    disk_write(disk, pg, &physmem[fr*npages]);
    diskWrites++;
    disk_read(disk, page, &physmem[fr*npages]);
    diskReads++;
    page_table_set_entry(pt, page, fr, PROT_READ);
    frameTable[fr] = page;
    page_table_set_entry(pt, pg, 0, 0);
    lruTable[fr] = 0;
	for(i=0; i<nframes; i++){
        if(i == fr) continue;
        val = lruTable[i];
        val++;
        lruTable[i] = val;
    }
}

void same_num_pf_handler(struct page_table *pt, int page){
	pageFaults++;
    page_table_set_entry(pt, page, page, PROT_READ|PROT_WRITE);
	pageFaults++;
}

void diff_num_pf_handler(struct page_table *pt, int page){
	int frame, bits, j, i, val;
    page_table_get_entry(pt, page, &frame, &bits);
	int found = in_frame_table(page);
	if(!found && bits == 0){
        for(j = 0; j < nframes; j++){
			if(frameTable[j] == -1){ //we found an empty spot!
                lruTable[j] = 0;
                for(i=0; i<nframes; i++){ //update array for custom algorithm
                    if(i == j) continue;
                    val = lruTable[i];
                    val++;
                    lruTable[i] = val;
                }
                page_table_set_entry(pt, page, j, PROT_READ);
                frameTable[j] = page;
                disk_read(disk, page, &physmem[j*nframes]);
                diskReads++;
                if(table_full()) return;
                else break;
            }
        }
		if(table_full()){
            if (!strcmp(algorithm, "rand")){
                rand_handler(pt, page);
			}
            else if(!strcmp(algorithm, "fifo")){
                fifo_handler(pt, page);
			}
            else if(!strcmp(algorithm, "custom")){
                custom_handler(pt, page);
			}
	    	else{
	      		printf("unknown algorithm\n");
	      		printf("use: virtmem <npages> <nframes> <rand|fifo|custom> <sort|scan|focus>\n");
	      		exit(1);
	    	}
        }
    }
	if(found){
      if(bits == 1){ //need to set write bits
            page_table_set_entry(pt, page, frame, PROT_READ|PROT_WRITE);
			int i, val;
            lruTable[frame] = 0;
            for(i=0; i<nframes; i++){
                if(i == frame) continue;
                val = lruTable[i];
                val++;
                lruTable[i] = val;
            }
        }
        else if(bits == 3){
            page_table_set_entry(pt, page, frame, PROT_READ|PROT_WRITE|PROT_EXEC);
        }    
    }
}

void page_fault_handler( struct page_table *pt, int page ){
	if(npages == nframes){
        same_num_pf_handler(pt, page);
    }
    else{
        diff_num_pf_handler(pt, page);
		return;
    }
}


int main( int argc, char *argv[] )
{
	//int t=1;
    //srand((unsigned) time(&t)); 
    pageFaults = 0;
    diskReads = 0;
    diskWrites = 0;

	if(argc!=5) {
		printf("use: virtmem <npages> <nframes> <rand|fifo|custom> <alpha|beta|gamma|delta>\n");
		return 1;
	}

	int npages = atoi(argv[1]);
	int nframes = atoi(argv[2]);
	const char *program = argv[4];
	if(nframes > npages){ //if more frames than pages
        nframes = npages;
    }
    frameTable = malloc(sizeof(int)*(nframes-1));
    lruTable = malloc(sizeof(int)*(nframes-1));
    initialize_frame_table();
    algorithm = argv[3];

/*
	if (strcmp(argv[3], "rand") == 0){
		page_fault_replacement_alg = 1;
	}
	if (strcmp(argv[3], "fifo") == 0){
		page_fault_replacement_alg = 2;
		oldest = 0;
	}
	if (strcmp(argv[3], "custom") == 0){
		page_fault_replacement_alg = 3;
	}


	ftarray = malloc(nframes * sizeof(int)); //for bytes
	int i;
	for (i= 0; i < nframes; i++){//initialize all to a number they'll will never be to check if it's used
		ftarray[i] = -1;
	}

	queueArray = malloc(nframes * sizeof(int)); //bytes
	for (i= 0; i < nframes; i++){	
		queueArray[i] = -1; //we set all to false
	}


	secondChance = malloc(nframes * sizeof(int)); //for bytes
	for (i= 0; i < nframes; i++){
		secondChance[i] = 0; //we set all to false
	}	
*/


	struct disk *disk = disk_open("myvirtualdisk",npages);
	if(!disk) {
		fprintf(stderr,"couldn't create virtual disk: %s\n",strerror(errno));
		return 1;
	}


	struct page_table *pt = page_table_create( npages, nframes, page_fault_handler );
	if(!pt) {
		fprintf(stderr,"couldn't create page table: %s\n",strerror(errno));
		return 1;
	}

	unsigned char *virtmem = page_table_get_virtmem(pt);

	//unsigned char *physmem = page_table_get_physmem(pt);
	physmem = page_table_get_physmem(pt);

	if(!strcmp(program,"alpha")) {
		alpha_program(virtmem,npages*PAGE_SIZE);

	} else if(!strcmp(program,"beta")) {
		beta_program(virtmem,npages*PAGE_SIZE);

	} else if(!strcmp(program,"gamma")) {
		gamma_program(virtmem,npages*PAGE_SIZE);

	} else if(!strcmp(program,"delta")) {
		delta_program(virtmem,npages*PAGE_SIZE);

	} else {
		fprintf(stderr,"unknown program: %s\n",argv[4]);
		return 1;
	}

	printf("Page Faults: %d\n", pageFaults);
	printf ("Disk Reads: %d\n", diskReads);
	printf("Disk Writes: %d\n", diskWrites); 


	page_table_delete(pt);
	disk_close(disk);

	free(frameTable);
    free(lruTable);

	return 0;
}
