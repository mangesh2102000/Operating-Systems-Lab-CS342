/* Name : Chandrawanshi Mangesh Shivaji 
Roll Number : 1801CS16
CS342 Lab - Assignment 9
FileName : README.txt */

Please make sure you are in the same folder as .c files
.c file names Q1.c, Q2.c, Q3.c for respective questions

Q1) =>

// Compilation :
$ gcc Q1.c -o Q1

// Example :
$ ./Q1
SIMULATION OF DEADLOCK PREVENTION
Enter no. of processes, resources: 3 2
Enter allocation matrix:
2 4 5
3 4 5
Enter max matrix:
4 3 4
5 6 1
Enter available matrix:
2 2
Printing need matrix:
2 2 
-1 2 
-1 -4 


Failing: Mutual Exclusion
 By allocating required resources to process 0 dead lock is prevented 

Lack of preemption
 By allocating required resources dead lock is prevented

Failing: Hold and Wait Condition

Q2) =>

// Compilation :
$ gcc Q2.c -o Q2

// Example :
$ ./Q2

SIMULATION OF DEADLOCK DETECTION

Enter no. of processes: 4
Enter no. of resources: 5
Total Amount of the Resource R1: 2
Total Amount of the Resource R2: 1
Total Amount of the Resource R3: 1
Total Amount of the Resource R4: 2
Total Amount of the Resource R5: 1
Enter the request matrix:
0 1 0 0 1
0 0 1 0 1
0 0 0 0 1
1 0 1 0 1
Enter the allocation matrix:
1 0 1 1 0
1 1 0 0 0
0 0 0 1 0
0 0 0 0 0

Deadlock Detected
Process 1 is deadlocked (1-based indexing)


Q3) =>

// Compilation : 
$ gcc Q3.c -o Q3

// Example :
$ ./Q3

SIMULATION OF BANKER'S DEADLOCK AVOIDANCE

Enter no. of processes: 5
Enter no. of resources: 3
Total Amount of the Resource R1: 10
Total Amount of the Resource R2: 5
Total Amount of the Resource R3: 7

Enter the max matrix:
P0 7 5 3
P1 3 2 2
P2 9 0 2
P3 2 2 2
P4 4 3 3

Enter the allocation matrix:
P0 0 1 0
P1 2 0 0
P2 3 0 2
P3 2 1 1
P4 0 0 2

Printing Need Matrix:
7 4 3 
1 2 2 
6 0 0 
0 1 1 
4 3 1 

Safe sequences are:

P1 -> P3 -> P0 -> P2 -> P4
P1 -> P3 -> P0 -> P4 -> P2
P1 -> P3 -> P2 -> P0 -> P4
P1 -> P3 -> P2 -> P4 -> P0
P1 -> P3 -> P4 -> P0 -> P2
P1 -> P3 -> P4 -> P2 -> P0
P1 -> P4 -> P3 -> P0 -> P2
P1 -> P4 -> P3 -> P2 -> P0
P3 -> P1 -> P0 -> P2 -> P4
P3 -> P1 -> P0 -> P4 -> P2
P3 -> P1 -> P2 -> P0 -> P4
P3 -> P1 -> P2 -> P4 -> P0
P3 -> P1 -> P4 -> P0 -> P2
P3 -> P1 -> P4 -> P2 -> P0
P3 -> P4 -> P1 -> P0 -> P2
P3 -> P4 -> P1 -> P2 -> P0

There are 16 safe sequences from the current state
