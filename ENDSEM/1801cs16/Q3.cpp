/*Name: Chandrawanshi Mangesh Shivaji
Roll No.: 1801cs16
CS342 Operating Systems Lab End Sem Exam
Filename: Q3.cpp
Problem : Program to execute given multiprocessor scheduling algorithm
*/

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[])
{
	int d1, d2, n; 
	printf("\nInput:\n");
	printf("Enter the processor 1 time slice: ");
	scanf("%d", &d1);

	printf("Enter the processor 2 time slice: ");
	scanf("%d", &d2);

	printf("Enter total number of jobs: ");
	scanf("%d", &n);

	string job_id[n];
	int arrival_time[n], execution_time[n], rem_execution_time[n];

	printf("Enter details for ith job on ith line (Format: job_id arrival_time execution_time): \n");
	for(int i=0;i<n;i++){
		cin >> job_id[i];
		scanf("%d %d", &arrival_time[i], &execution_time[i]);
		rem_execution_time[i] = execution_time[i];
	}

	int time_instant;
	printf("Enter time instant: ");
	scanf("%d", &time_instant);

	queue <int> q;
	int inqueue[n] = {0}, start_time[n], completion_time[n];

	int t = 0;
	int rem_tq1 = d1, rem_tq2 = d2;
	int completed_cnt;
	int process_in_1 = -1, process_in_2 = -1;

	char current_status[n];
	for(int i=0;i<n;i++){
		current_status[i] = 'W';
		start_time[i] = -1;
		completion_time[i] = -1;	
	}

	// Execute given algorithm
	while(1){

		// Push all arriving jobs in queue
		for(int i=0;i<n;i++){
			if(arrival_time[i] <= t && inqueue[i] == 0){
				q.push(i);
				inqueue[i] = 1;
			}
		}

		// Check if processor 1 is empty
		if(process_in_1 == -1){
			if(!q.empty()){
				process_in_1 = q.front();
				q.pop();
				current_status[process_in_1] = 'E';
				if(start_time[process_in_1] == -1)
					start_time[process_in_1] = t;
			}
		}

		// Check if processor 2 is empty
		if(process_in_2 == -1){
			if(!q.empty()){
				process_in_2 = q.front();
				q.pop();	
				current_status[process_in_2] = 'E';			
				if(start_time[process_in_2] == -1)
					start_time[process_in_2] = t;
			}
		}

		int itr = min(rem_tq1, rem_tq2);
		int flag = 0;

		// execute current time slice
		while(itr != 0){

			if(process_in_1 != -1 && rem_execution_time[process_in_1] == 0)
				break;

			if(process_in_2 != -1 && rem_execution_time[process_in_2] == 0)
				break;

			if(process_in_1 != -1){
				rem_execution_time[process_in_1] -= 1;
				rem_tq1--;
			}
			
			if(process_in_2 != -1){
				rem_execution_time[process_in_2] -= 1;
				rem_tq2--;
			}
			
			itr--;
			t++;

			for(int i=0;i<n;i++){
				if(arrival_time[i] <= t && inqueue[i] == 0){
					q.push(i);
					inqueue[i] = 1;
					flag = 1; 
				}
			}

			if(flag == 1 and (process_in_1 == -1 or process_in_2 == -1))
				break;

			if(t == time_instant)
				break;
		}

		// Completion for job in 1
		if(process_in_1 != -1 && rem_execution_time[process_in_1] == 0){
			completed_cnt++;
			completion_time[process_in_1] = t;
			current_status[process_in_1] = 'C';
			process_in_1 = -1;
			rem_tq1 = d1;
		}

		// Completion for job in 2
		if(process_in_2 != -1 && rem_execution_time[process_in_2] == 0){
			completed_cnt++;
			completion_time[process_in_2] = t;
			current_status[process_in_2] = 'C';
			process_in_2 = -1;
			rem_tq2 = d2;
		}


		// Expired time slice
		if(rem_tq1 == 0){
			rem_tq1 = d1;
			if(rem_execution_time[process_in_1] != 0){
				q.push(process_in_1);
				current_status[process_in_1] = 'W';
			}
			process_in_1 = -1;
		}

		// Expired time slice
		if(rem_tq2 == 0){
			rem_tq2 = d2;
			if(rem_execution_time[process_in_2] != 0){
				q.push(process_in_2);
				current_status[process_in_2] = 'W';
			}
			process_in_2 = -1;
		}

		if(completed_cnt == n)
			break;

		// Reached time instant requried
		if(t == time_instant)
			break;
	}

	printf("\nOutput(Format order as mentioned in pdf):\n");

	for(int i=0;i<n;i++){
		cout << job_id[i] << "\t" << arrival_time[i] << "\t" << execution_time[i] << "\t" << start_time[i] << "\t" << completion_time[i] << "\t" << current_status[i] << "\n";
	}
	cout << "\n";

	return 0;
}

