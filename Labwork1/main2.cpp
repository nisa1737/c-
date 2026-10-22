#include <iostream>

using namespace std;

template <class T>
struct TelemetryProcessor {
    T calibrationFactor;

    // Deger ile aktarim: value, gonderilen degiskenin KOPYASI
    void testPassByValue(T value) {
        value = value * calibrationFactor;
        cout << "[Inside testPassByValue] Modified copy inside function: " << value << endl;
    }

    // Referans ile aktarim: value, gonderilen degiskenin KENDISI
    void testPassByReference(T &value) {
        value = value * calibrationFactor;
        cout << "[Inside testPassByReference] Modified original via reference: " << value << endl;
    }
};

int main() {
    TelemetryProcessor<double> processor;   // T = double
    double userReading;

    cout << "Enter the calibration factor: ";
    cin >> processor.calibrationFactor;
    cout << "Enter a raw sensor reading value (e.g., 25.5): ";
    cin >> userReading;
    cout << endl;

    // 1) Pass-by-value
    cout << "Before pass-by-value function, userReading = " << userReading << endl;
    processor.testPassByValue(userReading);
    cout << "After pass-by-value function, userReading = " << userReading << " (Unchanged!)" << endl;
    cout << endl;

    // 2) Pass-by-reference
    cout << "Before pass-by-reference function, userReading = " << userReading << endl;
    processor.testPassByReference(userReading);
    cout << "After pass-by-reference function, userReading = " << userReading << " (Changed & Persisted!)" << endl;

    return 0;
}
