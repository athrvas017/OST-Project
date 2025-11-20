#include <iostream> 
#include <vector> 
#include <queue> 
using namespace std; 
 
class CountingSemaphore { 
    int count; 
public: 
    CountingSemaphore(int value) : count(value) {} 
 
    bool acquire(int pid, queue<int>& blockedQueue, vector<int>& 
runningQueue) { 
        if (count > 0) { 
            count--; 
            runningQueue.push_back(pid); 
            return true; 
        } else { 
            blockedQueue.push(pid); 
            return false; 
        } 
    } 
 
    void release(int pid, queue<int>& blockedQueue, vector<int>& 
runningQueue) { 
        count++; 
 
        for (auto it = runningQueue.begin(); it != runningQueue.end(); 
++it) { 
            if (*it == pid) { 
                runningQueue.erase(it); 
                break; 
            } 
        } 
        
        if (!blockedQueue.empty() && count > 0) { 
            int nextPid = blockedQueue.front(); blockedQueue.pop(); 
            count--; 
            runningQueue.push_back(nextPid); 
            cout << "Process " << nextPid << " moved from blocked to running.\n "; 
        } 
    } 
 
    int value() { return count; } 
}; 
 
void showQueues(const vector<int>& runningQueue, const 
queue<int>& blockedQueue) { 
    cout << "Running Queue: "; 
    for (int pid : runningQueue) cout << pid << " "; 
    cout << "\nBlocked Queue: "; 
    queue<int> temp = blockedQueue; 
    while (!temp.empty()) { 
        cout << temp.front() << " "; 
        temp.pop(); 
    } 
    cout << endl; 
} 
 
int main() { 
    int numProc, semVal; 
    cout << "Enter number of processes: "; 
    cin >> numProc; 
    cout << "Enter initial semaphore value: "; 
    cin >> semVal; 
 
    CountingSemaphore sem(semVal); 
    queue<int> blockedQueue; 
    vector<int> runningQueue; 
    vector<int> finishedQueue; 
 
    for (int i = 1; i <= numProc; ++i) { 
        cout << "Process " << i << " is requesting entry (sem = " << sem.value() << ")\n"; 
        sem.acquire(i, blockedQueue, runningQueue); 
        showQueues(runningQueue, blockedQueue); 
    } 
    cout << "\nSimulating execution and release...\n"; 
    while (!runningQueue.empty()) { 
        int pid = runningQueue.front(); 
        cout << "Process " << pid << " finished and releases (sem = " << sem.value() << ")\n"; 
        sem.release(pid, blockedQueue, runningQueue); 
        finishedQueue.push_back(pid); 
        showQueues(runningQueue, blockedQueue); 
    } 
    cout << "\nAll processes finished. Finished Queue: "; 
    for (int pid : finishedQueue) cout << pid << " "; 
    cout << endl; 
    return 0;
}