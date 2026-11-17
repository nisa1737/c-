# Cümle → Kod Rehberi

Sınav sorularındaki İngilizce cümleleri gördüğünde **ne yazman gerektiğini** gösteren kısa örnekler.
Cümlelerin hepsi senin gönderdiğin Labwork 1–4 ve Week 6 recitation sorularından (ya da onlara çok benzer).

Her madde 3 parçadan oluşuyor:
- **Cümle:** soruda nasıl yazıyor
- **Ne istiyor?** Türkçe açıklama
- **Kod:** yazman gereken kısa parça

| Bölüm | Konu |
|---|---|
| A | Sınıfın temelleri |
| B | Constructor |
| C | Destructor |
| D | Dinamik bellek |
| E | `this` ve zincirleme |
| F | Referans ve `const` |
| G | Friend |
| H | Global, namespace, `::` |
| I | Overloading, varsayılan değer, template |
| J | `main`'de istenenler |
| K | Koşullar ve kontroller |
| L | Girdi ve çıktı |

---

# A. Sınıfın temelleri

### A1
**Cümle:** *"Define a class Employee including the following: Data Members: employeeID, hourlyWage, hoursWorked, salary"*

**Ne istiyor?** Bu isimlerle **private** değişkenler. Tiplerini sen seçersin: numara/ID → `int`, para/saat/ölçü → `double`.

```cpp
class Employee {
private:
    int employeeID;
    double hourlyWage, hoursWorked, salary;
public:
    // fonksiyonlar
};
```

### A2
**Cümle (UML tablosu):** `- capacity: int` ve `+ initialize(int): void`

**Ne istiyor?** `-` = private, `+` = public. Değişken `isim: tip` → C++'ta `tip isim;`. Fonksiyon `isim(tipler): dönüş` → C++'ta `dönüş isim(parametreler)`.

```cpp
class Portfolio {
    int capacity;               // - capacity: int
public:
    void initialize(int x);     // + initialize(int): void
};
```

### A3
**Cümle (UML tablosu):** `<<struct>> TelemetryProcessor`

**Ne istiyor?** `class` yerine `struct`. İçindekiler varsayılan olarak **public**, `public:` yazmana gerek yok.

```cpp
struct TelemetryProcessor {
    double calibrationFactor;
    void testPassByValue(double value);
};
```

### A4
**Cümle:** *"getX(): Public member function to return the value of x."*

**Ne istiyor?** Private değişkeni dışarıya **okuma amaçlı** veren fonksiyon (getter). Değiştirmediği için `const`.

```cpp
int getX() const { return x; }
```

### A5
**Cümle:** *"setThreshold() function will set the maxTempThreshold to the value provided as a parameter."*

**Ne istiyor?** Private değişkene dışarıdan **değer yazan** fonksiyon (setter).

```cpp
void setThreshold(double t) { maxTempThreshold = t; }
```

### A6
**Cümle:** *"display(): Prints the vector in the format "V = (vx, vy, vz)"."*

**Ne istiyor?** Sadece `cout`. Format **birebir** aynı olmalı: tırnak içi aynen yazılır, değişkenler tırnaksız.

```cpp
void display() const {
    cout << vector_name << " = (" << x << "," << y << "," << z << ")" << endl;
}
```

### A7
**Cümle:** *"create an object of type Calculator"* / *"create a Portfolio class instance"*

**Ne istiyor?** *Object* ve *instance* aynı şey: **nesne**. Sınıf adı tip, nesnenin adını sen verirsin.

```cpp
Calculator calc;
calc.add(2, 9);
```

### A8
**Cümle:** *"calculateSalary(): To calculate the employee's salary (salary = hourlyWage * hoursWorked)."*

**Ne istiyor?** Hesaplanan değerler zaten nesnenin içinde → **parametre yok**. Sonuç da bir değişkene yazılıyor → `void`.

```cpp
void calculateSalary() {
    salary = hourlyWage * hoursWorked;
}
```

### A9
**Cümle:** *"calculateTotalValue() function will return the total of the assetPrices."*

**Ne istiyor?** "Return" diyor → sonucu **döndür**, dönüş tipi `double`. Döngüyle topla.

```cpp
double calculateTotalValue() {
    double total = 0;
    for (int i = 0; i < capacity; i++)
        total += assetPrices[i];
    return total;
}
```

---

# B. Constructor

### B1
**Cümle:** *"A default constructor initializing student_id and cgpa to 0."*

**Ne istiyor?** **Parametresiz** constructor.

```cpp
Student() : student_id(0), cgpa(0.0) {}
// ya da:  Student() { student_id = 0; cgpa = 0; }
```

### B2
**Cümle:** *"A parameterized constructor initializing student_id, name, and cgpa."*

**Ne istiyor?** Değer **alan** constructor.

```cpp
Student(int id, string n, float g) : student_id(id), name(n), cgpa(g) {}
```

### B3
**Cümle:** *"Constructor: Initializes data members using parameters, with default values 0 for x, y, z and '\0' for vector_name."*

**Ne istiyor?** Tek constructor; değer verilmezse varsayılanlar kullanılsın.

```cpp
Vector3D(int x = 0, int y = 0, int z = 0, char name = '\0')
    : x(x), y(y), z(z), vector_name(name) {}
```

Bu sayede `Vector3D v;`, `Vector3D v(1, 2, 3, 'V');` ikisi de çalışır.

### B4
**Cümle:** *"(you have to set each parameter name the same as the member variable of the class, so you have to use this pointer)"*

**Ne istiyor?** Parametre adı = değişken adı → `this->` **zorunlu**.

```cpp
DeviceMonitor(int deviceID, int operationalStatus) {
    this->deviceID = deviceID;
    this->operationalStatus = operationalStatus;
}
```

### B5
**Cümle:** Sınıfta `const int c;` ya da `int &ref;` gibi bir üye var.

**Ne istiyor?** `const` ve referans üyelere değer **sadece initialization list** ile verilir.

```cpp
R(int x) : i(x), c(x), ref(i) { }
```

### B6
**Cümle:** *"...it also calls a global function called registerDevice(DeviceMonitor*)"*

**Ne istiyor?** Constructor'ın içinde global bir fonksiyonu çağır ve ona **nesnenin adresini** (`this`) gönder.

```cpp
DeviceMonitor::DeviceMonitor(int deviceID, int operationalStatus, const char *deviceName) {
    ...
    registerDevice(this);
}
```

`registerDevice` constructor'ın gövdesinden **önce** tanımlanmış olmalı.

### B7
**Cümle:** *"Parameterized constructor ... { computeCourses(); }"* (değer gelince hesapla)

**Ne istiyor?** Constructor değerleri koyduktan sonra hesaplama fonksiyonunu **hemen çağırsın**, nesne hazır olsun.

```cpp
Student(int id, string n, float g) : student_id(id), name(n), cgpa(g) {
    computeCourses();
}
```

---

# C. Destructor

### C1
**Cümle:** *"Destructor (~Employee()): To output the employee ID and calculated salary."*

**Ne istiyor?** Sonucu `main` değil **destructor** yazdırsın. `main` bitince kendiliğinden, **ters sırayla** çalışır.

```cpp
~Employee() {
    cout << "Salary of ID " << employeeID << " is " << salary << endl;
}
```

### C2
**Cümle:** *"the destructor will release all dynamically allocated memory upon destruction"*

**Ne istiyor?** Constructor'daki **her `new` için** destructor'da bir `delete`.

```cpp
~EnchantedWeapon() {
    delete[] weaponName;
    delete[] loreScroll;
}
```

### C3
**Cümle:** *"cleanup() function will free the memory located by the initialize() function at the end of the program"*

**Ne istiyor?** Bu sefer destructor değil, **normal bir fonksiyon**. Kendiliğinden çalışmaz; `main`'in sonunda **sen çağırırsın**.

```cpp
void cleanup() { delete[] assetPrices; }

// main'in sonunda:
portfolio.cleanup();
```

---

# D. Dinamik bellek

### D1
**Cümle:** *"initialize() function will dynamically allocate memory for x assets"*

**Ne istiyor?** Değişken pointer (`double *assetPrices`). Boyutu da sakla, diğer fonksiyonlar kullanacak.

```cpp
void initialize(int x) {
    capacity = x;
    assetPrices = new double[x];
}
```

### D2
**Cümle:** *"then dynamically create an array for recording the related temperature for each greenhouse"* (`main` içinde)

**Ne istiyor?** Diziyi `main`'de `new` ile oluştur, iş bitince `delete[]`.

```cpp
double *temperatures = new double[n];
...
delete[] temperatures;
```

### D3
**Cümle:** *"Note: Do not forget to free the memory you have dynamically created."*

**Ne istiyor?** Her `new` için bir `delete`. Eşleştir:

```cpp
int *a = new int[n];          // dizi       → sonunda: delete[] a;
Rational *p = new Rational;   // tek nesne  → sonunda: delete p;
```

### D4
**Cümle:** *"allocate dynamic memory for both the weapon name and lore scroll"* (değişken `char*`)

**Ne istiyor?** Harfleri say → **harf + 1** kadar yer ayır → kopyala → sonuna `'\0'`.

```cpp
int len = 0;
while (weaponName[len] != '\0')
    len++;
this->weaponName = new char[len + 1];
for (int i = 0; i < len; i++)
    this->weaponName[i] = weaponName[i];
this->weaponName[len] = '\0';
```

### D5
**Cümle:** *"deviceName[] is a character array with a fixed size of 30"*

**Ne istiyor?** **Sabit boyut**, `new` yok. Kopyalarken en fazla 29 harf (biri `'\0'` için).

```cpp
char deviceName[30];
```

**D4 ile farkı:** `char*` → `new` ile yer ayırırsın. `char[30]` → yer hazır, sadece kopyalarsın.

### D6
**Cümle:** *"then pass this array as a parameter to the checkThreshold() function"* (UML: `checkThreshold(const double*, int)`)

**Ne istiyor?** Diziyi fonksiyona gönder. Fonksiyon boyutu bilemez, **boyutu da** gönder.

```cpp
bool checkThreshold(const double *temps, int size) { ... }

// main:
monitor.checkThreshold(temperatures, n);
```

### D7
**Cümle:** *"Allocates memory for a new Rational object"*

**Ne istiyor?** Tek nesne için `new`. Adres üzerinden `->` ile kullanılır.

```cpp
Rational *q = new Rational(3, 4);
q->display();
delete q;
```

### D8
**Cümle:** *"dynamically create an array of Product objects"*

**Ne istiyor?** Nesne dizisi `new` ile. Her eleman **default constructor** ile oluşur, o yüzden sınıfta parametresiz constructor olmalı.

```cpp
Product *products = new Product[n];
products[i].read();          // dizinin elemanı → nokta
delete[] products;
```

---

# E. `this` ve zincirleme

### E1
**Cümle:** *"setOperationalStatus(int) and setDeviceName(const char*) functions should be written in a way that they can be called with an instance via chaining."*

**Ne istiyor?** Dönüş tipi `Sinif&`, son satır `return *this;`.

```cpp
DeviceMonitor& setOperationalStatus(int operationalStatus) {
    this->operationalStatus = operationalStatus;
    return *this;
}
```

### E2
**Cümle:** *"The upgradeDamage() function will return a reference to the current object to enable method chaining."*

**Ne istiyor?** E1 ile aynı. *"reference to the current object"* = `*this`, dönüş tipi `EnchantedWeapon&`.

```cpp
EnchantedWeapon& upgradeDamage(double amount) {
    this->baseDamage += amount;
    return *this;
}
```

### E3
**Cümle:** *"These functions should use the this pointer to update the information."*

**Ne istiyor?** Değişkenlere `this->` ile eriş.

```cpp
Car& setBrand(string b) {
    this->brand = b;
    return *this;
}
```

### E4
**Cümle:** *"Ensure that the setBrand(), setModel(), and setYear() functions can be used in a chainable way on the same line."*

**Ne istiyor?** `main`'de üç fonksiyonu **tek satırda** art arda çağır.

```cpp
myCar.setBrand(brand).setModel(model).setYear(year);
```

---

# F. Referans ve `const`

### F1
**Cümle:** *"testPassByValue() function will take a T type variable ... (recognize pass-by-value behavior)"*

**Ne istiyor?** Parametrede `&` **yok** → kopya gelir, asıl değişken değişmez.

```cpp
void testPassByValue(T value) {
    value = value * calibrationFactor;
}
```

### F2
**Cümle:** *"testPassByReference() ... (however, this time as pass-by-reference)"* (UML: `T&`)

**Ne istiyor?** Parametrede `&` **var** → asıl değişken gelir ve değişir.

```cpp
void testPassByReference(T &value) {
    value = value * calibrationFactor;
}
```

### F3
**Cümle (UML):** `inspectWeaponLore(const EnchantedWeapon&)`

**Ne istiyor?** Nesne **kopyalanmadan** gelsin ama fonksiyon onu **değiştiremesin**.

```cpp
void inspectWeaponLore(const EnchantedWeapon &weapon) { ... }
```

### F4
**Cümle:** *"display() ... while omitting the lore text"* / *"Function to return the first name"*

**Ne istiyor?** Sadece okuyan fonksiyonların sonuna `const`.

```cpp
void displayStats() const { ... }
string getFirstName() const { return firstName; }
```

---

# G. Friend

### G1
**Cümle:** *"a friend function named inspectWeaponLore() is declared to directly access and display the private loreScroll member"*

**Ne istiyor?** Sınıfın içinde `friend` bildirimi, gövde dışarıda (başında `Sinif::` **yok**). Nokta olmadan çağrılır.

```cpp
class EnchantedWeapon {
    ...
    friend void inspectWeaponLore(const EnchantedWeapon &weapon);
};

void inspectWeaponLore(const EnchantedWeapon &weapon) {
    cout << weapon.loreScroll << endl;
}

// main:
inspectWeaponLore(weapon);
```

### G2
**Cümle:** *"Friend function: crossProduct(): Computes the cross product of two vectors and returns the result as a Vector3D object."*

**Ne istiyor?** Friend fonksiyon **iki nesne alıp yeni bir nesne döndürsün**.

```cpp
friend Vector3D crossProduct(const Vector3D &v1, const Vector3D &v2);   // class içinde

Vector3D crossProduct(const Vector3D &v1, const Vector3D &v2) {
    return Vector3D(v1.y * v2.z - v1.z * v2.y,
                    v1.z * v2.x - v1.x * v2.z,
                    v1.x * v2.y - v1.y * v2.x, 'C');
}
```

### G3
**Cümle:** *"addition(): Adds two vectors and returns the result as a Vector3D object."* (üye fonksiyon)

**Ne istiyor?** G2'nin **üye** hali: bir nesne parametreden, diğeri nesnenin kendisi.

```cpp
Vector3D addition(const Vector3D &v) {
    return Vector3D(x + v.x, y + v.y, z + v.z, 'U');
}

// main:
Vector3D U = V.addition(W);
```

### G4
**Cümle:** *"Declares B as a friend class, allowing it to access A's private members."*

**Ne istiyor?** B'nin **bütün** fonksiyonları A'nın private'larına erişebilsin.

```cpp
class A {
    int x;
public:
    friend class B;
};
```

---

# H. Global, namespace, `::`

### H1
**Cümle:** *"...greater than the globally declared GLOBAL_MARKET_RISK_THRESHOLD value (set it to 0.05)"*

**Ne istiyor?** Sınıfın ve `main`'in **dışında**, değişmeyen bir değer.

```cpp
const double GLOBAL_MARKET_RISK_THRESHOLD = 0.05;
```

### H2
**Cümle:** *"(to do this you have to use unary scope resolution operator)"*

**Ne istiyor?** Global olana başında **`::`** ile eriş.

```cpp
cout << ::GLOBAL_MARKET_RISK_THRESHOLD * 100 << "%";
```

### H3
**Cümle:** *"an internal scope resolution operator will be used within the upgradeDamage() and sharpenEdge() functions to access a global game balance constant"*

**Ne istiyor?** H2 ile aynı, ama bu sefer **sınıfın fonksiyonunun içinde**.

```cpp
if (this->baseDamage > ::MAX_GLOBAL_DAMAGE)
    this->baseDamage = ::MAX_GLOBAL_DAMAGE;
```

### H4
**Cümle:** *"Write a C++ program which implements the below class inside a namespace called Math"*

**Ne istiyor?** Sınıfı namespace'in içine koy; dışarıdan `Math::` ile kullan.

```cpp
namespace Math {
    class Calculator { ... };
}

// main:
Math::Calculator calc;
```

---

# I. Overloading, varsayılan değer, template

### I1
**Cümle:** *"Notice that each function has two types (meaning you will perform function overloading)."*

**Ne istiyor?** **Aynı isim, farklı parametre tipleri.**

```cpp
int add(int a, int b) { return a + b; }
double add(double a, double b) { return a + b; }
```

### I2
**Cümle (UML / kod):** `int modify(int&, int = 4);`

**Ne istiyor?** İkinci parametrenin varsayılan değeri 4. Varsayılan değer **sadece bildirimde** yazılır.

```cpp
int modify(int &m, int n = 4);              // class içinde: = 4 VAR

int Sample::modify(int &m, int n) { ... }   // dışarıda: = 4 YOK
```

### I3
**Cümle:** *"testPassByValue() function will take a T type variable"*

**Ne istiyor?** **T** = template'in yer tutucusu.

```cpp
template <class T>
struct TelemetryProcessor {
    T calibrationFactor;
    void testPassByValue(T value) { ... }
};
```

### I4
**Cümle:** *"create a TelemetryProcessor instance"* (template olan bir struct için)

**Ne istiyor?** Nesne oluştururken T'nin ne olacağını **sen yaz**.

```cpp
TelemetryProcessor<double> processor;
```

---

# J. `main`'de istenenler

### J1
**Cümle:** *"ask the user how many assetPrices would like to be entered"*

```cpp
int n;
cout << "Enter how many assets you would like to enter: ";
cin >> n;
```

### J2
**Cümle:** *"The main function should declare an array for up to 50 employees"*

**Ne istiyor?** Sınır 50; kullanıcı fazlasını girerse 50'ye çek.

```cpp
const int SIZE = 50;
if (n > SIZE)
    n = SIZE;
Employee employees[SIZE];
```

### J3
**Cümle:** *"take their input, and output their employee IDs along with their salaries"*

**Ne istiyor?** Döngüde her nesnenin fonksiyonlarını çağır.

```cpp
for (int i = 0; i < n; i++) {
    employees[i].input();
    employees[i].calculateSalary();
}
```

### J4
**Cümle:** *"Create an object for yourself and print the maximum courses you can take. (e.g. 101 John 3.6)"*

**Ne istiyor?** Parametreli constructor ile **sabit değerlerle** bir nesne.

```cpp
Student me(101, "John", 3.6);
me.displayStudentInfo();
me.display();
```

### J5
**Cümle:** *"Then create two DeviceMonitor instances with these parameters, after creating the instances, display them."*

```cpp
DeviceMonitor device1(id1, status1, name1);
DeviceMonitor device2(id2, status2, name2);
device1.displayInfo();
device2.displayInfo();
```

### J6
**Cümle:** *"according to the return value if it is True, print ..., if it is False, print ..."*

**Ne istiyor?** `bool` döndüren fonksiyonu doğrudan `if`'in içinde kullan.

```cpp
if (portfolio.exceedsRiskLimit(drawdown))
    cout << "[WARNING] ..." << endl;
else
    cout << "Portfolio risk is within acceptable parameters." << endl;
```

### J7
**Cümle:** *"(Do not forget to call the cleanup() function at the end of the program)"*

```cpp
portfolio.cleanup();
return 0;
```

---

# K. Koşullar ve kontroller

### K1
**Cümle:** *"exceedsRiskLimit() will return True if the value provided by the user ... is greater than ..., False otherwise"*

**Ne istiyor?** Dönüş tipi `bool`.

```cpp
bool exceedsRiskLimit(double drawdown) {
    if (drawdown > ::GLOBAL_MARKET_RISK_THRESHOLD)
        return true;
    else
        return false;
}
```

Kısa yazımı: `return drawdown > ::GLOBAL_MARKET_RISK_THRESHOLD;`

### K2
**Cümle:** *"if weapon's damage exceeds this value ... display the message: "This weapon is pretty overpowered!", and set the damage to 200"*

**Ne istiyor?** Önce artır, sonra **sınırı aştı mı** bak; aştıysa mesaj ver ve sınıra çek.

```cpp
baseDamage += amount;
if (baseDamage > ::MAX_GLOBAL_DAMAGE) {
    cout << "\"This weapon is pretty overpowered!\"" << endl;
    baseDamage = ::MAX_GLOBAL_DAMAGE;
}
```

### K3
**Cümle:** *"Students with a CGPA >= 3.5 can take an additional 3 courses. Students with a CGPA >= 3.0 ... 2 courses. ... >= 2.5 ... 1 additional course."*

**Ne istiyor?** Kademeli kural → `if / else if`, **büyükten küçüğe**. Sadece ilk uyan çalışır.

```cpp
maxCourses = 5;
if (cgpa >= 3.5)
    maxCourses += 3;
else if (cgpa >= 3.0)
    maxCourses += 2;
else if (cgpa >= 2.5)
    maxCourses += 1;
```

### K4
**Cümle:** *"checkThreshold() function will print "[WARNING] ..." and return True if any of the read temperature value ... exceed the maxTempThreshold, return False otherwise."*

**Ne istiyor?** "**Any**" (herhangi biri) → döngüde ilk bulduğun an `return true;`. Hiçbiri yoksa döngü bitince `return false;`.

```cpp
for (int i = 0; i < size; i++) {
    if (temps[i] > maxTempThreshold) {
        cout << "[WARNING] At least one sensor exceeds limit " << maxTempThreshold << "!" << endl;
        return true;
    }
}
return false;
```

### K5
**Cümle:** *"You also have to consider the condition where the second parameter is 0, if that is the case, you should display an error message "Division by zero error!" and terminate the program."*

**Ne istiyor?** Bölmeden **önce** kontrol et; `main` içinde `return` programı bitirir.

```cpp
if (i2 == 0) {
    cout << "Division by zero error!" << endl;
    return 1;
}
```

### K6
**Cümle:** *"setValue(index, value): Assign value ... (check the index)"*

**Ne istiyor?** Dizinin dışına yazmayı engelle: geçerli indeks **0 ile size − 1** arası.

```cpp
if (index >= 0 && index < size)
    parr[index] = value;
else
    cout << "Index out of bounds!" << endl;
```

---

# L. Girdi ve çıktı

### L1
**Cümle:** Örnek girdide **boşluklu** metin var: *"Enter Weapon Lore Description: By Ysmir created at Sky Forge"*

**Ne istiyor?** `cin >>` boşlukta durur; **bütün satırı** al.

```cpp
char loreScroll[200];
cin.getline(loreScroll, 200);       // char dizisi için

string title;
getline(cin, title);                // string için
```

### L2
**Cümle:** Bir sayı okuduktan **hemen sonra** boşluklu metin okunacak.

**Ne istiyor?** `cin >>` sayıdan sonra Enter'ı bırakır; `getline` onu görüp boş döner. Araya `cin.ignore()` koy.

```cpp
cin >> weaponID;
cin.ignore();
cin.getline(weaponName, 50);
```

### L3
**Cümle:** *"ask for ... two character inputs (representing operators)"*

**Ne istiyor?** `char` ile oku, `switch` ile karar ver.

```cpp
char op;
cin >> op;
switch (op) {
    case '+': cout << calc.add(a, b); break;
    case '-': cout << calc.subtract(a, b); break;
    default:  cout << "Invalid operator";
}
```

### L4
**Cümle:** Örnek çıktıda fiyatlar virgülden sonra **2 basamaklı**: *"Prices: $1250.50 $430.25 $2100.00"*

```cpp
cout << fixed;
cout.precision(2);
```

### L5
**Cümle:** *"which displays the memory address of the provided variable"*

**Ne istiyor?** Pointer'ı `cout` ile yazdırınca **adres** çıkar.

```cpp
void registerDevice(DeviceMonitor *device) {
    cout << "Device pointer registered at address: " << device << endl;
}
```

### L6
**Cümle:** Çıktıda **tırnak işareti** var: *"This weapon is pretty overpowered!"*

**Ne istiyor?** Metnin içinde `"` yazdırmak için önüne `\` koy.

```cpp
cout << "\"This weapon is pretty overpowered!\"" << endl;
```

### L7
**Cümle:** Örnek çıktıda kullanıcı değeri yazının **yanına** giriyor: *"Enter two integer numbers: 2 9"*

**Ne istiyor?** Soru yazısından sonra `endl` **koyma**.

```cpp
cout << "Enter two integer numbers: ";
cin >> i1 >> i2;
```

---

## Son kontrol listesi (kodu teslim etmeden önce)

- [ ] Her `class` / `struct` sonunda `};` var mı?
- [ ] UML'deki `-` olanlar private, `+` olanlar public mi?
- [ ] Parametre adı = değişken adı olan yerlerde `this->` var mı?
- [ ] Her `new` için bir `delete` var mı? (`[]` eşleşiyor mu?)
- [ ] Zincirlenecek fonksiyonlar `Sinif&` döndürüp `return *this;` yapıyor mu?
- [ ] Friend fonksiyonun gövdesinde `Sinif::` **yok**, `friend` kelimesi sadece sınıfın içinde mi?
- [ ] Varsayılan değerler sadece bildirimde mi?
- [ ] Çıktıdaki yazılar örnek çıktıyla **birebir** aynı mı (boşluklar, iki nokta, büyük/küçük harf)?
