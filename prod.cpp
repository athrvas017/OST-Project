#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <iomanip>
#include <chrono>

using namespace std;

// Shared buffer and control variables
vector<int> buffer;
int bufferSize;
int in = 0, out = 0;
int countItems = 0;

// Stats
int totalProduced = 0;
int totalConsumed = 0;
int step = 0; // step counter for the output table

// Synchronization primitives
mutex mtx;
condition_variable notFull, notEmpty;

// Helper: convert buffer to printable string
string bufferToString() {
    string s = "[ ";
    for (int i = 0; i < bufferSize; i++) {
        if (buffer[i] == -1)
            s += "_ ";
        else
            s += to_string(buffer[i]) + " ";
    }
    s += "]";
    return s;
}

// Producer thread
void producer(int id, int produceCount) {
    for (int i = 0; i < produceCount; i++) {
        int item = totalProduced + 1;  // item = 1, 2, 3, 4...

        unique_lock<mutex> lock(mtx);
        notFull.wait(lock, [] { return countItems < bufferSize; });

        // --- Produce item ---
        buffer[in] = item;
        totalProduced++;
        step++;

        cout << left << setw(6) << step
             << setw(15) << ("Produce(" + to_string(id) + ")")
             << setw(8) << item
             << setw(10) << in
             << setw(10) << "-"
             << bufferToString() << endl;

        in = (in + 1) % bufferSize;
        countItems++;

        lock.unlock();
        notEmpty.notify_one();

        this_thread::sleep_for(chrono::milliseconds(600));
    }
}

// Consumer thread
void consumer(int id, int consumeCount) {
    for (int i = 0; i < consumeCount; i++) {
        unique_lock<mutex> lock(mtx);
        notEmpty.wait(lock, [] { return countItems > 0; });

        // --- Consume item ---
        int item = buffer[out];
        buffer[out] = -1;
        totalConsumed++;
        step++;

        cout << left << setw(6) << step
             << setw(15) << ("Consume(" + to_string(id) + ")")
             << setw(8) << item
             << setw(10) << "-"
             << setw(10) << out
             << bufferToString() << endl;

        out = (out + 1) % bufferSize;
        countItems--;

        lock.unlock();
        notFull.notify_one();

        this_thread::sleep_for(chrono::milliseconds(900));
    }
}

int main() {
    cout << "Enter buffer size: ";
    cin >> bufferSize;

    buffer.assign(bufferSize, -1);

    cout << "\n=== 🧩 Producer–Consumer Simulation ===\n";
    cout << "Buffer size: " << bufferSize << "\n\n";

    // Print table header
    cout << left
         << setw(6) << "Step"
         << setw(15) << "Action"
         << setw(8) << "Item"
         << setw(10) << "In"
         << setw(10) << "Out"
         << "Buffer" << endl;
    cout << string(70, '-') << endl;

    // Create producer and consumer
    int produceCount = 6, consumeCount = 6;
    thread prod(producer, 1, produceCount);
    thread cons(consumer, 1, consumeCount);

    prod.join();
    cons.join();

    // Summary
    cout << "\n============================================\n";
    cout << "           📊 Simulation Summary             \n";
    cout << "============================================\n";
    cout << left << setw(25) << "Total items produced:" << totalProduced << endl;
    cout << left << setw(25) << "Total items consumed:" << totalConsumed << endl;
    cout << left << setw(25) << "Final 'in' index:" << in << endl;
    cout << left << setw(25) << "Final 'out' index:" << out << endl;
    cout << left << setw(25) << "Final Buffer State:" << bufferToString() << endl;
    cout << "============================================\n";
    cout << "✅ Simulation finished successfully!\n";
    cout << "============================================\n";

    return 0;
}