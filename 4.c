#include <stdio.h>
#include <string.h>

void main() {
    int bt[80], wt[80], at[80], ft[80], tat[80], wat[80];
    int i, j, n, temp;
    float awt, att, sum = 0, sum1 = 0;
    char p[10][5], tempStr[5];

    printf("\nEnter the number of processes: ");
    scanf("%d", &n);

    printf("\nEnter the process name and burst time:\n");
    for (i = 0; i < n; i++) {
        scanf("%s %d", p[i], &bt[i]);
    }

    printf("\nEnter the arrival time:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &at[i]);
    }

    // Sort processes by arrival time using bubble sort
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (at[i] > at[j]) {
                // Swap arrival times
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                // Swap burst times
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                // Swap process names
                strcpy(tempStr, p[i]);
                strcpy(p[i], p[j]);
                strcpy(p[j], tempStr);
            }
        }
    }

    // Calculate Finish Time (FT)
    // The first process finishes at its arrival time + burst time
    ft[0] = at[0] + bt[0];
    for (i = 1; i < n; i++) {
        // If a process arrives after the previous one finished, it starts at its arrival time
        if (at[i] > ft[i-1]) {
            ft[i] = at[i] + bt[i];
        } else {
            ft[i] = ft[i-1] + bt[i];
        }
    }

    // Calculate Turnaround Time (TAT) and Waiting Time (WAT)
    for (i = 0; i < n; i++) {
        tat[i] = ft[i] - at[i];
        wat[i] = tat[i] - bt[i];
        sum += wat[i];
        sum1 += tat[i];
    }

    // Print Gantt Chart
    printf("\n\n\t\tGantt Chart\n\n");
    for (i = 0; i < n; i++) {
        printf("\t|  %s  ", p[i]);
    }
    printf("|\n");

    // Print timeline below Gantt Chart
    printf("%d\t", at[0]);
    for (i = 0; i < n; i++) {
        printf("\t\t%d", ft[i]);
    }

    // Print final result table
    printf("\n\n--- FIRST COME FIRST SERVE ---\n");
    printf("\nID\tProcess\tBurst\tArrival\tFinish\tWaiting\tTurnaround\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n", i + 1, p[i], bt[i], at[i], ft[i], wat[i], tat[i]);
    }

    // Final Average Calculations
    awt = sum / n;
    att = sum1 / n;
    printf("\nAverage Waiting Time: %.2f", awt);
    printf("\nAverage Turnaround Time: %.2f\n", att);
}

