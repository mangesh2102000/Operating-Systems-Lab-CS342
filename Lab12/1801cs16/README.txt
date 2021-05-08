/* Name: Chandrawanshi Mangesh Shivaji
Roll Number: 1801cs16
CS342 Operating Systems Lab Assignment 12
filename : README.txt*/

Please keep all .cpp file in the same folder before compilation and execution
Filenames are Q1.cpp, Q2.cpp for respective 1,2 questions

Note: seek rate = 5ms for Q1 and Q2 as mentioned in the assignment

// Install the gnuplot package to view graph plots in ubuntu
Installation command : sudo apt-get install gnuplot-x11
screenshots of graph plots for given example are attached in the pdf report

Q1) => 

Points to consider: 
* User input is taken for initial direction of SCAN and C-SCAN algorithms (0-left, 1-right)
* Incase of tie in SSTF (i.e two requests are at same seek length from current head position) request which occurs first
is given priority.
* For N number of total cylinders, available positions range from 0 to N-1

Compilation : $ g++ Q1.cpp -o Q1

Execution : $ ./Q1

// Example
Number of cylinders: 200
Head position: 100
Size of Disk request queue: 5
Disk request queue: 23 89 132 42 187
Intial direction for SCAN (0-left, 1-right): 0
Intial direction for C-SCAN (0-left, 1-right): 0


Disk Scheduling Algorithm: FCFS
Total head movement: 421
Seek time: 2105ms
Graph: Displayed in gnu plot
Order of Processed Requests: 23 89 132 42 187 


Disk Scheduling Algorithm: SCAN
Total head movement: 287
Seek time: 1435ms
Graph: Displayed in gnu plot
Order of Processed Requests: 89 42 23 132 187 


Disk Scheduling Algorithm: C-SCAN
Total head movement: 366
Seek time: 1830ms
Graph: Displayed in gnu plot
Order of Processed Requests: 89 42 23 187 132 


Disk Scheduling Algorithm: SSTF
Total head movement: 273
Seek time: 1365ms
Graph: Displayed in gnu plot
Order of Processed Requests: 89 132 187 42 23 


Sorted Order of Algorithms from worst to best on the basis of seek time:
FCFS - 2105ms
C-SCAN - 1830ms
SCAN - 1435ms
SSTF - 1365ms

Q2) => 

Points to consider: 
* Incase of tie in S-LOOL (i.e both far-ends are at same distance from initial head position) disk head moves in left direction
* For N number of total cylinders, available positions range from 0 to N-1

Compilation : $ g++ Q2.cpp -o Q2

Execution : $ ./Q2

// Example
Number of cylinders: 200
Head position: 100 
Size of Disk request queue: 8
Disk request queue: 98 183 37 122 14 124 65 67


Disk Scheduling Algorithm: S-LOOK
Total head movement: 252
Seek time: 1260ms
Graph: Displayed in gnu plot
Order of Processed Requests: 122 124 183 98 67 65 37 14
