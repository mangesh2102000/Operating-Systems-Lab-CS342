/* Name : Chandrawanshi Mangesh Shivaji 
Roll Number : 1801CS16
CS342 Lab - Assignment 7
FileName : Q1.cpp
Problem Statement : Write a program to calculate average WT, TAT, the completion order using Round Robin (RR) scheduling */

#include <iostream>
#include <queue>

using namespace std;

// driver code
int main(int argc, char const *argv[])
{
	// Input from user
	int n, tq;
	printf("\nEnter number of total processes (n), time quantum (tq) on First Line and\nSpecify arrival_time and burst_time of n processes on following lines (ith line should contain data for ith process) : \n");
	cin >> n >> tq;

	double avg_wt = 0, avg_tat = 0;

	if(n == 0){
		printf("\nAverage Waiting Time : %.2lf    Average Turnaround Time : %.2lf\n", avg_wt, avg_tat);
		printf("Completion order of Processes : \n");
		return 0;
	}

	// Input of arrival and burst times for respective processes
	int arrival_time[n], burst_time[n], rem_burst_time[n];

	for(int i=0;i<n;i++)
	{
		cin >> arrival_time[i] >> burst_time[i];

		if(arrival_time[i] < 0 || burst_time[i] < 0){
			printf("Usage : Input Only Non-negative Values for time\n");
			exit(1);
		}
		rem_burst_time[i] = burst_time[i];
	}

	// declare and initialize required arrays for storing times for each process
	int waiting_time[n] = {0}, turnaround_time[n] = {0}, completion_time[n] = {0}, completion_order[n] = {0};

	// queue to perform RR scheduling
	queue <int> q;
	int inqueue[n] = {0};

	// calculate completion time for each process
	int completed_cnt = 0;
	int t=0;
	int idx=0;
	int rem_tq = tq;
	while(1){

		// reset remaining time quantum to max value
		rem_tq = tq;

		// check if any process not in queue(not completed yet) has arrived, if yes add it to the back of queue
		for(int i=0;i<n;i++){
			if(arrival_time[i] <= t && inqueue[i] == 0){
				q.push(i);
				inqueue[i] = 1;
			}
		}

		// Keep CPU idle if there is no process in queue
		if(q.empty()){
			t++;
			continue;
		}

		// get PID for process at the front of queue
		int curr_pid = q.front();
		q.pop();

		// execute current time quantum
		while(rem_tq != 0 and rem_burst_time[curr_pid] != 0){
			rem_burst_time[curr_pid] -= 1;
			rem_tq--;
			t++;

			// check if any process not in queue(not completed yet) has arrived if yes add it to the back of queue
			for(int i=0;i<n;i++){
				if(arrival_time[i] <= t && inqueue[i] == 0){
					q.push(i);
					inqueue[i] = 1;
				}
			}
		}

		// Check for completion of current selected process
		if(rem_burst_time[curr_pid] == 0)
		{
			completed_cnt++;
			completion_time[curr_pid] = t;
			completion_order[idx] = curr_pid + 1;
			idx++;
		}
		else{
			// Add it to back of queue, if not completed
			q.push(curr_pid);
		}

		// break the loop if all processes are completed
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
	printf("\nScheduing Algorithm Used : Round Robin\n");
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