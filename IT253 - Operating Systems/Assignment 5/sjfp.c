#include<stdio.h>
int main()
{
    int  p[100],arrivalTime[100],burstTime[100],burstTimeFinal[100],completionTime[100],turnaroundTime[100],waitingTime[100],vis[100]= {0},ser[100],i,j,temp=0,n;
    float avgWaitingTime=0,avgTurnaroundTime=0;
    printf("enter no of proccess you want:");
    scanf("%d",&n);
    printf("enter %d process:\n",n);
    for(i=0; i<n; i++)
    {
        p[i]=i+1;
        scanf("%d %d",&arrivalTime[i],&burstTime[i]);
        burstTimeFinal[i]=burstTime[i];
    }
    int ans=0;
    for(j=0; j<n; )
    {
        int mn,idx;
        mn=idx=100000000;
        for(i=0; i<n; i++)
        {
            if(vis[i]==0)
            {
                if(ans>=arrivalTime[i] && mn>burstTime[i])
                {
                    mn=burstTime[i];
                    idx=i;
                }
                else if(ans>=arrivalTime[i] && mn==burstTime[i])
                {
                    if(arrivalTime[idx]>arrivalTime[i])
                    {
                        mn=burstTime[i];
                        idx=i;
                    }
                }
            }
        }
        if(idx==10000000000)
        {
            ans++;
        }
        else
        {
            ans++;
            burstTime[idx]--;
            if(burstTime[idx]==0)
            {
                j++;
                vis[idx]=1;
                completionTime[idx]=ans;
            }
        }
    }
    printf("\np\t A.T\t B.T\t C.T\t TAT\t WT");
    for(i=0; i<n; i++)
    {
        turnaroundTime[i]=completionTime[i]-arrivalTime[i];
        waitingTime[i]=turnaroundTime[i]-burstTimeFinal[i];
        avgTurnaroundTime+=turnaroundTime[i];
        avgWaitingTime+=waitingTime[i];
    }
    avgTurnaroundTime=avgTurnaroundTime/n;
    avgWaitingTime=avgWaitingTime/n;
    for(i=0; i<n; i++)
    {
        printf("\nP%d\t %d\t %d\t %d \t %d \t %d",p[i],arrivalTime[i],burstTimeFinal[i],completionTime[i],turnaroundTime[i],waitingTime[i]);
    }
    printf("\naverage turnaround time is %f",avgTurnaroundTime);

    printf("\naverage wating timme is %f",avgWaitingTime);
    return 0;
}