/***************************************************************************
 **Author: Jianzhi Li
 **Project: CS444 Concurrency Project 1
 **Date: 10/12/2015
 ****************************************************************************/
 
 
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>
#include<malloc.h>

#define N 32; //32 items on the buffer for maximum
#define PC 1; //number of consumer or producer
 
//int buff[N]= {0};
 
pthread_mutex_t mutex; //mutex lock, every time only one thread can access buffer
sem_t full; //if buffer is full then stop producer to produce items
sem_t empty; //if the buffer is empty then stop consumers to consume items
 
int pro = 0; //where the producer produce items
int pro_id = 0; //id for producer
int con = 0; //where consumer consume items
int con_id = 0; //id for consumer
 
void *producer();
void *consumer();
void print_buff();
 
 
 int main(){
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 return 0;
 }
 
/*void print_buff(){
	
	int i;
	for(i = 0; i < N; i++)
		printf("\n");
		printf("Buffer has %d", buff[i]);
		printf("\n");
	
}*/
 
 void *producer(){
	 
	 int id = ++ pro_id;
	 
	 while(1){
	 
	 sleep(1);
	 sem_wait(&empty);
	 pthread_mutex_lock(&mutex);
	 pro = pro % N;
	 
	 printf("Producer %d in %d.", id, pro);
	 
	// buff[pro] = 1;
	// print_buff();
	 ++pro;
	 
	 pthread_mutex_unlock(&mutex);
     sem_post(&full); 
	 }
	 
 }

