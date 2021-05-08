/* Name : Chandrawanshi Mangesh Shivaji 
Roll Number : 1801CS16
CS342 Lab - Assignment 7
FileName : Q2.cpp
Problem Statement : Write a program to calculate average WT, TAT, the completion order using Non-preemptive Priority scheduling */

#include <iostream>

using namespace std;

// driver code
int main(int argc, char const *argv[])
{
	// Input from user
	int n;
	printf("\nEnter number of total processes (n) on First Line and\nSpecify arrival_time, burst_time, priority of n processes on following lines (ith line should contain data for ith process) : \n");
	cin >> n;

	double avg_wt = 0, avg_tat = 0;

	if(n == 0){
		printf("\nAverage Waiting Time : %.2lf    Average Turnaround Time : %.2lf\n", avg_wt, avg_tat);
		printf("Completion order of Processes : \n");
		return 0;
	}

	// Input of arrival and burst times along with priority for respective processes
	int arrival_time[n], burst_time[n], priority[n], rem_burst_time[n];

	for(int i=0;i<n;i++)
	{
		cin >> arrival_time[i] >> burst_time[i] >> priority[i];

		if(arrival_time[i] < 0 || burst_time[i] < 0 || priority[i] < 0){
			printf("Usage : Input Only Non-negative Values for time and priority\n");
			exit(1);
		}
		rem_burst_time[i] = burst_time[i];
	}

	// declare and initialize required arrays for storing times for each process
	int waiting_time[n] = {0}, turnaround_time[n] = {0}, completion_time[n] = {0}, completion_order[n] = {0};

	// calculate completion time for each process
	int completed_cnt = 0;
	int t=0;
	int idx=0;
	while(1){

		// On each iteration (time unit), select available and yet to complete process with maximum priority, use FCFS incase of equal priority
		// Note: (the lower the priority number, the higher is the priority of the process)
		int curr_pid = -1, curr_max_priority = 1e9+5;
		for(int i=0;i<n;i++)
		{
			if(rem_burst_time[i] != 0 && arrival_time[i] <= t && priority[i] <= curr_max_priority)
			{
				if(priority[i] == curr_max_priority){
					if(arrival_time[i] < arrival_time[curr_pid]){
						curr_max_priority = priority[i];
						curr_pid = i;					
					}
					else if(arrival_time[i] == arrival_time[curr_pid])
					{
						if(i < curr_pid)
						{
							curr_max_priority = priority[i];
							curr_pid = i;
						}
					}	
				}
				else{
					curr_max_priority = priority[i];
					curr_pid = i;
				}
			}
		} 

		// if no process satisfies the conditions, keep CPU idle for that time unit
		if(curr_pid == -1){
			t++;
			continue;
		}

		// Execute current selected process to completion
		t += rem_burst_time[curr_pid];
		rem_burst_time[curr_pid] = 0;
		completed_cnt++;
		completion_time[curr_pid] = t;
		completion_order[idx] = curr_pid + 1;
		idx++;

		if(completed_cnt == n)
			break;
	}

	// calculate turnaround time for each process and average turnaround time
	for(int i=0;i<n;i++)
	{
		turnaround_time[i] = completion_time[i] - arrival_time[i];
		avg_tat += turnaround_time[i];
	}

	avg_tat /= (double)n;

	// calculate waiting time for each process and average waiting time
	for(int i=0;i<n;i++)
	{
		waiting_time[i] = turnaround_time[i] - burst_time[i];
		avg_wt += waiting_time[i];
	}

	avg_wt /= (double)n;

	// Output 
	printf("\nScheduing Algorithm Used : Non-preemptive Priority\n");
	printf("\nAverage Waiting Time : %.2lf    Average Turnaround Time : %.2lf\n", avg_wt, avg_tat);
	printf("Completion order of Processes : ");
	for(int i=0;i<n;i++)
	{
		printf("P%d ", completion_order[i]);
	}
	printf("\n\n");

	// for(int i=0;i<n;i++)
	// {
	// 	printf("completion_time[%d] = %d, ", i, completion_time[i]);
	// }
	// printf("\n\n");

	// for(int i=0;i<n;i++)
	// {
	// 	printf("turnaround_time[%d] = %d, ", i, turnaround_time[i]);
	// }
	// printf("\n\n");

	// for(int i=0;i<n;i++)
	// {
	// 	printf("waiting_time[%d] = %d, ", i, waiting_time[i]);
	// }
	// printf("\n\n");

	return 0;
}