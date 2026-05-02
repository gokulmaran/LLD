#include <bits/stdc++.h>
using namespace std;

class Person{
   public:
      int age;
      string name;

      Person(int age_,string name_){
        age=age_;
        name=name_;
      }
      void getName(){
        cout<<name<<endl;;
      }
};
int main(){
    Person p1(25,"gokul");
    p1.getName();
    cout<<"Hello world"<<endl;
}