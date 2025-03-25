#include <stdio.h>
#include <stdbool.h>

struct Process {
    int pid;        // Process ID
    int arrival;    // Arrival Time
    int burst;      // Burst Time
    int completion; // Completion Time
    int turnaround; // Turnaround Time
    int waiting;    // Waiting Time
    int response;   // Response Time
    bool completed; // Completion Status
};

void calculateSJF(struct Process processes[], int n) {
    int completed = 0, currentTime = 0;
    float totalWaitingTime = 0;
    int ganttChart[n], ganttSize = 0; // Array to store the Gantt chart order

    printf("\nGantt Chart:\n");

    while (completed < n) {
        int minIndex = -1;

        // Find the shortest burst time process that has arrived
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrival <= currentTime) {
                if (minIndex == -1 || processes[i].burst < processes[minIndex].burst) {
                    minIndex = i;
                }
            }
        }

        if (minIndex == -1) {
            // If no process has arrived yet, move the current time forward
            currentTime++;
        } else {
            // Process execution
            processes[minIndex].response = currentTime - processes[minIndex].arrival;
            currentTime += processes[minIndex].burst;
            processes[minIndex].completion = currentTime;
            processes[minIndex].turnaround = processes[minIndex].completion - processes[minIndex].arrival;
            processes[minIndex].waiting = processes[minIndex].turnaround - processes[minIndex].burst;
            processes[minIndex].completed = true;
            totalWaitingTime += processes[minIndex].waiting;

            // Store process in Gantt chart order
            ganttChart[ganttSize++] = minIndex;

            // Print the Gantt chart
            printf("| P%d ", processes[minIndex].pid);

            completed++;
        }
    }

    printf("|\n");

    // Print the timeline for the Gantt chart
    currentTime = 0;
    printf("0");
    for (int i = 0; i < ganttSize; i++) {
        currentTime = processes[ganttChart[i]].completion;
        printf("   %d", currentTime);
    }
    printf("\n");

    // Display results in the order of the Gantt chart
    printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\tResponse\n");
    for (int i = 0; i < ganttSize; i++) {
        int idx = ganttChart[i];
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\t%d\n",
               processes[idx].pid, processes[idx].arrival, processes[idx].burst,
               processes[idx].completion, processes[idx].turnaround,
               processes[idx].waiting, processes[idx].response);
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

    // Input arrival time and burst time for each process in the specified format
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        processes[i].completed = false; // Initialize as not completed
        printf("Enter arrival time for Process P%d: ", i + 1);
        scanf("%d", &processes[i].arrival);
        printf("Enter burst time for Process P%d: ", i + 1);
        scanf("%d", &processes[i].burst);
    }

    // Sort processes by Arrival Time (to handle cases where they are not provided in order)
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
    calculateSJF(processes, n);

    return 0;
}
