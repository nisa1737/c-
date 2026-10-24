#include <iostream>

using namespace std;

// Global sabit (tum fonksiyonlarin disinda tanimli)
const double GLOBAL_MARKET_RISK_THRESHOLD = 0.05;

class Portfolio {
    int capacity;           // kac tane varlik var
    double *assetPrices;    // fiyatlari tutan dinamik dizinin adresi

public:
    // Bellek ayirir ve kullanicidan x tane fiyat alir
    void initialize(int x) {
        capacity = x;
        assetPrices = new double[x];
        for (int i = 0; i < capacity; i++) {
            cout << "Enter Asset Price " << i + 1 << ": ";
            cin >> assetPrices[i];
        }
    }

    // initialize'da ayrilan bellegi geri verir
    void cleanup() {
        delete[] assetPrices;
        cout << "[INFO] Released portfolio dynamic memory." << endl;
    }

    // Tum fiyatlarin toplamini dondurur
    double calculateTotalValue() {
        double total = 0;
        for (int i = 0; i < capacity; i++) {
            total = total + assetPrices[i];
        }
        return total;
    }

    // drawdown, global esikten buyukse true, degilse false dondurur
    bool exceedsRiskLimit(double drawdown) {
        if (drawdown > ::GLOBAL_MARKET_RISK_THRESHOLD)
            return true;
        else
            return false;
    }

    // Portfoy bilgilerini ekrana yazar
    void displayPortfolio() {
        cout << fixed;          // sayilari ondalikli yaz
        cout.precision(2);      // virgulden sonra 2 basamak

        cout << "Assets Tracked: " << capacity << "/" << capacity << endl;
        cout << "Prices: ";
        for (int i = 0; i < capacity; i++) {
            cout << "$" << assetPrices[i] << " ";
        }
        cout << endl;
        cout << "Total Portfolio Value: $" << calculateTotalValue() << endl;
    }
};

int main() {
    int n;
    double drawdown;

    cout << "Enter how many assets you would like to enter: ";
    cin >> n;

    Portfolio portfolio;
    portfolio.initialize(n);

    cout << "Enter the drawdown you have observed so far: ";
    cin >> drawdown;

    if (portfolio.exceedsRiskLimit(drawdown))
        cout << "[WARNING] Portfolio drawdown exceeds global risk limit ("
             << ::GLOBAL_MARKET_RISK_THRESHOLD * 100 << "%)!" << endl;
    else
        cout << "Portfolio risk is within acceptable parameters." << endl;

    portfolio.displayPortfolio();
    portfolio.cleanup();

    return 0;
}
