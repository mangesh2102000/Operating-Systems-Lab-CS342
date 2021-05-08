/* Name : Chandrawanshi Mangesh Shivaji 
Roll Number : 1801CS16
CS342 Lab - Assignment 9
FileName : Q1.c 
Problem Statement : Program to simulate DEADLOCK PREVENTION ALGORITHM*/

/*
NOTE: The question is ambiguous and the objective of the question is not be clear to me.
Also, the test case provided allocation matrix entities are greater than max matrix which is not possible.
*/

#include <stdio.h>
#include <stdlib.h>

#define N 505	// Max number of processes
#define M 505   // Max number of resources

// Variable Declarations
int num_of_processes, num_of_resources;
int alloc[N][M];
int max[N][M];
int need[N][M];
int avail[M];	
int total[M];
int finish[N];
int golbal_flag = 0;

void simulate(){

	while(1){
		int flag = 0;
		for(int i=0, golbal_flag = 0;i<num_of_processes;i++){
			if(finish[i] == 0){
				flag = 0; 
				for(int j=0;j<num_of_resources;j++){
					if(need[i][j] > avail[j]){
						flag = 1;
						break;
					}
				}

				if(flag == 0){
					for(int j=0;j<num_of_resources;j++){
						avail[j] += alloc[i][j];
					}
					golbal_flag = 1;
					finish[i] = 1;
				}
			}
		}
		if(golbal_flag == 0)
			break;
	}
}

// driver code
int main(int argc, char *argv[])
{
	// Input 
	printf("SIMULATION OF DEADLOCK PREVENTION\n");

	printf("Enter no. of processes, resources: ");
	scanf("%d %d", &num_of_processes, &num_of_resources);


	int i,j;
	printf("Enter allocation matrix:\n");
	for(i=0;i<num_of_resources;i++){
		total[i]=0;
		for(j=0;j<num_of_processes;j++){
			scanf("%d", &alloc[j][i]);
			total[i] += alloc[j][i];
		}
	}

	printf("Enter max matrix:\n");
	for(i=0;i<num_of_resources;i++){
		for(j=0;j<num_of_processes;j++){
			finish[i] = 0;
			scanf("%d", &max[j][i]);
		}
	}

	printf("Enter available matrix:\n");
	for(i=0;i<num_of_resources;i++){
		scanf("%d", &avail[i]);
		total[i] += avail[i];
	}

	printf("Printing need matrix:\n");
	for(i=0;i<num_of_processes;i++){
		for(j=0;j<num_of_resources;j++){
			need[i][j] = max[i][j] - alloc[i][j];
			printf("%d ",need[i][j]);
		}
		printf("\n");
	}

	//simulate();

	for(int i=0;i<num_of_processes;i++){
		if(golbal_flag == 0){
			if(finish[i] == 0){
			
				// Case 1
				printf("\n\nFailing: Mutual Exclusion");
				for(int j=0;j<num_of_resources;j++){
					if(avail[j] < need[i][j])
						avail[j] = need[i][j];
				}

				simulate();

				if(finish[i] == 1){
					printf("\n By allocating required resources to process %d dead lock is prevented ",i); 
				}

				// Case 2
				printf("\n\nLack of preemption");
				for(int j=0;j<num_of_resources;j++){
					if(avail[j] < need[i][j])
						avail[j] = need[i][j];
					alloc[i][j] = 0;
				}

				simulate();

				if(finish[i] == 1){
					printf("\n By allocating required resources dead lock is prevented"); 
				}

				// Case 3
				printf("\n\nFailing: Hold and Wait Condition\n");
			
				for(int j=0;j<num_of_resources;j++){
					if(avail[j] < need[i][j])
						avail[j] = need[i][j];
				}
				simulate();

				// Avoiding any one of above 3 conditions can prevent deadlock
			}
		}	
	}

	return 0;
}
