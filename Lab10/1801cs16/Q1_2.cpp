/*Name: Chandrawanshi Mangesh Shivaji
Roll No.: 1801cs16
CS342 Operating Systems Lab  Assignment 10
Filename: Q1_2.cpp
Problem Statement: Page Replacement Algorithm - Least Recently Used (LRU)*/

/* Compilation :$ g++ Q1_2.cpp -o Q1_2
Usage : $ ./Q1_2
*/

#include <bits/stdc++.h>

using namespace std;

#define MAX_SIZE 1005

// Find page replacement according to the LRU algorithm
int find_replacement(int reference_time[], int num_of_frames) {

    int frame_idx_to_replace = -1;
    int min_time = 1e8 + 5;
    for (int i = 0; i < num_of_frames; i++) {
        if (reference_time[i] < min_time) {
            frame_idx_to_replace = i;
            min_time = reference_time[i];
        }
    }

    return frame_idx_to_replace;
}

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
    int len, time, page_faults, frame_idx_to_replace, replaced_page, curr_page_idx;
    int page_in_frame[MAX_SIZE];
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
        printf("LRU:\n");
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
        memset(page_in_frame, -1, sizeof(page_in_frame));

        int page_frames[num_of_frames];
        int reference_time[num_of_frames];
        memset(page_frames, -1, sizeof(page_frames));
        memset(reference_time, -1, sizeof(reference_time));

        for (int i = 0; i < num_of_frames; i++)
            printf("X  ");
        printf("at t = %d\n", time);

        // Execute LRU algorithm
        for (time = 1; time <= len; time++) {

            // Page Fault
            if (page_in_frame[reference_string[time - 1]] == -1) {

                if (page_faults < num_of_frames) {

                    // Fill all empty frames at first
                    page_frames[page_faults] = reference_string[time - 1];
                    reference_time[page_faults] = time;
                    page_in_frame[reference_string[time - 1]] = page_faults;

                } else {

                    // find replacement according to LRU
                    frame_idx_to_replace = find_replacement(reference_time, num_of_frames);

                    replaced_page = page_frames[frame_idx_to_replace];
                    page_frames[frame_idx_to_replace] = reference_string[time - 1];
                    reference_time[frame_idx_to_replace] = time;

                    if (replaced_page != -1)
                        page_in_frame[replaced_page] = -1;

                    page_in_frame[reference_string[time - 1]] = frame_idx_to_replace;

                }
                page_faults++;

            } else {

                reference_time[page_in_frame[reference_string[time - 1]]] = time;
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