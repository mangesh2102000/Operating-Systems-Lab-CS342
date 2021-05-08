/*Name: Chandrawanshi Mangesh Shivaji
Roll No.: 1801cs16
CS342 Operating Systems Lab  Assignment 10
FileName : README.txt */

Please make sure you are in the same folder as .cpp files
.cpp file names Q1_1.cpp, Q1_2.cpp, Q1_3.cpp for respective parts of question 1

Input File used for all examples : pages.txt is attached in the zip

Q1_1) => a) FIRST IN FIRST OUT

// Compilation :
$ g++ Q1_1.cpp -o Q1_1

// Example :
$ ./Q1_1

Test Case 0:

FIFO:
Number of frames : 3
Reference String : 4 7 6 1 7 6 1 2 7 2 

Frame content at each time step t
F1 F2 F3 
X  X  X  at t = 0
4  X  X  at t = 1
4  7  X  at t = 2
4  7  6  at t = 3
1  7  6  at t = 4
1  7  6  at t = 5
1  7  6  at t = 6
1  7  6  at t = 7
1  2  6  at t = 8
1  2  7  at t = 9
1  2  7  at t = 10

#Page Faults: 6



Test Case 1:

FIFO:
Number of frames : 4
Reference String : 1 2 3 4 2 7 5 1 1 6 4 7 2 1 2 5 

Frame content at each time step t
F1 F2 F3 F4 
X  X  X  X  at t = 0
1  X  X  X  at t = 1
1  2  X  X  at t = 2
1  2  3  X  at t = 3
1  2  3  4  at t = 4
1  2  3  4  at t = 5
7  2  3  4  at t = 6
7  5  3  4  at t = 7
7  5  1  4  at t = 8
7  5  1  4  at t = 9
7  5  1  6  at t = 10
4  5  1  6  at t = 11
4  7  1  6  at t = 12
4  7  2  6  at t = 13
4  7  2  1  at t = 14
4  7  2  1  at t = 15
5  7  2  1  at t = 16

#Page Faults: 13



Test Case 2:

FIFO:
Number of frames : 3
Reference String : 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1 

Frame content at each time step t
F1 F2 F3 
X  X  X  at t = 0
7  X  X  at t = 1
7  0  X  at t = 2
7  0  1  at t = 3
2  0  1  at t = 4
2  0  1  at t = 5
2  3  1  at t = 6
2  3  0  at t = 7
4  3  0  at t = 8
4  2  0  at t = 9
4  2  3  at t = 10
0  2  3  at t = 11
0  2  3  at t = 12
0  2  3  at t = 13
0  1  3  at t = 14
0  1  2  at t = 15
0  1  2  at t = 16
0  1  2  at t = 17
7  1  2  at t = 18
7  0  2  at t = 19
7  0  1  at t = 20

#Page Faults: 15



Q1_2) => b) LEAST RECENTLY USED

// Compilation :
$ g++ Q1_2.cpp -o Q1_2

// Example :
$ ./Q1_2

Test Case 0:

LRU:
Number of frames : 3
Reference String : 4 7 6 1 7 6 1 2 7 2 

Frame content at each time step t
F1 F2 F3 
X  X  X  at t = 0
4  X  X  at t = 1
4  7  X  at t = 2
4  7  6  at t = 3
1  7  6  at t = 4
1  7  6  at t = 5
1  7  6  at t = 6
1  7  6  at t = 7
1  2  6  at t = 8
1  2  7  at t = 9
1  2  7  at t = 10

#Page Faults: 6



Test Case 1:

LRU:
Number of frames : 4
Reference String : 1 2 3 4 2 7 5 1 1 6 4 7 2 1 2 5 

Frame content at each time step t
F1 F2 F3 F4 
X  X  X  X  at t = 0
1  X  X  X  at t = 1
1  2  X  X  at t = 2
1  2  3  X  at t = 3
1  2  3  4  at t = 4
1  2  3  4  at t = 5
7  2  3  4  at t = 6
7  2  5  4  at t = 7
7  2  5  1  at t = 8
7  2  5  1  at t = 9
7  6  5  1  at t = 10
4  6  5  1  at t = 11
4  6  7  1  at t = 12
4  6  7  2  at t = 13
4  1  7  2  at t = 14
4  1  7  2  at t = 15
5  1  7  2  at t = 16

#Page Faults: 13



Test Case 2:

LRU:
Number of frames : 3
Reference String : 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1 

Frame content at each time step t
F1 F2 F3 
X  X  X  at t = 0
7  X  X  at t = 1
7  0  X  at t = 2
7  0  1  at t = 3
2  0  1  at t = 4
2  0  1  at t = 5
2  0  3  at t = 6
2  0  3  at t = 7
4  0  3  at t = 8
4  0  2  at t = 9
4  3  2  at t = 10
0  3  2  at t = 11
0  3  2  at t = 12
0  3  2  at t = 13
1  3  2  at t = 14
1  3  2  at t = 15
1  0  2  at t = 16
1  0  2  at t = 17
1  0  7  at t = 18
1  0  7  at t = 19
1  0  7  at t = 20

#Page Faults: 12



Q1_3) => c) OPTIMAL

// Compilation :
$ g++ Q1_3.cpp -o Q1_3

// Example :
$ ./Q1_3

Test Case 0:

Optimal:
Number of frames : 3
Reference String : 4 7 6 1 7 6 1 2 7 2 

Frame content at each time step t
F1 F2 F3 
X  X  X  at t = 0
4  X  X  at t = 1
4  7  X  at t = 2
4  7  6  at t = 3
1  7  6  at t = 4
1  7  6  at t = 5
1  7  6  at t = 6
1  7  6  at t = 7
2  7  6  at t = 8
2  7  6  at t = 9
2  7  6  at t = 10

#Page Faults: 5



Test Case 1:

Optimal:
Number of frames : 4
Reference String : 1 2 3 4 2 7 5 1 1 6 4 7 2 1 2 5 

Frame content at each time step t
F1 F2 F3 F4 
X  X  X  X  at t = 0
1  X  X  X  at t = 1
1  2  X  X  at t = 2
1  2  3  X  at t = 3
1  2  3  4  at t = 4
1  2  3  4  at t = 5
1  2  7  4  at t = 6
1  5  7  4  at t = 7
1  5  7  4  at t = 8
1  5  7  4  at t = 9
1  6  7  4  at t = 10
1  6  7  4  at t = 11
1  6  7  4  at t = 12
1  2  7  4  at t = 13
1  2  7  4  at t = 14
1  2  7  4  at t = 15
5  2  7  4  at t = 16

#Page Faults: 9



Test Case 2:

Optimal:
Number of frames : 3
Reference String : 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1 

Frame content at each time step t
F1 F2 F3 
X  X  X  at t = 0
7  X  X  at t = 1
7  0  X  at t = 2
7  0  1  at t = 3
2  0  1  at t = 4
2  0  1  at t = 5
2  0  3  at t = 6
2  0  3  at t = 7
2  4  3  at t = 8
2  4  3  at t = 9
2  4  3  at t = 10
2  0  3  at t = 11
2  0  3  at t = 12
2  0  3  at t = 13
2  0  1  at t = 14
2  0  1  at t = 15
2  0  1  at t = 16
2  0  1  at t = 17
7  0  1  at t = 18
7  0  1  at t = 19
7  0  1  at t = 20

#Page Faults: 9


