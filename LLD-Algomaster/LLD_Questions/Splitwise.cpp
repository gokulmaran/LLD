#include <bits/stdc++.h>
using namespace std;

/*
User--> id,name,email
Split--> user and amount
Expense--> id, amount, splits, paidBy, type
SplitStrategy --> exact, percentage, equal
SplitStrategyFactory --> returns strategy
ExpenseManager --> add expense and show balances
*/

class User{
public:
    string id;
    string name;
    string email;

    User(string id,string name,string email){
        this->id=id;
        this->name=name;
        this->email=email;
    }
};

class Split{
public:
    User* user;
    double amount;

    Split(User* user,double amt=0){
        this->user=user;
        this->amount=amt;
    }
};

enum ExpenseType {EXACT,EQUAL,PERCENT};

class Expense{
public:
    User* paidBy;
    string id;
    double amount;
    vector<Split*> splits;
    ExpenseType type;

    Expense(string id,double amt,User* paidBy,vector<Split*> splits,ExpenseType type){
        this->id=id;
        this->paidBy=paidBy;
        this->amount=amt;
        this->splits=splits;
        this->type=type;
    }
};

class SplitStrategy{
public:
    virtual void validate(double amt,vector<Split*>& splits)=0;
};

class EqualSplit:public SplitStrategy{
public:
    void validate(double amt,vector<Split*>& splits){

        int n=splits.size();
        double splitAmount=amt/n;

        for(auto s:splits){
            s->amount=splitAmount;
        }
    }
};

class ExactSplit:public SplitStrategy{
public:
    void validate(double amt,vector<Split*>& splits){

        double sum=0;

        for(auto s:splits){
            sum+=s->amount;
        }

        if(sum!=amt){
            throw runtime_error("Invalid exact amount");
        }
    }
};

class PercentSplit:public SplitStrategy{
public:
    void validate(double amt,vector<Split*>& splits){

        double percentSum=0;

        for(auto s:splits){
            percentSum+=s->amount;
        }

        if(percentSum!=100){
            throw runtime_error("Percent must equal 100");
        }

        for(auto s:splits){
            s->amount=(s->amount/100.0)*amt;
        }
    }
};

class SplitStrategyFactory{
public:

    static SplitStrategy* getStrategy(ExpenseType type){

        if(type==EQUAL)
            return new EqualSplit();

        else if(type==EXACT)
            return new ExactSplit();

        else if(type==PERCENT)
            return new PercentSplit();

        return nullptr;
    }
};

class ExpenseManager{
public:

    map<string,map<string,double>> balanceSheet;

    void addExpense(Expense* expense){

        SplitStrategy* strategy=
        SplitStrategyFactory::getStrategy(expense->type);

        strategy->validate(expense->amount,expense->splits);

        User* paidBy=expense->paidBy;

        for(auto split:expense->splits){

            User* user=split->user;
            double amount=split->amount;

            if(user->id==paidBy->id)
                continue;

            balanceSheet[user->id][paidBy->id]+=amount;
            balanceSheet[paidBy->id][user->id]-=amount;
        }
    }

    void showBalances(){

        for(auto user:balanceSheet){

            for(auto entry:user.second){

                if(entry.second>0){

                    cout<<user.first
                        <<" owes "
                        <<entry.first
                        <<" : "
                        <<entry.second
                        <<endl;
                }
            }
        }
    }
};

int main(){

    User* u1=new User("u1","Alice","a@gmail");
    User* u2=new User("u2","Bob","b@gmail");
    User* u3=new User("u3","Charlie","c@gmail");

    vector<Split*> splits;

    splits.push_back(new Split(u1));
    splits.push_back(new Split(u2));
    splits.push_back(new Split(u3));

    Expense* e1=new Expense("e1",300,u1,splits,EQUAL);

    ExpenseManager manager;

    manager.addExpense(e1);

    manager.showBalances();
}