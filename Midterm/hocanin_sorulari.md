# CENG241 – Week 6 Midterm Recitation (Hocanın Soruları)

Hocanın recitation slaytlarındaki **7 soru** (Ex 1–7). Her sorunun **hemen altında** cevabı ve Türkçe açıklaması var.

- Soru metinleri slaytlardaki gibi **İngilizce**.
- Bütün kodlar derlenip çalıştırıldı; çıktılar slaytlardaki çıktılarla aynı.
- Slaytta eksik olan kısımları (bazı `main` fonksiyonları) ben tamamladım; hangi kısımların benim eklemem olduğu her soruda yazıyor.

| Soru | Tür | Konu |
|---|---|---|
| Ex 1 | Çıktı bulma | iki constructor, `&`, varsayılan parametre, destructor sırası, global değişken |
| Ex 2 | Çıktı bulma | aynı konular + sonradan oluşturulan üçüncü nesne |
| Ex 3 | Çıktı bulma | aynı isimli iki fonksiyon, `::`, yerel değişken |
| Ex 4 | Kod yazma | nesne dizisi, sonucu destructor'da yazdırmak |
| Ex 5 | Kod yazma | iki constructor, `if / else if`, nesne dizisi |
| Ex 6 | Kod yazma | nesne döndüren üye fonksiyon, friend fonksiyon |
| Ex 7 | Kod yazma | `this` pointer, zincirleme (function chaining) |

**Çıktı sorularını çözme yöntemi:** Bütün değişkenler için kağıda kutu çiz, kodu satır satır oku ve her satırda kutuları güncelle.

---

## Ex 1

What is the output of the following program?

```cpp
#include <iostream>
using namespace std;

int globalVar = 10;

class Sample {
    int a, b;
public:
    Sample(int x, int y) : a(x), b(y) { globalVar += 5; }
    Sample(int z) { a = z, b = z; }
    ~Sample() { cout << a << " " << b << " " << globalVar << endl; }
    int modify(int&, int = 4);
};

int Sample::modify(int& m, int n) {
    m += 2;
    n += 3;
    a -= 1;
    b += 2;
    cout << m << " " << n << endl;
    return m + n;
}

int main() {
    int p = 3, q = 5;
    Sample objA(4), objB(2, 6);
    globalVar = objA.modify(p, q);
    globalVar = objB.modify(q);
    cout << p << " " << q << endl;
}
```

### Cevap

```
5 8
7 7
5 7
1 8 14
3 6 14
```

### Açıklama

**Parçaları tanı:**

| Parça | Ne yapıyor? |
|---|---|
| `Sample(int x, int y)` | **2 sayı** ile: a = x, b = y, **globalVar 5 artar** |
| `Sample(int z)` | **1 sayı** ile: a = z, b = z (globalVar'a dokunmaz) |
| `~Sample()` | yok olurken `a b globalVar` yazar |
| `modify(int& m, int n = 4)` | **m referans** (asıl değişken değişir), **n kopya**; n verilmezse 4 |

**Başlangıç:** globalVar = 10, p = 3, q = 5

**1) `Sample objA(4)`** → tek sayı: a = 4, b = 4. globalVar değişmez.

**2) `objB(2, 6)`** → iki sayı: a = 2, b = 6, globalVar = 10 + 5 = **15**.

```
globalVar = 15
p = 3    q = 5
objA:  a = 4   b = 4
objB:  a = 2   b = 6
```

**3) `globalVar = objA.modify(p, q);`** → m = **p'nin kendisi**, n = q'nun **kopyası** (5); a ve b **objA'nın**.

| Satır | Sonuç |
|---|---|
| `m += 2;` | m = 5 → **p = 5** |
| `n += 3;` | n = 8 (q hâlâ 5) |
| `a -= 1;` | objA.a = **3** |
| `b += 2;` | objA.b = **6** |
| `cout` | **`5 8`** |
| `return m + n;` | 13 → **globalVar = 13** |

**4) `globalVar = objB.modify(q);`** → m = **q'nun kendisi**, n = **4** (varsayılan); a ve b **objB'nin**.

| Satır | Sonuç |
|---|---|
| `m += 2;` | m = 7 → **q = 7** |
| `n += 3;` | n = 7 |
| `a -= 1;` | objB.a = **1** |
| `b += 2;` | objB.b = **8** |
| `cout` | **`7 7`** |
| `return m + n;` | 14 → **globalVar = 14** |

**5) `cout << p << " " << q`** → **`5 7`**

**6) main biter, destructor'lar ters sırayla:** objB sonra doğdu → **önce** o: **`1 8 14`**; sonra objA: **`3 6 14`**

**Tuzaklar:**
- `objA(4)` tek sayılı constructor'ı çağırır, globalVar'ı **artırmaz**.
- Her nesnenin **kendi** a ve b'si var: `objA.modify` objA'nınkileri, `objB.modify` objB'ninkileri değiştirir.
- q, ilk çağrıda kopyaya (n) gitti, değişmedi; ikinci çağrıda referansa (m) gitti, değişti.
- Destructor'lar globalVar'ın **son** değerini (14) yazar.

---

## Ex 2

What is the output of the following program?

```cpp
#include <iostream>
using namespace std;

int globalVal = 7;

class ComplexTest {
    int a, b;
public:
    ComplexTest(int x, int y) : a(x), b(y) { globalVal += 2; }
    ComplexTest(int z) { a = z, b = z + 1; }
    ~ComplexTest() { cout << a << " " << b << " " << globalVal << endl; }
    int compute(int&, int = 5);
};

int ComplexTest::compute(int& m, int n) {
    m *= 2;
    n += a;
    a += 3;
    b -= 2;
    cout << m << " " << n << " " << a << " " << b << endl;
    return m - n;
}

int main() {
    int x = 2, y = 4;
    ComplexTest obj1(3, 5), obj2(6);
    globalVal = obj1.compute(x, y);
    ComplexTest obj3(globalVal);
    globalVal = obj2.compute(y);
    cout << x << " " << y << " " << globalVal << endl;
}
```

### Cevap

```
4 7 6 3
8 11 9 5
4 8 -3
-3 -2 -3
9 5 -3
6 3 -3
```

### Açıklama

**Parçaları tanı:**

| Parça | Ne yapıyor? |
|---|---|
| `ComplexTest(int x, int y)` | **2 sayı** ile: a = x, b = y, **globalVal 2 artar** |
| `ComplexTest(int z)` | **1 sayı** ile: a = z, **b = z + 1** |
| `compute(int& m, int n = 5)` | m referans, n kopya; n verilmezse 5 |

**Başlangıç:** globalVal = 7, x = 2, y = 4

**1) `obj1(3, 5)`** → a = 3, b = 5, globalVal = **9**
**2) `obj2(6)`** → a = 6, b = **7**

**3) `globalVal = obj1.compute(x, y);`** → m = x'in kendisi (2), n = y'nin kopyası (4); a ve b **obj1'in**.

| Satır | Sonuç |
|---|---|
| `m *= 2;` | m = 4 → **x = 4** |
| `n += a;` | n = 4 + 3 = 7 |
| `a += 3;` | obj1.a = **6** |
| `b -= 2;` | obj1.b = **3** |
| `cout` | **`4 7 6 3`** |
| `return m - n;` | 4 − 7 = −3 → **globalVal = −3** |

**4) `ComplexTest obj3(globalVal);`** → globalVal şu an −3: a = −3, b = **−2**

**5) `globalVal = obj2.compute(y);`** → m = y'nin kendisi (4), n = **5** (varsayılan); a ve b **obj2'nin**.

| Satır | Sonuç |
|---|---|
| `m *= 2;` | m = 8 → **y = 8** |
| `n += a;` | n = 5 + 6 = 11 |
| `a += 3;` | obj2.a = **9** |
| `b -= 2;` | obj2.b = **5** |
| `cout` | **`8 11 9 5`** |
| `return m - n;` | 8 − 11 = −3 → **globalVal = −3** |

**6) `cout << x << y << globalVal`** → **`4 8 -3`**

**7) main biter:** oluşma sırası obj1 → obj2 → obj3, yok olma sırası **obj3 → obj2 → obj1**:
**`-3 -2 -3`**, **`9 5 -3`**, **`6 3 -3`**

**Tuzaklar:**
- Tek sayılı constructor'da **b = z + 1**.
- `n += a` satırındaki a, **o anki nesnenin** a'sı: obj1'de 3, obj2'de 6.
- obj3, `globalVal`'ın o anki değeriyle (−3) oluşur; en son doğduğu için **ilk o** yok olur.

---

## Ex 3

What is the output of the following program?

```cpp
#include <iostream>
using namespace std;

int globalVar = 10;

class B {
    int p, q;
public:
    B(int x, int y = 1) : p(x), q(y) {}
    void process(int&, int);
    void process(int&);
    void display() { cout << "p=" << p << " q=" << q << endl; }
};

void B::process(int &a, int b) {
    globalVar = p + 3;
    a = q + 2;
    b = p * 3;
    q += 2;
}

void B::process(int &b) {
    int localVar = p;
    ::globalVar += 2;
    q = ::globalVar;
    b = localVar;
}

int main() {
    B obj1(3), obj2(5, 7);
    int x = 4, y = 8;

    obj1.process(x, y);
    obj1.display();
    cout << x << " " << y << " " << globalVar << endl;

    obj2.process(y);
    obj2.display();
    cout << x << " " << y << " " << globalVar << endl;

    return 0;
}
```

### Cevap

```
p=3 q=3
3 8 6
p=5 q=8
3 5 8
```

### Açıklama

**Parçaları tanı:**
- Tek constructor var, ikinci parametresi varsayılan: `obj1(3)` → p = 3, **q = 1**; `obj2(5, 7)` → p = 5, q = 7.
- `process` adında **iki** fonksiyon var: **iki değer** gönderilirse `process(int&, int)`, **tek değer** gönderilirse `process(int&)` çalışır.
- Destructor **yok**: program sonunda ekstra satır çıkmaz.

**Başlangıç:** globalVar = 10, x = 4, y = 8

**1) `obj1.process(x, y);`** → a = **x'in kendisi**, b = y'nin **kopyası** (8); p ve q **obj1'in** (3, 1).

| Satır | Sonuç |
|---|---|
| `globalVar = p + 3;` | globalVar = **6** |
| `a = q + 2;` | a = 3 → **x = 3** |
| `b = p * 3;` | b = 9 (sadece kopya; **y hâlâ 8**) |
| `q += 2;` | obj1.q = **3** |

`display()` → **`p=3 q=3`**; sonraki satır → **`3 8 6`**

**2) `obj2.process(y);`** → b = **y'nin kendisi**; p ve q **obj2'nin** (5, 7).

| Satır | Sonuç |
|---|---|
| `int localVar = p;` | localVar = 5 |
| `::globalVar += 2;` | globalVar = **8** |
| `q = ::globalVar;` | obj2.q = **8** |
| `b = localVar;` | **y = 5** |

`display()` → **`p=5 q=8`**; sonraki satır → **`3 5 8`**

**Tuzaklar:**
- `obj1(3)` için **q = 1** (varsayılan), 0 değil.
- İlk `process`'teki b kopya, ikincisindeki b **referans**: aynı harf, farklı davranış.
- `a = q + 2;` satırında q'nun **eski** değeri (1) kullanılır; `q += 2` daha sonra çalışıyor.
- Bu fonksiyonlarda aynı isimde yerel değişken olmadığı için `::globalVar` ile `globalVar` aynı şey.

---

## Ex 4

Write a C++ program to calculate employees' salaries in a company.
Define a **class Employee** including the following:

**Data Members:** *employeeID, hourlyWage, hoursWorked, salary*

**Member Functions:**
- **input():** To input the employee ID, hourly wage, and hours worked.
- **calculateSalary():** To calculate the employee's salary (salary = hourlyWage * hoursWorked).
- **Destructor (~Employee()):** To output the employee ID and calculated salary.

The main function should declare an array for up to 50 employees, take their input, and output their employee IDs along with their salaries.

**Sample Output:**

```
Input ID, hourly wage, hours worked: 101 20 40
Input ID, hourly wage, hours worked: 102 25 35
...
Salary of ID 102 is 875
Salary of ID 101 is 800
```

### Cevap (hocanın çözümü)

```cpp
#include <iostream>
using namespace std;

class Employee {
private:
    int employeeID;
    double hourlyWage, hoursWorked, salary;

public:
    void input() {
        cout << "Input ID, hourly wage, hours worked: ";
        cin >> employeeID >> hourlyWage >> hoursWorked;
    }

    void calculateSalary() {
        salary = hourlyWage * hoursWorked;
    }

    ~Employee() {
        cout << "Salary of ID " << employeeID << " is " << salary << endl;
    }
};

int main() {
    const int SIZE = 50;
    int n;

    cout << "Enter number of employees (max 50): ";
    cin >> n;

    Employee employees[n];

    if (n > SIZE) {
        cout << "Max number of employees is 50. Setting n to 50." << endl;
        n = SIZE;
    }

    for (int i = 0; i < n; i++) {
        employees[i].input();
        employees[i].calculateSalary();
    }

    return 0;
}
```

### Açıklama

- **Tipler:** ID → `int` (küsuratsız numara); ücret, saat ve maaş → `double` (küsuratlı olabilir).
- **`input()`:** `cout` ile soruyu sorar, `cin` ile üç değeri alır. `salary` alınmaz; onu `calculateSalary()` hesaplar.
- **`calculateSalary()`:** parantezi boş, çünkü ücret ve saat zaten **nesnenin içinde** duruyor.
- **`Employee employees[n];`:** `Employee` tip (sınıfın adı), `employees` dizinin adı.
- **`employees[i].input();`:** "i'inci çalışanın input'unu çalıştır."
- **Maaşları kim yazıyor?** `main` değil, **destructor**. `main` bitince dizideki nesneler yok olurken her biri kendi maaşını yazar.
- **Neden ters sırada (önce 102)?** Nesneler **oluşturulma sırasının tersine** yok olur: son eleman ilk.

**Hesap:** 20 × 40 = **800**, 25 × 35 = **875**

---

## Ex 5

Write a C++ program to compute the maximum number of courses a student can enroll in at XYZ University based on their CGPA. The university regulations are as follows:

- All students can take 5 courses.
- Students with a CGPA >= 3.5 can take an additional 3 courses.
- Students with a CGPA >= 3.0 can take an additional 2 courses.
- Students with a CGPA >= 2.5 can take 1 additional course.

In your program, include the following:
- Define a Student class with the following:
  - Private data members: *student_id, name, cgpa, maxCourses*
- Constructors:
  - A default constructor initializing student_id and cgpa to 0.
  - A parameterized constructor initializing student_id, name, and cgpa.
- Functions:
  - **read():** Reads student details.
  - **computeCourses():** Computes the maximum number of courses the student can take.
  - **display():** Displays student details.
  - **displayStudentInfo():** Displays student details for yourself object.

The main() function should:
- Create an object for yourself and print the maximum courses you can take. (e.g. 101 John 3.6)
- Create at most 50 element array of students, read their data, and compute their maximum courses.

**Sample Run:**

```
101 John 3.6
John can take at most 8 courses.
Enter number of students: 3
Enter student ID, name, and CGPA: 12345 Alice 3.2
Alice can take at most 7 courses.
Enter student ID, name, and CGPA: 23456 Bob 2.7
Bob can take at most 6 courses.
Enter student ID, name, and CGPA: 34567 Charlie 2.4
Charlie can take at most 5 courses.
```

### Cevap

(Sınıf slaytlardaki gibi; `main`'i slaytta olmadığı için ben yazdım.)

```cpp
#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    int student_id;
    string name;
    float cgpa;
    int maxCourses;

public:
    // Default constructor
    Student() : student_id(0), cgpa(0.0), maxCourses(5) {}

    // Parameterized constructor
    Student(int id, string n, float g) : student_id(id), name(n), cgpa(g) { computeCourses(); }

    // Function to read student data
    void read() {
        cout << "Enter student ID, name, and CGPA: ";
        cin >> student_id >> name >> cgpa;
        computeCourses();
    }

    // Function to compute max courses a student can take
    void computeCourses() {
        maxCourses = 5;  // Base courses for all students
        if (cgpa >= 3.5)
            maxCourses += 3;
        else if (cgpa >= 3.0)
            maxCourses += 2;
        else if (cgpa >= 2.5)
            maxCourses += 1;
    }

    // Function to display student information
    void display() {
        cout << name << " can take at most " << maxCourses << " courses." << endl;
    }

    void displayStudentInfo() {
        cout << student_id << " " << name << " " << cgpa << endl;
    }
};

int main() {
    Student me(101, "John", 3.6);
    me.displayStudentInfo();
    me.display();

    const int SIZE = 50;
    Student students[SIZE];
    int n;

    cout << "Enter number of students: ";
    cin >> n;

    if (n > SIZE)
        n = SIZE;

    for (int i = 0; i < n; i++) {
        students[i].read();
        students[i].display();
    }

    return 0;
}
```

### Açıklama

- **`if / else if`** kullanılıyor, 3 ayrı `if` değil: sadece **ilk uyan** koşul çalışır. 3.6 için sadece +3 eklenir; 3 ayrı `if` olsaydı +3 +2 +1 eklenirdi.
- Koşullar **büyükten küçüğe** sıralı: önce `>= 3.5`, sonra `>= 3.0`, sonra `>= 2.5`.
- `maxCourses = 5;` her hesaplamanın başında; fonksiyon tekrar çağrılsa da değer üst üste eklenmez.
- Parametreli constructor ve `read()` sonunda **`computeCourses()`** çağırıyor: CGPA'nın değer aldığı her yerde ders sayısı yeniden hesaplanmalı.
- **`Student students[SIZE];`** 50 nesnenin her biri için **parametresiz constructor**'ı çalıştırır; o constructor olmasaydı bu satır hata verirdi.

| Öğrenci | CGPA | Koşul | Ders |
|---|---|---|---|
| John | 3.6 | `>= 3.5` | 5 + 3 = **8** |
| Alice | 3.2 | `>= 3.0` | 5 + 2 = **7** |
| Bob | 2.7 | `>= 2.5` | 5 + 1 = **6** |
| Charlie | 2.4 | hiçbiri | **5** |

---

## Ex 6

Write a C++ program for basic 3D vector operations as described below:

- A vector is a physical quantity represented using three integers:
  `v = (vx, vy, vz)`
- The cross product of two vectors results in another vector:
  `v × w = (vy·wz − vz·wy, vz·wx − vx·wz, vx·wy − vy·wx)`
- The addition of two vectors produces another vector:
  `u = v + w` or `u = (vx + wx, vy + wy, vz + wz)`
- Define a class **Vector3D** which consists of:
  - **Data members:** Three integers (x, y, z) and a single character (vector_name) to label the vector.
  - **Constructor:** Initializes data members using parameters, with default values 0 for x, y, z and '\0' for vector_name.
  - **Member functions:**
    - **addition():** Adds two vectors and returns the result as a Vector3D object.
    - **display():** Prints the vector in the format "V = (vx, vy, vz)".
  - **Friend function:**
    - **crossProduct():** Computes the cross product of two vectors and returns the result as a Vector3D object.
- **main() Function Tasks:**
  - Create two vectors: V = (1, 2, 3) and W = (3, 2, 1).
  - Compute their sum and cross product.
  - Output the results.

**Sample Run:**

```
V = (1,2,3)
W = (3,2,1)
V + W = U = (4,4,4)
V × W = C = (-4,8,-4)
```

### Cevap

(Sınıf slaytlardaki gibi; `crossProduct`'ın gövdesini ve `main`'i slaytta olmadığı için ben yazdım. Son satırda `×` yerine `x` kullandım; `×` özel bir karakter ve bazı konsollarda bozuk görünür.)

```cpp
#include <iostream>
using namespace std;

class Vector3D {
private:
    int x, y, z; // Coordinates of the vector
    char vector_name;

public:
    // Constructor with default values
    Vector3D(int x = 0, int y = 0, int z = 0, char name = '\0') : x(x), y(y), z(z), vector_name(name) {}

    // Function to display the vector
    void display() {
        cout << vector_name << " = (" << x << "," << y << "," << z << ")" << endl;
    }

    // Member function to add two vectors
    Vector3D addition(const Vector3D &v) {
        return Vector3D(x + v.x, y + v.y, z + v.z, 'U'); // Resultant vector named 'U'
    }

    // Friend function to compute cross product
    friend Vector3D crossProduct(const Vector3D &v1, const Vector3D &v2);
};

// Friend function definition: cross product of two vectors
Vector3D crossProduct(const Vector3D &v1, const Vector3D &v2) {
    return Vector3D(v1.y * v2.z - v1.z * v2.y,
                    v1.z * v2.x - v1.x * v2.z,
                    v1.x * v2.y - v1.y * v2.x,
                    'C'); // Resultant vector named 'C'
}

int main() {
    Vector3D V(1, 2, 3, 'V');
    Vector3D W(3, 2, 1, 'W');

    V.display();
    W.display();

    Vector3D U = V.addition(W);
    cout << "V + W = ";
    U.display();

    Vector3D C = crossProduct(V, W);
    cout << "V x W = ";
    C.display();

    return 0;
}
```

### Açıklama

| | `addition` (üye) | `crossProduct` (friend) |
|---|---|---|
| Çağrılışı | `V.addition(W)` | `crossProduct(V, W)` |
| Kaç parametre? | 1 (diğeri V'nin kendisi) | 2 |
| İlk vektöre erişim | doğrudan `x`, `y`, `z` | `v1.x`, `v1.y`, `v1.z` |
| Gövdede `Vector3D::` var mı? | sınıfın içinde yazıldı | **yok** (üye değil) |

- İkisi de `return Vector3D(...)` ile **yeni bir nesne** oluşturup döndürüyor; V ve W değişmiyor.
- Constructor'daki `x(x)`: parantez dışındaki x **üye değişken**, içindeki x **parametre**. Initialization list'te isimler aynı olabilir.
- Parametreler `const Vector3D &`: kopya yok ve fonksiyon vektörleri değiştiremez.

**Hesap (V = (1,2,3), W = (3,2,1)):**
- Toplam: (1+3, 2+2, 3+1) = **(4, 4, 4)**
- Çapraz çarpım: x = 2·1 − 3·2 = **−4**; y = 3·3 − 1·1 = **8**; z = 1·2 − 2·3 = **−4**

---

## Ex 7

Create **a class Car** that stores a car's **brand, model, and year** of manufacture. Use **function chaining** for the functions **setBrand(), setModel(), and setYear()** to set the car's details. These functions should use the **this pointer** to update the information.

In your program, get **the brand, model, and year** of the car as input from the user and display the car's details. Ensure that the **setBrand(), setModel(), and setYear()** functions can be used in **a chainable way** on the same line.

**Sample Run:**

```
Enter car brand: TOGG
Enter car model: T10X
Enter manufacturing year: 2026

Car Details:
Brand: TOGG
Model: T10X
Year: 2026
```

### Cevap (hocanın çözümü)

```cpp
#include <iostream>
#include <string>
using namespace std;

class Car {
private:
    string brand;
    string model;
    int year;

public:
    // Default Constructor
    Car() : brand(""), model(""), year(0) {}

    // Function to set brand using function chaining
    Car& setBrand(string b) {
        this->brand = b;
        return *this; // Returning reference to the current object
    }

    // Function to set model using function chaining
    Car& setModel(string m) {
        this->model = m;
        return *this;
    }

    // Function to set year using function chaining
    Car& setYear(int y) {
        this->year = y;
        return *this;
    }

    // Function to display car details
    void display() const {
        cout << "Car Details:\n";
        cout << "Brand: " << brand << endl;
        cout << "Model: " << model << endl;
        cout << "Year: " << year << endl;
    }
};

int main() {
    Car myCar;

    string brand, model;
    int year;

    // Taking user input
    cout << "Enter car brand: ";
    cin >> brand;    // getline(cin, brand);

    cout << "Enter car model: ";
    cin >> model;    // getline(cin, model);

    cout << "Enter manufacturing year: ";
    cin >> year;

    // Using function chaining to set brand, model, and year in one statement
    myCar.setBrand(brand).setModel(model).setYear(year);

    // Displaying car details
    cout << "\n";
    myCar.display();

    return 0;
}
```

### Açıklama

- **Zincirleme için iki şart:** dönüş tipi **`Car&`** ve son satır **`return *this;`**. Her fonksiyon aynı arabayı geri verdiği için bir sonraki fonksiyon aynı araba üzerinde çalışır.
- **`this->brand = b;`:** Burada parametre adı (`b`) değişken adından farklı, yani `this->` zorunlu değil; soru "use the this pointer" dediği için yazılmış.
- **`display() const`:** fonksiyon sadece okuyor.
- **`cout << "\n";`:** örnek çıktıdaki **boş satırı** oluşturuyor.
- **`// getline(cin, brand);`:** marka boşluklu olsaydı ("Land Rover" gibi) `cin >>` yerine bunu kullanman gerekirdi.
- **Zincirleme satırı:** `myCar.setBrand(brand).setModel(model).setYear(year);`
