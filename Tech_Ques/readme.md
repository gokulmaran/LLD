🔥 1. Virtual Function

👉 Definition:

A virtual function is a member function declared with virtual that is resolved at runtime (not compile time) based on the actual object type, not the pointer type.

👉 Why it exists:
To enable runtime polymorphism

👉 Example:

class Base {
public:
    virtual void show() {
        cout << "Base\n";
    }
};

class Derived : public Base {
public:
    void show() override {
        cout << "Derived\n";
    }
};