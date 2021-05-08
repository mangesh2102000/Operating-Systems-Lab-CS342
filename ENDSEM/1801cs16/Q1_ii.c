/*Name: Chandrawanshi Mangesh Shivaji
Roll No.: 1801cs16
CS342 Operating Systems Lab End Sem Exam
Filename: Q1_ii.c
Problem: Take the value of a number of processes ‘n’ and number of copies ‘c(i)’ for process n(i) as input. 
Each process needs a different number of copies ‘c(i)’ of single instance resources ‘r’.
Print the, maximum/minimum copies of ‘r’ are required for the system not guaranteed/guaranteed to be deadlock free operation.
*/

#include<stdio.h>

int main(int argc, char const *argv[])
{
	int n;
	printf("\nInput:\n");
	printf("Enter value of 'n' (number of processes): ");
	scanf("%d", &n);

	int c[n];	
	printf("Enter values of 'c(i)' (copies of single instance resource required for ith process):\n");
	for(int i=0;i<n;i++){
		scanf("%d", &c[i]);
	}

	int max_r = 0, min_r = 0;

	/* To calculate max number of resources to ensure deadlock we can assign 
	(c1 - 1) resources to process 1
	(c2 - 1) resources to process 2
	(c3 - 1) resources to process 3
	.......
	(cn - 1) resources to process n

	Now no process can process further if no more resources are available 
	so max count to not guarantee deadlock free state will be sum(c(i)-1) for i(1,n)

	if we have at least 1 more resource deadlock will never occur
	so min count to guarantee deadlock free	state will be 1 + sum(c(i)-1) for i(1,n)
	*/

	for(int i=0;i<n;i++){
		max_r += (c[i] - 1);
	}

	min_r = max_r + 1;

	printf("\nOutput:\n");
	printf("Maximum value of 'r' (total number of single instance resource) required to not guarantee deadlock free operation: %d\n\n", max_r);
	printf("Minimum value of 'r' (total number of single instance resource) required to guarantee deadlock free operation: %d\n\n", min_r);


	return 0;
}
