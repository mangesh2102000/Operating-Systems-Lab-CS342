/* Name : Chandrawanshi Mangesh Shivaji 
Roll Number : 1801CS16
CS342 Lab - Assignment 9
FileName : Q3.c 
Problem Statement : Program to simulate BANKER'S DEADLOCK AVOIDANCE ALGORITHM*/

#include <stdio.h>
#include <stdlib.h>

#define N 505  // Max number of processes
#define M 505  // Max number of resources

// Variable Declaration
int num_of_processes, num_of_resources;
int total[M];
int used[M];
int avail[M];

int max[N][M];
int alloc[N][M];
int need[N][M];

int work[M];
int finish[N];
int count;

// Function to print all the safe sequences from current state 
void print_safe_sequences(int idx, int safe_sequence[]){

	int flag;
	for(int i=0;i<num_of_processes;i++){
		flag = 0;
		if(finish[i] == 0){

			// Check if ith process can be added to the sequence
			for(int j=0;j<num_of_resources;j++){
				if(need[i][j] > work[j]){
					flag = 1; 
					break;
				}
			}

			// Safe to add ith process to sequence 
			if(flag == 0){
				for(int j=0;j<num_of_resources;j++){
					work[j] += alloc[i][j];
				}
				// Mark Process as finished (included in safe sequence)
				finish[i] = 1;

				safe_sequence[idx++] = i;
				print_safe_sequences(idx, safe_sequence);
				idx--;

				// Unmark Process, (to include in other possible safe sequences)
				finish[i] = 0;

				for(int j=0;j<num_of_resources;j++){
					work[j] -= alloc[i][j];
				}
			}
		}		
	}

	// Print safe sequence 
	if(idx == num_of_processes){
		count++;
		for(int i=0;i<num_of_processes;i++){
			if(i != num_of_processes-1)
				printf("P%d -> ", safe_sequence[i]);
			else
				printf("P%d\n", safe_sequence[i]);
		}
	}
}

// driver code
int main(int argc, char *argv[])
{
	// Input 
	printf("\nSIMULATION OF BANKER'S DEADLOCK AVOIDANCE\n");

	printf("\nEnter no. of processes: ");
	scanf("%d", &num_of_processes);
	printf("Enter no. of resources: ");
	scanf("%d", &num_of_resources);

	for(int i=0;i<num_of_resources;i++){
		printf("Total Amount of the Resource R%d: ", i+1);
		scanf("%d", &total[i]);
	}

	printf("\nEnter the max matrix:\n");
	for(int i=0;i<num_of_processes;i++){
		printf("P%d ",i);
		for(int j=0;j<num_of_resources;j++){
			used[j]=0;
			scanf("%d", &max[i][j]);
		}
	}

	printf("\nEnter the allocation matrix:\n");
	for(int i=0;i<num_of_processes;i++){
		finish[i] = 0;
		printf("P%d ",i);
		for(int j=0;j<num_of_resources;j++){
			scanf("%d", &alloc[i][j]);
			used[j] += alloc[i][j];
			need[i][j] = max[i][j] - alloc[i][j];
		}
	}

	// Store available entity for each resource type 
	for(int i=0;i<num_of_resources;i++){
		avail[i] = total[i] - used[i];
		work[i] = avail[i];
	}

	printf("\nPrinting Need Matrix:\n");
	for(int i=0;i<num_of_processes;i++){
		for(int j=0;j<num_of_resources;j++){
			printf("%d ", need[i][j]);
		}
		printf("\n");
	}

	int safe_sequence[num_of_processes];
	int idx = 0;
	count = 0;

	// Output
	printf("\nSafe sequences are:\n\n");

	// Call to print all possible safe sequences
	print_safe_sequences(idx, safe_sequence);
	printf("\nThere are %d safe sequences from the current state\n", count);

	return 0;
}
