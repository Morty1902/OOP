#include <iostream>
#include <windows.h>
using namespace std;

class List 
{
private:
    int* data;
    int size;
    int capacity;

public:
    List() {
        size = 0;
        capacity = 4;
        data = new int[capacity];
    }

    ~List() {
        delete[] data;
    }

    void add(int value) {
        if (size >= capacity) {
            capacity *= 2;
            int* temp = new int[capacity];
            
            for (int i = 0; i < size; i++) {
                temp[i] = data[i];
            }     
            delete[] data;
            data = temp;
        }
        data[size] = value;
        size++;
    }

    int removeLast() {
        if (size > 0) {
            size--;
            return data[size];
        }
        return -1;
    }

    int getElement(int index) const {
        return data[index];
    }
    
    int getSize() const {
        return size;
    }
};

class Stack {
private:
    List list_data;

public:
    Stack() {
        cout << "Стек створено" << endl;
    }
    ~Stack() {
        cout << "Стек знищено" << endl;
    }

    void set(int value) {
        list_data.add(value);
    }

    int get() {
        if (list_data.getSize() == 0) {
            cout << "Стек порожній" << endl;
            return -1;
        }
        return list_data.removeLast();
    }

    void show() const {
        cout << "\nВміст стека" << endl;
        if (list_data.getSize() == 0) {
            cout << "Стек порожній" << endl;
            return;
        }
        for (int i = list_data.getSize() - 1; i >= 0; i--) {
            cout <<list_data.getElement(i)<< endl;
        }
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Stack myStack;

    int choice;
    int value;

    do{
    cout << "Оберіть режим: 1 - додати елемент, 2 - взяти останній елемент, 3 - показати стек, 0 - вихід: \n";
    cin >> choice;
        switch (choice) {
            case 1: {
                int n;
                cout << "Скільки елементів хочете внести? ";
                cin >> n;
                for (int i = 0; i < n; i++) {
                    int value;
                    cout << "Введіть елемент " << i + 1 << ": ";
                    cin >> value;
                    myStack.set(value);
                }
                cout << "\nУспішно додано " << n << " елементів\n";
                break;
            }

            case 2: {
                value = myStack.get();
                if (value != -1)
                    cout << "Отримано значення: " << value << endl;
                myStack.show();
                break;
            }

            case 3:
                myStack.show();
                break;

            case 0:
                cout << "Вихід" << endl;
                break;                
            default:
                cout << "Невірний вибір\n";
                break;
        }
    } while (choice != 0);

    return 0;
}