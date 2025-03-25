#include <stdio.h>

struct Process {
    int pid;
    int arrival;
    int burst;
    int completion;
    int turnaround;
    int waiting;
    int response;
};

void calculateFCFS(struct Process processes[], int n) {
    int currentTime = 0;
    float totalWaitingTime = 0;

    printf("\nGantt Chart:\n");

    for (int i = 0; i < n; i++) {
        // Process starts execution
        if (currentTime < processes[i].arrival) {
            currentTime = processes[i].arrival;
        }

        processes[i].completion = currentTime + processes[i].burst;

        // Turnaround time = Completion time - Arrival time
        processes[i].turnaround = processes[i].completion - processes[i].arrival;

        // Waiting time = Turnaround time - Burst time
        processes[i].waiting = processes[i].turnaround - processes[i].burst;

        // Response time = Waiting time for FCFS
        processes[i].response = processes[i].waiting;

        totalWaitingTime += processes[i].waiting;

        // Print Gantt Chart
        printf("| P%d ", processes[i].pid);

        // Move current time forward
        currentTime = processes[i].completion;
    }

    printf("|\n");

    // Print the timeline for the Gantt chart
    currentTime = 0;
    printf("0");
    for (int i = 0; i < n; i++) {
        if (currentTime < processes[i].arrival) {
            currentTime = processes[i].arrival;
        }
        currentTime += processes[i].burst;
        printf("   %d", currentTime);
    }
    printf("\n");

    // Display results
    printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\tResponse\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\t%d\n",
               processes[i].pid, processes[i].arrival, processes[i].burst,
               processes[i].completion, processes[i].turnaround,
               processes[i].waiting, processes[i].response);
    }

    // Calculate and display average waiting time
    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
}

int main() {
    int n;

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input arrival time and burst time for each process
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time for Process P%d: ", i + 1);
        scanf("%d", &processes[i].arrival);
        printf("Enter burst time for Process P%d: ", i + 1);
        scanf("%d", &processes[i].burst);
    }

    // Sort processes by Arrival Time (in case the user enters them out of order)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival > processes[j + 1].arrival) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // Calculate and display results
    calculateFCFS(processes, n);

    return 0;
}
