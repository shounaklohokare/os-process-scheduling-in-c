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
	PROCESS p1;
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
		}
	}
}

void getProcess()
{
	printf("Enter the number of processes : ");
	scanf("%d", &processCount);
	for (i = 0; i < processCount; i++)
	{
		p[i].pid = i;
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
	int time = 0, i = 0;
	printf("\nGanttChart : ");
	printf("\n");
	printf("|%d ", time);
	while (i < processCount)
	{
		p[i].wt = p[i].rt = time - p[i].at;
		time = time + p[i].bt;
		printf("%d ", p[i].pid);
		if (i == processCount - 1)
		{
			printf("%d| ", time);
		}
		else
		{
			printf("%d|%d ", time, time);
		}
		p[i].tat = p[i].wt + p[i].bt;
		totalTat += p[i].tat;
		totalWt += p[i].wt;
		i++;
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
Enter the burst time : 8

Enter the arrival time : 3
Enter the burst time : 1

Enter the arrival time : 8
Enter the burst time : 5

Enter the arrival time : 2
Enter the burst time : 3


GanttChart :
|0 0 8|8 3 11|11 1 12|12 2 17|

Pid     BT      AT      RT      WT      TAT
0       8       0       0       0       8
3       3       2       6       6       9
1       1       3       8       8       9
2       5       8       4       4       9

Average Response time is 4.500000
Average Waiting time is 4.500000
Average Turnaround time is 8.750000
*/
