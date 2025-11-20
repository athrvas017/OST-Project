#include <iostream> 
#include <vector> 
#include <queue> 
using namespace std; 
 
class BinarySemaphore { 
    int value; 
public: 
    BinarySemaphore() : value(1) {} 
     
    bool acquire(int pid, queue<int>& blocked, vector<int>& running) { 
        if (value > 0) { 
            value = 0; 
            running.push_back(pid); 
            return true; 
        } else { 
            blocked.push(pid); 
            return false; 
        } 
    } 
     
    void release(int pid, queue<int>& blocked, vector<int>& running) { 
        value = 1; 
        for (auto it = running.begin(); it != running.end(); ++it) 
            if (*it == pid) { 
                running.erase(it); 
                break; 
            } 
        if (!blocked.empty()) { 
            int next = blocked.front(); blocked.pop(); 
            value = 0;  
            running.push_back(next); 
            cout << "Process " << next << " moved from blocked to running.\n"; 
        } 
    } 
    int get() { return value; } 
}; 
 
void showQueues(const vector<int>& running, const queue<int>& 
blocked) { 
    cout << "Running Queue: "; 
    for (int pid : running) cout << pid << " "; 
    cout << "\nBlocked Queue: "; 
    queue<int> q = blocked; 
    while (!q.empty()) { cout << q.front() << " "; q.pop(); } 
    cout << endl; 
} 
 
int main() { 
    int numProcesses; 
    cout << "Enter number of processes: "; 
    cin >> numProcesses; 
 
    BinarySemaphore sem; 
    queue<int> blocked; 
    vector<int> running, finished; 
 
    for (int i = 1; i <= numProcesses; ++i) { 
        cout << "Process " << i << " requests entry (sem = " << sem.get() << ")\n"; 
        sem.acquire(i, blocked, running); 
        showQueues(running, blocked); 
    } 
    cout << "\nSimulating execution and release...\n"; 
    while (!running.empty()) { 
        int pid = running.front(); 
        cout << "Process " << pid << " finished and releases (sem = " << sem.get() << ")\n"; 
        sem.release(pid, blocked, running); 
        finished.push_back(pid); 
        showQueues(running, blocked); 
    } 
    cout << "\nAll processes finished. Finished Queue: "; 
    for (int pid : finished) cout << pid << " "; 
    cout << endl; 
    return 0;
}