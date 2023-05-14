//less value higher priority

#include<stdio.h>
int main()
{
    int  p[10],at[10],bt[10],ct[10],tat[10],wt[10],vis[10]= {0},i,j,temp=0,n,pr[10];
    float awt=0,atat=0;
    printf("enter no of proccess you want:");
    scanf("%d",&n);
    printf("enter %d Priority, Arrival Time and Burst Time:\n",n);
    for(i=0; i<n; i++)
    {
        p[i]=i+1;
        scanf("%d %d %d",&pr[i],&at[i],&bt[i]);
    }
    int ans=0;
    for(j=0; j<n;)
    {
        int mn,idx;
        mn=idx=1000000000;
        for(i=0; i<n; i++)
        {
            if(vis[i]==0)
            {
                if(ans>=at[i] && mn>pr[i])
                {
                    mn=pr[i];
                    idx=i;
                }
                else if(ans>=at[i] && mn==pr[i])
                {
                    if(at[idx]>at[i])
                    {
                        mn=pr[i];
                        idx=i;
                    }
                }
            }
        }
        if(idx==1000000000)
        {
            ans++;
        }
        else
        {
            ans+=bt[idx];
            vis[idx]=1;
            ct[idx]=ans;
            j++;
        }
    }
    printf("\np\t A.T\t B.T\t C.T\t TAT\t WT");
    for(i=0; i<n; i++)
    {
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
        atat+=tat[i];
        awt+=wt[i];
    }
    atat=atat/n;
    awt=awt/n;
    for(i=0; i<n; i++)
    {
        printf("\nP%d\t %d\t %d\t %d \t %d \t %d",p[i],at[i],bt[i],ct[i],tat[i],wt[i]);
    }
    printf("\naverage turnaround time is %f",atat);

    printf("\naverage wating timme is %f",awt);
    return 0;
}