/****************************************************
 * This is a test that will use system calls to open 
 * a file, read from it, write to it and close it.
 *
 ****************************************************/

#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "capi.h"

using namespace std;


#ifdef DEBUG
pthread_mutex_t lock;
#endif

// Function executed by each thread
void* read_and_write(void * threadid);

int main(int argc, char* argv[]){ // main begins
	
	// Read in the command line arguments
	unsigned int numThreads = 1;

	// Declare threads and related variables
	pthread_t threads[numThreads];
	pthread_attr_t attr;
	
#ifdef DEBUG
	cout << "This is the function main()" << endl;
#endif

	// Initialize threads and related variables
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

#ifdef DEBUG
	cout << "Spawning threads" << endl;
#endif
	for(unsigned int i = 0; i < numThreads; i++) 
        pthread_create(&threads[i], &attr, read_and_write, (void *) i);

	// Wait for all threads to complete
	for(unsigned int i = 0; i < numThreads; i++) 
        pthread_join(threads[i], NULL);

	pthread_exit(NULL);
} // main ends

void* read_and_write(void *threadid){

	// Declare local variables
	int tid;
	CAPI_return_t rtnVal;

	rtnVal = CAPI_Initialize(&tid);

	// Initialize local variables
	CAPI_rank(&tid);

    // Do the work
    FILE *fid;
    fid = fopen("./input", "r");

    int data_size = 1024 * sizeof(char);

    char *the_data = (char *)malloc(data_size);

    int read = fread(the_data,data_size, sizeof(char), fid);

    printf("Read: %s\n", the_data);

	pthread_exit(NULL);
}
