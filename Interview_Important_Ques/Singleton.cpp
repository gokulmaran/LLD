#include <iostream>
#include <mutex>
using namespace std;

class Singleton {
private:
    static Singleton* instance;
    static mutex mtx;

    // Private constructor
    Singleton() {
        cout << "Constructor called\n";
    }

    // Prevent copy & assignment
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    // Static method to get instance
    static Singleton* getInstance() {
        if (instance == nullptr) {                 // First check
            lock_guard<mutex> lock(mtx);
            if (instance == nullptr) {             // Second check
                instance = new Singleton();
            }
        }
        return instance;
    }

    void showMessage() {
        cout << "Singleton instance working\n";
    }

    // Optional cleanup (manual)
    static void destroyInstance() {
        lock_guard<mutex> lock(mtx);
        delete instance;
        instance = nullptr;
    }
};

// Static member initialization
Singleton* Singleton::instance = nullptr;
mutex Singleton::mtx;


// 🔥 Usage
int main() {
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();

    s1->showMessage();

    cout << "Address of s1: " << s1 << endl;
    cout << "Address of s2: " << s2 << endl;

    // Cleanup (optional)
    Singleton::destroyInstance();

    return 0;
}