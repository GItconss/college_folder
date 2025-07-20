#include<stdio.h>
int main()
{
	int n,i,bt[25],pid[25],tat[25],wt[25],t_tat=0.0,t_wt=0.0;
	printf("enter the size : ");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
	    printf("enter the brust time p %d=",i+1);
	    scanf("%d",&bt[i]);
	    pid[i]=i+1;
	}
	wt[0]=0;
	for(i=0;i<n;i++)
	{
		wt[i]=bt[i-1]+wt[i-1];
	}
	for(i=0;i<n;i++)
	{
		tat[i]=bt[i]+wt[i];
		t_tat+=tat[i];
		t_wt+=wt[i];
	}
	printf("p_id\tbrust_time\twaiting_t\tturnaround_t\t\n");
	for(i=0;i<n;i++)
	{
	    printf("%4d\t%10d\t%9d\t%11d\n",pid[i],bt[i],wt[i],tat[i]);
	}
	printf(" Avg turnaround time =%d",t_tat/n);
	printf(" Avg waiting time =%d",t_wt/n);
}

