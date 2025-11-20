#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

class SportsGame {
protected:
    string name;
    int players;

public:
    SportsGame(string n, int p) {
        name = n;
        players = p;
    }
    virtual ~SportsGame() {
    }

    virtual void show() {
        cout << "Гра: " << name << ", Гравців: " << players << endl;
    }

    virtual void saveToFile(ofstream &out) {
        out << "Назва гри: " << name << endl;
        out << "Кількість гравців: " << players << endl;
    }
};

class Football : public SportsGame {
private:
    string stadium;
    int time;

public:
    Football(string n, int p, string s, int t) : SportsGame(n, p) {
        stadium = s;
        time = t;
    }

    ~Football() {
    }
    void show() {
        SportsGame::show();
        cout << "Стадіон: " << stadium << ", Час гри: " << time << " хв." << endl;
    }

    void saveToFile(ofstream &out) {
        SportsGame::saveToFile(out);
        out << "Стадіон: " << stadium << endl;
        out << "Тривалість: " << time << " хв." << endl;
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Football match1("Футбол", 11, "Олімпійський", 90);
    match1.show();
    Football match2("Міні-футбол", 5, "Спортзал №3", 40);
    match2.show();
    Football match3("Міні-футбол", 7, "Спортзал №5", 45);
    match3.show();
    ofstream file;
    file.open("lab4_result.txt", ios::out | ios::app); 

    if (file.is_open()) {
        match1.saveToFile(file);
        match2.saveToFile(file);
        match3.saveToFile(file);
        file.close();
        cout << "Дані успішно записані у файл lab4_result.txt" << endl;
    } else {
        cout << "Помилка відкриття файлу!" << endl;
    }
    return 0;
}