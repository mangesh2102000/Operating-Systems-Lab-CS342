/* Name : Chandrawanshi Mangesh Shivaji 
Roll Number : 1801CS16
CS342 Lab - Assignment 8
FileName : README.txt*/

Please make sure you are in the same folder as .c files
.c file names Q1.c, Q2.c, Q3.c for respective questions

Q1) =>

Note: Out of order Printing of release of lock due to  multiple threads running at same time

/* Result:

// Compilation: 
$ gcc Q1.c -o Q1 -lpthread
$ ./Q1

Lock acquired by (Thread ID : 0x7fd024046640)

(Thread ID : 0x7fd024046640) is accessing function threadFunction()

(Thread ID : 0x7fd023845640) cannot access function threadFunction(), lock acquired by (Thread ID : 0x7fd024046640)

Lock acquired by (Thread ID : 0x7fd023845640)

(Thread ID : 0x7fd023845640) is accessing function threadFunction()

Lock released by (Thread ID : 0x7fd023845640)

Lock released by (Thread ID : 0x7fd024046640)

*/

Q2) =>

/* Result

// Compilation:
$ gcc Q2.c -o Q2 -lpthread

$ ./Q2

Sum of all primes from 0 to 10000 is 5736396

*/


Q3)=>

// Note:
1) Program will run till it is terminated by the user
2) I have not printed matrices (request and allocation) at each step because it is leading to out of order printing 
due to multiple threads making it really difficult to understand output (Though if want to see it printing I have wriiten 
commented lines, just need to uncomment them)


/* Result

// Compilation:
$ gcc Q3.c -o Q3 -lpthread

$ ./Q3
Philosopher 0 starts thinking
Philosopher 1 starts thinking
Philosopher 3 starts thinking
Philosopher 4 starts thinking
Philosopher 2 starts thinking
Philosopher 1 is Hungry
Philosopher 1 grabs fork 1 (left)
Philosopher 0 is Hungry
Philosopher 0 grabs fork 0 (left)
Philosopher 3 is Hungry
Philosopher 3 grabs fork 3 (left)
Philosopher 2 is Hungry
Philosopher 2 grabs fork 2 (left)
Philosopher 4 is Hungry
Philosopher 4 grabs fork 4 (left)
Parent detects deadlock,going to initiate recovery
Parent pre-empts Philosopher 1
Printing Request Matrix : 
0 0 0 0 0 
0 0 0 0 0 
0 0 0 0 0 
0 0 0 0 0 
0 0 0 0 0 

Printing Allocation Matrix : 
1 0 0 0 0 
0 0 0 0 0 
0 0 1 0 0 
0 0 0 1 0 
0 0 0 0 1 


Philosopher 0 grabs fork 1 (right)
Philosopher 0 starts eating.
Philosopher 1 starts thinking
Philosopher 0 ends eating and releases forks 0 (left) and 1 (right)
Philosopher 0 starts thinking
Philosopher 4 grabs fork 0 (right)
Philosopher 4 starts eating.
Philosopher 1 is Hungry
Philosopher 1 grabs fork 1 (left)
Philosopher 0 is Hungry
Philosopher 4 ends eating and releases forks 4 (left) and 0 (right)
Philosopher 4 starts thinking
Philosopher 3 grabs fork 4 (right)
Philosopher 3 starts eating.
Philosopher 0 grabs fork 0 (left)
Philosopher 3 ends eating and releases forks 3 (left) and 4 (right)
Philosopher 3 starts thinking
Philosopher 2 grabs fork 3 (right)
Philosopher 2 starts eating.
Philosopher 4 is Hungry
Philosopher 4 grabs fork 4 (left)
Philosopher 2 ends eating and releases forks 2 (left) and 3 (right)
Philosopher 2 starts thinking
Philosopher 1 grabs fork 2 (right)
Philosopher 1 starts eating.
Philosopher 3 is Hungry
Philosopher 3 grabs fork 3 (left)
Philosopher 1 ends eating and releases forks 1 (left) and 2 (right)
Philosopher 1 starts thinking
Philosopher 2 is Hungry
Philosopher 2 grabs fork 2 (left)
Philosopher 0 grabs fork 1 (right)
Philosopher 0 starts eating.
Philosopher 0 ends eating and releases forks 0 (left) and 1 (right)
Philosopher 0 starts thinking
Philosopher 4 grabs fork 0 (right)
Philosopher 4 starts eating.
Philosopher 1 is Hungry
Philosopher 1 grabs fork 1 (left)
Philosopher 0 is Hungry
Philosopher 4 ends eating and releases forks 4 (left) and 0 (right)
Philosopher 4 starts thinking
Philosopher 3 grabs fork 4 (right)
Philosopher 3 starts eating.
Philosopher 0 grabs fork 0 (left)
Philosopher 3 ends eating and releases forks 3 (left) and 4 (right)
Philosopher 3 starts thinking
Philosopher 2 grabs fork 3 (right)
Philosopher 2 starts eating.
Philosopher 4 is Hungry
Philosopher 4 grabs fork 4 (left)
Philosopher 2 ends eating and releases forks 2 (left) and 3 (right)
Philosopher 2 starts thinking
Philosopher 1 grabs fork 2 (right)
Philosopher 1 starts eating.
^C
mangesh2102000@Linux-Ubuntu:~/Documents$ 

*/
