/*****************************************************
 **Author: Jianzhi Li
 **Project: CS444 Concurrency 4 Problem 2 barber
 ****************************************************/

#include <pthread.h>
#include <stdio.h> 
#include <unistd.h>   
#include <stdlib.h>
#include <semaphore.h>
#include <sys/time.h>
#include <math.h>

#define TRUE 1
#define CHAIRS rand()%20 //the number of chairs I am using random number to test different number of chairs


sem_t barbers;
sem_t customers;
sem_t chairs;
sem_t sleep_barber;

pthread_mutex_t barber_mutex;

unsigned int wait_num = 0;
static int finish;

void *barber(void *arg);
void *customer(void *num);
int cut_hair(void);
int get_hair_cut(void);

int main(){
	
	int i, num_customers;
	int check_pCreate;
	
	num_customers = CHAIRS *3;
	
	pthread_t barber_p;
	pthread_t customer_p[num_customers];
	
	sem_init(&chairs, 0, CHAIRS);
	sem_init(&sleep_barber, 0, 0);
	
	check_pCreate = pthread_create(&barber_p,NULL,barber,NULL); //create barber thread
	
	if(check_pCreate != 0){//if the create function not return 0 that means create failed
		
		printf("Cannot create barber thread for barber.\n");
		return -1;
		
	}
	
	while(TRUE){
		
		usleep(300000);
		check_pCreate = pthread_create(&customer_p[num_customers], NULL, customer, NULL);
		
		if(check_pCreate != 0){
			
			printf("Cannot create customer thread for customer.\n");
			return -1;
			
		}
		
		
	}
	
	sem_destroy(&chairs);
	sem_destroy(&sleep_barber);
	
	return 0;
}

int cut_hair(void){
	
	printf("\n");
	printf("There is a customer here, I am woke up, it is time to work.\n");
	printf("Barber is not available, please wait. \n ");
	sleep(1); //time for hair cut_hair
	printf("Finished job with a customer, available.\n");
	
	
}
int get_hair_cut(void){
	
	printf("There has a customer cutting his/her hair, please wait.\n");
	sleep(2);
	printf("Finished cutting, got pretty.\n");
	
}


void *barber(void *arg){
	
	while(TRUE){
		
		sem_wait(&customers);//customer semaphore
		pthread_mutex_lock(&barber_mutex);
		wait_num = wait_num -1;
		sem_post(&barbers);
		pthread_mutex_unlock(&barber_mutex);
		cut_hair();
		
		if(!finish){
			printf("\n");
			printf("Barber: No customers come to me... I am sleep Zzzzzzzzzzzzzz\n");
			
		}
	}
	
}
void *customer(void *num){
	
	pthread_mutex_lock(&barber_mutex);
	
	//int CHAIRS;
	//printf("\n");
	//printf("To test this program can handle different number of chairs, please enter a number : ");
	//scanf("%d", &CHAIRS);
	
	if(wait_num < CHAIRS){
		
		wait_num = wait_num + 1;
		sem_post(&customers);
		pthread_mutex_unlock(&barber_mutex);
		sem_wait(&barbers);
		get_hair_cut();
		printf("There are %d customers in waiting.\n", wait_num);
	}
	
	else{
		
		printf("SORRY!!!There is no chairs for new customers.\n");
		pthread_mutex_unlock(&barber_mutex);
		
	}
	
}
