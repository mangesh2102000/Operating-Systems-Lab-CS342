/* Name : Chandrawanshi Mangesh Shivaji 
Roll Number : 1801CS16
CS342 Lab - Assignment 8
FileName : Q2.c 
Problem Statement : Sum of Primes from 0 to 10000 using 4 threads and a global variable*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h> 
#include <math.h> 

#define MAX_THREADS 4

typedef void* address_t;

// Structure to store interval for given thread
typedef struct{
	int start;
	int end;
} interval;

// To check whether number is prime or not
bool is_prime[10005];

// Store sum of all primes, shared between all the threads
int sum_of_primes = 0;

// To ensure that more than one threads do not access shared variable at the same time
pthread_mutex_t mutex_lock=PTHREAD_MUTEX_INITIALIZER;

// Determine all primes from 0 to 10000
void initialize_and_determine_primes(){

	is_prime[0] = is_prime[1] = false;
	for(int i=2;i<10005;i++){
		is_prime[i] = true;
	}

	for(int i=2;i*i<=10000;i++){
		if(is_prime[i]){
			for(int j=i*i;j<=10000;j+=i){
				is_prime[j] = false;
			}
		}
	}
}

// Thread function to calculate sum of prime numbers in given interval (first to last)
void* calculate_sum_of_primes(address_t args){

	interval *interval_ptr = args;

	int first = interval_ptr->start, last = interval_ptr->end;

	for(int i=first;i<=last;i++){
		if(is_prime[i]){
			//printf("Thread ID = [0x%lx], Current Prime Number = %d\n", pthread_self(), i);
            pthread_mutex_lock(&mutex_lock);
			sum_of_primes += i;
            pthread_mutex_unlock(&mutex_lock);
		}
	}

	free(interval_ptr);
}

// driver code
int main(int argc, char const *argv[])
{
	initialize_and_determine_primes();

	// declare variables to store thread info
	pthread_t threadID[MAX_THREADS];
	address_t statusp;
	int status;

	int add = 2500;

	int first = 0, last = add;	

	for(int i=0;i<4;i++){

		// Store current interval 
		interval *interval_ptr = malloc(sizeof(*interval_ptr));
		interval_ptr->start = first;
		interval_ptr->end = last;
		
		// Call current thread
		status = pthread_create(&threadID[i], NULL, calculate_sum_of_primes, interval_ptr);

		// Free memory after successfull call to the thread
		if(status == 1)
			free(interval_ptr);

		// Determine interval for the next thread
		first = last + 1;
		last = first + add - 1;

	}

	// Join all the threads
	for(int i=0;i<4;i++){
		pthread_join(threadID[i], &statusp);
	}

	// Output
	printf("\nSum of all primes from 0 to 10000 is %d\n\n", sum_of_primes);
	return 0;
}

