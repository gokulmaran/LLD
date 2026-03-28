// Producer → generates 10 numbers
// Consumer → consumes
// Only prints even numbers

// Let’s do it properly without breaking thread safety.
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

class BoundedBuffer {
private:
    queue<int> buffer;
    int capacity;

    mutex mtx;
    condition_variable not_full, not_empty;

public:
    BoundedBuffer(int cap) : capacity(cap) {}

    void produce(int item) {
        unique_lock<mutex> lock(mtx);

        not_full.wait(lock, [this]() {
            return buffer.size() < capacity;
        });

        buffer.push(item);
        cout << "Produced: " << item << endl;

        not_empty.notify_one();
    }

    int consume() {
        unique_lock<mutex> lock(mtx);

        not_empty.wait(lock, [this]() {
            return !buffer.empty();
        });

        int item = buffer.front();
        buffer.pop();

        not_full.notify_one();
        return item;
    }
};

// Producer thread
void producer(BoundedBuffer& buffer) {
    for (int i = 1; i <= 10; i++) {
        buffer.produce(i);
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

// Consumer thread
void consumer(BoundedBuffer& buffer) {
    for (int i = 1; i <= 10; i++) {
        int item = buffer.consume();

        if (item % 2 == 0) {
            cout << "Consumed EVEN: " << item << endl;
        }
    }
}

int main() {
    BoundedBuffer buffer(5);

    thread t1(producer, ref(buffer));
    thread t2(consumer, ref(buffer));

    t1.join();
    t2.join();

    return 0;
}