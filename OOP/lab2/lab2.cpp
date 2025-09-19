#include <iostream>
#include <stdexcept>
using namespace std;

class List {
private:
    int* data;         // ��������� ����� ��� ��������� ��������
    int capacity;      // �������� ��'�� ������
    int length;        // ������� ������� ��������

    // ����������� ���������� minCapacity
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
    // ����������� (�� �������������)
    List(int initCap = 10) : data(nullptr), capacity(0), length(0) {
        if (initCap > 0) {
            data = new int[initCap];
            capacity = initCap;
        }
    }

    // ����������� ��������� (������� ���������)
    List(const List& other) : data(nullptr), capacity(0), length(0) {
        capacity = other.capacity;
        length = other.length;
        if (capacity > 0) {
            data = new int[capacity];
            for (int i = 0; i < length; ++i) data[i] = other.data[i];
        }
    }

    // �������� ��������� (Rule of Three)
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

    // ����������
    ~List() { delete[] data; }

    // set(index, value) � ���������� �������� �� �������� (0-based)
    void set(int index, int value) {
        if (index < 0 || index >= length) {
            throw out_of_range("List::set(): invalid index");
        }
        data[index] = value;
    }

    // get(index) � ��������� �������� �� ��������
    int get(int index) const {
        if (index < 0 || index >= length) {
            throw out_of_range("List::get(): invalid index");
        }
        return data[index];
    }

    // show() � ������� ���� ������
    void show() const {
        cout << "[";
        for (int i = 0; i < length; ++i) {
            if (i) cout << ", ";
            cout << data[i];
        }
        cout << "]";
    }

    // �������� ������, �� ������������ ��� ����� � ������
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
// ���� ���� (Stack)
// -------------------------
class Stack {
private:
    List list;  // ���������� � ���� ������ ��'��� ������

public:
    // �����������: ����� ������ ��������� ������ ��� ����������� ������
    Stack(int initCap = 10) : list(initCap) {}

    // set(value) � � ����� ������� ����������� �� push(value)
    void set(int value) { push(value); }

    // get() � ��������� (� ��������) ������ ������� � pop()
    int get() { return pop(); }

    // push(value) � ������ ������� � ����
    void push(int value) { list.append(value); }

    // pop() � ����� ������ ������� � ��������� ����
    int pop() {
        int n = list.size();
        if (n == 0) throw runtime_error("Stack::pop(): ���� �������");
        int val = list.get(n - 1);
        list.removeAt(n - 1);
        return val;
    }

    // top() � ��������� ������ �������, �� ��������� ����
    int top() const {
        int n = list.size();
        if (n == 0) throw runtime_error("Stack::top(): ���� �������");
        return list.get(n - 1);
    }

    bool isEmpty() const { return list.size() == 0; }
    int size() const { return list.size(); }

    // show() � ������� ���� ����� �� ������� �� ����
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
// ������� ������������
// -------------------------
int main() {
    try {
        Stack st(5);

        // ������������� set() �� push()
        st.set(5);
        st.set(10);
        st.push(20); // ��� ����� ����� � ���� � ����

        cout << "���� ����� ���� ��������� ��������:\n";
        st.show();
        cout << "����� �����: " << st.size() << "\n";

        cout << "���������� �������� � �����: ";
        while (!st.isEmpty()) {
            int v = st.get(); // get() � ����� ������ �������
            cout << v << " ";
        }
        cout << "\n";

        cout << "ϳ��� ���������� ����: ";
        st.show();

    } catch (const exception& e) {
        cerr << "�������: " << e.what() << endl;
    }

    return 0;
}
