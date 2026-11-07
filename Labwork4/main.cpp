#include <iostream>

using namespace std;

// Global oyun dengesi sabiti
const double MAX_GLOBAL_DAMAGE = 200;

// Bir metnin kac harf oldugunu sayar ('\0' gorene kadar)
int textLength(const char *text) {
    int length = 0;
    while (text[length] != '\0')
        length++;
    return length;
}

// source metnini harf harf destination'a kopyalar, sonuna '\0' koyar
void copyText(char *destination, const char *source) {
    int i;
    for (i = 0; source[i] != '\0'; i++)
        destination[i] = source[i];
    destination[i] = '\0';
}

class EnchantedWeapon {
    int weaponID;
    char *weaponName;     // dinamik olarak ayrilacak metin
    double baseDamage;
    double durability;
    char *loreScroll;     // dinamik olarak ayrilacak metin

public:
    // Parametre isimleri degisken isimleriyle ayni, bu yuzden this-> kullaniliyor
    EnchantedWeapon(int weaponID, const char *weaponName, double baseDamage,
                    double durability, const char *loreScroll) {
        this->weaponID = weaponID;
        this->baseDamage = baseDamage;
        this->durability = durability;

        // Isim icin tam gerektigi kadar yer ayir (+1 '\0' icin), sonra kopyala
        this->weaponName = new char[textLength(weaponName) + 1];
        copyText(this->weaponName, weaponName);

        // Hikaye metni icin ayni islem
        this->loreScroll = new char[textLength(loreScroll) + 1];
        copyText(this->loreScroll, loreScroll);
    }

    // Destructor: constructor'da ayrilan iki metni de geri verir
    ~EnchantedWeapon() {
        delete[] weaponName;
        delete[] loreScroll;
        cout << "[Destructor Executed] Weapon ID " << weaponID << " dynamic memory freed." << endl;
    }

    // Hasari arttirir, 200'u gecerse uyarir ve 200'e sabitler
    EnchantedWeapon& upgradeDamage(double amount) {
        this->baseDamage = this->baseDamage + amount;
        if (this->baseDamage > ::MAX_GLOBAL_DAMAGE) {
            cout << "\"This weapon is pretty overpowered!\"" << endl;
            this->baseDamage = ::MAX_GLOBAL_DAMAGE;
        }
        return *this;
    }

    // Dayanikliligi arttirir, en fazla 100 olabilir
    EnchantedWeapon& repairWeapon(double amount) {
        this->durability = this->durability + amount;
        if (this->durability > 100)
            this->durability = 100;
        return *this;
    }

    // Silaha hangi elementin islendigini yazar
    EnchantedWeapon& infuseElement(const char *element) {
        cout << "Weapon " << this->weaponName << " successfully infused with "
             << element << " magic!" << endl;
        return *this;
    }

    // Bileme bonusu kadar hasari arttirir, 200'u gecerse uyarir ve 200'e sabitler
    EnchantedWeapon& sharpenEdge(double bonus) {
        this->baseDamage = this->baseDamage + bonus;
        if (this->baseDamage > ::MAX_GLOBAL_DAMAGE) {
            cout << "\"This weapon is pretty overpowered!\"" << endl;
            this->baseDamage = ::MAX_GLOBAL_DAMAGE;
        }
        return *this;
    }

    // Silah bilgilerini yazar (hikaye metni haric)
    void displayStats() {
        cout << "Weapon ID: " << weaponID << " | Name: " << weaponName
             << " | Damage: " << baseDamage << " | Durability: " << durability << "%" << endl;
    }

    // friend: class'in uyesi degil ama private degiskenlere erisebilir
    friend void inspectWeaponLore(const EnchantedWeapon &weapon);
};

// friend fonksiyonun govdesi (basinda EnchantedWeapon:: yok, cunku uye degil)
void inspectWeaponLore(const EnchantedWeapon &weapon) {
    cout << "Lore Scroll Content: " << weapon.loreScroll << endl;
}

int main() {
    int weaponID;
    char weaponName[50];
    double baseDamage, durability;
    char loreScroll[200];
    char element[30];

    cout << "--- RPG Weapon Customization System ---" << endl;
    cout << "Enter Weapon ID: ";
    cin >> weaponID;
    cin.ignore();                       // sayidan sonra kalan Enter'i at
    cout << "Enter Weapon Name: ";
    cin.getline(weaponName, 50);        // bosluklu da olsa butun satiri al
    cout << "Enter Initial Base Damage: ";
    cin >> baseDamage;
    cout << "Enter Initial Durability (0-100): ";
    cin >> durability;
    cin.ignore();                       // sayidan sonra kalan Enter'i at
    cout << "Enter Weapon Lore Description: ";
    cin.getline(loreScroll, 200);       // bosluklu butun satiri al
    cout << "Enter Elemental Infusion Type (e.g., Fire, Ice): ";
    cin >> element;
    cout << endl;

    EnchantedWeapon weapon(weaponID, weaponName, baseDamage, durability, loreScroll);

    cout << "--- Initial Weapon Status ---" << endl;
    weapon.displayStats();
    cout << endl;

    double upgradeAmount, repairAmount, sharpenAmount;

    cout << "Enter Damage Upgrade Amount: ";
    cin >> upgradeAmount;
    cout << "Enter Repair Amount: ";
    cin >> repairAmount;
    cout << "Enter Sharpening Bonus Amount: ";
    cin >> sharpenAmount;
    cout << endl;

    cout << "Executing Method Chaining.." << endl;
    weapon.upgradeDamage(upgradeAmount).repairWeapon(repairAmount).sharpenEdge(sharpenAmount).infuseElement(element);
    cout << endl;

    cout << "--- Updated Weapon Status After Chaining ---" << endl;
    weapon.displayStats();
    cout << endl;

    cout << "--- Weapon Lore ---" << endl;
    inspectWeaponLore(weapon);          // friend fonksiyon: nokta ile degil, dogrudan cagrilir
    cout << endl;

    return 0;
}   // main biter, weapon yok olur, destructor calisir
