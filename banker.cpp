#include <iostream>
using namespace std;

int main() {
    int n, r;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resources: ";
    cin >> r;

    int alloc[n][r];
    int max[n][r];
    int need[n][r];
    int avail[r];
    int f[n];       
    int ans[n];        
    int work_snapshot[n][r]; 

    cout << "Enter Allocation Matrix (" << n << "x" << r << "):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < r; j++)
            cin >> alloc[i][j];

    cout << "Enter Max Matrix (" << n << "x" << r << "):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < r; j++)
            cin >> max[i][j];

    cout << "Enter Available Resources (" << r << "): ";
    for (int i = 0; i < r; i++)
        cin >> avail[i];

    for (int i = 0; i < n; i++)
        f[i] = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < r; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    int ind = 0;

   
    for (int k = 0; k < n; k++) {
        bool allocated_in_this_round = false;
        for (int i = 0; i < n; i++) {
            if (f[i] == 0) {
                bool canAllocate = true;
                for (int j = 0; j < r; j++) {
                    if (need[i][j] > avail[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
          
                    for (int j = 0; j < r; j++)
                        work_snapshot[i][j] = avail[j];

                    ans[ind++] = i;

                    for (int j = 0; j < r; j++)
                        avail[j] += alloc[i][j];

                    f[i] = 1;
                    allocated_in_this_round = true;
                }
            }
        }
        if (!allocated_in_this_round)
            break;
    }

    cout << "\nProcessID\tAllocation\tMax\t\tNeed\t\tWork(before)\n";
    cout << "-----------------------------------------------------------------\n";

    for (int k = 0; k < ind; k++) {
        int i = ans[k];

        cout << "P" << i << "\t\t\t";

        for (int j = 0; j < r; j++)
            cout << alloc[i][j] << " ";
        cout << "\t\t";

        for (int j = 0; j < r; j++)
            cout << max[i][j] << " ";
        cout << "\t";

        for (int j = 0; j < r; j++)
            cout << need[i][j] << " ";
        cout << "\t";

        for (int j = 0; j < r; j++)
            cout << work_snapshot[i][j] << " ";

        cout << endl;
    }

    cout << "\nFinal Work (Available) vector: ";
    for (int i = 0; i < r; i++)
        cout << avail[i] << " ";
    cout << endl;

    if (ind == n) {
        cout << "\nThe SAFE Sequence is:\n";
        for (int i = 0; i < n - 1; i++)
            cout << "P" << ans[i] << " -> ";
        cout << "P" << ans[n - 1] << endl;
    } else {
        cout << "\nNo SAFE sequence found! The system is in an UNSAFE state.\n";
    }
    return 0;
}