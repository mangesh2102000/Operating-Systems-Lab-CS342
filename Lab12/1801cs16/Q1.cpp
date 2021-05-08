/* Name: Chandrawanshi Mangesh Shivaji
Roll No. 1801cs16
CS342 Operating Systems Lab Assignment 12
filename : Q1.cpp
Problem : Program to execute and compare various disk scheduling algorithms*/

// Install this package to view graph plots in ubuntu
// sudo apt-get install gnuplot-x11

#include <bits/stdc++.h>
using namespace std;

// Global variables
int total_cylinders, work_queue_size, seek_rate = 5;
vector<int> work_queue;

typedef struct Algorithm{
	string name;
	int seek_time;
}Algorithm;

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

// Function to execute FCFS disk scheduling algorithm
int FCFS(int disk_head_pos){
	
	// To store output results
	int total_head_movement = 0, seek_time;
	vector<double> x_coord, y_coord;
	x_coord.push_back(0);
	y_coord.push_back(disk_head_pos);

	vector<int> request_process_order;

	// FCFS execution
	for(int i=0;i<work_queue_size;i++){
		total_head_movement += abs(work_queue[i] - disk_head_pos);
		disk_head_pos = work_queue[i];	
		x_coord.push_back(seek_rate*total_head_movement);
		y_coord.push_back(disk_head_pos);
		request_process_order.push_back(work_queue[i]);
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
	graphplot2D("FCFS", x_coord, y_coord, 0);

	return seek_time;
}

// Function to execute SCAN disk scheduling algorithm
int SCAN(int disk_head_pos,int initial_direction_scan){

	// To store output results
	int total_head_movement = 0, seek_time;
	vector<double> x_coord, y_coord;
	x_coord.push_back(0);
	y_coord.push_back(disk_head_pos);

	vector<int> request_process_order;

	// SCAN execution

	int requested[total_cylinders]={0};
	int initial_direction = initial_direction_scan;
	int count = 0;

	for(int i=0;i<work_queue_size;i++){
		requested[work_queue[i]] = 1;
	}

	if(requested[disk_head_pos] == 1){
		requested[disk_head_pos] = 0;
		count++;
		x_coord.push_back(seek_rate*total_head_movement);
		y_coord.push_back(disk_head_pos);
		request_process_order.push_back(disk_head_pos);
	}

	// Move towards left initially
	if(initial_direction == 0){

		// service requests
		for(int i=disk_head_pos-1;i>=0 &&  count<work_queue_size;i--){
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

		// reasched left end
		if(count != work_queue_size){
			total_head_movement += abs(disk_head_pos - 0);
			disk_head_pos = 0;
			x_coord.push_back(seek_rate*total_head_movement);
			y_coord.push_back(disk_head_pos);
		}

		// now move towards right servicing requests along the way
		for(int i=0; i<total_cylinders && count<work_queue_size; i++){
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
		// Move towards right initially

		for(int i=disk_head_pos+1;i<total_cylinders &&  count<work_queue_size;i++){
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

		// readhed right end
		if(count != work_queue_size){
			total_head_movement += abs(total_cylinders - 1 - disk_head_pos);
			disk_head_pos = total_cylinders - 1;
			x_coord.push_back(seek_rate*total_head_movement);
			y_coord.push_back(disk_head_pos);
		}

		// now move towards left servicing requests along the way
		for(int i=total_cylinders-1; i>=0 && count<work_queue_size; i--){
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
	graphplot2D("SCAN", x_coord, y_coord, 1);

	return seek_time;
}

// Function to execute C-SCAN disk scheduling algorithm
int C_SCAN(int disk_head_pos, int initial_direction_cscan){

	// To store output results
	int total_head_movement = 0, seek_time;
	vector<double> x_coord, y_coord;
	x_coord.push_back(0);
	y_coord.push_back(disk_head_pos);

	vector<int> request_process_order;
	// C-SCAN execution

	int requested[total_cylinders]={0};
	int initial_direction = initial_direction_cscan;
	int count = 0;

	for(int i=0;i<work_queue_size;i++){
		requested[work_queue[i]] = 1;
	}

	if(requested[disk_head_pos] == 1){
		requested[disk_head_pos] = 0;
		count++;
		x_coord.push_back(seek_rate*total_head_movement);
		y_coord.push_back(disk_head_pos);
		request_process_order.push_back(disk_head_pos);

	}

	// Move towards left initially
	if(initial_direction == 0){

		// service requests
		for(int i=disk_head_pos-1;i>=0 &&  count<work_queue_size;i--){
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

		// reached left end, now shift head to rightmost
		if(count != work_queue_size){
			total_head_movement += abs(disk_head_pos - 0);
			disk_head_pos = 0;
			x_coord.push_back(seek_rate*total_head_movement);
			y_coord.push_back(disk_head_pos);

			disk_head_pos = total_cylinders - 1;
			total_head_movement += (total_cylinders -1);
			x_coord.push_back(seek_rate*total_head_movement);
			y_coord.push_back(disk_head_pos);
		}		


		// service requests from righmost moving towards left
		for(int i=total_cylinders-1; i>=0 && count<work_queue_size; i--){
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

		// Moving towards right initially

		// service requests
		for(int i=disk_head_pos+1;i<total_cylinders &&  count<work_queue_size;i++){
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

		// reached right end, now shift head to leftmost 
		if(count != work_queue_size){
			total_head_movement += abs(total_cylinders - 1 - disk_head_pos);
			disk_head_pos = total_cylinders - 1;
			x_coord.push_back(seek_rate*total_head_movement);
			y_coord.push_back(disk_head_pos);

			disk_head_pos = 0;
			total_head_movement += (total_cylinders -1);
			x_coord.push_back(seek_rate*total_head_movement);
			y_coord.push_back(disk_head_pos);
		}		

		// service requests from leftmost moving towards right
		for(int i=0; i<total_cylinders && count<work_queue_size; i++){
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
	graphplot2D("C_SCAN", x_coord, y_coord, 2);
	
	return seek_time;
}

// Function to execute SSTF disk scheduling algorithm
int SSTF(int disk_head_pos){

	// To store output results
	int total_head_movement = 0, seek_time;
	vector<double> x_coord, y_coord;
	x_coord.push_back(0);
	y_coord.push_back(disk_head_pos);

	vector<int> request_process_order;
	// SSTF execution

	int cnt = work_queue_size;
	int vis[work_queue_size] = {0};

	// get closet request to serve from curent head position
	while(cnt--){

		int min_dist = 1e8 + 5;
		int request_idx = -1;
		for(int i=0;i<work_queue_size;i++){
			if(vis[i] == 0 && abs(disk_head_pos-work_queue[i]) < min_dist){
				min_dist = abs(disk_head_pos-work_queue[i]);
				request_idx = i;
			}
		}

		vis[request_idx] = 1;
		total_head_movement += abs(disk_head_pos-work_queue[request_idx]);
		disk_head_pos = work_queue[request_idx];
		x_coord.push_back(seek_rate*total_head_movement);
		y_coord.push_back(disk_head_pos);
		request_process_order.push_back(disk_head_pos);
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
	graphplot2D("SSTF", x_coord, y_coord, 3);

	return seek_time;
}

// driver code
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

	int initial_direction_scan, initial_direction_cscan;
	printf("Intial direction for SCAN (0-left, 1-right): ");
	scanf("%d", &initial_direction_scan);

	printf("Intial direction for C-SCAN (0-left, 1-right): ");
	scanf("%d", &initial_direction_cscan);

	int idx=0;
	Algorithm array[4];

	// Calls to functions
	printf("\n\nDisk Scheduling Algorithm: FCFS\n");
	array[idx].name = "FCFS";
	array[idx++].seek_time = FCFS(disk_head_pos);

	printf("\n\nDisk Scheduling Algorithm: SCAN\n");
	array[idx].name = "SCAN";
	array[idx++].seek_time = SCAN(disk_head_pos, initial_direction_scan);

	printf("\n\nDisk Scheduling Algorithm: C-SCAN\n");
	array[idx].name = "C-SCAN";
	array[idx++].seek_time = C_SCAN(disk_head_pos, initial_direction_cscan);

	printf("\n\nDisk Scheduling Algorithm: SSTF\n");
	array[idx].name = "SSTF";
	array[idx++].seek_time = SSTF(disk_head_pos);

	// Sort the results from worst to best according to seek time
	for(int i=0;i<idx-1;i++){
		for(int j=0;j<idx-i-1;j++){
			if( array[j].seek_time < array[j+1].seek_time ){
				Algorithm temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp; 
			}
		}
	}

	// Output
	printf("\n\nSorted Order of Algorithms from worst to best on the basis of seek time:\n");
	for(int i=0;i<idx;i++){
		cout << array[i].name << " - " << array[i].seek_time << "ms\n";
	}	

	return 0;
}
