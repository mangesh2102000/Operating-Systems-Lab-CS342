/* Name : Chandrawanshi Mangesh Shivaji 
Roll Number : 1801CS16
CS342 Lab - Assignment 7
FileName : README.txt*/

Please make sure you are in the same folder as .cpp files
.cpp file names Q1.cpp, Q2.cpp, Q3.cpp for respective questions

Q1) =>

/* Result:

Compilation:
$ g++ Q1.cpp -o Q1

example a (given example in assignment)
$ ./Q1

Enter number of total processes (n), time quantum (tq) on First Line and
Specify arrival_time and burst_time of n processes on following lines (ith line should contain data for ith process) : 
6 2 
0 4
1 5
2 2
3 1
4 6
6 3

Scheduing Algorithm Used : Round Robin

Average Waiting Time : 7.33    Average Turnaround Time : 10.83
Completion order of Processes : P3 P1 P4 P2 P6 P5 

example b
$ ./Q1

Enter number of total processes (n), time quantum (tq) on First Line and
Specify arrival_time and burst_time of n processes on following lines (ith line should contain data for ith process) : 
6 4
0 5
1 6
2 3
3 1
4 5
6 4

Scheduing Algorithm Used : Round Robin

Average Waiting Time : 11.33    Average Turnaround Time : 15.33
Completion order of Processes : P3 P4 P1 P6 P2 P5 

*/

Q2) =>

/* Result:

Compilation:
$ g++ Q2.cpp -o Q2

example a (given example in assignment)
$ ./Q2

Enter number of total processes (n) on First Line and
Specify arrival_time, burst_time, priority of n processes on following lines (ith line should contain data for ith process) : 
4
0 10 5
1 6 4
3 2 2
5 4 0

Scheduing Algorithm Used : Non-preemptive Priority

Average Waiting Time : 7.75    Average Turnaround Time : 13.25
Completion order of Processes : P1 P4 P3 P2 

example b
$ ./Q2

Enter number of total processes (n) on First Line and
Specify arrival_time, burst_time, priority of n processes on following lines (ith line should contain data for ith process) : 
7
0 3 2
2 5 6
1 4 3
4 2 5
6 9 7
5 4 4
7 10 10

Scheduing Algorithm Used : Non-preemptive Priority

Average Waiting Time : 7.71    Average Turnaround Time : 13.00
Completion order of Processes : P1 P3 P6 P4 P2 P5 P7 

*/


Q3) =>

IMPORTANT NOTE : In this question, I have implemented program for different number of queues, like we can have 2,3,etc any number of 
queues, Each queue has a different time quantum and it is supposed to be given as input by user ( sequentially from 1st queue(highest priority) to qth queue(least priority) ) on the second line of input.

/* Result:

Compilation:
$ g++ Q3.cpp -o Q3

example a (given example in assignment)
$ ./Q3

Enter number of total processes (n), number of total queues(q) on First Line,
Time quantum for each queue on Second Line and
Specify arrival_time, burst_time, priority queue index of n processes on following lines (ith line should contain data for ith process) : 
5 2
4 3 	 (here, time quantum of queue1 = 4 and time quantum of queue2 = 3)
0 10 2
3 7 1
4 6 2
12 5 1
18 8 1


Scheduing Algorithm Used : Non-Preemptive Multi-level Queue

Average Waiting Time : 10.40    Average Turnaround Time : 17.60
Completion order of Processes : P2 P4 P5 P3 P1 

example b
$ ./Q3

Enter number of total processes (n), number of total queues(q) on First Line,
Time quantum for each queue on Second Line and
Specify arrival_time, burst_time, priority queue index of n processes on following lines (ith line should contain data for ith process) :
4 2
2 100
0 4 1
0 3 1
0 8 2
10 5 1

Scheduing Algorithm Used : Non-Preemptive Multi-level Queue

Average Waiting Time : 4.50    Average Turnaround Time : 9.50
Completion order of Processes : P1 P2 P3 P4 

example c (with 3 queues)
e$ ./Q3

Enter number of total processes (n), number of total queues(q) on First Line,
Time quantum for each queue on Second Line and
Specify arrival_time, burst_time, priority queue index of n processes on following lines (ith line should contain data for ith process) :
6 3
2 3 4
0 15 1
5 5 3
6 12 2
8 12 1
9 13 2
12 8 3

Scheduing Algorithm Used : Non-Preemptive Multi-level Queue

Average Waiting Time : 28.50    Average Turnaround Time : 39.33
Completion order of Processes : P1 P4 P3 P5 P2 P6 

*/