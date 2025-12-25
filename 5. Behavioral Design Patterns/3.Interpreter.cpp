#include <iostream>

using namespace std;

// =======================
// Operation Type (enum)
// =======================
enum OperationType {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE
};

// =======================
// Component Interface
// =======================
class ArithmeticExpression {
public:
    virtual int evaluate() = 0;
    virtual ~ArithmeticExpression() {}
};

// =======================
// Leaf - Number
// =======================
class Number : public ArithmeticExpression {
private:
    int value;

public:
    Number(int val) : value(val) {}

    int evaluate() override {
        cout << "Number value is: " << value << endl;
        return value;
    }
};

// =======================
// Composite - Expression
// =======================
class Expression : public ArithmeticExpression {
private:
    ArithmeticExpression* leftExpression;
    ArithmeticExpression* rightExpression;
    OperationType operation;

public:
    Expression(ArithmeticExpression* left,
               ArithmeticExpression* right,
               OperationType op)
        : leftExpression(left),
          rightExpression(right),
          operation(op) {}

    int evaluate() override {
        int value = 0;

        switch (operation) {
            case ADD:
                value = leftExpression->evaluate() +
                        rightExpression->evaluate();
                break;

            case SUBTRACT:
                value = leftExpression->evaluate() -
                        rightExpression->evaluate();
                break;

            case MULTIPLY:
                value = leftExpression->evaluate() *
                        rightExpression->evaluate();
                break;

            case DIVIDE:
                value = leftExpression->evaluate() /
                        rightExpression->evaluate();
                break;
        }

        cout << "Expression value is: " << value << endl;
        return value;
    }

    // Destructor to avoid memory leak
    ~Expression() {
        delete leftExpression;
        delete rightExpression;
    }
};

// =======================
// Client Code
// =======================
int main() {
    cout << "======= Composite Design Pattern =======" << endl;

    // Expression: 2 * (1 + 7)
    /*
            *
           / \
          2   +
             / \
            1   7
    */

    ArithmeticExpression* two = new Number(2);
    ArithmeticExpression* one = new Number(1);
    ArithmeticExpression* seven = new Number(7);

    ArithmeticExpression* addExpression =
        new Expression(one, seven, ADD);

    ArithmeticExpression* parentExpression =
        new Expression(two, addExpression, MULTIPLY);

    cout << "Final Result: " << parentExpression->evaluate() << endl;

    // Cleanup (recursively deletes entire tree)
    delete parentExpression;

    return 0;
}
