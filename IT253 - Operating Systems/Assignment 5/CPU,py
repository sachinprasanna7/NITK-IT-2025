#CPU SCHEDULING ALGORITHMS

#FCFS

def FCFS(processes, n):
    #sorting according to arrival time
    processes = sorted(processes, key = lambda processes:processes[1])
    print("Order in which process gets executed")
    for i in processes:
        print(i[0], end = " ")
    print()
    waiting_time = [0] * n
    turnaround_time = [0] * n
    #waiting time for first process is 0
    waiting_time[0] = 0
    #calculating waiting time
    for i in range(1, n):
        waiting_time[i] = processes[i - 1][2] + waiting_time[i - 1] - processes[i][1] + processes[i - 1][1]
        if waiting_time[i] < 0:
            waiting_time[i] = 0
    print("Waiting time for processes")
    for i in range(n):
        print(waiting_time[i], end = " ")
    print()
    #calculating turnaround time
    for i in range(n):
        turnaround_time[i] = processes[i][2] + waiting_time[i]
    print("Turnaround time for processes")
    for i in range(n):
        print(turnaround_time[i], end = " ")
    print()
    print("Average waiting time = %f "%(sum(waiting_time)/n))
    print("Average turnaround time = %f "%(sum(turnaround_time)/n))




#SJF
'''implement the non preemptive shortest job first cpu scheduling algorithm in python.

the function should output the compute start time the process, finish time of the
process, average waiting time and turnaround time.

def SJF(processes):
     #complete the code

input format is list of lists, where each list is -> [processid, arrival time, burst time]
for example, a test case
processes = [[1,0,2],[1,1,5],[3,2,3],[4,3,1],[5,5,4]

here, average waiting time = 2.4
average turnaround time = 5.4'''

# def SJF(processes, n):
#     #sorting according to arrival time
#     processes = sorted(processes, key = lambda processes:processes[1])
#     #sorting according to burst time
#     processes = sorted(processes, key = lambda processes:processes[2])
#     print("Order in which process gets executed")
#     for i in processes:
#         print(i[0], end = " ")
#     print()
#     waiting_time = [0] * len(processes)
#     turnaround_time = [0] * len(processes)
#     #waiting time for first process is 0
#     waiting_time[0] = 0
#     #calculating waiting time
#     for i in range(1, len(processes)):
#         waiting_time[i] = processes[i - 1][2] + waiting_time[i - 1] - processes[i][1] + processes[i - 1][1]
#         if waiting_time[i] < 0:
#             waiting_time[i] = 0
#     print("Waiting time for processes")
#     for i in range(len(processes)):
#         print(waiting_time[i], end = " ")
#     print()
#     #calculating turnaround time
#     for i in range(len(processes)):
#         turnaround_time[i] = processes[i][2] + waiting_time[i]
#     print("Turnaround time for processes")
#     for i in range(len(processes)):
#         print(turnaround_time[i], end = " ")
#     print()
#     print("Average waiting time = %f "%(sum(waiting_time)/len(processes)))
#     print("Average turnaround time = %f "%(sum(turnaround_time)/len(processes)))


def SJF(processes):
    def sort_by_arrival_time(process):
        return process[1]
    
    def sort_by_burst_time(process):
        return process[2]
    
    processes.sort(key=sort_by_arrival_time)
    timeline = []
    rows = processes.copy()
    time = rows[0][1]
    
    while rows:
        available_rows = []
        
        for row in rows:
            if row[1] <= time:
                available_rows.append(row)
                
        available_rows.sort(key=sort_by_burst_time)
        
        row = available_rows[0]
        timeline.append((row[0], time, time + row[2]))
        time += row[2]
        
        for i in range(len(rows)):
            if rows[i][0] == row[0]:
                rows.pop(i)
                break
                
    for row in processes:
        event = next((x for x in timeline if x[0] == row[0]), None)
        row.append(event[1] - row[1])
        row.append(row[2] + row[3])
        
    waiting_times = [row[3] for row in processes]
    turnaround_times = [row[4] for row in processes]
    avg_waiting_time = sum(waiting_times) / len(waiting_times)
    avg_turnaround_time = sum(turnaround_times) / len(turnaround_times)
    
    return avg_waiting_time, avg_turnaround_time










# SRTF
def SRTF(processes, n):
	wt = [0] * n
	tat = [0] * n

	# Function to find waiting time
	# of all processes
	rt = [0] * n

	# Copy the burst time into rt[]
	for i in range(n):
		rt[i] = processes[i][1]
	complete = 0
	t = 0
	minm = 999999999
	short = 0
	check = False

	# Process until all processes gets
	# completed
	while (complete != n):
		
		# Find process with minimum remaining
		# time among the processes that
		# arrives till the current time`
		for j in range(n):
			if ((processes[j][2] <= t) and
				(rt[j] < minm) and rt[j] > 0):
				minm = rt[j]
				short = j
				check = True
		if (check == False):
			t += 1
			continue
			
		# Reduce remaining time by one
		rt[short] -= 1

		# Update minimum
		minm = rt[short]
		if (minm == 0):
			minm = 999999999

		# If a process gets completely
		# executed
		if (rt[short] == 0):

			# Increment complete
			complete += 1
			check = False

			# Find finish time of current
			# process
			fint = t + 1

			# Calculate waiting time
			wt[short] = (fint - processes[short][1] - processes[short][2])

			if (wt[short] < 0):
				wt[short] = 0
		
		# Increment time
		t += 1

	# Function to find turn around time
	# for all processes
	for i in range(n):
		tat[i] = processes[i][1] + wt[i]

	# Display processes along with all details
	print("Processes Burst Time	 Waiting",
					"Time	 Turn-Around Time")
	total_wt = 0
	total_tat = 0
	for i in range(n):

		total_wt = total_wt + wt[i]
		total_tat = total_tat + tat[i]
		print(" ", processes[i][0], "\t\t",
				processes[i][1], "\t\t",
				wt[i], "\t\t", tat[i])

	print("\nAverage waiting time = %.5f "%(total_wt /n) )
	print("Average turn around time = ", total_tat / n)







#round robin scheduling

# Python program for implementing Round Robin Algorithm
def queueUpdation(queue, timer, arrival, n, maxProccessIndex):
	zeroIndex = -1
	for i in range(n):
		if(queue[i] == 0):
			zeroIndex = i
			break

	if(zeroIndex == -1):
		return
	queue[zeroIndex] = maxProccessIndex + 1


def checkNewArrival(timer, arrival, n, maxProccessIndex, queue):
	if(timer <= arrival[n-1]):
		newArrival = False
		for j in range(maxProccessIndex+1, n):
			if(arrival[j] <= timer):
				if(maxProccessIndex < j):
					maxProccessIndex = j
					newArrival = True

		# adds the index of the arriving process(if any)
		if(newArrival):
			queueUpdation(queue, timer, arrival, n, maxProccessIndex)


def queueMaintainence(queue, n):
	for i in range(n-1):
		if(queue[i+1] != 0):
			queue[i], queue[i+1] = queue[i+1], queue[i]


def RR(processes, n, quanta):
    timer, maxProccessIndex = 0, 0
    avgWait, avgTT = 0, 0
    tq = quanta
    arrival = [0]*n
    burst = [0]*n
    wait = [0]*n
    turn = [0]*n
    queue = [0]*n
    temp_burst = [0]*n
    complete = [False]*n

    for i in range(n):
        arrival[i] = processes[i][2]

    for i in range(n):
        burst[i] = processes[i][1]
        temp_burst[i] = burst[i]

    for i in range(n):
            # Initializing the queue and complete array
        complete[i] = False
        queue[i] = 0

    while(timer < arrival[0]):
            # Incrementing Timer until the first process arrives
        timer += 1
    queue[0] = 1
    print("gi")
    while(True):
        flag = True
        for i in range(n):
            if(temp_burst[i] != 0):
                flag = False
                break

        if(flag):
            break

        for i in range(n and queue[i] != 0):
            print("gi")
            ctr = 0
            while((ctr < tq) and (temp_burst[queue[0]-1] > 0)):
                temp_burst[queue[0]-1] -= 1
                timer += 1
                ctr += 1

                # Updating the ready queue until all the processes arrive
                checkNewArrival(timer, arrival, n, maxProccessIndex, queue)

            if((temp_burst[queue[0]-1] == 0) and (complete[queue[0]-1] == False)):
                # turn currently stores exit times
                turn[queue[0]-1] = timer
                complete[queue[0]-1] = True

            # checks whether or not CPU is idle
            idle = True
            if(queue[n-1] == 0):
                for k in range(n):
                    if(queue[k] != 0):
                        if(complete[queue[k]-1] == False):
                            idle = False
            else:
                idle = False

            if(idle):
                timer += 1
                checkNewArrival(timer, arrival, n, maxProccessIndex, queue)

            # Maintaining the entries of processes aftereach premption in the ready Queue
            queueMaintainence(queue, n)

    for i in range(n):
        turn[i] = turn[i] - arrival[i]
        wait[i] = turn[i] - burst[i]

    print("\nProgram No.\tArrival Time\tBurst Time\tWait Time\tTurnAround Time\n")

    for i in range(n):
        print(i+1, "\t\t", arrival[i], "\t\t", burst[i],
            "\t\t", wait[i], "\t\t", turn[i], "\n")

    for i in range(n):
        avgWait += wait[i]
        avgTT += turn[i]

    print("\nAverage wait time : ", (float(avgWait)/n))
    print("\nAverage Turn Around Time : ", (float(avgTT)/n))






#sample input to test the program fcfs
# sample = [[1, 4, 5], [2, 6, 4], [3, 0, 3], [4, 6, 2], [5, 5, 4]]
# FCFS(sample, 5)

#sample input to test the program sjf  
# sample = [[1, 0, 12], [2, 2, 4], [3, 3, 6], [4, 8, 5]]
# SRTF(sample, 4)

#SAMPLE INPUT TO PREEMPTIVE PRIORITY SCHEDULING
# sample = [[1, 0, 0, 4], [2, 1, 1, 3], [3, 2, 2, 1], [4, 3, 3, 5], [5,4,4,2]]
# PNP(sample, 5)

# proc = [[1, 10, 0], [2, 6, 3], [3, 1, 7], [4, 3, 8]]
# n = 4
# SRTF(proc, n)

#sample input for round robin
# sample = [[1, 0, 5], [2, 1, 3], [3, 2, 1], [4, 3, 2], [5, 4, 3]]
# RR(sample, 5, 2)

# sample = [[1,0,2],[1,1,5],[3,2,3],[4,3,1],[5,5,4]]
# SJF(sample,5)

processes = [[1,0,2],[1,1,5],[3,2,3],[4,3,1],[5,5,4]]
avg_waiting_time, avg_turnaround_time = SJF(processes)
print("Average waiting time:", avg_waiting_time)
print("Average turnaround time:", avg_turnaround_time)







