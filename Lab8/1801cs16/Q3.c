/* Name : Chandrawanshi Mangesh Shivaji 
Roll Number : 1801CS16
CS342 Lab - Assignment 8
FileName : Q3.c 
Problem Statement : Dining Philosophers Problem Solution*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#define N 5
#define LEFT (idx)%N
#define RIGHT (idx+1)%N
#define MAXSIZE 3

int allocationMatrix[N][N];
int requestMatrix[N][N];

pthread_mutex_t wait_lock;
pthread_mutex_t print_lock;
int semFork[N];

// Function to initialize all required variables
void initialize(){
	for(int i=0;i<N;i++){
		semFork[i] = 1;
	}

	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			allocationMatrix[i][j] = 0;
			requestMatrix[i][j] = 0;
		}
	}
}

// Function to pick one of the forks by the philosopher
void take_fork(int idx, int side){

	// if no LEFT fork is with the philosopher, dont allow to have right fork
	if(side == RIGHT && allocationMatrix[idx][LEFT]==0)
		return;

	// Wait for fork to be free
	while(!semFork[side]){

		// if LEFT fork is dropped to deadlock, drop right one also
		if(side == RIGHT && allocationMatrix[idx][LEFT]==0){
			requestMatrix[idx][side]=0;
			return;
		}
	}	

	// Modify the concerned variables
	pthread_mutex_lock(&wait_lock);
	requestMatrix[idx][side]=0;
	allocationMatrix[idx][side]=1;
	semFork[side]=0; 
	pthread_mutex_unlock(&wait_lock);
}

// Function to drop the fork 
void put_fork(int idx, int side){
	allocationMatrix[idx][side] = 0;
	semFork[side] = 1;
}

// Functions to print respective matrices
void print_request_matrix(){
	pthread_mutex_lock(&print_lock);
	printf("Printing Request Matrix : \n");
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			printf("%d ", requestMatrix[i][j]);
		}
		printf("\n");
	}
	pthread_mutex_unlock(&print_lock);

}	

void print_allocation_matrix(){

	pthread_mutex_lock(&print_lock);
	printf("\nPrinting Allocation Matrix : \n");
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			printf("%d ", allocationMatrix[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	pthread_mutex_unlock(&print_lock);
}

void deadlockDetection(){

	int cnt[N];

	// Check if any fork is yet to be taken, if it is the case no deadlock 
	for(int i=0;i<N;i++){
		cnt[i]=0;
		if(semFork[i])
			return;
	}

	// Check if all philosopher have one fork each, if yes there is a deadlock
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(allocationMatrix[i][j])
				cnt[i] += 1;
		}
	}

	for(int i=0;i<N;i++){
		if(cnt[i] != 1)
			return;
	}

	// Preempt one of the Philosopher to remove deadlock
	printf("Parent detects deadlock,going to initiate recovery\n");
	int idx=rand()%N;
	put_fork(idx,LEFT);
	printf("Parent pre-empts Philosopher %d\n", idx);
	print_request_matrix();
	print_allocation_matrix();
	return;
}

void* philosopher(void* args){
	int idx = *((int*)args);

	int thinkTime = (rand()%MAXSIZE)+1;
	int pickLag = (rand()%MAXSIZE)+1;
	int eatTime = (rand()%MAXSIZE)+1;
	while(1){

		// THINKING
		printf("Philosopher %d starts thinking\n", idx);
		sleep(thinkTime);
		requestMatrix[idx][LEFT]=0;
		requestMatrix[idx][RIGHT]=0;

		// HUNGRY
		printf("Philosopher %d is Hungry\n", idx);
		requestMatrix[idx][LEFT]=1;
		take_fork(idx, LEFT);
		printf("Philosopher %d grabs fork %d (left)\n", idx, LEFT);

		sleep(pickLag);
		requestMatrix[idx][RIGHT]=1;
		take_fork(idx, RIGHT);

		if(allocationMatrix[idx][LEFT]==0 && allocationMatrix[idx][RIGHT]==0)
			continue;

		// EATING
		printf("Philosopher %d grabs fork %d (right)\n", idx, RIGHT);
		printf("Philosopher %d starts eating.\n", idx);
		sleep(eatTime);

		printf("Philosopher %d ends eating and releases forks %d (left) and %d (right)\n", idx, LEFT, RIGHT);

		// DROP forks after finished EATING
		put_fork(idx, LEFT);
		put_fork(idx, RIGHT);

		// Uncommenting these will print matrices after every iteration but due to multiple threads it will not be in proper order
		// print_request_matrix();
		// print_allocation_matrix();
	}
	pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
	// Required thread variables
	pthread_t threadID[N];
	int status;

	// Create threads
	int idx[N];
	for(int i=0;i<N;i++){
		idx[i] = i;
		status = pthread_create(&threadID[i], NULL, philosopher, &idx[i]);
	
		if(status != 0){
			perror("Error in thread creation!\n");
		}
	}	

	initialize();

	while(1){
		deadlockDetection();
	}

	// Join Threads
	for(int i=0;i<N;i++){
		pthread_join(threadID[i], NULL);
	}
	return 0;
}