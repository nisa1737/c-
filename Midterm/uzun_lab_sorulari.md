# CENG241 – Lab Tarzı Uzun Sorular (Cümle Cümle Çözüm)

Labwork'ler gibi **uzun** iki soru. Her sorunun altında:

1. **Kod** (çalıştırıldı, bellek kontrolünden geçti)
2. **Cümle cümle çözüm:** sorudaki her cümlenin koda **nasıl** dönüştüğü
3. **`main` ↔ örnek çıktı:** çıktıdaki her satırın kodun neresinden geldiği

| Soru | İçindeki konular |
|---|---|
| 1 – StepTracker | namespace, `string`, constructor'da `new int[]`, destructor'da `delete[]`, `this->`, `const` fonksiyon, `bool`, global sabit ve `::`, friend fonksiyon |
| 2 – Spaceship | iki constructor (overloading), varsayılan parametre, `char*` ile dinamik isim, `this->`, destructor, zincirleme, global sabit ve `::`, friend `bool` fonksiyon |

**Önce soruyu kendin çözmeyi dene, sonra koda ve açıklamaya bak.**

---
---

# SORU 1 – StepTracker

**1)** Write a C++ program for a fitness application that tracks the daily steps of people. To achieve this task, first implement the following class inside a namespace called **Health**:

```
+--------------------------------------------------------------------+
|                            StepTracker                             |
+--------------------------------------------------------------------+
| - ownerName: string                                                |
| - days: int                                                        |
| - steps: int*                                                      |
+--------------------------------------------------------------------+
| + StepTracker(string, int)                                         |
| + ~StepTracker()                                                   |
| + recordSteps(): void                                              |
| + totalSteps(): int                                                |
| + averageSteps(): double                                           |
| + reachedGoal(): bool                                              |
| + displaySummary(): void                                           |
| + compareTrackers(const StepTracker&, const StepTracker&): void    |  <-- friend
+--------------------------------------------------------------------+
```

The constructor StepTracker(string, int) will set the owner's name and the number of days (the parameter names must be the same as the data members, so you have to use the **this pointer**) and **dynamically allocate** an integer array for the steps of each day, setting all elements to 0. The destructor will **free the dynamically allocated memory** and print `[INFO] Memory of <name> released.`

recordSteps() will let the user enter the number of steps for each day into the steps array. totalSteps() will return the total number of steps, and averageSteps() will return the average number of steps per day. reachedGoal() will return **True** if the average is greater than or equal to a **globally declared constant** named **DAILY_GOAL** (set it to 8000), and **False** otherwise; to access this constant you have to use the **unary scope resolution operator**. displaySummary() will display the information of the tracker as in the sample run. The functions that do not change the object must be **const**. Finally, a **friend function** named compareTrackers() will compare the total steps of two trackers and print who walked more (or that they walked the same).

After implementing the class, in the main function, ask the user the names and the number of days of two people, create two StepTracker instances, record their steps, display their summaries, and compare them.

**Sample Run:**

```
Enter first person's name and number of days: Ayse 3
Enter second person's name and number of days: Mehmet 2

Day 1 steps for Ayse: 9000
Day 2 steps for Ayse: 8500
Day 3 steps for Ayse: 10000
Day 1 steps for Mehmet: 6000
Day 2 steps for Mehmet: 7500

--- Summary of Ayse ---
Days tracked: 3
Total steps: 27500
Average steps: 9166.67
Daily goal (8000) reached!

--- Summary of Mehmet ---
Days tracked: 2
Total steps: 13500
Average steps: 6750
Daily goal (8000) not reached.

Ayse walked more than Mehmet.

[INFO] Memory of Mehmet released.
[INFO] Memory of Ayse released.
```

---

## Kod

```cpp
#include <iostream>
#include <string>
using namespace std;

const int DAILY_GOAL = 8000;

namespace Health {

class StepTracker {
    string ownerName;
    int days;
    int *steps;

public:
    StepTracker(string ownerName, int days) {
        this->ownerName = ownerName;
        this->days = days;
        steps = new int[days];
        for (int i = 0; i < days; i++)
            steps[i] = 0;
    }

    ~StepTracker() {
        delete[] steps;
        cout << "[INFO] Memory of " << ownerName << " released." << endl;
    }

    void recordSteps() {
        for (int i = 0; i < days; i++) {
            cout << "Day " << i + 1 << " steps for " << ownerName << ": ";
            cin >> steps[i];
        }
    }

    int totalSteps() const {
        int total = 0;
        for (int i = 0; i < days; i++)
            total += steps[i];
        return total;
    }

    double averageSteps() const {
        double total = totalSteps();
        return total / days;
    }

    bool reachedGoal() const {
        if (averageSteps() >= ::DAILY_GOAL)
            return true;
        else
            return false;
    }

    void displaySummary() const {
        cout << "--- Summary of " << ownerName << " ---" << endl;
        cout << "Days tracked: " << days << endl;
        cout << "Total steps: " << totalSteps() << endl;
        cout << "Average steps: " << averageSteps() << endl;
        if (reachedGoal())
            cout << "Daily goal (" << ::DAILY_GOAL << ") reached!" << endl;
        else
            cout << "Daily goal (" << ::DAILY_GOAL << ") not reached." << endl;
    }

    friend void compareTrackers(const StepTracker &t1, const StepTracker &t2);
};

void compareTrackers(const StepTracker &t1, const StepTracker &t2) {
    if (t1.totalSteps() > t2.totalSteps())
        cout << t1.ownerName << " walked more than " << t2.ownerName << "." << endl;
    else if (t2.totalSteps() > t1.totalSteps())
        cout << t2.ownerName << " walked more than " << t1.ownerName << "." << endl;
    else
        cout << t1.ownerName << " and " << t2.ownerName << " walked the same." << endl;
}

} // namespace Health

int main() {
    string name1, name2;
    int days1, days2;

    cout << "Enter first person's name and number of days: ";
    cin >> name1 >> days1;
    cout << "Enter second person's name and number of days: ";
    cin >> name2 >> days2;

    Health::StepTracker t1(name1, days1);
    Health::StepTracker t2(name2, days2);

    cout << endl;
    t1.recordSteps();
    t2.recordSteps();

    cout << endl;
    t1.displaySummary();
    cout << endl;
    t2.displaySummary();

    cout << endl;
    Health::compareTrackers(t1, t2);
    cout << endl;

    return 0;
}
```

---

## Cümle cümle çözüm

### 1) "implement the following class inside a namespace called **Health**"

```cpp
namespace Health {
class StepTracker { ... };
void compareTrackers(...) { ... }
}
```

- Sınıf `namespace Health { ... }` bloğunun **içine** yazılır (Labwork 1'deki `Math` gibi).
- Friend fonksiyonun gövdesini de namespace'in **içine** yazdık; böylece `main`'den `Health::compareTrackers(...)` diye çağrılabiliyor.
- `main`'de nesne oluştururken: `Health::StepTracker t1(...)`.

### 2) UML tablosu → değişkenler

| Tabloda | Kodda | Neden? |
|---|---|---|
| `- ownerName: string` | `string ownerName;` | `-` → private; `string` için `#include <string>` |
| `- days: int` | `int days;` | |
| `- steps: int*` | `int *steps;` | `*` → adres tutacak; dizi için yer `new` ile ayrılacak |

### 3) "the parameter names must be the same as the data members, so you have to use the this pointer"

```cpp
StepTracker(string ownerName, int days) {
    this->ownerName = ownerName;
    this->days = days;
```

Parametreler (`ownerName`, `days`) değişkenlerle **aynı isimde**. `this->ownerName` = nesnenin değişkeni, `ownerName` = parametre. `this->` yazmasaydık parametre kendine atanırdı.

### 4) "dynamically allocate an integer array for the steps of each day, setting all elements to 0"

```cpp
    steps = new int[days];
    for (int i = 0; i < days; i++)
        steps[i] = 0;
}
```

- **"dynamically allocate"** → `new`. Gün sayısı kullanıcıdan geldiği için boyut önceden belli değil.
- `steps` zaten `int *steps;` olarak tanımlı; burada **yıldız tekrar yazılmaz**.
- **"setting all elements to 0"** → döngüyle hepsine 0.

### 5) "The destructor will free the dynamically allocated memory and print ..."

```cpp
~StepTracker() {
    delete[] steps;
    cout << "[INFO] Memory of " << ownerName << " released." << endl;
}
```

- **"free the memory"** → `delete[]` (dizi olduğu için köşeli parantezli).
- Mesaj soruda verildiği gibi, **birebir aynı**.

### 6) "recordSteps() will let the user enter the number of steps for each day"

```cpp
void recordSteps() {
    for (int i = 0; i < days; i++) {
        cout << "Day " << i + 1 << " steps for " << ownerName << ": ";
        cin >> steps[i];
    }
}
```

- "for each day" → `days` kere dönen döngü.
- "let the user enter" → `cin`.
- Ekranda gün numarası 1'den başlıyor ama dizi 0'dan; bu yüzden `i + 1`.
- Parametre yok, çünkü `days` ve `steps` zaten nesnenin içinde.

### 7) "totalSteps() will return the total number of steps"

```cpp
int totalSteps() const {
    int total = 0;
    for (int i = 0; i < days; i++)
        total += steps[i];
    return total;
}
```

- **"return"** + tablodaki `: int` → dönüş tipi `int`.
- **"functions that do not change the object must be const"** → sadece okuduğu için sonuna `const`.

### 8) "averageSteps() will return the average number of steps per day"

```cpp
double averageSteps() const {
    double total = totalSteps();
    return total / days;
}
```

- Tabloda `: double` → ortalama küsuratlı olabilir (27500 / 3 = 9166.67).
- `total` **double** yapıldı. İki int bölünseydi küsurat atılırdı: 27500 / 3 = 9166.
- Kendi sınıfının fonksiyonunu (`totalSteps()`) doğrudan çağırabiliyor.

### 9) "reachedGoal() will return True if the average is greater than or equal to a globally declared constant named DAILY_GOAL (set it to 8000) ... use the unary scope resolution operator"

```cpp
const int DAILY_GOAL = 8000;            // dosyanin en ustunde, her seyin disinda
```

```cpp
bool reachedGoal() const {
    if (averageSteps() >= ::DAILY_GOAL)
        return true;
    else
        return false;
}
```

| Cümledeki ifade | Kodda |
|---|---|
| "return True / False" | dönüş tipi `bool` |
| "greater than or equal" | `>=` |
| "globally declared constant" | sınıfın ve namespace'in **dışında** `const int DAILY_GOAL = 8000;` |
| "unary scope resolution operator" | `::DAILY_GOAL` |

### 10) "displaySummary() will display the information of the tracker as in the sample run"

```cpp
void displaySummary() const {
    cout << "--- Summary of " << ownerName << " ---" << endl;
    cout << "Days tracked: " << days << endl;
    cout << "Total steps: " << totalSteps() << endl;
    cout << "Average steps: " << averageSteps() << endl;
    if (reachedGoal())
        cout << "Daily goal (" << ::DAILY_GOAL << ") reached!" << endl;
    else
        cout << "Daily goal (" << ::DAILY_GOAL << ") not reached." << endl;
}
```

- **"as in the sample run"** → yazıları örnek çıktıdan **birebir** kopyala.
- Hesapları tekrar yazmadık; daha önce yazdığımız fonksiyonları çağırdık.
- `if (reachedGoal())`: fonksiyon `bool` döndürdüğü için doğrudan `if` içinde.
- `const` bir fonksiyonun içinden sadece `const` fonksiyonlar çağrılabilir; `totalSteps`, `averageSteps`, `reachedGoal` bu yüzden de `const`.

### 11) "a friend function named compareTrackers() will compare the total steps of two trackers and print who walked more"

Sınıfın içinde (izin):

```cpp
friend void compareTrackers(const StepTracker &t1, const StepTracker &t2);
```

Sınıfın dışında, namespace'in içinde (gövde):

```cpp
void compareTrackers(const StepTracker &t1, const StepTracker &t2) {
    if (t1.totalSteps() > t2.totalSteps())
        cout << t1.ownerName << " walked more than " << t2.ownerName << "." << endl;
    else if (t2.totalSteps() > t1.totalSteps())
        cout << t2.ownerName << " walked more than " << t1.ownerName << "." << endl;
    else
        cout << t1.ownerName << " and " << t2.ownerName << " walked the same." << endl;
}
```

| Cümledeki ifade | Kodda |
|---|---|
| "friend function" | içeride `friend ...;`, gövde dışarıda, başında `StepTracker::` **yok** |
| tablodaki `(const StepTracker&, const StepTracker&)` | parametreler **aynen** böyle |
| tablodaki `: void` + "print" | bir şey döndürmüyor, ekrana yazıyor |
| "two trackers" | iki parametre: friend'in `this`'i yok |

**Neden friend?** `ownerName` private. Friend olmasaydı `t1.ownerName` yazılamazdı.

### 12) `main`: "ask the user the names and the number of days of two people, create two instances, record, display, compare"

| Cümledeki ifade | `main`'de |
|---|---|
| "ask the user the names and the number of days" | `cin >> name1 >> days1;` (iki kişi için) |
| "create two StepTracker instances" | `Health::StepTracker t1(name1, days1);` ve `t2` |
| "record their steps" | `t1.recordSteps(); t2.recordSteps();` |
| "display their summaries" | `t1.displaySummary(); t2.displaySummary();` |
| "compare them" | `Health::compareTrackers(t1, t2);` (friend: nokta yok) |

---

## `main` ↔ örnek çıktı

| Örnek çıktıdaki satır | Kodun neresi? |
|---|---|
| `Enter first person's name ...: Ayse 3` | `main`: `cout` + `cin` |
| `Day 1 steps for Ayse: 9000` ... | `recordSteps()` içindeki döngü |
| `--- Summary of Ayse ---` ... `Daily goal (8000) reached!` | `displaySummary()` |
| `Ayse walked more than Mehmet.` | friend `compareTrackers()` |
| `[INFO] Memory of Mehmet released.` | **destructor** (t2 sonra doğdu → **önce** ölür) |
| `[INFO] Memory of Ayse released.` | destructor (t1) |

**Hesaplar:** Ayse: 9000 + 8500 + 10000 = 27500, 27500 / 3 = 9166.67 ≥ 8000 → reached. Mehmet: 6000 + 7500 = 13500, 13500 / 2 = 6750 < 8000 → not reached.

---
---

# SORU 2 – Spaceship

**2)** Write a C++ program for the mission control system of a space agency. To achieve this task, first implement the following class:

```
+----------------------------------------------------------------+
|                           Spaceship                            |
+----------------------------------------------------------------+
| - shipID: int                                                  |
| - shipName: char*                                              |
| - fuel: double                                                 |
| - crew: int                                                    |
+----------------------------------------------------------------+
| + Spaceship()                                                  |
| + Spaceship(int, const char*, double, int = 1)                 |
| + ~Spaceship()                                                 |
| + refuel(double): Spaceship&                                   |
| + travel(double): Spaceship&                                   |
| + addCrew(int): Spaceship&                                     |
| + displayStatus(): void                                        |
| + hasMoreFuel(const Spaceship&, const Spaceship&): bool        |  <-- friend
+----------------------------------------------------------------+
```

The class has **two overloaded constructors**. The **default constructor** sets the ID, the fuel and the crew to 0 and the name to "Unknown". The **parameterized constructor** sets all data members (the parameter names must be the same as the data members, so you have to use the **this pointer**); the crew has a **default value of 1**. Both constructors must **dynamically allocate** memory for the ship name, and the destructor must print `[Destructor] Ship <name> (ID <id>) memory freed.` and **release the memory**.

refuel() increases the fuel. The fuel cannot exceed a **global constant** named **MAX_FUEL** (set it to 100); if it does, print `Tank is full! Fuel set to 100.` and set the fuel to MAX_FUEL (use the **unary scope resolution operator**). travel() uses **1 unit of fuel for every 10 km**. If there is not enough fuel, it prints `Not enough fuel to travel X km!` and the ship does not travel; otherwise it decreases the fuel and prints `<name> traveled X km.` addCrew() increases the number of crew members. refuel(), travel() and addCrew() must use the this pointer and must be **chainable**. displayStatus() displays the ship's information. Finally, a **friend function** hasMoreFuel() returns True if the first ship has more fuel than the second one.

In the main function, create a **backup** ship with the default constructor, a **scout** ship (ID 7, name "Scout", fuel 30) **without giving the crew**, and a ship with the information taken from the user. Display the initial status of the three ships. Then take a refuel amount, two distances and the number of new crew members from the user, and perform the mission on the user's ship **in a single line using function chaining** in this order: refuel, travel (first distance), addCrew, travel (second distance). Display the final status of the ship and compare its fuel with the scout ship.

**Sample Run:**

```
Enter ship ID, name, fuel and crew: 42 Voyager 60 3

--- Initial Status ---
ID: 0 | Name: Unknown | Fuel: 0 | Crew: 0
ID: 7 | Name: Scout | Fuel: 30 | Crew: 1
ID: 42 | Name: Voyager | Fuel: 60 | Crew: 3

Enter refuel amount, two distances and new crew members: 55 300 900 2

--- Mission ---
Tank is full! Fuel set to 100.
Voyager traveled 300 km.
Not enough fuel to travel 900 km!

--- Final Status ---
ID: 42 | Name: Voyager | Fuel: 70 | Crew: 5

Voyager has more fuel than Scout.

[Destructor] Ship Voyager (ID 42) memory freed.
[Destructor] Ship Scout (ID 7) memory freed.
[Destructor] Ship Unknown (ID 0) memory freed.
```

---

## Kod

```cpp
#include <iostream>
using namespace std;

const double MAX_FUEL = 100;

// Bir metnin kac harf oldugunu sayar
int textLength(const char *text) {
    int length = 0;
    while (text[length] != '\0')
        length++;
    return length;
}

// source metnini destination'a kopyalar, sonuna '\0' koyar
void copyText(char *destination, const char *source) {
    int i;
    for (i = 0; source[i] != '\0'; i++)
        destination[i] = source[i];
    destination[i] = '\0';
}

class Spaceship {
    int shipID;
    char *shipName;
    double fuel;
    int crew;

public:
    Spaceship() : shipID(0), fuel(0), crew(0) {
        shipName = new char[textLength("Unknown") + 1];
        copyText(shipName, "Unknown");
    }

    Spaceship(int shipID, const char *shipName, double fuel, int crew = 1) {
        this->shipID = shipID;
        this->fuel = fuel;
        this->crew = crew;
        this->shipName = new char[textLength(shipName) + 1];
        copyText(this->shipName, shipName);
    }

    ~Spaceship() {
        cout << "[Destructor] Ship " << shipName << " (ID " << shipID << ") memory freed." << endl;
        delete[] shipName;
    }

    Spaceship& refuel(double amount) {
        this->fuel += amount;
        if (this->fuel > ::MAX_FUEL) {
            cout << "Tank is full! Fuel set to " << ::MAX_FUEL << "." << endl;
            this->fuel = ::MAX_FUEL;
        }
        return *this;
    }

    Spaceship& travel(double distance) {
        double needed = distance / 10;
        if (needed > this->fuel)
            cout << "Not enough fuel to travel " << distance << " km!" << endl;
        else {
            this->fuel -= needed;
            cout << this->shipName << " traveled " << distance << " km." << endl;
        }
        return *this;
    }

    Spaceship& addCrew(int count) {
        this->crew += count;
        return *this;
    }

    void displayStatus() const {
        cout << "ID: " << shipID << " | Name: " << shipName
             << " | Fuel: " << fuel << " | Crew: " << crew << endl;
    }

    friend bool hasMoreFuel(const Spaceship &s1, const Spaceship &s2);
};

bool hasMoreFuel(const Spaceship &s1, const Spaceship &s2) {
    return s1.fuel > s2.fuel;
}

int main() {
    int id, crew;
    char name[30];
    double fuel;

    cout << "Enter ship ID, name, fuel and crew: ";
    cin >> id >> name >> fuel >> crew;

    Spaceship backup;
    Spaceship scout(7, "Scout", 30);
    Spaceship ship(id, name, fuel, crew);

    cout << endl << "--- Initial Status ---" << endl;
    backup.displayStatus();
    scout.displayStatus();
    ship.displayStatus();

    double fuelAmount, d1, d2;
    int newCrew;
    cout << endl << "Enter refuel amount, two distances and new crew members: ";
    cin >> fuelAmount >> d1 >> d2 >> newCrew;

    cout << endl << "--- Mission ---" << endl;
    ship.refuel(fuelAmount).travel(d1).addCrew(newCrew).travel(d2);

    cout << endl << "--- Final Status ---" << endl;
    ship.displayStatus();

    cout << endl;
    if (hasMoreFuel(ship, scout))
        cout << name << " has more fuel than Scout." << endl;
    else
        cout << "Scout has more fuel than " << name << "." << endl;
    cout << endl;

    return 0;
}
```

---

## Cümle cümle çözüm

### 1) UML tablosu → değişkenler

| Tabloda | Kodda | Neden? |
|---|---|---|
| `- shipID: int` | `int shipID;` | private |
| `- shipName: char*` | `char *shipName;` | isim için yer `new` ile ayrılacak |
| `- fuel: double` | `double fuel;` | |
| `- crew: int` | `int crew;` | |

### 2) "a global constant named MAX_FUEL (set it to 100)"

```cpp
const double MAX_FUEL = 100;
```

Sınıfın **dışında**, dosyanın en üstünde. `double`, çünkü `fuel` ile karşılaştırılacak.

### 3) "Both constructors must dynamically allocate memory for the ship name"

İki constructor da aynı işi (harf say → yer ayır → kopyala) yapacak. Aynı kodu iki kere yazmamak için Labwork 4'teki iki yardımcı fonksiyonu kullandık:

```cpp
int textLength(const char *text) { ... }                  // harfleri sayar
void copyText(char *destination, const char *source) { ... }  // kopyalar, sonuna '\0' koyar
```

Bunlar soruda istenmiyor; işi kolaylaştırmak için **bizim** eklediğimiz global fonksiyonlar. İstersen döngüleri doğrudan constructor'ların içine de yazabilirsin.

### 4) "The default constructor sets the ID, the fuel and the crew to 0 and the name to "Unknown""

```cpp
Spaceship() : shipID(0), fuel(0), crew(0) {
    shipName = new char[textLength("Unknown") + 1];
    copyText(shipName, "Unknown");
}
```

- **"default constructor"** → parametresiz: `Spaceship()`.
- Sayılar initialization list ile 0.
- İsim için de `new` gerekiyor ("**Both** constructors must dynamically allocate"): "Unknown" 7 harf → `new char[8]`.
- Burada parametre yok, isim çakışması yok → `this->` gerekmiyor.

### 5) "The parameterized constructor sets all data members (... use the this pointer); the crew has a default value of 1"

```cpp
Spaceship(int shipID, const char *shipName, double fuel, int crew = 1) {
    this->shipID = shipID;
    this->fuel = fuel;
    this->crew = crew;
    this->shipName = new char[textLength(shipName) + 1];
    copyText(this->shipName, shipName);
}
```

| Cümledeki ifade | Kodda |
|---|---|
| "parameterized constructor" | 4 parametreli constructor (tablodaki sırayla) |
| "parameter names must be the same" | `shipID`, `shipName`, `fuel`, `crew` → `this->` zorunlu |
| "the crew has a default value of 1" (tabloda `int = 1`) | `int crew = 1` |
| "dynamically allocate memory for the ship name" | `new char[uzunluk + 1]` + kopyalama |

**"two overloaded constructors"** → aynı isimde (`Spaceship`), parametreleri farklı iki constructor. Hangisinin çalışacağına, nesne oluşturulurken verilen değer sayısı karar verir.

### 6) "the destructor must print ... and release the memory"

```cpp
~Spaceship() {
    cout << "[Destructor] Ship " << shipName << " (ID " << shipID << ") memory freed." << endl;
    delete[] shipName;
}
```

**Önce yazdır, sonra sil.** Tersini yapsaydık silinmiş ismi yazdırmaya çalışırdık.

### 7) "refuel() increases the fuel. The fuel cannot exceed MAX_FUEL; if it does, print ... and set the fuel to MAX_FUEL (use the unary scope resolution operator)"

```cpp
Spaceship& refuel(double amount) {
    this->fuel += amount;
    if (this->fuel > ::MAX_FUEL) {
        cout << "Tank is full! Fuel set to " << ::MAX_FUEL << "." << endl;
        this->fuel = ::MAX_FUEL;
    }
    return *this;
}
```

| Cümledeki ifade | Kodda |
|---|---|
| "increases the fuel" | `this->fuel += amount;` |
| "cannot exceed" | `if (this->fuel > ::MAX_FUEL)` |
| "print ... and set the fuel to MAX_FUEL" | `cout` + `this->fuel = ::MAX_FUEL;` |
| "unary scope resolution operator" | `::MAX_FUEL` |
| "must use the this pointer" | `this->fuel` |
| "must be chainable" (tabloda `: Spaceship&`) | dönüş tipi `Spaceship&`, son satır `return *this;` |

### 8) "travel() uses 1 unit of fuel for every 10 km. If there is not enough fuel, it prints ... and the ship does not travel; otherwise it decreases the fuel and prints ..."

```cpp
Spaceship& travel(double distance) {
    double needed = distance / 10;
    if (needed > this->fuel)
        cout << "Not enough fuel to travel " << distance << " km!" << endl;
    else {
        this->fuel -= needed;
        cout << this->shipName << " traveled " << distance << " km." << endl;
    }
    return *this;
}
```

| Cümledeki ifade | Kodda |
|---|---|
| "1 unit of fuel for every 10 km" | `needed = distance / 10;` (300 km → 30 yakıt) |
| "If there is not enough fuel" | `if (needed > this->fuel)` |
| "the ship does not travel" | `if` kolunda yakıta **dokunmuyoruz** |
| "otherwise it decreases the fuel and prints" | `else { fuel -= needed; cout ...; }` |

**Dikkat:** Yolculuk yapılmasa bile `return *this;` çalışıyor; yoksa zincirin devamı kopardı.

### 9) "addCrew() increases the number of crew members"

```cpp
Spaceship& addCrew(int count) {
    this->crew += count;
    return *this;
}
```

Zincirlenebilir olması gerektiği için yine `Spaceship&` ve `return *this;`.

### 10) "displayStatus() displays the ship's information"

```cpp
void displayStatus() const {
    cout << "ID: " << shipID << " | Name: " << shipName
         << " | Fuel: " << fuel << " | Crew: " << crew << endl;
}
```

Yazı biçimi örnek çıktıdan birebir. Sadece okuduğu için `const` (soru istemese de iyi alışkanlık).

### 11) "a friend function hasMoreFuel() returns True if the first ship has more fuel than the second one"

```cpp
friend bool hasMoreFuel(const Spaceship &s1, const Spaceship &s2);   // sinifin icinde
```

```cpp
bool hasMoreFuel(const Spaceship &s1, const Spaceship &s2) {         // sinifin disinda
    return s1.fuel > s2.fuel;
}
```

| Cümledeki ifade | Kodda |
|---|---|
| "friend function" | içeride `friend`, dışarıda gövde (başında `Spaceship::` yok) |
| "returns True if" | dönüş tipi `bool` |
| "the first ship ... than the second one" | iki parametre: `s1`, `s2` |
| tablodaki `const Spaceship&` | parametreler **aynen** böyle |

`return s1.fuel > s2.fuel;` → karşılaştırmanın sonucu zaten `true` ya da `false`; ayrıca `if` yazmaya gerek yok.

### 12) `main`

| Cümledeki ifade | `main`'de |
|---|---|
| "create a backup ship with the default constructor" | `Spaceship backup;` (parantez yok → parametresiz constructor) |
| "a scout ship (ID 7, name "Scout", fuel 30) without giving the crew" | `Spaceship scout(7, "Scout", 30);` → crew varsayılan **1** |
| "a ship with the information taken from the user" | `cin >> id >> name >> fuel >> crew;` sonra `Spaceship ship(id, name, fuel, crew);` |
| "Display the initial status of the three ships" | üç kere `displayStatus()` |
| "take a refuel amount, two distances and the number of new crew members" | `cin >> fuelAmount >> d1 >> d2 >> newCrew;` |
| "in a single line using function chaining in this order: refuel, travel, addCrew, travel" | `ship.refuel(fuelAmount).travel(d1).addCrew(newCrew).travel(d2);` |
| "Display the final status" | `ship.displayStatus();` |
| "compare its fuel with the scout ship" | `if (hasMoreFuel(ship, scout))` (friend: nokta yok) |

**Neden `name` dizisini `main`'de yazdırdık?** Gemi isminin bulunduğu `shipName` private; `main` ona erişemez. Kullanıcının girdiği isim zaten `main`'deki `name` dizisinde duruyor.

---

## Zincirleme adım adım (örnek girdiyle)

`ship.refuel(55).travel(300).addCrew(2).travel(900);`

| Adım | fuel | crew | Ekran |
|---|---|---|---|
| başlangıç | 60 | 3 | |
| `refuel(55)` | 115 → 100'ü geçti → **100** | 3 | `Tank is full! Fuel set to 100.` |
| `.travel(300)` | 30 gerekli, 100 var → **70** | 3 | `Voyager traveled 300 km.` |
| `.addCrew(2)` | 70 | **5** | |
| `.travel(900)` | 90 gerekli, 70 var → **değişmez** | 5 | `Not enough fuel to travel 900 km!` |

Son durum: Fuel 70, Crew 5. `hasMoreFuel(ship, scout)`: 70 > 30 → `true` → "Voyager has more fuel than Scout."

---

## `main` ↔ örnek çıktı

| Örnek çıktıdaki satır | Kodun neresi? |
|---|---|
| `Enter ship ID, name, fuel and crew: 42 Voyager 60 3` | `main`: `cout` + `cin` |
| `ID: 0 \| Name: Unknown ...` | `backup.displayStatus()` (parametresiz constructor'ın değerleri) |
| `ID: 7 \| Name: Scout ... Crew: 1` | `scout.displayStatus()` (crew **varsayılan** 1) |
| `ID: 42 \| Name: Voyager ...` | `ship.displayStatus()` |
| `Tank is full! ...` / `... traveled ...` / `Not enough fuel ...` | zincirdeki fonksiyonların içindeki `cout`'lar |
| `ID: 42 \| ... Fuel: 70 \| Crew: 5` | `ship.displayStatus()` |
| `Voyager has more fuel than Scout.` | `main`'deki `if (hasMoreFuel(...))` |
| `[Destructor] Ship Voyager ...` | destructor: ship **en son** doğdu → **ilk** ölür |
| `[Destructor] Ship Scout ...` | destructor (scout) |
| `[Destructor] Ship Unknown ...` | destructor: backup **ilk** doğdu → **en son** ölür |
