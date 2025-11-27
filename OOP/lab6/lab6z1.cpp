#include <iostream>
#include <windows.h>
using namespace std;

template <class T>
void replaceElement(T* arr, int size, int oldIndex, T newValue) {
    if (oldIndex < 0 || oldIndex >= size) {
        cerr << "Індекс " << oldIndex << " поза межами масиву!" << endl;
        return;
    }
    arr[oldIndex] = newValue;
}

template <class T>
void printArray(const T* arr, int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

template <class T>
void inputArray(T* arr, int size) {
    for (int i = 0; i < size; ++i) {
        cout << "Елемент " << (i+1)<< ": ";
        cin >> arr[i];
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int index;
    int size;
    int newValue;
    cout << "\nВведіть розмір масиву: ";
    cin >> size;

    int* intArr = new int[size];

    cout << "\nЗаповніть масив:" << endl;
    inputArray(intArr, size);
    
    cout << "Ваш масив: ";
    printArray(intArr, size);
    
    cout << "\nВведіть індекс елемента для заміни: ";
    cin >> index;
    
    cout << "Введіть нове значення: ";
    cin >> newValue;
    
    replaceElement(intArr, size, index, newValue);
    cout << "Масив після заміни: ";
    printArray(intArr, size);

    delete[] intArr;
    return 0;
}