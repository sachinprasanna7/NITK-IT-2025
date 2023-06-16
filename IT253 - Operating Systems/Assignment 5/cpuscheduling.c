#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// FIRST COME FIRST SERVE

void FCFS(int processes[][2], int n)
{
    int process[100], arrivalTime[100], burstTime[100], completionTime[100], turnaroundTime[100], waitingTime[100], vis[100] = {0}, ser[100], i, j, temp = 0;
    float avgWaitingTime = 0, avgTurnaroundTime = 0;

    for (i = 0; i < n; i++)
    {
        process[i] = i + 1;
        arrivalTime[i] = processes[i][0];
        burstTime[i] = processes[i][1];
    }

    int ans = 0;
    for (j = 0; j < n;)
    {
        int mn = INT_MAX, idx = INT_MAX;
        for (i = 0; i < n; i++)
        {
            if (vis[i] == 0)
            {
                if (ans >= arrivalTime[i] && mn > arrivalTime[i])
                {
                    mn = arrivalTime[i];
                    idx = i;
                }
            }
        }
        if (idx == INT_MAX)
        {
            ans++;
        }
        else
        {
            ans += burstTime[idx];
            vis[idx] = 1;
            completionTime[idx] = ans;
            ser[j] = process[idx];
            j++;
        }
    }

    printf("\n\nProcess\t| Arrival Time\t| Burst Time\t| Completion Time\t| Turnaround Time\t| Waiting Time");
    for (i = 0; i < n; i++)
    {
        turnaroundTime[i] = completionTime[i] - arrivalTime[i];
        waitingTime[i] = turnaroundTime[i] - burstTime[i];
        avgTurnaroundTime += turnaroundTime[i];
        avgWaitingTime += waitingTime[i];
    }
    avgTurnaroundTime = avgTurnaroundTime / n;
    avgWaitingTime = avgWaitingTime / n;
    for (i = 0; i < n; i++)
    {
        printf("\n------------------------------------------------------------------------------------------------------");
        printf("\nP%d\t| %d\t\t| %d\t\t| %d\t\t\t| %d\t\t\t| %d", process[i], arrivalTime[i], burstTime[i], completionTime[i], turnaroundTime[i], waitingTime[i]);
    }
    printf("\n------------------------------------------------------------------------------------------------------");
    printf("\nAverage Turnaround Time: %.2f", avgTurnaroundTime);
    printf("\nAverage Waiting Time: %.2f", avgWaitingTime);
}



// SHORTEST JOB FIRST NON PREEMPTIVE

void SJFNP(int arr[][2], int num_processes)
{
    int p[100], arrivalTime[100], burstTime[100], completionTime[100], turnaroundTime[100], waitingTime[100], vis[100] = {0}, ser[100], i, j, temp = 0;
    float avgWaitingTime = 0, avgTurnaroundTime = 0;
    for (i = 0; i < num_processes; i++)
    {
        p[i] = i + 1;
        arrivalTime[i] = arr[i][0];
        burstTime[i] = arr[i][1];
    }
    int ans = 0;
    for (j = 0; j < num_processes;)
    {
        int mn, idx;
        mn = idx = INT_MAX;
        for (i = 0; i < num_processes; i++)
        {
            if (vis[i] == 0)
            {
                if (ans >= arrivalTime[i] && mn > burstTime[i])
                {
                    mn = burstTime[i];
                    idx = i;
                }
                else if (ans >= arrivalTime[i] && mn == burstTime[i])
                {
                    if (arrivalTime[idx] > arrivalTime[i])
                    {
                        mn = burstTime[i];
                        idx = i;
                    }
                }
            }
        }
        if (idx == INT_MAX)
        {
            ans++;
        }
        else
        {
            ans += mn;
            vis[idx] = 1;
            completionTime[idx] = ans;
            ser[j] = p[idx];
            j++;
        }
    }
    printf("\n\nProcess\t| Arrival Time\t| Burst Time\t| Completion Time\t| Turnaround Time\t| Waiting Time");
    for (i = 0; i < num_processes; i++)
    {
        turnaroundTime[i] = completionTime[i] - arrivalTime[i];
        waitingTime[i] = turnaroundTime[i] - burstTime[i];
        avgTurnaroundTime += turnaroundTime[i];
        avgWaitingTime += waitingTime[i];
    }
    avgTurnaroundTime = avgTurnaroundTime / num_processes;
    avgWaitingTime = avgWaitingTime / num_processes;
    for (i = 0; i < num_processes; i++)
    {
        printf("\n------------------------------------------------------------------------------------------------------");
        printf("\nP%d\t| %d\t\t| %d\t\t| %d\t\t\t| %d\t\t\t| %d", p[i], arrivalTime[i], burstTime[i], completionTime[i], turnaroundTime[i], waitingTime[i]);
    }
    printf("\n------------------------------------------------------------------------------------------------------");
    printf("\nAverage Turnaround Time: %.2f", avgTurnaroundTime);
    printf("\nAverage Waiting Time: %.2f", avgWaitingTime);
}



// SHORTEST JOB FIRST PREEMPTIVE

void SJFP(int processes[][2], int n)
{
    int p[100], arrivalTime[100], burstTime[100], burstTimeFinal[100], completionTime[100], turnaroundTime[100], waitingTime[100], vis[100] = {0}, ser[100], i, j, temp = 0;
    float avgWaitingTime = 0, avgTurnaroundTime = 0;
    for (i = 0; i < n; i++)
    {
        p[i] = i + 1;
        arrivalTime[i] = processes[i][0];
        burstTime[i] = processes[i][1];
        burstTimeFinal[i] = burstTime[i];
    }
    int ans = 0;
    for (j = 0; j < n;)
    {
        int mn, idx;
        mn = idx = 100000000;
        for (i = 0; i < n; i++)
        {
            if (vis[i] == 0)
            {
                if (ans >= arrivalTime[i] && mn > burstTime[i])
                {
                    mn = burstTime[i];
                    idx = i;
                }
                else if (ans >= arrivalTime[i] && mn == burstTime[i])
                {
                    if (arrivalTime[idx] > arrivalTime[i])
                    {
                        mn = burstTime[i];
                        idx = i;
                    }
                }
            }
        }
        if (idx == INT_MAX)
        {
            ans++;
        }
        else
        {
            ans++;
            burstTime[idx]--;
            if (burstTime[idx] == 0)
            {
                j++;
                vis[idx] = 1;
                completionTime[idx] = ans;
            }
        }
    }
    printf("\n\nProcess\t| Arrival Time\t| Burst Time\t| Completion Time\t| Turnaround Time\t| Waiting Time");
    for (i = 0; i < n; i++)
    {
        turnaroundTime[i] = completionTime[i] - arrivalTime[i];
        waitingTime[i] = turnaroundTime[i] - burstTimeFinal[i];
        avgTurnaroundTime += turnaroundTime[i];
        avgWaitingTime += waitingTime[i];
    }
    avgTurnaroundTime = avgTurnaroundTime / n;
    avgWaitingTime = avgWaitingTime / n;
    for (i = 0; i < n; i++)
    {
        printf("\n------------------------------------------------------------------------------------------------------");
        printf("\nP%d\t| %d\t\t| %d\t\t| %d\t\t\t| %d\t\t\t| %d", p[i], arrivalTime[i], burstTimeFinal[i], completionTime[i], turnaroundTime[i], waitingTime[i]);
    }
    printf("\n------------------------------------------------------------------------------------------------------");
    printf("\nAverage Turnaround Time: %.2f", avgTurnaroundTime);
    printf("\nAverage Waiting Time: %.2f", avgWaitingTime);
}



// ROUND ROBIN

void RR(int processes[][2], int n, int time_quantum)
{
    int p[100], arrivalTime[100], burstTime[100], burstTimeFinal[100], completionTime[100], turnaaroundTime[100], waitingTime[100], vis[100] = {0}, i, j, temp = 0, pr[100], m, bf[10000];
    float avgWaitingTime = 0, avgTurnaaroundTime = 0;

    int min = 100000000, ix = -1;
    for (i = 0; i < n; i++)
    {
        p[i] = i + 1;
        arrivalTime[i] = processes[i][0];
        burstTime[i] = processes[i][1];
        burstTimeFinal[i] = burstTime[i];
        if (min > arrivalTime[i])
        {
            min = arrivalTime[i];
            ix = i;
        }
    }

    int ans = 0, ii = 0, jj = 0;
    bf[jj++] = ix;
    vis[ix] = 1;
    for (j = 0; j < n;)
    {
        int o = burstTime[bf[ii]], sub;
        if (o > time_quantum)
        {
            ans += time_quantum;
            burstTime[bf[ii]] -= time_quantum;
            for (i = 0; i < n; i++)
            {
                if (vis[i] == 0 && arrivalTime[i] <= ans)
                {
                    bf[jj++] = i;
                    vis[i] = 1;
                }
            }
            bf[jj++] = bf[ii];
        }
        else
        {
            ans += o;
            burstTime[bf[ii]] -= o;
            for (i = 0; i < n; i++)
            {
                if (vis[i] == 0 && arrivalTime[i] <= ans)
                {
                    bf[jj++] = i;
                    vis[i] = 1;
                }
            }
            completionTime[bf[ii]] = ans;
            j++;
        }

        ii++;
    }
    printf("\n\nProcess\t| Arrival Time\t| Burst Time\t| Completion Time\t| Turnaround Time\t| Waiting Time");
    for (i = 0; i < n; i++)
    {
        turnaaroundTime[i] = completionTime[i] - arrivalTime[i];
        waitingTime[i] = turnaaroundTime[i] - burstTimeFinal[i];
        avgTurnaaroundTime += turnaaroundTime[i];
        avgWaitingTime += waitingTime[i];
    }

    avgTurnaaroundTime = avgTurnaaroundTime / n;
    avgWaitingTime = avgWaitingTime / n;

    for (i = 0; i < n; i++)
    {
        printf("\n------------------------------------------------------------------------------------------------------");
        printf("\nP%d\t| %d\t\t| %d\t\t| %d\t\t\t| %d\t\t\t| %d", p[i], arrivalTime[i], burstTimeFinal[i], completionTime[i], turnaaroundTime[i], waitingTime[i]);
    }
    printf("\n------------------------------------------------------------------------------------------------------");
    printf("\nAverage Turnaround Time: %.2f", avgTurnaaroundTime);
    printf("\nAverage Waiting Time: %.2f", avgWaitingTime);
}



// PRIORIY NON PREEMPTIVE

void PNP(int processes[][3], int n)
{
    int p[n], arrivalTime[n], burstTime[n], completionTime[n], turnaroundTime[n], waitingTime[n], vis[100] = {0}, i, j, temp = 0, pr[n];
    float avgTurnaroundTime = 0, avgWaitingTime = 0;

    for (i = 0; i < n; i++)
    {
        p[i] = i + 1;
        pr[i] = processes[i][2];
        arrivalTime[i] = processes[i][0];
        burstTime[i] = processes[i][1];
    }

    int ans = 0;
    for (j = 0; j < n;)
    {
        int mn, idx;
        mn = idx = INT_MAX;
        for (i = 0; i < n; i++)
        {
            if (vis[i] == 0)
            {
                if (ans >= arrivalTime[i] && mn > pr[i])
                {
                    mn = pr[i];
                    idx = i;
                }
                else if (ans >= arrivalTime[i] && mn == pr[i])
                {
                    if (arrivalTime[idx] > arrivalTime[i])
                    {
                        mn = pr[i];
                        idx = i;
                    }
                }
            }
        }
        if (idx == INT_MAX)
        {
            ans++;
        }
        else
        {
            ans += burstTime[idx];
            vis[idx] = 1;
            completionTime[idx] = ans;
            j++;
        }
    }
    printf("\n\nProcess\t| Priority\t| Arrival Time\t| Burst Time\t| Completion Time\t| Turnaround Time\t| Waiting Time");
    for (i = 0; i < n; i++)
    {
        turnaroundTime[i] = completionTime[i] - arrivalTime[i];
        waitingTime[i] = turnaroundTime[i] - burstTime[i];
        avgTurnaroundTime += turnaroundTime[i];
        avgWaitingTime += waitingTime[i];
    }
    avgTurnaroundTime = avgTurnaroundTime / n;
    avgWaitingTime = avgWaitingTime / n;
    for (i = 0; i < n; i++)
    {
        printf("\n----------------------------------------------------------------------------------------------------------------------");
        printf("\nP%d\t| %d\t\t| %d\t\t| %d\t\t| %d\t\t\t| %d\t\t\t| %d", p[i], pr[i],arrivalTime[i], burstTime[i], completionTime[i], turnaroundTime[i], waitingTime[i]);
    }
    printf("\n----------------------------------------------------------------------------------------------------------------------");
    printf("\nAverage Turnaround Time: %.2f", avgTurnaroundTime);
    printf("\nAverage Waiting Time: %.2f", avgWaitingTime);
}



// PROIRITY PREEMPTIVE

void PP(int processes[][3], int n)
{
    int p[n], arrivalTime[n], burstTime[n], burstTimeFinal[n], completionTime[n], turnaroundTime[n], waitingTime[n], i, j, temp = 0, pr[n];
    int vis[100] = {0};
    float avgWaitingTime = 0, avgTurnaroundTime = 0;

    for (i = 0; i < n; i++)
    {
        p[i] = i + 1;
        pr[i] = processes[i][2];
        arrivalTime[i] = processes[i][0];
        burstTime[i] = processes[i][1];
        burstTimeFinal[i] = burstTime[i];
    }

    int ans = 0;
    for (j = 0; j < n;)
    {
        int mn, idx;
        mn = idx = INT_MAX;
        for (i = 0; i < n; i++)
        {
            if (vis[i] == 0)
            {
                if (ans >= arrivalTime[i] && mn > pr[i])
                {
                    mn = pr[i];
                    idx = i;
                }
                else if (ans >= arrivalTime[i] && mn == pr[i])
                {
                    if (arrivalTime[idx] > arrivalTime[i])
                    {
                        mn = pr[i];
                        idx = i;
                    }
                }
            }
        }
        if (idx == INT_MAX)
        {
            ans++;
        }
        else
        {
            ans++;
            burstTime[idx]--;
            if (burstTime[idx] == 0)
            {
                j++;
                vis[idx] = 1;
                completionTime[idx] = ans;
            }
        }
    }
    printf("\n\nProcess\t| Priority\t| Arrival Time\t| Burst Time\t| Completion Time\t| Turnaround Time\t| Waiting Time");
    for (i = 0; i < n; i++)
    {
        turnaroundTime[i] = completionTime[i] - arrivalTime[i];
        waitingTime[i] = turnaroundTime[i] - burstTimeFinal[i];
        avgTurnaroundTime += turnaroundTime[i];
        avgWaitingTime += waitingTime[i];
    }
    avgTurnaroundTime = avgTurnaroundTime / n;
    avgWaitingTime = avgWaitingTime / n;
    for (i = 0; i < n; i++)
    {
        printf("\n----------------------------------------------------------------------------------------------------------------------");
        printf("\nP%d\t| %d\t\t| %d\t\t| %d\t\t| %d\t\t\t| %d\t\t\t| %d", p[i], pr[i],arrivalTime[i], burstTimeFinal[i], completionTime[i], turnaroundTime[i], waitingTime[i]);
    }
    printf("\n----------------------------------------------------------------------------------------------------------------------");
    printf("\nAverage Turnaround Time: %.2f", avgTurnaroundTime);
    printf("\nAverage Waiting Time: %.2f", avgWaitingTime);
}



// MAIN

int main()
{

    printf("***WELCOME TO CPU SCHEDULING PROCESSES***\n\n");

    int n;
    printf("ENTER THE NUMBER OF PROCESSES:");
    scanf("%d", &n);

    int processesPriority[n][3];
    printf("Enter Arrival time, Burst time process in the same order:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &processesPriority[i][0], &processesPriority[i][1]);
        processesPriority[i][2] = i + 1;
    }

    int processes[n][2];

    for (int i = 0; i < n; i++)
    {
        processes[i][0] = processesPriority[i][0];
        processes[i][1] = processesPriority[i][1];
    }

    int option;
    int time_quantum;

    printf("\n\nNOTE THAT PRIORIITY OPTION IS ONLY APPLICABLE FOR PRIORITY NON PREEMPTIVE AND PRIORITY PREEMPTIVE\n\n");

    printf("\n\nPRESS\n1 for FIRST COME FIRST SERVE\n2 for SHORTEST JOB FIRST\n3 for SHORTEST REMAINING JOB FIRST\n4 for ROUND ROBIN\n5 for PRIORITY NON PREEMPTIVE\n6 for PRIORITY PREEMPTIVE\n7 for EXIT\n");
    scanf("%d", &option);

    do
    {
        switch (option)
        {
        case 1:
            FCFS(processes, n);
            printf("\n\nPRESS\n1 for FIRST COME FIRST SERVE\n2 for SHORTEST JOB FIRST\n3 for SHORTEST REMAINING JOB FIRST\n4 for ROUND ROBIN\n5 for PRIORITY NON PREEMPTIVE\n6 for PRIORITY PREEMPTIVE\n7 for EXIT\n");
            scanf("%d", &option);
            break;
        case 2:
            SJFNP(processes, n);
            printf("\n\nPRESS\n1 for FIRST COME FIRST SERVE\n2 for SHORTEST JOB FIRST\n3 for SHORTEST REMAINING JOB FIRST\n4 for ROUND ROBIN\n5 for PRIORITY NON PREEMPTIVE\n6 for PRIORITY PREEMPTIVE\n7 for EXIT\n");
            scanf("%d", &option);
            break;
        case 3:
            SJFP(processes, n);
            printf("\n\nPRESS\n1 for FIRST COME FIRST SERVE\n2 for SHORTEST JOB FIRST\n3 for SHORTEST REMAINING JOB FIRST\n4 for ROUND ROBIN\n5 for PRIORITY NON PREEMPTIVE\n6 for PRIORITY PREEMPTIVE\n7 for EXIT\n");
            scanf("%d", &option);
            break;
        case 4:
            printf("Enter the time quantum:");
            scanf("%d", &time_quantum);
            RR(processes, n, time_quantum);
            printf("\n\nPRESS\n1 for FIRST COME FIRST SERVE\n2 for SHORTEST JOB FIRST\n3 for SHORTEST REMAINING JOB FIRST\n4 for ROUND ROBIN\n5 for PRIORITY NON PREEMPTIVE\n6 for PRIORITY PREEMPTIVE\n7 for EXIT\n");
            scanf("%d", &option);
            break;
        case 5:
            printf("Enter the priority of processes in the same order you entered:\n");
            for (int i = 0; i < n; i++)
            {
                scanf("%d", &processesPriority[i][2]);
            }
            PNP(processesPriority, n);
            printf("\n\nPRESS\n1 for FIRST COME FIRST SERVE\n2 for SHORTEST JOB FIRST\n3 for SHORTEST REMAINING JOB FIRST\n4 for ROUND ROBIN\n5 for PRIORITY NON PREEMPTIVE\n6 for PRIORITY PREEMPTIVE\n7 for EXIT\n");
            scanf("%d", &option);
            break;
        case 6:
            printf("Enter the priority of processes in the same order you entered:\n");
            for (int i = 0; i < n; i++)
            {
                scanf("%d", &processesPriority[i][2]);
            }
            PP(processesPriority, n);
            printf("\n\nPRESS\n1 for FIRST COME FIRST SERVE\n2 for SHORTEST JOB FIRST\n3 for SHORTEST REMAINING JOB FIRST\n4 for ROUND ROBIN\n5 for PRIORITY NON PREEMPTIVE\n6 for PRIORITY PREEMPTIVE\n7 for EXIT\n");
            scanf("%d", &option);
            break;
        case 7:
            exit(0);
            break;
        default:
            printf("Invalid option selected.\n");
            break;
        }
    } while (option != 7);

    return 0;
}