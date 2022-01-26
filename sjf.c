#include <stdio.h>

typedef struct PROCESS
{
	int pid, tat, wt, at, bt, rt;
} PROCESS;

PROCESS p[10];
int processCount, i, j, k, totalTat = 0, totalWt = 0;
float avgtat, avgwt;

void sort()
{
	PROCESS p1, p2;
	for (i = 0; i < processCount; i++)
	{
		for (j = i + 1; j < processCount; j++)
		{
			if (p[j].at < p[i].at)
			{
				p1 = p[j];
				p[j] = p[i];
				p[i] = p1;
			}
			else if (p[j].bt < p[i].bt && p[j].at == p[i].at)
			{
				p2 = p[j];
				p[j] = p[i];
				p[i] = p2;
			}
		}
	}
}

void getProcess()
{
	printf("Enter the number of processes : ");
	scanf("%d", &processCount);
	for (i = 0; i < processCount; i++)
	{

		p[i].pid = i + 1;

		printf("Enter the arrival time : ");
		scanf("%d", &p[i].at);

		printf("Enter the burst time : ");
		scanf("%d", &p[i].bt);

		printf("\n");
	}
	sort();
}

void process()
{
	int time = 0, i = 0, k = 1, min, sum = 0, sum1 = 0;
	PROCESS temp1;
	printf("\nGanttChart : ");
	printf("\n");
	printf("|%d ", time);
	for (j = 0; j < processCount; j++)
	{
		time = time + p[j].bt;
		min = p[k].bt;
		for (i = k; i < processCount; i++)
		{
			if (time >= p[i].at && p[i].bt < min)
			{
				temp1 = p[k];
				p[k] = p[i];
				p[i] = temp1;
			}
		}
		k++;
		printf("P%d ", p[j].pid);
		if (j == processCount - 1)
		{
			printf("%d|", time);
		}
		else
		{
			printf("%d|%d ", time, time);
		}
	}
	for (i = 1; i < processCount; i++)
	{
		sum = sum + p[i - 1].bt;
		p[i].wt = p[i].rt = sum - p[i].at;
		totalWt = totalWt + p[i].wt;
	}
	for (i = 0; i < processCount; i++)
	{
		p[i].tat = p[i].wt + p[i].bt;
		totalTat = totalTat + p[i].tat;
	}
	printf("\n");
	avgtat = (float)totalTat / processCount;
	avgwt = (float)totalWt / processCount;
}

void display()
{
	printf("\n");
	printf("Pid\tBT\tAT\tRT\tWT\tTAT\n");
	for (i = 0; i < processCount; i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].bt, p[i].at, p[i].rt, p[i].wt, p[i].tat);
	}
	printf("\n");
	printf("Average Response time is %f \n", avgwt);
	printf("Average Waiting time is %f \n", avgwt);
	printf("Average Turnaround time is %f \n", avgtat);
}
main()
{
	getProcess();
	process();
	display();
}
/*
Enter the number of processes : 4
Enter the arrival time : 0
Enter the burst time : 2

Enter the arrival time : 2
Enter the burst time : 3

Enter the arrival time : 2
Enter the burst time : 4

Enter the arrival time : 3
Enter the burst time : 3


GanttChart :
|0 P1 2|2 P2 5|5 P4 8|8 P3 12|

Pid     BT      AT      RT      WT      TAT
1       2       0       0       0       2
2       3       2       0       0       3
4       3       3       2       2       5
3       4       2       6       6       10

Average Response time is 2.000000
Average Waiting time is 2.000000
Average Turnaround time is 5.000000
*/
