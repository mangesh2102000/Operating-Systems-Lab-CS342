/*Name: Chandrawanshi Mangesh Shivaji
Roll No.: 1801cs16
CS342 Operating Systems Lab  Assignment 10
Filename: Q1_3.cpp
Problem Statement: Page Replacement Algorithm - Optimal*/

/* Compilation :$ g++ Q1_3.cpp -o Q1_3
Usage : $ ./Q1_3
*/

#include <bits/stdc++.h>

using namespace std;

#define MAX_SIZE 1005

// Function to find optimal replacement using future references
int find_optimal_replacement(int page_frames[], int num_of_frames,
    const vector < int > & reference_string, int time) {

    int frame_idx_to_replace = -1;

    int next_usage_time[num_of_frames];
    memset(next_usage_time, 1e8 + 5, sizeof(next_usage_time));

    int len = reference_string.size();

    // find next reference of each page in frame
    for (int i = 0; i < num_of_frames; i++) {
        for (int j = time + 1; j < len + 1; j++) {
            if (page_frames[i] == reference_string[j - 1]) {
                next_usage_time[i] = j;
                break;
            }
        }
    }

    int max_next_usage_time = -1;

    // get page with reference at most later time(or no next reference)
    for (int i = 0; i < num_of_frames; i++) {
        if (next_usage_time[i] > max_next_usage_time) {
            max_next_usage_time = next_usage_time[i];
            frame_idx_to_replace = i;
        }
    }

    return frame_idx_to_replace;
}

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
        printf("Optimal:\n");
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
        memset(page_frames, -1, sizeof(page_frames));

        for (int i = 0; i < num_of_frames; i++)
            printf("X  ");
        printf("at t = %d\n", time);

        // Execute Optimal Algorithm
        for (time = 1; time <= len; time++) {

            // Page fault
            if (page_in_frame[reference_string[time - 1]] == -1) {

                if (page_faults < num_of_frames) {

                    // At first fill all the frames
                    page_frames[page_faults] = reference_string[time - 1];
                    page_in_frame[reference_string[time - 1]] = page_faults;

                } else {

                    // find most optimal frame to reference
                    frame_idx_to_replace = find_optimal_replacement(page_frames, num_of_frames, reference_string, time);
                    replaced_page = page_frames[frame_idx_to_replace];
                    page_frames[frame_idx_to_replace] = reference_string[time - 1];

                    if (replaced_page != -1)
                        page_in_frame[replaced_page] = -1;

                    page_in_frame[reference_string[time - 1]] = frame_idx_to_replace;

                }
                page_faults++;

            }

            // Print current state of all the frames 
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