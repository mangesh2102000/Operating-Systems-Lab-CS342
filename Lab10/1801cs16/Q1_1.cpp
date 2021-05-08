/*Name: Chandrawanshi Mangesh Shivaji
Roll No.: 1801cs16
CS342 Operating Systems Lab  Assignment 10
Filename: Q1_1.cpp
Problem Statement: Page Replacement Algorithm - First-in-First-out (FIFO)*/

/* Compilation :$ g++ Q1_1.cpp -o Q1_1
Usage : $ ./Q1_1
*/

#include <bits/stdc++.h>

using namespace std;

#define MAX_SIZE 1005

// driver code
int main(void) {
    // Open Input file to read
    fstream fp;
    fp.open("pages.txt", ios:: in );
    if (!fp) {
        printf("FILE NOT FOUND!\n");
        exit(1);
    }

    // Variable Declarations 
    int num_of_frames;
    vector < int > reference_string;
    string line, page_num;
    int len, time, page_faults, frame_idx_to_replace, replaced_page;
    bool page_in_frame[MAX_SIZE];
    int tc = 0;

    // Read input file line by line 
    while (getline(fp, line)) {

        printf("\nTest Case %d:\n\n", tc);

        // get number of frames
        num_of_frames = stoi(line);

        getline(fp, line);
        len = line.length();
        page_num = "";

        // store all page references 
        for (int i = 0; i < len; i++) {
            if (line[i] == '-')
                break;

            if (line[i] == ' ') {
                reference_string.push_back(stoi(page_num));
                page_num = "";
            } else {
                page_num += line[i];
            }
        }
        len = reference_string.size();

        // Print Algorithm Type and input details of current test case
        printf("FIFO:\n");
        printf("Number of frames : %d\nReference String : ", num_of_frames);
        for (int i = 0; i < len; i++) {
            printf("%d ", reference_string[i]);
        }
        printf("\n\n");

        printf("Frame content at each time step t\n");
        for (int i = 0; i < num_of_frames; i++) {
            printf("F%d ", i + 1);
        }
        printf("\n");

        time = 0;
        page_faults = 0;
        frame_idx_to_replace = 0;
        memset(page_in_frame, false, sizeof(page_in_frame));

        int page_frames[num_of_frames];
        memset(page_frames, -1, sizeof(page_frames));

        for (int i = 0; i < num_of_frames; i++)
            printf("X  ");
        printf("at t = %d\n", time);

        // Execute FIFO algorithm
        for (time = 1; time <= len; time++) {

            replaced_page = -1;

            // Page Fault
            if (!page_in_frame[reference_string[time - 1]]) {

                page_faults++;

                // Replace page which was inserted at first
                replaced_page = page_frames[frame_idx_to_replace];
                page_frames[frame_idx_to_replace] = reference_string[time - 1];

                frame_idx_to_replace += 1;
                frame_idx_to_replace %= num_of_frames;

                if (replaced_page != -1)
                    page_in_frame[replaced_page] = false;

                page_in_frame[reference_string[time - 1]] = true;
            }

            // Print current state of all frames
            for (int i = 0; i < num_of_frames; i++) {
                if (page_frames[i] == -1) {
                    printf("X  ");
                } else {
                    if (page_frames[i] / 10 == 0) {
                        printf("%d  ", page_frames[i]);
                    } else {
                        printf("%d ", page_frames[i]);
                    }
                }
            }
            printf("at t = %d\n", time);
        }

        printf("\n#Page Faults: %d\n\n\n", page_faults);
        reference_string.clear();
        tc++;
    }

    fp.close();
    return 0;
}