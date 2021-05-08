/*Name: Chandrawanshi Mangesh Shivaji
Roll No.: 1801cs16
CS342 Operating Systems Lab End Sem Exam
Filename: Q2.cpp
Problem : Program to compare multiple disk scheduling algorithms
*/

#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

// P => length of page sequence 
// K => num of frames

const int MAX_SIZE = 10005;

// to store count page faults and execution time
vector <int> A_list, FIFO_list, LRU_list, LIFO_list;
double A_time = 0, FIFO_time = 0, LRU_time = 0, LIFO_time = 0;

// Algorithm designed by me 
void A(int PS[], int P, int K){

	int page_frames[K];
	memset(page_frames, -1, sizeof(page_frames));

	int page_faults = 0;
    int frame_idx_to_replace = 0;

    int page_in_frame[MAX_SIZE];
    memset(page_in_frame, -1, sizeof(page_in_frame));

    int replaced_page = -1;

    int reference_time[K];
    memset(reference_time, -1, sizeof(reference_time));

    for (int i=0;i<P;i++) {

    	// Page fault
        if (page_in_frame[PS[i]] == -1) {

        	// Fill all empty frames one by one
            if (page_faults < K) {

                page_frames[page_faults] = PS[i];
                reference_time[page_faults] = i;
                page_in_frame[PS[i]] = page_faults;

            } else {

            	// Calculate frame to replace 
            	// from all the page references currently existing in frames we replace the page with 
            	// minimum number of occurences in the page reference string from now till the end of length of it.

                frame_idx_to_replace = -1;
                int min_count = 1e8+5;
                for(int j=0;j<K;j++){
                	int count = 0;
                	for(int itr=i+1;itr<P;itr++){
                		if(PS[itr] == page_frames[j]){
                			count++;
                		}
                	}
                	if(count < min_count){
                		frame_idx_to_replace = j;
                		min_count = count;
                	}
                }

                replaced_page = page_frames[frame_idx_to_replace];
                page_frames[frame_idx_to_replace] = PS[i];
                reference_time[frame_idx_to_replace] = i+1;

                if (replaced_page != -1)
                    page_in_frame[replaced_page] = -1;

                page_in_frame[PS[i]] = frame_idx_to_replace;

            }
            page_faults++;

        } else {

            reference_time[page_in_frame[PS[i]]] = i+1;
        }
    }

    // Push page fault count to list
    A_list.push_back(page_faults);
}

// Already existing algorithms

// First in First Out
void FIFO(int PS[], int P, int K){

	int page_frames[K];
	memset(page_frames, -1, sizeof(page_frames));

	int page_faults = 0;
    int frame_idx_to_replace = 0;
    bool page_in_frame[MAX_SIZE];
    memset(page_in_frame, false, sizeof(page_in_frame));

    int replaced_page = -1;

    for(int i=0;i<P;i++){
    	
    	replaced_page = -1;

    	if(!page_in_frame[PS[i]]){

    		page_faults++;

    		replaced_page = page_frames[frame_idx_to_replace];
    		page_frames[frame_idx_to_replace] = PS[i];

    		frame_idx_to_replace += 1;
    		frame_idx_to_replace %= K;

    		if (replaced_page != -1)
                page_in_frame[replaced_page] = false;

            page_in_frame[PS[i]] = true;
    	}
    }
    FIFO_list.push_back(page_faults);
}

// Least Recently Used
void LRU(int PS[], int P, int K){

	int page_frames[K];
	memset(page_frames, -1, sizeof(page_frames));

	int page_faults = 0;
    int frame_idx_to_replace = 0;

    int page_in_frame[MAX_SIZE];
    memset(page_in_frame, -1, sizeof(page_in_frame));

    int replaced_page = -1;

    int reference_time[K];
    memset(reference_time, -1, sizeof(reference_time));

    for (int i=0;i<P;i++) {

        if (page_in_frame[PS[i]] == -1) {

            if (page_faults < K) {

                page_frames[page_faults] = PS[i];
                reference_time[page_faults] = i;
                page_in_frame[PS[i]] = page_faults;

            } else {

                frame_idx_to_replace = -1;
			    int min_time = 1e8 + 5;
			    for (int i = 0; i < K; i++) {
			        if (reference_time[i] < min_time) {
			            frame_idx_to_replace = i;
			            min_time = reference_time[i];
			        }
			    }

                replaced_page = page_frames[frame_idx_to_replace];
                page_frames[frame_idx_to_replace] = PS[i];
                reference_time[frame_idx_to_replace] = i+1;

                if (replaced_page != -1)
                    page_in_frame[replaced_page] = -1;

                page_in_frame[PS[i]] = frame_idx_to_replace;

            }
            page_faults++;

        } else {

            reference_time[page_in_frame[PS[i]]] = i+1;
        }
    }

    LRU_list.push_back(page_faults);
}

// Last in First out
void LIFO(int PS[], int P, int K){


	int page_frames[K];
	memset(page_frames, -1, sizeof(page_frames));

	int page_faults = 0;
    int frame_idx_to_replace = 0;
    bool page_in_frame[MAX_SIZE];
    memset(page_in_frame, false, sizeof(page_in_frame));

    int replaced_page = -1;

    for(int i=0;i<P;i++){
    	
    	replaced_page = -1;

    	if(!page_in_frame[PS[i]]){

    		if (page_faults < K) {

                page_frames[page_faults] = PS[i];
                page_in_frame[PS[i]] = true;

            } else {

            	frame_idx_to_replace = K-1;

	    		replaced_page = page_frames[frame_idx_to_replace];
	    		page_frames[frame_idx_to_replace] = PS[i];

	    		if (replaced_page != -1)
	                page_in_frame[replaced_page] = false;

	            page_in_frame[PS[i]] = true;

            }
            page_faults++;    		
    	}

    }
   	LIFO_list.push_back(page_faults);
}

// driver code
int main(int argc, char const *argv[])
{
	int N;
	printf("Enter No. of trials: ");
	scanf("%d", &N);

	for(int i=1;i<=N;i++){

		printf("\nTry %d\n", i);

		int K, P;
		printf("Enter No. of frame: ");
		scanf("%d", &K);

		printf("Enter Length of page sequence of trial %d: ", i);
		scanf("%d", &P);

		printf("Enter Page Sequence of trial %d: ", i);
		int PS[P];
		for(int i=0;i<P;i++){
			scanf("%d", &PS[i]);
		}

		auto start = high_resolution_clock::now();

		// Call A Algorithm		
		A(PS, P, K);
		
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
  		A_time += duration.count();

		start = high_resolution_clock::now();
		
		// Call FIFO Algorithm
		FIFO(PS, P, K);
		
		stop = high_resolution_clock::now();
		duration = duration_cast<microseconds>(stop - start);
  		FIFO_time += duration.count();


		start = high_resolution_clock::now();
		
		// Call LRU Algorithm
		LRU(PS, P, K);
		
		stop = high_resolution_clock::now();
		duration = duration_cast<microseconds>(stop - start);
  		LRU_time += duration.count();

		start = high_resolution_clock::now();
		
		// Call LIFO Algorithm
		LIFO(PS, P, K);
		
		stop = high_resolution_clock::now();
		duration = duration_cast<microseconds>(stop - start);
  		LIFO_time += duration.count();
	}

	printf("\nOutput:\n");
	printf("A : ");
	for(int i=0;i<A_list.size();i++){
		printf("%d ", A_list[i]);
	}
	printf("\n");

	printf("FIFO : ");
	for(int i=0;i<FIFO_list.size();i++){
		printf("%d ", FIFO_list[i]);
	}
	printf("\n");

	printf("LRU : ");
	for(int i=0;i<LRU_list.size();i++){
		printf("%d ", LRU_list[i]);
	}
	printf("\n");

	printf("LIFO : ");
	for(int i=0;i<LIFO_list.size();i++){
		printf("%d ", LIFO_list[i]);
	}
	printf("\n");

	printf("T1, T2, T3, T4 : %lf %lf %lf %lf (all in microseconds)\n\n", A_time, FIFO_time, LRU_time, LIFO_time);

	return 0;
}
