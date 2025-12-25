#include <iostream>
#include <string>

using namespace std;

// =======================
// Product
// =======================
class Student {
public:
    string name;
    int age;
    string course;
    string email;
    bool hostel;
    bool scholarship;

    void printDetails() {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Course: " << course << endl;
        cout << "Email: " << email << endl;
        cout << "Hostel: " << (hostel ? "Yes" : "No") << endl;
        cout << "Scholarship: " << (scholarship ? "Yes" : "No") << endl;
    }
};

// =======================
// Builder Interface
// =======================
class StudentBuilder {
public:
    virtual void buildName() = 0;
    virtual void buildAge() = 0;
    virtual void buildCourse() = 0;
    virtual void buildEmail() = 0;
    virtual void buildHostel() = 0;
    virtual void buildScholarship() = 0;
    virtual Student* getStudent() = 0;
    virtual ~StudentBuilder() {}
};

// =======================
// Concrete Builder
// =======================
class EngineeringStudentBuilder : public StudentBuilder {
private:
    Student* student;

public:
    EngineeringStudentBuilder() {
        student = new Student();
    }

    void buildName() override {
        student->name = "Gokul";
    }

    void buildAge() override {
        student->age = 22;
    }

    void buildCourse() override {
        student->course = "Computer Science";
    }

    void buildEmail() override {
        student->email = "gokul@student.edu";
    }

    void buildHostel() override {
        student->hostel = true;
    }

    void buildScholarship() override {
        student->scholarship = false;
    }

    Student* getStudent() override {
        return student;
    }
};

// =======================
// Director
// =======================
class StudentDirector {
private:
    StudentBuilder* builder;

public:
    StudentDirector(StudentBuilder* b) : builder(b) {}

    Student* createStudent() {
        builder->buildName();
        builder->buildAge();
        builder->buildCourse();
        builder->buildEmail();
        builder->buildHostel();
        builder->buildScholarship();
        return builder->getStudent();
    }
};

// =======================
// Client
// =======================
int main() {
    cout << "======= Builder Design Pattern =======" << endl;

    StudentBuilder* builder = new EngineeringStudentBuilder();
    StudentDirector director(builder);

    Student* student = director.createStudent();
    student->printDetails();

    delete student;
    delete builder;

    return 0;
}
