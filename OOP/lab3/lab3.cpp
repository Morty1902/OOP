#include <iostream>
#include <string>
#include <stdexcept>
#include <windows.h>
using namespace std;

class Word {
private:
    string ukr;
    string eng;
public:
    Word() : ukr(""), eng("") {}
    Word(const string& u, const string& e) : ukr(u), eng(e) {}

    const string& getUkr() const { return ukr; }
    const string& getEng() const { return eng; }

    bool operator<(const Word& other) const { return ukr < other.ukr; }
    bool operator>=(const Word& other) const { return !(ukr < other.ukr); }

    void print() const { cout << ukr << " - " << eng << '\n'; }
};

class Dictionary {
private:
    Word* words;
    int size;
    int capacity;

    void resize(int newCapacity) {
        if (!words) throw runtime_error("Помилка: вказівник words не ініціалізований!");
        Word* newWords = new Word[newCapacity];
        for (int i = 0; i < size; i++)
            newWords[i] = words[i];
        delete[] words;
        words = newWords;
        capacity = newCapacity;
    }

public:
    Dictionary(int initialCapacity = 2) : size(0), capacity(initialCapacity) {
        words = new Word[capacity];
    }

    ~Dictionary() {
        delete[] words;
    }

    Dictionary& operator+(const Word& w) {
        if (!words) throw runtime_error("Помилка: вказівник words не ініціалізований!");
        if (size >= capacity) resize(capacity * 2);
        words[size++] = w;
        return *this;
    }

    Dictionary& operator-(const Word& w) {
        if (!words) throw runtime_error("Помилка: вказівник words не ініціалізований!");
        for (int i = 0; i < size; i++) {
            if (words[i].getUkr() == w.getUkr()) {
                for (int j = i; j < size - 1; j++)
                    words[j] = words[j + 1];
                size--;
                return *this;
            }
        }
        throw runtime_error("Слово для видалення не знайдено!");
    }

    Word* findByUkr(const string& ukr) {
        if (!words) throw runtime_error("Помилка: вказівник words не ініціалізований!");
        for (int i = 0; i < size; i++)
            if (words[i].getUkr() == ukr)
                return &words[i];
        return nullptr;
    }

    enum class SortBy { UKR, ENG };
    void sort() {
        sort(SortBy::UKR);
    }

    void sort(SortBy sortBy) {
        if (!words) throw runtime_error("Помилка: вказівник words не ініціалізований!");
        
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                bool needSwap = false;
                
                if (sortBy == SortBy::UKR) {
                    needSwap = words[j + 1] < words[j];
                } else if (sortBy == SortBy::ENG) {
                    needSwap = words[j].getEng() >= words[j + 1].getEng();
                }
                
                if (needSwap) {
                    Word temp = words[j];
                    words[j] = words[j + 1];
                    words[j + 1] = temp;
                }
            }
        }
    }

    void print() const {
        if (!words) throw runtime_error("Помилка: вказівник words не ініціалізований!");
        if (size == 0) cout << "Словник порожній\n";
        for (int i = 0; i < size; i++) words[i].print();
    }
};

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    
    try {
        Dictionary dict;

        dict + Word("Яблуко","Apple");
        dict + Word("Кіт","Cat");
        dict + Word("Собака","Dog");
        dict + Word("Дім","House");
        dict + Word("Автомобіль","Car");

        cout << "Початковий словник:\n";
        dict.print();

        cout << "\nСортуємо за українськими словами (використовуючи sort() без параметрів):\n";
        dict.sort();
        dict.print();

        cout << "\nСортуємо за українськими словами (використовуючи sort(SortBy::UKR)):\n";
        dict.sort(Dictionary::SortBy::UKR);
        dict.print();

        cout << "\nСортуємо за англійськими словами (використовуючи sort(SortBy::ENG)):\n";
        dict.sort(Dictionary::SortBy::ENG);
        dict.print();

        cout << "\nПошук 'Кіт':\n";
        if (auto f = dict.findByUkr("Кіт")) f->print();
        else cout << "Не знайдено\n";

        cout << "\nВидаляємо 'Собака':\n";
        dict - Word("Собака","Dog");
        dict.print();

    } catch (const exception& ex) {
        cerr << "Виняток: " << ex.what() << "\n";
    }
    return 0;
}
