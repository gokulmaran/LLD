#include <bits/stdc++.h>
using namespace std;

class Course{
  public:
    string name;
    Course(string name):name(name) {}
    string getName(){
      return name;
    }
};

class Teacher{
  public:
  string name;
    vector<Course*>courses;
    Teacher(string name):name(name){}
    string teach(Course*c){
       courses.push_back(c);
       return name+"teaches"+c->getName();
    }
};
int main(){
   Teacher t("Dr smith");
   Course c("pythio coding");
   
   cout<<t.teach(&c);
}