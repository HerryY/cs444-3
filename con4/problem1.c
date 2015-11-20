/*****************************************
 **Author: Jianzhi Li
 **Project: CS444 Concurrency 4 Problem 1
 *****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define NUM_THREADS 9
#define MAX_RESOURCE 3
#define TRUE 1

pthread_mutex_t shareResource;

sem_t resource;
sem_t lock;
static int block;

void *threads(void* arg);
int block_fuc(int num);


int main(int argc, char *argv[]){
	
	int i;
	int check_pCreate;
	
	pthread_t shareResource[NUM_THREADS];
	
	block = 0;
	
	sem_init(&resource, 0, MAX_RESOURCE);
	sem_init(&lock, 0, 1);
	
	for(i = 0; i < NUM_THREADS; i++){
		
		check_pCreate = pthread_create(&shareResource[i], NULL, threads, NULL);
		
		if(check_pCreate != 0){
			
			printf("\n");
			printf("ERROR: Cannot create threads. \n");
			return -1;
		}
		
		usleep(30000);
	}
	
	void *status;
	
	for(i = 0; i < NUM_THREADS; i++){
		
		check_pCreate = pthread_join(shareResource[i], &status);
		
		
		if(check_pCreate != 0 ){
			
			printf("\n");
			printf("ERROR: Cannot create threads. \n");
			
		}
		
		
		
	}
	
	sem_destroy(&resource);
	sem_destroy(&lock);
	pthread_mutex_destroy(&shareResource);
	
	return 0;
}


void *threads(void* arg){
	
	int pthread_num = *((int*)arg);
	int count;
	
	while(TRUE){
		
		if(count > 0){
			
			count --;
			printf("Thread %d is using resource. \n", pthread_num);
			sleep(rand()%3);
			count ++;
			return 0;
			
		}
		
		else{
			
			printf("Threads %d blocked since there is no resource.\n", pthread_num);
			pthread_mutex_lock(&shareResource);
			
		}
	}
	
}
int block_fuc(int num){
	
	int sleepTime;
	
	sleepTime = rand()%4 + 1;
	printf("Thread %d is using resource.\n", num);
	sleep(sleepTime);
	
	return -1;
	
	
}