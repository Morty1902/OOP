#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

template <class T>
class FileHandler {
private:
    string filename;
    fstream fileStream;

public:
    FileHandler(string name);
    ~FileHandler();

    void openFile(bool writeMode);
    void writeToFile(T value);
    void readFromFile();
    void closeFile();
};

template <class T>
FileHandler<T>::FileHandler(string name) {
    filename = name;
}

template <class T>
FileHandler<T>::~FileHandler() {
    closeFile();
}

template <class T>
void FileHandler<T>::openFile(bool writeMode) {
    if (writeMode) {
        fileStream.open(filename, ios::out | ios::app);
    } else {
        fileStream.open(filename, ios::in);
    }

    if (!fileStream.is_open()) {
        cerr << "Помилка відкриття файлу: " << filename << endl;
    }
}

template <class T>
void FileHandler<T>::writeToFile(T value) {
    if (fileStream.is_open()) {
        fileStream << value << endl;
        cout << "Записано у файл " << filename << endl;
    } else {
        cerr << "Файл не відкритий для запису!" << endl;
    }
}

template <class T>
void FileHandler<T>::readFromFile() {
    T value;
    if (fileStream.is_open()) {
        cout << "Зчитування з файлу " << filename << endl;
        while (fileStream >> value) {
            cout << "Зчитано: " << value << endl;
        }
        fileStream.clear(); 
    } else {
        cerr << "Файл не відкритий для читання!" << endl;
    }
}

template <class T>
void FileHandler<T>::closeFile() {
    if (fileStream.is_open()) {
        fileStream.close();
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    FileHandler<int> intFile("numbers.txt");

    intFile.openFile(true);
    int count;
    cout << "Введіть кількість цілих чисел для запису: ";
    cin >> count;
    for (int i = 0; i < count; ++i) {
        int num;
        cout << "Введіть ціле число " << (i + 1) << ": ";
        cin >> num;
        intFile.writeToFile(num);
    }
    intFile.closeFile();

    intFile.openFile(false);
    intFile.readFromFile();
    intFile.closeFile();
    cout << endl;

    FileHandler<string> stringFile("words.txt");


    stringFile.openFile(true);
    int strCount;
    cout << "Введіть кількість слів для запису: ";
    cin >> strCount;
    cin.ignore();
    for (int i = 0; i < strCount; ++i) {
        string word;
        cout << "Введіть слово " << (i + 1) << ": ";
        getline(cin, word);
        stringFile.writeToFile(word);
    }
    stringFile.closeFile();

    stringFile.openFile(false);
    stringFile.readFromFile();
    stringFile.closeFile();

    return 0;
}
