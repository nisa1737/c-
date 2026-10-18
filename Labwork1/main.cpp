#include <iostream>

using namespace std;

namespace Math {

class Calculator {
public:
    // Toplama
    int add(int a, int b) { return a + b; }
    double add(double a, double b) { return a + b; }

    // Cikarma
    int subtract(int a, int b) { return a - b; }
    double subtract(double a, double b) { return a - b; }

    // Carpma
    int multiply(int a, int b) { return a * b; }
    double multiply(double a, double b) { return a * b; }

    // Bolme (sifira bolme kontrolu main icinde yapiliyor)
    int divide(int a, int b) { return a / b; }
    double divide(double a, double b) { return a / b; }
};

} // namespace Math

int main() {
    Math::Calculator calc;

    int i1, i2;
    double d1, d2;
    char intOp, doubleOp;

    cout << "Enter two integer numbers: ";
    cin >> i1 >> i2;
    cout << "Enter two double numbers: ";
    cin >> d1 >> d2;
    cout << "Enter the desired operation to perform on integer numbers: ";
    cin >> intOp;
    cout << "Enter the desired operation to perform on double numbers: ";
    cin >> doubleOp;

    cout << "Results of the operations:" << endl;

    // Tam sayilar uzerinde islem (int surumleri cagrilir)
    switch (intOp) {
        case '+':
            cout << "Addition of " << i1 << " and " << i2 << " is: " << calc.add(i1, i2) << endl;
            break;
        case '-':
            cout << "Subtraction of " << i1 << " from " << i2 << " is: " << calc.subtract(i1, i2) << endl;
            break;
        case '*':
            cout << "Multiplication of " << i1 << " and " << i2 << " is: " << calc.multiply(i1, i2) << endl;
            break;
        case '/':
            if (i2 == 0) {
                cout << "Division by zero error!" << endl;
                return 1; // main'den return etmek programi sonlandirir
            }
            cout << "Division of " << i1 << " by " << i2 << " is: " << calc.divide(i1, i2) << endl;
            break;
        default:
            cout << "Invalid operator: " << intOp << endl;
    }

    // Ondalikli sayilar uzerinde islem (double surumleri cagrilir)
    switch (doubleOp) {
        case '+':
            cout << "Addition of " << d1 << " and " << d2 << " is: " << calc.add(d1, d2) << endl;
            break;
        case '-':
            cout << "Subtraction of " << d1 << " from " << d2 << " is: " << calc.subtract(d1, d2) << endl;
            break;
        case '*':
            cout << "Multiplication of " << d1 << " and " << d2 << " is: " << calc.multiply(d1, d2) << endl;
            break;
        case '/':
            if (d2 == 0.0) {
                cout << "Division by zero error!" << endl;
                return 1;
            }
            cout << "Division of " << d1 << " by " << d2 << " is: " << calc.divide(d1, d2) << endl;
            break;
        default:
            cout << "Invalid operator: " << doubleOp << endl;
    }

    return 0;
}
