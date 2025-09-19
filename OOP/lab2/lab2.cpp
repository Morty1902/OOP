#include <iostream>
#include <stdexcept>
using namespace std;

class List {
private:
    int* data;         // динамічний масив для зберігання елементів
    int capacity;      // поточний об'єм масиву
    int length;        // кількість логічних елементів

    // Забезпечити щонайменше minCapacity
    void ensureCapacity(int minCapacity) {
        if (capacity >= minCapacity) return;
        int newCap = (capacity == 0) ? 1 : capacity;
        while (newCap < minCapacity) newCap *= 2;
        int* newData = new int[newCap];
        for (int i = 0; i < length; ++i) newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity = newCap;
    }

public:
    // Конструктор (за замовчуванням)
    List(int initCap = 10) : data(nullptr), capacity(0), length(0) {
        if (initCap > 0) {
            data = new int[initCap];
            capacity = initCap;
        }
    }

    // Конструктор копіювання (глибоке копіювання)
    List(const List& other) : data(nullptr), capacity(0), length(0) {
        capacity = other.capacity;
        length = other.length;
        if (capacity > 0) {
            data = new int[capacity];
            for (int i = 0; i < length; ++i) data[i] = other.data[i];
        }
    }

    // Оператор присвоєння (Rule of Three)
    List& operator=(const List& other) {
        if (this == &other) return *this;
        delete[] data;
        capacity = other.capacity;
        length = other.length;
        data = nullptr;
        if (capacity > 0) {
            data = new int[capacity];
            for (int i = 0; i < length; ++i) data[i] = other.data[i];
        }
        return *this;
    }

    // Деструктор
    ~List() { delete[] data; }

    // set(index, value) — встановити значення за індексом (0-based)
    void set(int index, int value) {
        if (index < 0 || index >= length) {
            throw out_of_range("List::set(): invalid index");
        }
        data[index] = value;
    }

    // get(index) — повернути значення за індексом
    int get(int index) const {
        if (index < 0 || index >= length) {
            throw out_of_range("List::get(): invalid index");
        }
        return data[index];
    }

    // show() — вивести вміст списку
    void show() const {
        cout << "[";
        for (int i = 0; i < length; ++i) {
            if (i) cout << ", ";
            cout << data[i];
        }
        cout << "]";
    }

    // Додаткові методи, що знадобляться при роботі зі стеком
    void append(int value) {
        ensureCapacity(length + 1);
        data[length++] = value;
    }

    void removeAt(int index) {
        if (index < 0 || index >= length) throw out_of_range("List::removeAt(): invalid index");
        for (int i = index; i < length - 1; ++i) data[i] = data[i + 1];
        --length;
    }

    int size() const { return length; }

    void clear() { length = 0; }
};

// -------------------------
// Клас СТЕК (Stack)
// -------------------------
class Stack {
private:
    List list;  // композиція — стек містить об'єкт СПИСОК

public:
    // Конструктор: можна задати початкову ємність для внутрішнього списку
    Stack(int initCap = 10) : list(initCap) {}

    // set(value) — у цьому прикладі використаємо як push(value)
    void set(int value) { push(value); }

    // get() — прочитати (і видалити) верхній елемент — pop()
    int get() { return pop(); }

    // push(value) — додати елемент у стек
    void push(int value) { list.append(value); }

    // pop() — зняти верхній елемент і повернути його
    int pop() {
        int n = list.size();
        if (n == 0) throw runtime_error("Stack::pop(): стек порожній");
        int val = list.get(n - 1);
        list.removeAt(n - 1);
        return val;
    }

    // top() — повернути верхній елемент, не видаляючи його
    int top() const {
        int n = list.size();
        if (n == 0) throw runtime_error("Stack::top(): стек порожній");
        return list.get(n - 1);
    }

    bool isEmpty() const { return list.size() == 0; }
    int size() const { return list.size(); }

    // show() — вивести вміст стеку від вершини до низу
    void show() const {
        cout << "Stack (top -> bottom): ";
        int n = list.size();
        for (int i = n - 1; i >= 0; --i) {
            cout << list.get(i);
            if (i > 0) cout << " ";
        }
        cout << endl;
    }
};

// -------------------------
// Приклад використання
// -------------------------
int main() {
    try {
        Stack st(5);

        // Використовуємо set() як push()
        st.set(5);
        st.set(10);
        st.push(20); // той самий ефект — додає у стек

        cout << "Вміст стеку після додавання елементів:\n";
        st.show();
        cout << "Розмір стеку: " << st.size() << "\n";

        cout << "Зчитування елементів зі стеку: ";
        while (!st.isEmpty()) {
            int v = st.get(); // get() — зняти верхній елемент
            cout << v << " ";
        }
        cout << "\n";

        cout << "Після зчитування стек: ";
        st.show();

    } catch (const exception& e) {
        cerr << "Помилка: " << e.what() << endl;
    }

    return 0;
}
