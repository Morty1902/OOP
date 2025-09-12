#include <iostream>
#include <conio.h>
#include <windows.h>
#include <math.h>
using namespace std;

double calculateB(double x, double y, double z) {
    double b1= 2 * z + cos(pow(fabs(y - 3 * x), 1.0 / 3.0));
    double b2= 2.1 + pow(sin(pow(fabs(pow(z, 3) - y), 0.2)), 2);
    double b3 = pow(log(fabs((z-x) / (z+y))), 2);
    double result_b = (b1 / b2) + b3;
    return result_b;
}

double calculateA(double x, double y, double z, double result_b) {
    double a1 = pow(fabs(x), 0.43);
    double a2 = exp(y-x) + pow(sqrt(fabs(pow(y, 2)+result_b)), 0.22);
    double a3 = (1 + pow(x, 2)) * fabs(y-pow(tan(z), 2));
    double result_a = a1 + (a2 / a3);
    return result_a;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    double y, z;
    y= 0.47 * 2;
    z= -1.32 * 2;

    int mode;
    do {
        cout << "Оберіть режим: 1 - обчислення зі статичними даними, 2 - табулювання функції, 0 - вихід: ";
        cin >> mode;
        switch (mode) {
            case 1: {
                double x = 0.48 * 2;
                double b = calculateB(x, y, z);
                double a = calculateA(x, y, z, b);
                cout << "Результат обчислення виразу b: " << b << endl;
                cout << "Результат обчислення виразу a: " << a << endl;
                break;
            }
            case 2: {
                double x_start, x_end, x_step;
                cout << "Введіть початкове значення х : ";
                cin >> x_start;
                cout << "Введіть кінцеве значення х : ";
                cin >> x_end;
                cout << "Введіть крок : ";
                cin >> x_step;

                for (double x = x_start; x <= x_end; x += x_step) {
                    double b = calculateB(x, y, z);
                    double a = calculateA(x, y, z, b);
                    if (fabs(x) < 1e-12) x = 0;
                    cout << "x=" << x << "  b=" << b << "  a=" << a << endl;
                }
                break;
            }
            case 0:
                cout << "Вихід" << endl;
                break;
            default:
                cout << "Невірний вибір" << endl;
        }
    } while (mode != 0);

    return 0;  
}  