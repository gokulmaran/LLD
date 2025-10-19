#include <iostream>
#include <string>
using namespace std;

/*
Single Responsibility Principle (SRP) Definition: A class should have only one
reason to change, meaning it should have a single responsibility. Benefits: Reduces complexity. Makes code more understandable. Enhances maintainability.
To illustrate SRP, let's consider an application that calculates the total area of
a collection of shapes (circles and squares). We'll start by creating the shape
classes and then develop a calculator to sum their areas.*/

// Employee class
class Employee {
private:
    int empId;
    string name;
    double salary;

public:
    Employee(int empId, string name, double salary) {
        this->empId = empId;
        this->name = name;
        this->salary = salary;
    }

    int getEmpId() { return empId; }
    string getName() { return name; }
    double getSalary() { return salary; }
};

// Salary calculation responsibility
class SalaryCalculator {
public:
    double calculateSalary(Employee& employee) {
        return employee.getSalary() * 1.1; // 10% increment
    }
};

// Database responsibility
class EmployeeRepository {
public:
    void saveToDatabase(Employee& employee) {
        cout << "Saving " << employee.getName() << " to database..." << endl;
    }
};

// Reporting responsibility
class EmployeeReport {
public:
    void generateReport(Employee& employee) {
        cout << "Employee Report: " << employee.getName()
             << ", Salary: " << employee.getSalary() << endl;
    }
};

// Main function to demonstrate
int main() {
    Employee emp(101, "Gokul", 50000.0);

    SalaryCalculator salaryCalc;
    EmployeeRepository repo;
    EmployeeReport report;

    double newSalary = salaryCalc.calculateSalary(emp);
    cout << "Updated Salary: " << newSalary << endl;

    repo.saveToDatabase(emp);
    report.generateReport(emp);

    return 0;
}
