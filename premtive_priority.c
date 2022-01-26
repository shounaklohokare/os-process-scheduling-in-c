#include<stdio.h>
#define MAX 9999;

struct proc
{
	int no,at,bt,rt,ct,res,wt,tat,pri,temp,visited,cur;
};

struct proc read(int i)
{
	struct proc p;
	printf("\nProcess No:%d",i);	
	p.no=i;
	printf("\nEnter arrival Time:");
	scanf("%d",&p.at);
	printf("\nEnter Burst Time:");
	scanf("%d",&p.bt);
	p.rt=p.bt;
	printf("\nEnter priority:");
	scanf("%d",&p.pri);
	p.temp=p.pri;
	p.visited=0;
	return p;
}

int main()
{
	int i,j,n,c,remaining,min_val,min_index;
	struct proc p[10],temp;
	float avgtat=0,avgwt=0,avgrt=0;
	printf("\nEnter no. of processes:");
	scanf("%d",&n);
	for(i=0;i<n;i++)
		p[i]=read(i+1);
	remaining=n;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(p[j].at > p[j+1].at)
			{
				temp=p[j];
				p[j]=p[j+1];
				p[j+1]=temp;
			}
		}
	}
	min_val=p[0].temp;
	min_index=0;
	
	for(j=0;j<n && p[j].at<=p[0].at;j++)
	{
		if(p[j].temp<min_val)
		{
			min_val=p[j].temp;
			min_index=j;
		}
	}
	i=min_index;
	c=p[i].ct=p[i].at+1;
	printf("|%d P%d %d|",c-1,p[i].no,c);
	p[i].rt--;
	if(p[i].rt==0)
	{
		p[i].temp=MAX;
		remaining--;
	}
	while(remaining>0)
	{
		min_val=p[0].temp;
		min_index=0;

		if(p[i].visited==0)
		{
			p[i].cur=c-1;
			p[i].visited=1;
		}
			
		for(j=0;j<n && p[j].at<=c;j++)
		{
			if(p[j].temp<min_val)
			{
				min_val=p[j].temp;
				min_index=j;
			}
		}
		i=min_index;
		c=p[i].ct=c+1;
		printf("|%d P%d %d|",c-1,p[i].no,c);
		p[i].rt--;
		if(p[i].rt==0)
		{
			p[i].temp=MAX;
			remaining--;
		}
	}

	printf("\nPNo\tat\tbt\tpri\tct\trt\twt\ttat\tcur");
	for(i=0;i<n;i++)
	{
		p[i].tat=p[i].ct-p[i].at;
		avgtat+=p[i].tat;
		p[i].wt=p[i].tat-p[i].bt;
		avgwt+=p[i].wt;
		p[i].res=p[i].cur-p[i].at;
		avgrt+=p[i].res;
		printf("\nP%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d",p[i].no,p[i].at,p[i].bt,p[i].pri,p[i].ct,p[i].res,p[i].wt,p[i].tat,p[i].cur);
	}
	


	avgtat=avgtat/n;
	avgwt=avgwt/n;
	avgrt=avgrt/n;
	
	printf("\nAverage RT=%f",avgrt);	
	printf("\nAverage WT=%f",avgwt);			
	printf("\nAverage TAT=%f\n",avgtat);
	
	
	return 0;
}
/*
Enter no. of processes:5

Process No:1
Enter arrival Time:
E^C
C:\Users\Admin\Desktop\mru OS\OS>a

Enter no. of processes:6

Process No:1
Enter arrival Time:12

Enter Burst Time:7

Enter priority:5

Process No:2
Enter arrival Time:1

Enter Burst Time:4

Enter priority:1

Process No:3
Enter arrival Time:0

Enter Burst Time:3

Enter priority:2

Process No:4
Enter arrival Time:2

Enter Burst Time:4

Enter priority:1

Process No:5
Enter arrival Time:8

Enter Burst Time:7

Enter priority:2

Process No:6
Enter arrival Time:14

Enter Burst Time:2

Enter priority:4
|0 P3 1||1 P2 2||2 P2 3||3 P2 4||4 P2 5||5 P4 6||6 P4 7||7 P4 8||8 P4 9||9 P3 10||10 P3 11||11 P5 12||12 P5 13||13 P5 14||14 P5 15||15 P5 16||16 P5 17||17 P5 18||18 P6 19||19 P6 20||20 P1 21||21 P1 22||22 P1 23||23 P1 24||24 P1 25||25 P1 26||26 P1 27|
PNo     at      bt      pri     ct      rt      wt      tat     cur
P3      0       3       2       11      0       8       11      0
P2      1       4       1       5       0       0       4       1
P4      2       4       1       9       3       3       7       5
P5      8       7       2       18      3       3       10      11
P1      12      7       5       27      8       8       15      20
P6      14      2       4       20      4       4       6       18
Average RT=3.000000
Average WT=4.333333
Average TAT=8.833333
  
 */
