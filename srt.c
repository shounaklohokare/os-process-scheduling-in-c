#include <stdio.h>
#include <stdbool.h>

struct process
{
    int pid;
    int at;
    int bt;
    int wt;
    int tat;
    int ct;
    int rt;
    int start_time;
} p[100];

int main()
{

    int n, i;

    float bt_remaining[100];
    bool is_completed[100] = {false}, is_first_process = true;

    int current_time = 0;
    int completed = 0;

    float sum_tat = 0;
    float sum_wt = 0;
    float sum_rt = 0;
    float total_idle_time = 0;
    float length_cycle;
    float prev;
    float cpu_utilisation;

    printf("\nEnter the number of process: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {

        printf("\nProcess----->%d", i + 1);
        printf("\nEnter the arrival time of process: ");
        scanf("%d", &p[i].at);

        p[i].pid = i;

        printf("\nEtner the burst time of process: ");
        scanf("%d", &p[i].bt);

        bt_remaining[i] = p[i].bt;
    }

    while (completed != n)
    {

        int min_index = -1;
        int minimum = 1000;

        for (i = 0; i < n; i++)
        {

            if (p[i].at <= current_time && is_completed[i] == false)
            {
                if (bt_remaining[i] < minimum)
                { // find out the minimum bt
                    minimum = bt_remaining[i];
                    min_index = i;
                }

                if (bt_remaining[i] == minimum)
                { // if the bt is same as min bt then check if at is less, if it is so then make it as the next process

                    if (p[i].at < p[min_index].at)
                    {
                        minimum = bt_remaining[i];
                        min_index = i;
                    }
                }
            }
        }

        if (min_index == -1)
        {
            current_time++;
        }

        else
        {
            if (bt_remaining[min_index] == p[min_index].bt)
            { // if remaining bt is same as initial then set start time of process as current time
                p[min_index].start_time = current_time;
                total_idle_time += (is_first_process == true) ? 0 : (p[min_index].start_time - prev);
                is_first_process = false;
            }

            bt_remaining[min_index] -= 1;

            current_time++;
            prev = current_time;
            if (bt_remaining[min_index] == 0)
            { // if remaining bt is 0 then process has finished, thus calculate all attributes

                p[min_index].ct = current_time;
                p[min_index].tat = p[min_index].ct - p[min_index].at;
                p[min_index].wt = p[min_index].tat - p[min_index].bt;
                p[min_index].rt = p[min_index].start_time - p[min_index].at;

                sum_tat += p[min_index].tat;
                sum_wt += p[min_index].wt;
                sum_rt += p[min_index].rt;

                completed++;
                is_completed[min_index] = true;
            }
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT");
    for (i = 0; i < n; i++)
        printf("\n%d\t%d\t%d\t%d\t%d\t%d\t%d", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);

    printf("\n\nAverage TAT = %f", (float)sum_tat / n);
    printf("\nAverage WT = %f", (float)sum_wt / n);
    printf("\nAverage RT = %f", (float)sum_rt / n);
    return 0;
}

/*
Enter the number of process: 4

Process----->1
Enter the arrival time of process: 0

Etner the burst time of process: 10

Process----->2
Enter the arrival time of process: 1

Etner the burst time of process: 2

Process----->3
Enter the arrival time of process: 4

Etner the burst time of process: 5

Process----->4
Enter the arrival time of process: 6

Etner the burst time of process: 1

PID     AT      BT      CT      TAT     WT      RT
0       0       10      18      18      8       0
1       1       2       3       2       0       0
2       4       5       10      6       1       0
3       6       1       7       1       0       0

Average TAT = 6.750000
Average WT = 2.250000
Average RT = 0.000000
*/
