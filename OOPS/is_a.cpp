#include <bits/stdc++.h>
using namespace std;

class Person{
   public:
      int age;
      string name;
};
class Employee: public Person{
 public:
      string company;
      string id;
};
int main(){
   Employee e1;

   e1.company="algozenith";
   e1.id=25;

   e1.age=55;
   e1.name="gokul";
   cout<<e1.name<<endl;
}