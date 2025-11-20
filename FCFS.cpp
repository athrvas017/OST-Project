#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int processID[100], burstTime[100], waitingTime[100], turnaroundTime[100], completionTime[100], arrivalTime[100];

    for (int i = 0; i < n; i++) {
        processID[i] = i + 1;
        cout << "Enter arrival time for Process " << i + 1 << ": ";
        cin >> arrivalTime[i];
        cout << "Enter burst time for Process " << i + 1 << ": ";
        cin >> burstTime[i];
    }

    waitingTime[0] = 0;
    completionTime[0] = burstTime[0];
    for (int i = 1; i < n; i++) {
        waitingTime[i] = waitingTime[i - 1] + burstTime[i - 1];
        completionTime[i] = completionTime[i - 1] + burstTime[i];
    }

    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = burstTime[i] + waitingTime[i];
    }

    cout << "\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << processID[i] << "\t" << arrivalTime[i] << "\t\t"
             << burstTime[i] << "\t\t" << waitingTime[i] << "\t\t"
             << turnaroundTime[i] << "\n";
    }

    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        totalWT += waitingTime[i];
        totalTAT += turnaroundTime[i];
    }
    cout << "\nAverage Waiting Time: " << totalWT / n;
    cout << "\nAverage Turnaround Time: " << totalTAT / n << "\n";

    cout << "\nGantt Chart:\n ";
    for (int i = 0; i < n; i++) {
        cout << "  P" << processID[i] << "  |";
    }
    cout << "\n0";
    for (int i = 0; i < n; i++) {
        cout << "     " << completionTime[i];
    }
    cout << "\n";

    return 0;
}
