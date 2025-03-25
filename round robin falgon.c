#include <stdio.h>

// Structure to hold process information
struct Process {
    int pid;        // Process ID
    int arrival;    // Arrival Time
    int burst;      // Burst Time
    int remaining;  // Remaining Burst Time (for Round Robin)
    int completion; // Completion Time
    int turnaround; // Turnaround Time
    int waiting;    // Waiting Time
    int response;   // Response Time
};

void roundRobin(struct Process processes[], int n, int timeQuantum) {
    int currentTime = 0, completed = 0, queue[n], front = 0, rear = 0;
    int visited[n];

    // Initialize processes and queue
    for (int i = 0; i < n; i++) {
        processes[i].remaining = processes[i].burst;
        processes[i].pid = i + 1;
        visited[i] = 0; // Mark all processes as not yet visited
    }

    // Start with the first process
    queue[rear++] = 0;
    visited[0] = 1;

    printf("\nGantt Chart: ");
    while (completed < n) {
        int currentProcess = queue[front++];

        // Process starts execution
        if (processes[currentProcess].remaining == processes[currentProcess].burst) {
            processes[currentProcess].response = currentTime - processes[currentProcess].arrival;
        }

        // Execute the process for the time quantum
        printf("[ %d ] ", currentTime); // Print current time in the Gantt chart
        if (processes[currentProcess].remaining > timeQuantum) {
            currentTime += timeQuantum;
            processes[currentProcess].remaining -= timeQuantum;
        } else {
            currentTime += processes[currentProcess].remaining;
            processes[currentProcess].completion = currentTime;
            processes[currentProcess].turnaround = processes[currentProcess].completion - processes[currentProcess].arrival;
            processes[currentProcess].waiting = processes[currentProcess].turnaround - processes[currentProcess].burst;
            processes[currentProcess].remaining = 0;  // Process finished
            completed++;
        }

        // Add new arriving processes to the queue
        for (int i = 0; i < n; i++) {
            if (!visited[i] && processes[i].arrival <= currentTime) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        // Re-queue the current process if it hasn't finished
        if (processes[currentProcess].remaining > 0) {
            queue[rear++] = currentProcess;
        }

        // Print the process id in the Gantt chart
        printf("P%d ", processes[currentProcess].pid);
    }

    printf("[ %d ]\n", currentTime); // Final time after all processes finish

    // Print the results for each process
    printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\tResponse\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\t%d\n",
               processes[i].pid, processes[i].arrival, processes[i].burst,
               processes[i].completion, processes[i].turnaround,
               processes[i].waiting, processes[i].response);
    }

    // Calculate and print the average waiting time
    int totalWaitingTime = 0;
    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waiting;
    }
    float averageWaitingTime = (float) totalWaitingTime / n;
    printf("\nAverage Waiting Time: %.2f\n", averageWaitingTime);
}

int main() {
    int n, timeQuantum;

    // Input number of processes
    printf("Round Robin Scheduling Algorithm: \n");
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input arrival and burst times for all processes
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time for Process P%d: ", i + 1);
        scanf("%d", &processes[i].arrival);
        printf("Enter burst time for Process P%d: ", i + 1);
        scanf("%d", &processes[i].burst);
    }

    // Input time quantum
    printf("Enter the time quantum: ");
    scanf("%d", &timeQuantum);

    // Call round robin function
    roundRobin(processes, n, timeQuantum);

    return 0;
}
