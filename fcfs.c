#include <stdio.h>

struct process
{
    int at;
    int bt;
    int tat;
    int wt;
    int rt;
    int pid;
};

void sort_by_at(struct process p[3], int n)
{

    int i, j;
    for (i = 0; i < n - 1; i++)
    {

        for (j = 0; j < n - i - 1; j++)
        {

            if (p[j].at > p[j + 1].at)
            {
                struct process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void sort_by_pid(struct process p[3], int n)
{

    int i, j;
    for (i = 0; i < n - 1; i++)
    {

        for (j = 0; j < n - i - 1; j++)
        {

            if (p[j].pid > p[j + 1].pid)
            {
                struct process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void calculate(struct process p[3], int n)
{

    int sum_bt = 0;
    int i;
    for (i = 0; i < n; i++)
    {

        p[i].rt = sum_bt - p[i].at;
        p[i].wt = sum_bt - p[i].at;

        sum_bt += p[i].bt;

        p[i].tat = sum_bt - p[i].at;
    }
}

void print_table(struct process p[3], int n)
{

    int i;
    printf("PID\t\tRT\t\tWT\t\tTAT\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d", p[i].pid + 1, p[i].rt, p[i].wt, p[i].tat);
        printf("\n");
    }
}

void print_gantt_chart(struct process p[3], int n)
{
    printf("Gantt Chart is: \n");
    int sum_bt = 0;
    int i;
    for (i = 0; i < n; i++)
    {
        printf(" [P%d]%d -->", i + 1, sum_bt);
        sum_bt += p[i].bt;
    }
    printf(" [P%d]%d \n\n", i + 1, sum_bt);
}

void avgWT(struct process p[3], int n)
{
    int sumWT = 0;
    int i;
    for (i = 0; i < n; i++)
    {
        sumWT += p[i].wt;
    }

    printf("\nAverage WT = %f", (float)sumWT / n);
}

void avgTAT(struct process p[3], int n)
{
    int sumTAT = 0;
    int i;
    for (i = 0; i < n; i++)
    {
        sumTAT += p[i].tat;
    }

    printf("\nAverage TAT = %f", (float)sumTAT / n);
}

int main()
{

    int n;

    printf("Enter the number of processes you want:");
    scanf("%d", &n);

    struct process p[n];

    int i;
    for (i = 0; i < n; i++)
    {
        p[i].pid = i;

        printf("\nEnter the details of process number %d\n", i + 1);

        printf("Enter the arrival of the process: ");
        scanf("%d", &p[i].at);

        printf("Enter the burst time of the process: ");
        scanf("%d", &p[i].bt);

        printf("\n");
    }

    sort_by_at(p, n);

    print_gantt_chart(p, n);

    calculate(p, n);

    sort_by_pid(p, n);

    print_table(p, n);

    avgTAT(p, n);

    avgWT(p, n);

    return 0;
}
