/*
       Client--> class singleton(instance finc, show message func) 
*/

#include <iostream>
using namespace std;

class Singleton{
  public: 
     static Singleton*instance;
     Singleton(){
       cout<<"Instance created\n";
     }
     
     static Singleton*getInstance(){
       if(instance==NULL){
         cout<<"first time ";
         instance= new Singleton();
       }
       return instance;
     }
     
     void showMessage(){
       cout<<"Hello message printed"<<endl;
     }
};
Singleton*Singleton::instance=nullptr;
int main() 
{
  Singleton*s1= Singleton::getInstance();
  Singleton*s2= Singleton::getInstance();
  
  s1->showMessage();
  if(s1==s2){
    cout<<"Both instances have been created"<<endl;
  }
  
}
