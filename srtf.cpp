#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int Process_ID[100], Arrival_Time[100], Burst_Time[100];
    int Remaining_BT[100], Waiting_Time[100], Turn_Around_Time[100], Exit_Time[100];
    bool completed[100] = {false};

    for (int i = 0; i < n; i++) {
        Process_ID[i] = i + 1;
        cout << "Enter arrival time for process " << Process_ID[i] << ": ";
        cin >> Arrival_Time[i];
        cout << "Enter burst time for process " << Process_ID[i] << ": ";
        cin >> Burst_Time[i];
        Remaining_BT[i] = Burst_Time[i]; 
    }

    int completed_count = 0, current_time = 0;
    double total_tat = 0, total_wt = 0;

    int exec_order[100]; 
    int order_count = 0;


    while (completed_count < n) {
        int idx = -1;
        int lowest_bt = 1000;

        for (int i = 0; i < n; i++) {
            if (Arrival_Time[i] <= current_time && !completed[i]) {
                if (Remaining_BT[i] < lowest_bt && Remaining_BT[i] > 0) {
                    lowest_bt = Remaining_BT[i];
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            if (order_count == 0 || exec_order[order_count - 1] != idx) {
                exec_order[order_count++] = idx;
            }

            Remaining_BT[idx]--;
            current_time++;
        
            if (Remaining_BT[idx] == 0) {
                completed[idx] = true;
                completed_count++;
                Exit_Time[idx] = current_time;
                Turn_Around_Time[idx] = Exit_Time[idx] - Arrival_Time[idx];
                Waiting_Time[idx] = Turn_Around_Time[idx] - Burst_Time[idx];

                total_tat += Turn_Around_Time[idx];
                total_wt += Waiting_Time[idx];
            }
        } else {
            current_time++;
        }
    }

    cout << "\nPID\tAT\tBT\tET\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << Process_ID[i] << "\t" << Arrival_Time[i] << "\t"
             << Burst_Time[i] << "\t" << Exit_Time[i] << "\t"
             << Turn_Around_Time[i] << "\t" << Waiting_Time[i] << "\n";
    }
    cout << "\nGantt Chart:\n";
    for (int i = 0; i < order_count; i++) {
        cout << "| P" << Process_ID[exec_order[i]] << "    ";
    }
    cout << "|\n0";

    int last_time = 0;
    for (int i = 0; i < order_count; i++) {
        int p = exec_order[i];
        for (int j = last_time + 1; j <= Exit_Time[p]; j++) {
            if (Remaining_BT[p] == 0) {
                last_time = Exit_Time[p];
            }
        }
        cout << "\t" << Exit_Time[p];
    }
    cout << endl;

    cout << "\nAverage Turnaround Time = " << (total_tat / n);
    cout << "\nAverage Waiting Time = " << (total_wt / n) << "\n";

    return 0;
}
