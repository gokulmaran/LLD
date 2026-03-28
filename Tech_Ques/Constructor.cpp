
#include<bits/stdc++.h>
using namespace std;

class A {
    int* ptr;

public:
    A() {
        ptr = new int(10);

        try {
            throw runtime_error("fail");
        } catch (...) {
            delete ptr;   // manual cleanup
            throw;        // rethrow
        }
    }
};