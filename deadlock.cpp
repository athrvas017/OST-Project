#include <iostream> 
#include <vector> 
using namespace std; 
int main() { 
int PROCESSES, RESOURCES; 
cout << "Enter number of processes: "; 
cin >> PROCESSES; 
cout << "Enter number of resources: "; 
cin >> RESOURCES; 
vector<int> Available(RESOURCES); 
cout << "Enter Available resources:\n"; 
for (int i = 0; i < RESOURCES; i++) { 
cin >> Available[i]; 
} 
vector<vector<int>> Allocation(PROCESSES, vector<int>(RESOURCES)); 
cout << "Enter Allocation matrix (" << PROCESSES << "x" << RESOURCES << 
"):\n"; 
for (int i = 0; i < PROCESSES; i++) { 
for (int j = 0; j < RESOURCES; j++) { 
cin >> Allocation[i][j]; 
} 
} 
vector<vector<int>> Request(PROCESSES, vector<int>(RESOURCES)); 
cout << "Enter Request matrix (" << PROCESSES << "x" << RESOURCES << 
"):\n"; 
for (int i = 0; i < PROCESSES; i++) { 
for (int j = 0; j < RESOURCES; j++) { 
cin >> Request[i][j]; 
} 
} 
vector<bool> Finish(PROCESSES, false); 
vector<int> Work = Available; 
bool changed; 
do { 
changed = false; 
for (int i = 0; i < PROCESSES; i++) { 
if (!Finish[i]) { 
bool canFinish = true; 
for (int j = 0; j < RESOURCES; j++) { 
if (Request[i][j] > Work[j]) { 
canFinish = false; 
break; 
} 
                } 
                if (canFinish) { 
                    for (int j = 0; j < RESOURCES; j++) 
                        Work[j] += Allocation[i][j]; 
                    Finish[i] = true; 
                    changed = true; 
                } 
            } 
        } 
    } while (changed); 
 
    cout << "Deadlocked processes:"; 
    bool anyDeadlock = false; 
    for (int i = 0; i < PROCESSES; i++) { 
        if (!Finish[i]) { 
            cout << " " << i; 
            anyDeadlock = true; 
        } 
    } 
    if (!anyDeadlock) cout << " None"; 
    cout << endl; 
 
    return 0; 
}