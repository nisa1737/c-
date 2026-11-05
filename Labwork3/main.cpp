#include <iostream>

using namespace std;

class DeviceMonitor {
    int deviceID;
    int operationalStatus;
    char deviceName[30];    // sabit boyutlu karakter dizisi (en fazla 29 harf + '\0')

public:
    // Constructor: sadece bildirim, govdesi asagida (registerDevice'tan sonra)
    DeviceMonitor(int deviceID, int operationalStatus, const char *deviceName);

    // Durumu degistirir, zincirleme cagri icin nesnenin kendisini dondurur
    DeviceMonitor& setOperationalStatus(int operationalStatus) {
        this->operationalStatus = operationalStatus;
        return *this;
    }

    // Ismi harf harf kopyalar, zincirleme cagri icin nesnenin kendisini dondurur
    DeviceMonitor& setDeviceName(const char *deviceName) {
        int i;
        for (i = 0; i < 29 && deviceName[i] != '\0'; i++) {
            this->deviceName[i] = deviceName[i];
        }
        this->deviceName[i] = '\0';   // metnin bittigini gosteren isaret
        return *this;
    }

    // Cihaz bilgilerini ekrana yazar
    void displayInfo() {
        cout << "Device ID : " << deviceID << endl;
        cout << "Name      : " << deviceName << endl;
        cout << "Status    : " << operationalStatus << endl;
    }
};

// Global fonksiyon: kendisine verilen nesnenin bellek adresini yazar
void registerDevice(DeviceMonitor *device) {
    cout << "[Registry System] Device pointer registered at address: " << device << endl;
}

// Constructor'in govdesi: registerDevice'i cagirdigi icin onun altinda yazildi
DeviceMonitor::DeviceMonitor(int deviceID, int operationalStatus, const char *deviceName) {
    this->deviceID = deviceID;
    this->operationalStatus = operationalStatus;
    this->setDeviceName(deviceName);
    registerDevice(this);
}

int main() {
    int id1, id2, status1, status2;
    char name1[30], name2[30];

    cout << "Enter first deviceID: ";
    cin >> id1;
    cout << "Enter second deviceID: ";
    cin >> id2;
    cout << "Enter first deviceName: ";
    cin >> name1;
    cout << "Enter second deviceName: ";
    cin >> name2;
    cout << "Enter first deviceStatus: ";
    cin >> status1;
    cout << "Enter second deviceStatus: ";
    cin >> status2;
    cout << endl;

    // Iki nesne olusur, her birinde constructor calisir ve adres yazdirilir
    DeviceMonitor device1(id1, status1, name1);
    DeviceMonitor device2(id2, status2, name2);
    cout << endl;

    cout << "--- Initial States ---" << endl;
    device1.displayInfo();
    cout << endl;
    device2.displayInfo();
    cout << endl;

    char newName[30];
    int newStatus;

    cout << "Enter new deviceName for first instance: ";
    cin >> newName;
    cout << "Enter new deviceStatus for first instance: ";
    cin >> newStatus;
    cout << endl;

    // Zincirleme cagri: iki degisiklik tek satirda, ayni nesne uzerinde
    device1.setDeviceName(newName).setOperationalStatus(newStatus);

    cout << "--- State After Method Chaining ---" << endl;
    device1.displayInfo();

    return 0;
}
