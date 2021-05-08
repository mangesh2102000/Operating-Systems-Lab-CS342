/* Name : Chandrawanshi Mangesh Shivaji 
Roll Number : 1801CS16
CS342 Lab - Assignment 8
FileName : Q1.c 
Problem Statement : Create 2 threads to show mutex lock on the function*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h> 
#include <math.h> 

typedef void* address_t;

pthread_t threadID_with_lock;
pthread_mutex_t mutex_lock=PTHREAD_MUTEX_INITIALIZER;

void* threadFunction(address_t args){

	// Check if function can be accessed by current thread or not
	while(pthread_mutex_trylock(&mutex_lock) != 0){
		printf("\n(Thread ID : 0x%lx) cannot access function threadFunction(), lock acquired by (Thread ID : 0x%lx)\n", pthread_self(), threadID_with_lock);
	}

	// Print Statement after access
    threadID_with_lock = pthread_self();
    printf("\nLock acquired by (Thread ID : 0x%lx)\n", pthread_self());
    printf("\n(Thread ID : 0x%lx) is accessing function threadFunction()\n", pthread_self());

    for(int i=0;i<7500;i++){

    }

    pthread_mutex_unlock (&mutex_lock);
    printf("\nLock released by (Thread ID : 0x%lx)\n", pthread_self());
    
    pthread_exit(NULL);

}

// driver code
int main(int argc, char const *argv[])
{
	// declare variables to store thread info
	pthread_t threadID[2];
	address_t statusp;
	int status;

	for(int i=1;i<=2;i++){
		status = pthread_create(&threadID[i-1], NULL, threadFunction, &i);
	}

	for(int i=0;i<2;i++){
		pthread_join(threadID[i], &statusp);
	}

	return 0;
}

