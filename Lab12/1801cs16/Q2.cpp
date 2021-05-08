/* Name: Chandrawanshi Mangesh Shivaji
Roll No. 1801cs16
CS342 Operating Systems Lab Assignment 12
filename : Q2.cpp
Problem : Program to execute disk scheduling algorithm S-LOOK*/

// Install this package to view graph plots in ubuntu
// sudo apt-get install gnuplot-x11

#include <bits/stdc++.h>
using namespace std;

// Global variables
int total_cylinders, work_queue_size, seek_rate = 5;
vector<int> work_queue;

// Function to plot a 2D Graph when (x,y) coordinates are given
void graphplot2D(string scheduling_algo, vector<double> &x_coord, vector<double> &y_coord, int plot_num){

	int cnt_points = x_coord.size(), cnt_commands = 3;

	// Set title, xlablel and ylabel for the graph
    scheduling_algo =  "\"" + scheduling_algo + "\"";
    scheduling_algo = "set title " + scheduling_algo;

    char * title = new char [scheduling_algo.length()+1];
    strcpy (title, scheduling_algo.c_str());

    char const * commands[10000];
    commands[0] = title;
    commands[1] = "set xlabel \"Seek time (ms)\"";
    commands[2] = "set ylabel \"#Cylinders\"";


    // To plot all points
    for (int i=0; i < cnt_points; i++){
      
      string tmp= "\"" + to_string(  (int)x_coord[i]) + ", " + to_string((int)y_coord[i]) + "\"" ;
      tmp = "set label " + tmp + " at " +  to_string( x_coord[i]) + "," + to_string(y_coord[i]);
      
      char * label = new char [tmp.length()+1];
      strcpy (label, tmp.c_str());
      commands[cnt_commands] = label;
      
      cnt_commands++;
    }

    // Store filename of the plot
    string filename = "data";
    filename += "_" + to_string((int)plot_num) + ".temp";

    string content = "plot '";
    content += filename;
    content += "' with linespoints";

    commands[cnt_commands++] = content.c_str();

    // Use gnu plot to draw the graph and display in newly opened window
    FILE * temp = fopen(filename.c_str(), "w");
    FILE * gnu_plot_pipe = popen("gnuplot -persistent", "w");

    for (int i=0; i < cnt_points; i++)
    	fprintf(temp, "%lf %lf\n", x_coord[i], y_coord[i]);
    
    for (int i=0; i < cnt_commands; i++)
    	fprintf(gnu_plot_pipe, "%s \n", commands[i]);
}

// Function to execute S-LOOK disk scheduling algorithm
void S_LOOK(int disk_head_pos){

	// To store output results
	int total_head_movement = 0, seek_time;
	vector<double> x_coord, y_coord;
	x_coord.push_back(0);
	y_coord.push_back(disk_head_pos);

	vector<int> request_process_order;

    // S-LOOK execution
	int requested[total_cylinders]={0};
	int initial_direction = 0;
	int count = 0;

	// Calculate farthest requests from current head position
	int left_far_end = 1e8+5, right_far_end = -1;

	for(int i=0;i<work_queue_size;i++){
		requested[work_queue[i]] = 1;
		left_far_end = min(left_far_end, work_queue[i]);
		right_far_end = max(right_far_end, work_queue[i]);
	}

	// Move initially to the direction with closer far-end
	if( abs(left_far_end-disk_head_pos) < abs(right_far_end-disk_head_pos) ){
		initial_direction = 0;
	}
	else{
		initial_direction = 1;
	}

	if(requested[disk_head_pos] == 1){
		requested[disk_head_pos] = 0;
		count++;
		x_coord.push_back(seek_rate*total_head_movement);
		y_coord.push_back(disk_head_pos);
		request_process_order.push_back(disk_head_pos);

	}

	// Move initially towards left
	if(initial_direction == 0){

		// service request till farthest request on left side
		for(int i=disk_head_pos-1;i>=left_far_end &&  count<work_queue_size;i--){
			if(requested[i]){
				count++;
				total_head_movement += abs(disk_head_pos - i);
				disk_head_pos = i;
				requested[i] = 0;
				x_coord.push_back(seek_rate*total_head_movement);
				y_coord.push_back(disk_head_pos);
				request_process_order.push_back(disk_head_pos);
			}
		}

		// After reaching left end, move towards right and service requests along the way
		for(int i=left_far_end+1; i<=right_far_end && count<work_queue_size; i++){
			if(requested[i]){
				count++;
				total_head_movement += abs(disk_head_pos - i);
				disk_head_pos = i;
				requested[i] = 0;
				x_coord.push_back(seek_rate*total_head_movement);
				y_coord.push_back(disk_head_pos);
				request_process_order.push_back(disk_head_pos);
			}
		}

	}
	else{

		// Move initially towards right

		// service request till farthest request on right side
		for(int i=disk_head_pos+1;i<=right_far_end &&  count<work_queue_size;i++){
			if(requested[i]){
				count++;
				total_head_movement += abs(disk_head_pos - i);
				disk_head_pos = i;
				requested[i] = 0;
				x_coord.push_back(seek_rate*total_head_movement);
				y_coord.push_back(disk_head_pos);
				request_process_order.push_back(disk_head_pos);
			}
		}

		// After reaching right end, move towards left and service requests along the way

		for(int i=right_far_end-1; i>=left_far_end && count<work_queue_size; i--){
			if(requested[i]){
				count++;
				total_head_movement += abs(disk_head_pos - i);
				disk_head_pos = i;
				requested[i] = 0;
				x_coord.push_back(seek_rate*total_head_movement);
				y_coord.push_back(disk_head_pos);
				request_process_order.push_back(disk_head_pos);
			}
		}

	}

	// Calculate seek time
	seek_time = total_head_movement * seek_rate;

	printf("Total head movement: %d\n", total_head_movement);
	printf("Seek time: %dms\n", seek_time);
	printf("Graph: Displayed in gnu plot\n");
	printf("Order of Processed Requests: ");
	for(int i=0;i<request_process_order.size();i++){
		printf("%d ", request_process_order[i]);
	}
	printf("\n");
	graphplot2D("S-LOOK", x_coord, y_coord, 4);
}


int main(int argc, char const *argv[])
{
	// Input
	printf("Number of cylinders: ");
	scanf("%d", &total_cylinders);

	int disk_head_pos;
	printf("Head position: ");
	scanf("%d", &disk_head_pos);

	printf("Size of Disk request queue: ");
	scanf("%d", &work_queue_size);

	int request;
	printf("Disk request queue: ");
	for(int i=0;i<work_queue_size;i++){
		scanf("%d", &request);
		work_queue.push_back(request);
	}

	// Call to function
	printf("\n\nDisk Scheduling Algorithm: S-LOOK\n");
	S_LOOK(disk_head_pos);

	return 0;
}