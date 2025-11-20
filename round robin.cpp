#include <iostream>
using namespace std;
const int MAX = 100;

int main() {
    int n, quantum;
    int pid[MAX], arrival[MAX], burst[MAX], remaining[MAX], exitT[MAX], tat[MAX], wt[MAX];
    int queue[MAX], front = 0, rear = 0;
    bool inQueue[MAX] = {false};
    bool completed[MAX] = {false};

    int Gant_PID[1000], startTime[1000], endTime[1000];
    int ganttSize = 0;

    cout << "Enter number of processes: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "Enter arrival time of Process P" << pid[i] << ": ";
        cin >> arrival[i];
        cout << "Enter burst time of Process P" << pid[i] << ": ";
        cin >> burst[i];
        remaining[i] = burst[i];
    }

    cout << "Enter time quantum: ";
    cin >> quantum;

    int time = 0, completedCount = 0;


    for (int i = 0; i < n; i++) {
        if (arrival[i] <= time && remaining[i] > 0) {
            queue[rear++] = i;
            inQueue[i] = true;
        }
    }

    while (completedCount < n) {
        if (front == rear) {
        
            time++;
            for (int i = 0; i < n; i++) {
                if (!inQueue[i] && remaining[i] > 0 && arrival[i] <= time) {
                    queue[rear++] = i;
                    inQueue[i] = true;
                }
            }
            continue;
        }

        int idx = queue[front++];
        inQueue[idx] = false;

        if (time < arrival[idx]) {
            time = arrival[idx];
        }

        int runTime = (remaining[idx] < quantum) ? remaining[idx] : quantum;

        if (runTime > 0) {
            Gant_PID[ganttSize] = pid[idx];
            startTime[ganttSize] = time;
            endTime[ganttSize] = time + runTime;
            ganttSize++;
        }

        time += runTime;
        remaining[idx] -= runTime;

        for (int i = 0; i < n; i++) {
            if (!inQueue[i] && remaining[i] > 0 && arrival[i] > time - runTime && arrival[i] <= time) {
                queue[rear++] = i;
                inQueue[i] = true;
            }
        }

        if (remaining[idx] > 0) {
            queue[rear++] = idx;
            inQueue[idx] = true;
        } else if (!completed[idx]) {
            exitT[idx] = time;
            tat[idx] = exitT[idx] - arrival[idx];
            wt[idx] = tat[idx] - burst[idx];
            completed[idx] = true;
            completedCount++;
        }
    }

    float total_TAT = 0, total_WT = 0;
    cout << "\nPID\tArrival\tBurst\tExit\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        total_TAT += tat[i];
        total_WT += wt[i];
        cout << "P" << pid[i] << "\t" << arrival[i] << "\t" << burst[i] << "\t"
             << exitT[i] << "\t" << tat[i] << "\t" << wt[i] << "\n";
    }

    
    cout << "\nGantt Chart:\n";
    for (int i = 0; i < ganttSize; i++) {
        cout << "| P" << Gant_PID[i] << "    ";
    }
    cout << "|\n";

    cout << startTime[0];
    for (int i = 0; i < ganttSize; i++) {
        cout << "\t" << endTime[i];
    }
    cout << "\n";

    cout << "\nAverage Turnaround Time: " << total_TAT / n;
    cout << "\nAverage Waiting Time: " << total_WT / n << "\n";

    return 0;
}