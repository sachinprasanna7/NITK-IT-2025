#include<stdio.h>
int main()

{
    int  p[100],arrivalTime[100],burstTime[100],burstTimeFinal[100],completionTime[100],turnaaroundTime[100],waitingTime[100],vis[100]= {0},i,j,temp=0,n,pr[100],m,bf[10000];
    float avgWaitingTime=0,avgTurnaaroundTime=0;
    printf("enter no of proccess you want:");
    scanf("%d",&n);
    printf("enter %d Arrival Time and Burst Time:\n",n);
    int min=100000000,ix=-1;
    for(i=0; i<n; i++)
    {
        p[i]=i+1;
        scanf("%d %d",&arrivalTime[i],&burstTime[i]);
        burstTimeFinal[i]=burstTime[i];
        if(min>arrivalTime[i])
        {
            min=arrivalTime[i];
            ix=i;
        }
    }
    printf("enter time quantam:");
    scanf("%d",&m);
    int ans=0,ii=0,jj=0;
    bf[jj++]=ix;
    vis[ix]=1;
    for(j=0; j<n; )
    {
        printf("%d ",bf[ii]+1);
        int o=burstTime[bf[ii]],sub;
        if(o>m)
        {
            ans+=m;
            burstTime[bf[ii]]-=m;
            for(i=0; i<n; i++)
            {
                if(vis[i]==0 &&arrivalTime[i]<=ans)
                {
                    bf[jj++]=i;
                    vis[i]=1;
                }
            }
            bf[jj++]=bf[ii];
        }
        else
        {
            ans+=o;
            burstTime[bf[ii]]-=o;
            for(i=0; i<n; i++)
            {
                if(vis[i]==0 &&arrivalTime[i]<=ans)
                {
                    bf[jj++]=i;
                    vis[i]=1;
                }
            }
            completionTime[bf[ii]]=ans;
            j++;
        }

        ii++;
    }
    printf("\np\t A.T\t B.T\t C.T\t TAT\t WT");
    for(i=0; i<n; i++)
    {
        turnaaroundTime[i]=completionTime[i]-arrivalTime[i];
        waitingTime[i]=turnaaroundTime[i]-burstTimeFinal[i];
        avgTurnaaroundTime+=turnaaroundTime[i];
        avgWaitingTime+=waitingTime[i];
    }
    avgTurnaaroundTime=avgTurnaaroundTime/n;
    avgWaitingTime=avgWaitingTime/n;
    for(i=0; i<n; i++)
    {
        printf("\nP%d\t %d\t %d\t %d \t %d \t %d",p[i],arrivalTime[i],burstTimeFinal[i],completionTime[i],turnaaroundTime[i],waitingTime[i]);
    }
    printf("\naverage turnaround time is %f",avgTurnaaroundTime);

    printf("\naverage wating timme is %f",avgWaitingTime);
    return 0;
}