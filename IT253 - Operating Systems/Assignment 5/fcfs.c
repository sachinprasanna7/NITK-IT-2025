#include<stdio.h>
int main()
{
    int process[100],arrivalTime[100],burstTime[100],completionTime[100],turnaroundTime[100],waitingTime[100],vis[100]= {0},ser[100],i,j,temp=0,n;
    float avgWaitingTime=0,avgTurnaroundTime=0;
    printf("enter no of proccess you want:");
    scanf("%d",&n);
    printf("enter %d arrival time and burst time:\n",n);
    for(i=0; i<n; i++)
    {
        process[i]=i+1;
        scanf("%d %d",&arrivalTime[i],&burstTime[i]);
    }
    int ans=0;
    for(j=0; j<n;)
    {
        int mn=1000000000,idx=1000000000;
        for(i=0; i<n; i++)
        {
            if(vis[i]==0)
            {
                if(ans>=arrivalTime[i] && mn>arrivalTime[i])
                {
                    mn=arrivalTime[i];
                    idx=i;
                }
            }
        }
        if(idx==1000000000)
        {
            ans++;
        }
        else
        {
            ans+=burstTime[idx];
            vis[idx]=1;
            completionTime[idx]=ans;
            ser[j]=process[idx];
            j++;
        }
    }

    printf("\n\nProcess\t Arrival Time\t Burst Time\t Completion Time\t Turnaround Time\t Waiting Time");
    for(i=0; i<n; i++)
    {
        turnaroundTime[i]=completionTime[i]-arrivalTime[i];
        waitingTime[i]=turnaroundTime[i]-burstTime[i];
        avgTurnaroundTime+=turnaroundTime[i];
        avgWaitingTime+=waitingTime[i];
    }
    avgTurnaroundTime=avgTurnaroundTime/n;
    avgWaitingTime=avgWaitingTime/n;
    for(i=0; i<n; i++)
    {
        printf("\nP%d\t\t %d\t\t %d\t\t %d\t\t %d\t\t %d",process[i],arrivalTime[i],burstTime[i],completionTime[i],turnaroundTime[i],waitingTime[i]);
    }
    printf("\nAverage turnaround time is %f",avgTurnaroundTime);

    printf("\nAverage wating timme is %f",avgWaitingTime);

    return 0;
}
