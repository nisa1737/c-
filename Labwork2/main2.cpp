#include <iostream>

using namespace std;

class GreenhouseMonitor {
    double maxTempThreshold;   // sicaklik siniri (private)

public:
    // Gelen degeri sinir olarak kaydeder
    void setThreshold(double t) {
        maxTempThreshold = t;
    }

    // Dizide sinirdan buyuk bir sicaklik varsa uyari yazar ve true dondurur
    bool checkThreshold(const double *temps, int size) {
        for (int i = 0; i < size; i++) {
            if (temps[i] > maxTempThreshold) {
                cout << "[WARNING] At least one sensor exceeds limit " << maxTempThreshold << "!" << endl;
                return true;    // fonksiyon burada biter
            }
        }
        return false;           // hicbiri siniri asmadi
    }
};

int main() {
    GreenhouseMonitor monitor;
    double threshold;
    int n;

    cout << "Enter the maximum acceptable temperature value: ";
    cin >> threshold;
    monitor.setThreshold(threshold);

    cout << "Enter number of temperatures: ";
    cin >> n;

    // Dinamik dizi: n tane sicaklik icin yer ayir
    double *temperatures = new double[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter temperature value: " << i + 1 << ": ";
        cin >> temperatures[i];
    }

    // Diziyi ve boyutunu fonksiyona gonder, donen degere gore mesaj yaz
    if (monitor.checkThreshold(temperatures, n))
        cout << "[ALERT] Greenhouse climate regulation required!" << endl;
    else
        cout << "[OK] All greenhouse temperatures are within optimal range." << endl;

    // Dinamik olarak ayrilan bellegi geri ver
    delete[] temperatures;

    return 0;
}
