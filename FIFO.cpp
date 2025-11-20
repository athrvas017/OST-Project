#include <iostream>
using namespace std;

void printFrames(int frames[], int capacity) {
    cout << "[ ";
    for (int i = 0; i < capacity; i++) {
        if (frames[i] == -1)
            cout << "_ ";
        else
            cout << frames[i] << " ";
    }
    cout << "]";
}

int find(int arr[], int size, int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value)
            return i;
    }
    return -1;
}

void fifo(int pages[], int n, int capacity) {
    cout << "\n*****Using FIFO Algorithm:*****\n";

    int frames[100];   // assuming capacity <= 100
    for (int i = 0; i < capacity; i++) frames[i] = -1;

    int front = 0, rear = 0, count = 0;
    int faults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        cout << "page: " << page << " : ";

        if (find(frames, capacity, page) == -1) { // page fault
            if (count < capacity) {
                frames[rear] = page;
                rear = (rear + 1) % capacity;
                count++;
            } else {
                frames[front] = page;
                front = (front + 1) % capacity;
                rear = front;
            }
            faults++;
            cout << "Page Fault! ";
        } else {
            cout << "Page Hit! ";
        }

        printFrames(frames, capacity);
        cout << "\n";
    }
    cout << "Total Page Faults: " << faults << "\n";
}

void lru(int pages[], int n, int capacity) {
    cout << "\n*****Using LRU Algorithm:*****\n";

    int frames[100];
    int usageOrder[100]; // stores usage order for frames, index = frame index, value = usage time
    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
        usageOrder[i] = -1;
    }

    int time = 0;
    int faults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        cout << "page: " << page << " : ";

        int pos = find(frames, capacity, page);

        if (pos == -1) { // Page fault
            faults++;
            int lru_index = 0;
            int min_time = usageOrder[0];

            // If there is empty frame
            int empty_index = find(frames, capacity, -1);
            if (empty_index != -1) {
                frames[empty_index] = page;
                usageOrder[empty_index] = time;
            } else {
                // find least recently used (min usageOrder)
                for (int j = 1; j < capacity; j++) {
                    if (usageOrder[j] < min_time) {
                        min_time = usageOrder[j];
                        lru_index = j;
                    }
                }
                frames[lru_index] = page;
                usageOrder[lru_index] = time;
            }
            cout << "Page Fault! ";
        } else {
            usageOrder[pos] = time; // update usage time for hit
            cout << "Page Hit! ";
        }
        time++;
        printFrames(frames, capacity);
        cout << "\n";
    }
    cout << "Total Page Faults: " << faults << "\n";
}

void optimal(int pages[], int n, int capacity) {
    cout << "\n*****Using Optimal Algorithm:*****\n";

    int frames[100];
    for (int i = 0; i < capacity; i++) frames[i] = -1;

    int faults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        cout << "page: " << page << " : ";

        int pos = find(frames, capacity, page);
        if (pos == -1) {
            faults++;

            // If empty slot available
            int empty_index = find(frames, capacity, -1);
            if (empty_index != -1) {
                frames[empty_index] = page;
            } else {
                // find page to replace - the one with farthest next use
                int indexToReplace = 0;
                int farthest = i;
                for (int j = 0; j < capacity; j++) {
                    int k;
                    for (k = i + 1; k < n; k++) {
                        if (frames[j] == pages[k]) break;
                    }
                    if (k == n) { // not used again
                        indexToReplace = j;
                        break;
                    }
                    if (k > farthest) {
                        farthest = k;
                        indexToReplace = j;
                    }
                }
                frames[indexToReplace] = page;
            }
            cout << "Page Fault! ";
        } else {
            cout << "Page Hit! ";
        }
        printFrames(frames, capacity);
        cout << "\n";
    }
    cout << "Total Page Faults: " << faults << "\n";
}

void secondChance(int pages[], int n, int capacity) {
    cout << "\nSecond Chance Algorithm:\n";

    int frames[100];
    bool refBit[100];
    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
        refBit[i] = false;
    }

    int pointer = 0;
    int faults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        cout << " page: " << page << " -> ";

        int pos = find(frames, capacity, page);

        if (pos != -1) { // Page hit
            refBit[pos] = true;
            cout << "Page Hit! ";
        } else {
            faults++;
            while (refBit[pointer]) {
                refBit[pointer] = false;
                pointer = (pointer + 1) % capacity;
            }
            frames[pointer] = page;
            refBit[pointer] = true;
            pointer = (pointer + 1) % capacity;
            cout << "Page Fault! ";
        }
        printFrames(frames, capacity);
        cout << "\n";
    }
    cout << "Total Page Faults: " << faults << "\n";
}

int main() {
    int n, capacity;
    cout << "Enter number of pages: ";
    cin >> n;

    int pages[100];
    cout << "Enter the page reference string:";
    for (int i = 0; i < n; i++) {
        cin >> pages[i];
    }

    cout << "Enter number of frames: ";
    cin >> capacity;

    fifo(pages, n, capacity);
    lru(pages, n, capacity);
    optimal(pages, n, capacity);
    // secondChance(pages, n, capacity);

    return 0;
}