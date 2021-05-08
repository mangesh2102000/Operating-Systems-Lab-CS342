/*Name: Chandrawanshi Mangesh Shivaji
Roll No.: 1801cs16
CS342 Operating Systems Lab End Sem Exam
Filename: Q1_i.c
Problem: Take the value of ‘c’ (c<r) and ‘r’ as input and each process requires ‘c’ copies of ‘r’ to complete its execution.
Print the maximum value of ‘n’ (number of processes) to ensure a deadlock free operation.
*/

// Assumption both c and r are positive integers

#include<stdio.h>

int main(int argc, char const *argv[])
{
	int c, r, n;
	printf("\nInput:\n");
	printf("Enter value of 'c' (copies of 'r' required for each process): ");
	scanf("%d", &c);	

	printf("Enter value of 'r' (total number of copies for single resource): ");
	scanf("%d", &r);

	if(c >= r){
		printf("Improper Input Values! Ensure that c<r.\n");
		return 1;
	}

	if(c == 1 && r > 0){
		printf("Infinite number of processes can be executed without deadlock\n\n");
		return 0;
	}

	/*
	First to every process we assign (c-1) resources i.e. total n*(c-1) resources are allocated 
	to ensure deadlock free state at least 1 resource should be remaining for any one of process to execute
	i.e. r > n*(c-1)
	 	 n*(c-1) <= r-1 
	     n <= (r-1)/(c-1)
	*/

	n = (r-1)/(c-1);

	printf("\nOutput:\n");
	printf("Maximum value of 'n' (number of processes) to ensure deadlock free operation: %d\n\n", n);

	return 0;
}
