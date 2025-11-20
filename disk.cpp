#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

// Function to print the disk movement table
void printTable(const vector<int>& sequence) {
    int totalDistance = 0;
    cout << "\nFrom   ->   To     | Distance\n";
    cout << "----------------------------\n";
    for (size_t i = 1; i < sequence.size(); i++) {
        int dist = abs(sequence[i] - sequence[i-1]);
        totalDistance += dist;
        cout << setw(5) << sequence[i-1] 
             << "   ->   " << setw(5) << sequence[i] 
             << "    | " << setw(5) << dist << "\n";
    }
    cout << "----------------------------\n";
    cout << "Total head movement: " << totalDistance << "\n";
}

// FCFS
void fcfs(int head, const vector<int>& requests) {
    vector<int> sequence = {head};
    sequence.insert(sequence.end(), requests.begin(), requests.end());
    cout << "\n--- FCFS ---\n";
    printTable(sequence);
}

// SSTF
void sstf(int head, vector<int> requests) {
    vector<int> sequence = {head};
    int current = head;

    while (!requests.empty()) {
        auto it = min_element(requests.begin(), requests.end(),
                              [current](int a, int b){ return abs(a - current) < abs(b - current); });
        current = *it;
        sequence.push_back(current);
        requests.erase(it);
    }

    cout << "\n--- SSTF ---\n";
    printTable(sequence);
}

// SCAN
void scan(int head, vector<int> requests, int diskSize) {
    vector<int> sequence = {head};
    vector<int> left, right;

    for (int r : requests) (r < head ? left : right).push_back(r);

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    for (int r : right) sequence.push_back(r);
    if (!right.empty()) sequence.push_back(diskSize - 1);
    for (auto it = left.rbegin(); it != left.rend(); ++it) sequence.push_back(*it);

    cout << "\n--- SCAN ---\n";
    printTable(sequence);
}

// C-SCAN
void cscan(int head, vector<int> requests, int diskSize) {
    vector<int> sequence = {head};
    vector<int> left, right;

    for (int r : requests) (r < head ? left : right).push_back(r);

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    for (int r : right) sequence.push_back(r);
    if (!right.empty()) sequence.push_back(diskSize - 1);
    sequence.push_back(0);
    for (int r : left) sequence.push_back(r);

    cout << "\n--- C-SCAN ---\n";
    printTable(sequence);
}

// LOOK
void look(int head, vector<int> requests) {
    vector<int> sequence = {head};
    vector<int> left, right;

    for (int r : requests) (r < head ? left : right).push_back(r);

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    for (int r : right) sequence.push_back(r);
    for (auto it = left.rbegin(); it != left.rend(); ++it) sequence.push_back(*it);

    cout << "\n--- LOOK ---\n";
    printTable(sequence);
}

// C-LOOK
void clook(int head, vector<int> requests) {
    vector<int> sequence = {head};
    vector<int> left, right;

    for (int r : requests) (r < head ? left : right).push_back(r);

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    for (int r : right) sequence.push_back(r);
    for (int r : left) sequence.push_back(r);

    cout << "\n--- C-LOOK ---\n";
    printTable(sequence);
}

int main() {
    int n, head, diskSize;
    cout << "Enter number of disk requests: ";
    cin >> n;
    vector<int> requests(n);
    cout << "Enter disk requests: ";
    for (int i = 0; i < n; i++) cin >> requests[i];

    cout << "Enter initial head position: ";
    cin >> head;

    cout << "Enter disk size (max track number): ";
    cin >> diskSize;

    fcfs(head, requests);
    sstf(head, requests);
    scan(head, requests, diskSize);
    cscan(head, requests, diskSize);
    look(head, requests);
    clook(head, requests);

    return 0;
}

// for (int i = 0; i < 1000; i++) {
//     requests.push_back(rand() % 5000); // random number between 0–4999
// }
