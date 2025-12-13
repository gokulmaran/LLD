#include <bits/stdc++.h>
using namespace std;

/*
class Diagam
  main-->Vending machine --.(State*state,int balance,map<Item,price>|| setstate(),insertstate->selectItem,dispense)
          | 
         State(abstract class) --insertMoney(),selectItem(),dispense()
         |
         Idle state hasMoney state Dispense state
*/
//Vending machine intrface
class State;
class VendingMachine{
    public:
       State* state;
       int balance;

       VendingMachine(State*initialState): state(initialState),balance(0){}

       void setState(State* newState){
        state=newState;
       }

       void addBalance(int amt){
          balance+=amt;
       }
       void deductBalance(int amt){
         balance-=amt;
       }
       int getBalance(){
          return balance;
       }
       void insertMoney(int amt){
          state->insertMoney(this,amt);
       }
       void selectItem(int price){
          state->selectItem(this,price);
       }
       void dispense(){
          state->dispense(this);
       }
};
class State{
    public:
     virtual void insertMoney(VendingMachine* vm, int amount)=0;
     virtual void selectItem(VendingMachine* vm, int price)=0;
     virtual void dispense(VendingMachine* vm)=0;
     virtual ~State(){}
};
//IdleState
class IdleState: public State{
   public:
      void insertMoney(VendingMachine*vm,int amt){
          
      }
      void selectItem(VendingMachine*vm,int){

      }
      void dispense(){

      }
};
//HasMoneyState
class IdleState: public State{
   public:
      void insertMoney(VendingMachine*vm,int amt){
          
      }
      void selectItem(VendingMachine*vm,int){

      }
      void dispense(){

      }
};
//Dispense State
class IdleState: public State{
   public:
      void insertMoney(VendingMachine*vm,int amt){
          
      }
      void selectItem(VendingMachine*vm,int){

      }
      void dispense(){

      }
};
//main
int main(){
   
}

