#include <stdio.h>
#include <stdlib.h>
#define MAX 20

struct process
{
    int pid;
    int at;
    int bt;
    int tat;
    int ct;
    int wt;
};

struct process p[MAX];
int cur = 0;

float sum_tat = 0.0;
float sum_wt = 0.0;

void getPCB(int n)
{

    int i;

    printf("\nEnter the details of process: ");
    for (i = 0; i < n; i++)
    {

        printf("\nProcess---->%d", i + 1);

        printf("\nEnter the arrival time of process: ");
        scanf("%d", &p[i].at);

        p[i].pid = i + 1;

        printf("\nEnter the burst time of process: ");
        scanf("%d", &p[i].bt);
    }
}

void putPCB(int n)
{

    int i;

    printf("\nPID\tWT\tRT\tTAT");
    for (i = 0; i < n; i++)
    {
        printf("\nP%d\t%d\t%d\t%d", p[i].pid, p[i].wt, p[i].wt, p[i].tat);
    }
}

void sortAT(int n)
{

    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {

            if (p[i].at > p[j].at)
            {
                struct process temp;
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void sortPID(int n)
{

    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {

            if (p[i].pid > p[j].pid)
            {
                struct process temp;
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

int getSJ(int n)
{

    int i, j, min = 1000;
    for (i = 0; i < n; i++)
    {

        if (p[i].ct == 0 && p[i].bt < min && p[i].at <= cur)
        {
            min = p[i].bt;
            j = i;
        }
    }

    return j;
}

void setGantt(int n)
{

    int i, sjpos;

    for (i = 0; i < n; i++)
    {

        if (p[i].at > cur)
        {

            p[i].ct = p[i].at + p[i].bt;

            cur = p[i].ct;

            p[i].tat = p[i].ct - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;
        }
        else
        {

            sjpos = getSJ(n);

            p[sjpos].ct = cur + p[sjpos].bt;

            cur = p[sjpos].ct;

            p[sjpos].tat = p[sjpos].ct - p[sjpos].at;
            p[sjpos].wt = p[sjpos].tat - p[sjpos].bt;
        }
    }
}

void calculateAvgTat(int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        sum_tat += p[i].tat;
    }

    printf("\nAverage TAT = %f", (float)sum_tat / n);
}

void calculateAvgWt(int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        sum_wt += p[i].wt;
    }

    printf("\nAverage WT = %f", (float)sum_wt / n);
}

int main()
{

    int i, n;

    printf("\nEnter the number of process you want: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        p[i].ct = 0;
    }

    getPCB(n);
    sortAT(n);
    setGantt(n);
    sortPID(n);
    putPCB(n);
    calculateAvgTat(n);
    calculateAvgWt(n);

    return 0;
}