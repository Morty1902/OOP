#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

class Worker {
protected:
    string name;
    int salary;
public:
    Worker(string n,int s){
        name = n;
        salary = s;
    }
    virtual ~Worker(){    
    }
    virtual void calculateSalary(){
        cout<<"Заробітня плата робітника "<< name <<" = "<<salary<<endl;
    }
};

class Worker_hp : public Worker {
private:
    int HoursWorked;
    int HoursPay;

public:
    Worker_hp(string n, int s, int hs, int hp) : Worker(n,s) {
        HoursWorked = hs;
        HoursPay = hp;
    }
    ~Worker_hp(){
    }
    void calculateSalary() override {
        int HoursSalary = HoursWorked * HoursPay;
        cout<<"Заробітня плата робітника з почасовою оплатою "<<name<<" = "<<HoursSalary<<endl;
    }
};

class Worker_os : public Worker {
private:
    int orderSalary;
public:
    Worker_os( string n, int s, int os) : Worker(n,s){
        orderSalary = os;
        salary = orderSalary;
    }
    ~Worker_os(){
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Worker *human = new Worker_hp("Василь Іванович", 0, 160, 50);
    human->calculateSalary();
    Worker *human2= new Worker_os("Іван Петрович", 0, 5000);
    human2->calculateSalary();
    return 0;
}