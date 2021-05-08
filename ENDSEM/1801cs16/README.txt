/*Name: Chandrawanshi Mangesh Shivaji
Roll No.: 1801cs16
CS342 Operating Systems Lab End Sem Exam
Filename: README.txt
*/

Please keep all the files in same folder
Q1_i.c, Q1_ii.c, Q2.cpp, Q3.cpp, Q4.cpp are the filenames for source codes of repective questions

Q1)=>

i)=>

// Compilation: gcc Q1_i.c -o Q1_i

// Execution: ./Q1_i

// Examples:

a) $ ./Q1_i

Input:
Enter value of 'c' (copies of 'r' required for each process): 2
Enter value of 'r' (total number of copies for single resource): 6

Output:
Maximum value of 'n' (number of processes) to ensure deadlock free operation: 5

b) $ ./Q1_i

Input:
Enter value of 'c' (copies of 'r' required for each process): 1
Enter value of 'r' (total number of copies for single resource): 5
Infinite number of processes can be executed without deadlock

// Note: In case 'c' is one and r > 0, we can have infinite processes without deadlock 

ii)=>

// Compilation: gcc Q1_ii.c -o Q1_ii

// Execution: ./Q1_ii

// Examples:

a) $ ./Q1_ii

Input:
Enter value of 'n' (number of processes): 5
Enter values of 'c(i)' (copies of single instance resource required for ith process):
2 3 4 5 6

Output:
Maximum value of 'r' (total number of single instance resource) required to not guarantee deadlock free operation: 15

Minimum value of 'r' (total number of single instance resource) required to guarantee deadlock free operation: 16

b) $ ./Q1_ii

Input:
Enter value of 'n' (number of processes): 3
Enter values of 'c(i)' (copies of single instance resource required for ith process):
2 2 2

Output:
Maximum value of 'r' (total number of single instance resource) required to not guarantee deadlock free operation: 3

Minimum value of 'r' (total number of single instance resource) required to guarantee deadlock free operation: 4


// Note: All c(i) values are greater than equal to 1

Q2)=>

A Algorithm Explanation : 
// At First all the free frames are allocated as per the requirement
// In case there is no free frame we have to  Calculate frame to replace 
      from all the page references currently existing in frames we replace the page in frame with minimum number of 
      occurences in the page reference string from now till the end of it.

for eg. 
Page reference string is (1 2 3 4 1 1 1 2 2 3)
suppose the next page we have to refer is 4 and current frames are having 1 2 3 pages 
so we have to choose one victim frame 

first calculate occurences of 1,2,3 from next to last reference
cnt(1) -> 3
cnt(2) -> 2
cnt(3) -> 1
so we get cnt(3) as minimum, select 3 as victim and replace it with page 4.


// Few traits of the algortihm:
	*Run time will be on higher side as we have loop through reference string each time we want to select a victim
	*One advantage is that pages with high requirement will stay in the page frame which may lead to fewer page faults for inputs
	with repetitive requests of some specific pages

	So if any specific page is present in the frame and it will be required to refer again many times it will stay there and other 
	page will be selected for replacement

	1 2 3 4 1 1 2 2 2 1 1 4 


// Compilation: g++ Q2.cpp -o Q2

// Execution: ./Q2

// Example:  

a) $ ./Q2
Enter No. of trials: 5

Try 1
Enter No. of frame: 3
Enter Length of page sequence of trial 1: 12
Enter Page Sequence of trial 1: 1 2 3 4 1 1 2 2 2 1 1 4 

Try 2
Enter No. of frame: 2
Enter Length of page sequence of trial 2: 6 
Enter Page Sequence of trial 2: 1 3 2 1 1 1        

Try 3
Enter No. of frame: 3
Enter Length of page sequence of trial 3: 10
Enter Page Sequence of trial 3: 1 3 2 4 2 2 4 6 4 1

Try 4
Enter No. of frame: 4
Enter Length of page sequence of trial 4: 8
Enter Page Sequence of trial 4: 1 2 3 4 5 1 2 2

Try 5
Enter No. of frame: 3
Enter Length of page sequence of trial 5: 8
Enter Page Sequence of trial 5: 5 4 3 5	3 4 4 4  

Output:
A : 4 3 5 5 3 
FIFO : 6 4 6 7 3 
LRU : 6 4 6 7 3 
LIFO : 4 3 8 5 3 
T1, T2, T3, T4 : 113.000000 9.000000 27.000000 7.000000 (all in microseconds)

// Note : A is the above described algorithm, others are well known existing algorithms
number of page faults for each test case are shown in output for each algorithm
execution time is also shown where 
T1 <=> A
T2 <=> FIFO
T3 <=> LRU
T4 <=> LIFO
respectively

lesser page faults are in A for above kind of inputs.


Q3)=>

// Compilation: g++ Q3.cpp -o Q3

// Execution: ./Q3

// Example:

a) $ ./Q3

Input:
Enter the processor 1 time slice: 5
Enter the processor 2 time slice: 10
Enter total number of jobs: 7
Enter details for ith job on ith line (Format: job_id arrival_time execution_time): 
A 0 18
B 0 12
C 0 7
D 0 11
E 0 28
F 7 18
G 16 12
Enter time instant: 53

Output(Format order as mentioned in pdf):
A	0	18	0	43	C
B	0	12	0	24	C
C	0	7	5	22	C
D	0	11	10	30	C
E	0	28	10	-1	E
F	7	18	20	51	C
G	16	12	25	52	C


// Format Order : Job_ID, Arrival_Time, Execution_Time, Start_Time, End_Time, Current_Status 
// Note: instead of blank, I have used -1 where the time value is yet to be decided

// Also if at any time instant x some process will start executing in the output the
 current status will show 'W' (waiting) rather than 'E' (executing). This is because 
 process will be into the process just a moment after time instant x, so for subsequent time 
 instances (x+1, ...) its status will be shown as 'E'.


Q4)=>

// Compilation: g++ Q4.cpp -o Q4

// Execution: ./Q4

// Example:

a) $ ./Q4
Number of cylinders: 200
Head position: 98
Size of Disk request queue: 8
Disk request queue: 98 183 37 122 14 124 65 67


Disk Scheduling Algorithm: S-LOOK
Total head movement: 253
Seek time: 1265ms
Graph: Displayed in gnu plot
Order of Processed Requests: 98 67 65 37 14 122 124 183 

// Note : Screenshot of graph for this example is in the zip

// Please Install this package before execution to view graph plots of disk head movement in ubuntu
// sudo apt-get install gnuplot-x11