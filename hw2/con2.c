/***************************************************
 **Author:Jianzhi Li
 **Project: CS444 Concurrency Programming 2
 **Date: 10/22/2015
 ***************************************************/




#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <memory.h>
#include <math.h>
#include <errno.h>



#define N 5

pthread_mutex_t forks[5]; //forks to be mutex

void think(void *ph);
void get_forks(void *ph, int *left, int *right);
void eat(void *ph);
void put_forks(void *ph, int *left, int *right);
void *table(void *ph);

int main(){
	
	pthread_t thread1, thread2, thread3, thread4, thread5;
	
	int i;
	
	for(i = 0; i < 5; i++)
	
	pthread_mutex_init(&forks[i], NULL);
	
	pthread_create(&thread1,NULL, table, "A");
	pthread_create(&thread2,NULL, table, "B");
	pthread_create(&thread3,NULL, table, "C");
	pthread_create(&thread4,NULL, table, "D");
	pthread_create(&thread5,NULL, table, "E");

	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	pthread_join(thread3,NULL);
	pthread_join(thread4,NULL);
	pthread_join(thread5,NULL);
	
	
	return 0;
}

void *table(void *ph){
	
	char phi;
	phi = *(char*)ph;
	
	
	int left_fork, right_fork;//fork on the left and fork on the right
	//there is five situation to pick up forks. Only people pick up two forks under those rules are allowed
	switch(phi){
		
		case 'A':
			left_fork = 5;
			right_fork = 1;
			break;
		case 'B':
			left_fork = 1;
			right_fork = 2;
			break;
		case 'C':
			left_fork = 2;
			right_fork = 3;
			break;
		case 'D':
			left_fork = 3;
			right_fork = 4;
			break;
		case 'E':
			left_fork = 4;
			right_fork = 5;
			break;
		
		
	}
	while(1){
		
		think((void*)ph);
		get_forks((void*)ph, &left_fork, &right_fork);
		eat((void*)ph);
		put_forks((void*)ph, &left_fork, &right_fork);
		
	}
	pthread_exit(NULL);
	
}

void think(void *ph){
	
	char phi;
    phi = *(char*)ph;
	
	int think_time = 1 + rand()%20;//random thinking for 1 to 20 seconds
	
	usleep(think_time);//using microsecond intervals to observe if has a dead lock
	printf("%c philosopher is thinking for %d seconds\n", phi, think_time);
	
	
}
void get_forks(void *ph, int *left, int *right){
	
	 int l = *left;
	 int r = *right;
	char phi;
    phi = *(char*)ph;
	pthread_mutex_lock(&forks[l]);
	printf("%c philosopher picked up the fork %d\n", phi, l);//pick up the fork on the left
	
//if there has a thread waiting for another then destroy this mutex lock that is the way to avoid dead lock
		
		if(pthread_mutex_trylock(&forks[r]) == EBUSY){ 
//if the fork on the right is picked up by others then put down the fork just picked up since people have to have two forks then can eat	
			pthread_mutex_unlock(&forks[l]);//pick up the fork on left hand
			 
			
		}
  
	printf("%c philosopher picked up the fork %d\n", phi, r);
	
}

void eat(void *ph){
	
	char phi;
    phi = *(char*)ph;
	int eat_time = 2 + rand()%9;//random eating for 2 to 9 seconds
	printf("%c philosopher is eating for %d seconds.\n", phi, eat_time);
	usleep(eat_time);
	
	
}
void put_forks(void *ph, int *left, int *right){
	

	char phi;
    phi = *(char*)ph;
	int l = *left;
	int r = *right;
	pthread_mutex_unlock(&forks[l]);//put down the fork on left hand
	printf("%c philosopher put down the fork %d\n",phi, l);
	pthread_mutex_unlock(&forks[r]);
	printf("%c philosopher put down the fork %d\n",phi, r);//put down the fork on right hand

	
	
}