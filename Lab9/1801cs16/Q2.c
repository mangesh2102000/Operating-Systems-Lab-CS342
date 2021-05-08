/* Name : Chandrawanshi Mangesh Shivaji 
Roll Number : 1801CS16
CS342 Lab - Assignment 9
FileName : Q2.c 
Problem Statement : Program to simulate DEADLOCK DETECTION ALGORITHM*/

#include <stdio.h>
#include <stdlib.h>

#define N 505	// Max number of processes
#define M 505 	// Max number of resources

// Variable Declarations
int num_of_processes, num_of_resources;
int total[M];
int used[M];
int avail[M];	
int request[N][M];
int alloc[N][M];

int work[M];
int finish[N];
int safe_sequence[N];

// driver code
int main(int argc, char *argv[])
{
	// Input 
	printf("\nSIMULATION OF DEADLOCK DETECTION\n");

	printf("\nEnter no. of processes: ");
	scanf("%d", &num_of_processes);
	printf("Enter no. of resources: ");
	scanf("%d", &num_of_resources);

	for(int i=0;i<num_of_resources;i++){
		printf("Total Amount of the Resource R%d: ", i+1);
		scanf("%d", &total[i]);
	}

	printf("Enter the request matrix:\n");
	for(int i=0;i<num_of_processes;i++){
		for(int j=0;j<num_of_resources;j++){
			used[j]=0;
			scanf("%d", &request[i][j]);
		}
	}

	printf("Enter the allocation matrix:\n");
	for(int i=0;i<num_of_processes;i++){
		finish[i] = 1;
		for(int j=0;j<num_of_resources;j++){
			scanf("%d", &alloc[i][j]);
			if(alloc[i][j] != 0)
				finish[i] = 0;
			used[j] += alloc[i][j];
		}
	}

	// Store available entity for each resource type
	for(int i=0;i<num_of_resources;i++){
		avail[i] = total[i] - used[i];
		work[i] = avail[i];
	}

	int curr_idx=0;
	int idx=-1, flag=0, deadlock = -1;

	// Safety Algorithm for deadlock detection
	for(int i=0;i<num_of_processes;i++){
		idx=-1;
		flag=0;
		if(finish[i] == 0){
			// Check if current process can be allocated requested resources	
			for(int j=0;j<num_of_resources;j++){
				if(request[i][j] > work[j]){
					flag = 1; 
					break;
				}
			}

			// If yes, allocate the resources and finish the process
			if(flag == 0){
				for(int j=0;j<num_of_resources;j++){
					work[j] += alloc[i][j];
				}
				safe_sequence[curr_idx++] = i+1;
				finish[i] = 1;
			}
			else{
				// if no there exits a deadlock
				for(int j=0;j<num_of_processes;j++){
					if(finish[i] == 0){
						deadlock = i;
						break;
					}
				}
			}
		}
		else{
			safe_sequence[curr_idx++] = i+1;
		}

		// if deadlock exit the loop
		if(deadlock != -1)
			break;
	}

	// Output
	if(deadlock == -1){
		printf("\nNo Deadlock Detected, System is in safe state\n");
		printf("(1-based indexing) One Possible Safe Sequence: ");
		for(int i=0;i<num_of_processes;i++){
			printf("P%d ", safe_sequence[i]);
		}
		printf("\n\n");
	}
	else{
		printf("\nDeadlock Detected\n");
		printf("Process %d is deadlocked (1-based indexing)\n\n", deadlock+1);
	}

	return 0;
}
