# CENG241 – Midterm Hazırlık Soruları

Bu dosyadaki sorular, Week 6 recitation'daki Ex 1–7 sorularına **benzer ama farklı** sorulardır.
Sadece derste, lab'larda ve recitation'da gördüğün konular var; **yeni konu yok**.
Bütün kodlar derlenip çalıştırıldı; cevaplardaki çıktılar gerçek çıktılardır.

**Nasıl çalışmalısın?**

1. Önce soruyu **kağıt üzerinde** çöz. Çıktı sorularında değişkenler için kutu çiz, satır satır güncelle.
2. Sonra dosyanın altındaki **CEVAPLAR** bölümüne bak.
3. Yanlış yaptıysan, cevaptaki adım tablosunda hangi satırda ayrıldığını bul.

| Soru | Tür | Benzediği recitation sorusu | Konu |
|---|---|---|---|
| 1 | Çıktı bulma | Ex 1 | constructor seçimi, `&`, varsayılan parametre, destructor sırası |
| 2 | Çıktı bulma | Ex 2 | aynı konular + sonradan oluşturulan üçüncü nesne |
| 3 | Çıktı bulma | Ex 3 | aynı isimli iki fonksiyon, `::`, yerel/global değişken |
| 4 | Çıktı bulma | (ders notları) | constructor/destructor sırası, nesne dizisi, varsayılan değer |
| 5 | Çıktı bulma | (ders notları) | namespace, template, varsayılan parametre |
| 6 | Hata bulma | (ders notları) | referans, const, private, namespace kuralları |
| 7 | Kod yazma | Ex 4 | nesne dizisi, destructor'da çıktı |
| 8 | Kod yazma | Ex 5 | iki constructor, `if / else if`, nesne dizisi |
| 9 | Kod yazma | Ex 6 | friend fonksiyon, nesne döndüren fonksiyon |
| 10 | Kod yazma | Ex 7 | `this` pointer, zincirleme (chaining) |

---

# SORULAR

## Bölüm A – What is the output?

### Soru 1

What is the output of the following program?

```cpp
#include <iostream>
using namespace std;

int counter = 20;

class Box {
    int w, h;
public:
    Box(int a, int b) : w(a), h(b) { counter -= 4; }
    Box(int s) { w = s; h = s * 2; }
    ~Box() { cout << w << " " << h << " " << counter << endl; }
    int resize(int&, int = 3);
};

int Box::resize(int& m, int n) {
    m -= 1;
    n *= 2;
    w += n;
    h -= m;
    cout << m << " " << n << endl;
    return m * n;
}

int main() {
    int x = 6, y = 2;
    Box b1(5), b2(1, 4);
    counter = b2.resize(x, y);
    counter = b1.resize(y);
    cout << x << " " << y << endl;
}
```

---

### Soru 2

What is the output of the following program?

```cpp
#include <iostream>
using namespace std;

int total = 3;

class Node {
    int a, b;
public:
    Node(int x, int y) : a(x), b(y) { total *= 2; }
    Node(int z) { a = z - 1; b = z + 1; }
    ~Node() { cout << a << " " << b << " " << total << endl; }
    int mix(int&, int = 2);
};

int Node::mix(int& m, int n) {
    m += b;
    n -= a;
    a *= 2;
    b += n;
    cout << m << " " << n << " " << a << " " << b << endl;
    return m + n;
}

int main() {
    int x = 1, y = 3;
    Node n1(4), n2(2, 5);
    total = n1.mix(x, y);
    Node n3(total);
    total = n3.mix(y);
    total = n2.mix(x);
    cout << x << " " << y << " " << total << endl;
}
```

---

### Soru 3

What is the output of the following program? (Dikkat: `update` adında **iki** fonksiyon var.)

```cpp
#include <iostream>
using namespace std;

int value = 5;

class Data {
    int p, q;
public:
    Data(int x = 2, int y = 4) : p(x), q(y) {}
    void update(int&, int);
    void update(int&);
    void show() { cout << "p=" << p << " q=" << q << endl; }
};

void Data::update(int &a, int b) {
    int value = p + q;
    a = value;
    b = ::value;
    ::value = b + q;
    p = b;
}

void Data::update(int &b) {
    ::value -= 1;
    b += p;
    q = ::value + b;
}

int main() {
    Data d1, d2(7), d3(1, 3);
    int x = 10, y = 20;

    d1.update(x, y);
    d1.show();
    cout << x << " " << y << " " << value << endl;

    d2.update(y);
    d2.show();
    cout << x << " " << y << " " << value << endl;

    d3.update(x, x);
    d3.show();
    cout << x << " " << y << " " << value << endl;

    return 0;
}
```

---

### Soru 4

What is the output of the following program? (Çıktı tek satırdır.)

```cpp
#include <iostream>
using namespace std;

class Item {
    int id;
public:
    Item(int i = 0) : id(i) { cout << "C" << id << " "; }
    ~Item() { cout << "D" << id << " "; }
};

int main() {
    Item a(1);
    cout << "| ";
    Item arr[3] = {7, 8, 9};
    cout << "| ";
    Item b;
    Item c(4);
    cout << "| ";
    return 0;
}
```

---

### Soru 5

What is the output of the following program?

```cpp
#include <iostream>
using namespace std;

namespace A {
    int x = 3;
    int f(int a, int b = 2) { return a * b; }
}

namespace B {
    int x = 7;
    int f(int a) { return a + x; }
}

template <class T>
T bigger(T a, T b) {
    if (a > b)
        return a;
    return b;
}

int x = 1;

int main() {
    int x = 10;
    cout << x << " " << ::x << " " << A::x << " " << B::x << endl;
    cout << A::f(4) << " " << A::f(4, 5) << " " << B::f(4) << endl;
    cout << bigger(3, 8) << " " << bigger(2.5, 1.5) << " " << bigger('a', 'c') << endl;
    return 0;
}
```

---

## Bölüm B – Find the errors

### Soru 6

Aşağıdaki 7 kod parçasının **hangileri derleme hatası verir? Neden?**
Hata vermeyen varsa çıktısını yaz.
(Hepsinin başında `#include <iostream>` ve `using namespace std;` olduğunu düşün.)

**a)**
```cpp
int main() {
    int a = 5;
    int &r;
    r = a;
    cout << r;
}
```

**b)**
```cpp
void f(const int &x) {
    x = 10;
}
int main() {
    int a = 8;
    f(a);
    cout << a;
}
```

**c)**
```cpp
class A {
    const int c;
public:
    A(int x) { c = x; }
};
int main() {
    A a(3);
}
```

**d)**
```cpp
class B {
    int v;
public:
    B(int x) : v(x) {}
    void show() const { v = v + 1; cout << v; }
};
int main() {
    B b(1);
    b.show();
}
```

**e)**
```cpp
class D {
    int v;
public:
    D(int x = 0) : v(x) {}
};
int main() {
    D d(4);
    cout << d.v;
}
```

**f)**
```cpp
namespace first { int x = 5; }
namespace second { int x = 10; }
using namespace first;
using namespace second;
int main() {
    cout << x << endl;
}
```

**g)**
```cpp
class E {
    int v;
public:
    E(int x = 0) : v(x) {}
    E& add(int n) { v += n; return *this; }
    void show() const { cout << v << endl; }
};
int main() {
    E e;
    e.add(2).add(3).show();
}
```

---

## Bölüm C – Write the program

### Soru 7

Write a C++ program to calculate parking fees in a car park.
Define a **class Vehicle** including the following:

**Data Members:** *plateNo, ratePerHour, hours, fee*

**Member Functions:**
- **input():** To input the plate number, hourly rate, and hours parked.
- **calculateFee():** To calculate the fee (fee = ratePerHour * hours). If the vehicle is parked **more than 10 hours**, a **20% discount** is applied.
- **Destructor (~Vehicle()):** To output the plate number and the calculated fee.

The main function should declare an array for up to 50 vehicles, take their input,
and output their plate numbers along with their fees.

**Türkçesi:** Otopark ücreti hesaplayan bir program. `Vehicle` sınıfı yaz. Ücret = saatlik ücret × saat;
10 saatten fazla kalana %20 indirim. Sonuçları **destructor** yazdıracak. En fazla 50 araçlık dizi kullan.

Sample Run:

```
Enter number of vehicles (max 50): 3
Input plate no, hourly rate, hours: 34 15 4
Input plate no, hourly rate, hours: 6 20 12
Input plate no, hourly rate, hours: 35 10 2.5
Fee of vehicle 35 is 25
Fee of vehicle 6 is 192
Fee of vehicle 34 is 60
```

**Ek soru:** Araçlar neden girildikleri sıranın **tersine** yazdırıldı?

---

### Soru 8

Write a C++ program to compute the delivery fee of packages in a cargo company.
The company rules are as follows:

- All packages pay a base fee of **50 TL**.
- Packages with a weight **>= 20** kg pay an additional **60 TL**.
- Packages with a weight **>= 10** kg pay an additional **35 TL**.
- Packages with a weight **>= 5** kg pay an additional **15 TL**.

In your program, include the following:

- Define a **Package** class with the private data members: *package_id, receiver, weight, fee*
- **Constructors:**
  - A default constructor initializing *package_id* and *weight* to 0.
  - A parameterized constructor initializing *package_id, receiver,* and *weight*.
- **Functions:**
  - **read():** Reads package details.
  - **computeFee():** Computes the fee of the package.
  - **display():** Displays the receiver and the fee.
  - **displayPackageInfo():** Displays package details for your own package object.

The main() function should:
- Create an object for your own package and print its fee (e.g. 501 Ayse 12.5).
- Create an at most 50 element array of packages, read their data, and compute their fees.

**Türkçesi:** Kargo ücreti hesaplayan program. Temel ücret 50 TL; ağırlığa göre ek ücret eklenir
(sadece **en yüksek** uyan kural uygulanır). İki constructor, dört fonksiyon ve 50 elemanlı nesne dizisi isteniyor.

Sample Run:

```
501 Ayse 12.5
Ayse pays 85 TL.
Enter number of packages: 3
Enter package ID, receiver, and weight: 601 Ali 22
Ali pays 110 TL.
Enter package ID, receiver, and weight: 602 Zeynep 7.5
Zeynep pays 65 TL.
Enter package ID, receiver, and weight: 603 Can 3
Can pays 50 TL.
```

---

### Soru 9

Write a C++ program for basic fraction operations as described below:

- A fraction is represented using two integers: `f = num / den`
- The multiplication of two fractions results in another fraction:
  `a * b = (a.num * b.num) / (a.den * b.den)`
- The addition of two fractions produces another fraction:
  `a + b = (a.num * b.den + b.num * a.den) / (a.den * b.den)`
- Define a **class Fraction** which consists of:
  - **Data members:** Two integers (*num, den*) and a single character (*fraction_name*) to label the fraction.
  - **Constructor:** Initializes data members using parameters, with default values 0 for num, 1 for den, and '\0' for fraction_name.
  - **Member functions:**
    - **multiply():** Multiplies two fractions and returns the result as a Fraction object (named 'M').
    - **display():** Prints the fraction in the format "A = num/den".
  - **Friend function:**
    - **addFractions():** Adds two fractions and returns the result as a Fraction object (named 'S').
- **main() Function Tasks:**
  - Create two fractions: A = 1/2 and B = 3/4.
  - Compute their product and sum.
  - Output the results. (You do not need to simplify the fractions.)

**Türkçesi:** Kesir sınıfı. Çarpma **üye fonksiyon**, toplama **friend fonksiyon** olacak; ikisi de yeni bir
`Fraction` nesnesi döndürecek. Sadeleştirme yapmana gerek yok.

Sample Run:

```
A = 1/2
B = 3/4
A * B = M = 3/8
A + B = S = 10/8
```

---

### Soru 10

Create **a class Book** that stores a book's **title, author, and number of pages**.
Use **function chaining** for the functions **setTitle(), setAuthor(), and setPages()** to set the
book's details. The parameter names must be **the same as the data member names**, so these
functions should use the **this pointer** to update the information.

In your program, get **the title, author, and number of pages** as input from the user
(the title and the author may contain spaces) and display the book's details. Ensure that the
**setTitle(), setAuthor(), and setPages()** functions are used in **a chainable way** on the same line.

**Türkçesi:** `Book` sınıfı. Üç set fonksiyonu **tek satırda zincirleme** çağrılabilmeli. Parametre isimleri
değişken isimleriyle aynı olacağı için `this->` kullanmak zorundasın. Başlık ve yazar boşluk içerebilir.

Sample Run:

```
Enter book title: Les Miserables
Enter author: Victor Hugo
Enter number of pages: 1462

Book Details:
Title: Les Miserables
Author: Victor Hugo
Pages: 1462
```

---
---

# CEVAPLAR

## Cevap 1

**Output:**

```
5 4
1 6
5 1
5 -1 6
11 9 6
```

**Çözüm (kutucuklarla):**

Başlangıç: `counter = 20`, `x = 6`, `y = 2`

**1) `Box b1(5)`** → tek sayı var, `Box(int s)` çalışır: w = 5, h = 5 × 2 = 10. counter'a dokunmaz.

**2) `b2(1, 4)`** → iki sayı var, `Box(int a, int b)` çalışır: w = 1, h = 4, counter = 20 − 4 = **16**.

```
counter = 16
x = 6    y = 2
b1:  w = 5   h = 10
b2:  w = 1   h = 4
```

**3) `counter = b2.resize(x, y);`** → m = **x'in kendisi**, n = y'nin **kopyası** (2). w ve h **b2'nin**.

| Satır | Ne oluyor? |
|---|---|
| `m -= 1;` | m = 6 − 1 = 5 → **x = 5** |
| `n *= 2;` | n = 2 × 2 = 4 (y hâlâ 2) |
| `w += n;` | b2.w = 1 + 4 = **5** |
| `h -= m;` | b2.h = 4 − 5 = **−1** |
| `cout` | ekrana **`5 4`** |
| `return m * n;` | 5 × 4 = 20 → **counter = 20** |

**4) `counter = b1.resize(y);`** → tek değer gönderildi: m = **y'nin kendisi**, n = **3** (varsayılan). w ve h **b1'in**.

| Satır | Ne oluyor? |
|---|---|
| `m -= 1;` | m = 2 − 1 = 1 → **y = 1** |
| `n *= 2;` | n = 3 × 2 = 6 |
| `w += n;` | b1.w = 5 + 6 = **11** |
| `h -= m;` | b1.h = 10 − 1 = **9** |
| `cout` | ekrana **`1 6`** |
| `return m * n;` | 1 × 6 = 6 → **counter = 6** |

**5) `cout << x << " " << y`** → **`5 1`**

**6) main biter, destructor'lar ters sırayla:** önce b2 → **`5 -1 6`**, sonra b1 → **`11 9 6`**

**Tuzaklar:** `b1(5)` counter'ı değiştirmez. `h -= m` satırında m'nin **yeni** değeri kullanılır. Destructor'lar counter'ın **son** değerini (6) yazar.

---

## Cevap 2

**Output:**

```
6 0 6 5
10 -3 10 4
11 0 4 5
11 10 11
10 4 11
4 5 11
6 5 11
```

**Çözüm:**

Başlangıç: `total = 3`, `x = 1`, `y = 3`

**1) `Node n1(4)`** → tek sayı: a = 4 − 1 = 3, b = 4 + 1 = 5.

**2) `n2(2, 5)`** → iki sayı: a = 2, b = 5, total = 3 × 2 = **6**.

```
total = 6
x = 1    y = 3
n1:  a = 3   b = 5
n2:  a = 2   b = 5
```

**3) `total = n1.mix(x, y);`** → m = x'in kendisi (1), n = y'nin kopyası (3), a ve b **n1'in**.

| Satır | Ne oluyor? |
|---|---|
| `m += b;` | m = 1 + 5 = 6 → **x = 6** |
| `n -= a;` | n = 3 − 3 = 0 |
| `a *= 2;` | n1.a = 3 × 2 = **6** |
| `b += n;` | n1.b = 5 + 0 = **5** |
| `cout` | ekrana **`6 0 6 5`** |
| `return m + n;` | 6 + 0 = 6 → **total = 6** |

**4) `Node n3(total);`** → total şu an 6, yani `n3(6)`. Tek sayı: a = 6 − 1 = 5, b = 6 + 1 = 7.

**5) `total = n3.mix(y);`** → m = y'nin kendisi (3), n = **2** (varsayılan), a ve b **n3'ün**.

| Satır | Ne oluyor? |
|---|---|
| `m += b;` | m = 3 + 7 = 10 → **y = 10** |
| `n -= a;` | n = 2 − 5 = −3 |
| `a *= 2;` | n3.a = 5 × 2 = **10** |
| `b += n;` | n3.b = 7 + (−3) = **4** |
| `cout` | ekrana **`10 -3 10 4`** |
| `return m + n;` | 10 + (−3) = 7 → **total = 7** |

**6) `total = n2.mix(x);`** → m = x'in kendisi (6), n = 2 (varsayılan), a ve b **n2'nin**.

| Satır | Ne oluyor? |
|---|---|
| `m += b;` | m = 6 + 5 = 11 → **x = 11** |
| `n -= a;` | n = 2 − 2 = 0 |
| `a *= 2;` | n2.a = 2 × 2 = **4** |
| `b += n;` | n2.b = 5 + 0 = **5** |
| `cout` | ekrana **`11 0 4 5`** |
| `return m + n;` | 11 + 0 = 11 → **total = 11** |

```
total = 11
x = 11   y = 10
n1:  a = 6    b = 5
n2:  a = 4    b = 5
n3:  a = 10   b = 4
```

**7) `cout << x << y << total`** → **`11 10 11`**

**8) main biter, destructor'lar ters sırayla:** n3 → **`10 4 11`**, n2 → **`4 5 11`**, n1 → **`6 5 11`**

**Tuzaklar:**
- `n3(total)` yazıldığı anda total **6**'dır; n3 o değerle oluşur. total sonradan değişse de n3'ün a ve b'si etkilenmez.
- n3 en son oluşturuldu, bu yüzden **ilk o** yok olur.
- Üç destructor da total'in **son** değerini (11) yazar.

---

## Cevap 3

**Output:**

```
p=5 q=4
6 20 9
p=7 q=35
6 27 8
p=8 q=3
4 27 11
```

**Çözüm:**

Constructor'da iki parametrenin de varsayılan değeri var (`x = 2, y = 4`):

| Nesne | p | q |
|---|---|---|
| `d1` (değer yok) | 2 | 4 |
| `d2(7)` | 7 | 4 |
| `d3(1, 3)` | 1 | 3 |

Başlangıç: `value = 5` (global), `x = 10`, `y = 20`

**Hangi `update` çalışır?** İki değer gönderilirse `update(int&, int)`, tek değer gönderilirse `update(int&)`.

**1) `d1.update(x, y);`** → iki değer. a = **x'in kendisi**, b = y'nin **kopyası** (20).

| Satır | Ne oluyor? |
|---|---|
| `int value = p + q;` | **yerel** value = 2 + 4 = 6 (global value değişmedi!) |
| `a = value;` | yerel value kullanılır → **x = 6** |
| `b = ::value;` | b = global value = 5 (y hâlâ 20) |
| `::value = b + q;` | global value = 5 + 4 = **9** |
| `p = b;` | d1.p = **5** |

`d1.show()` → **`p=5 q=4`** ; sonraki satır → **`6 20 9`**

**2) `d2.update(y);`** → tek değer. b = **y'nin kendisi** (20).

| Satır | Ne oluyor? |
|---|---|
| `::value -= 1;` | global value = 9 − 1 = **8** |
| `b += p;` | b = 20 + 7 = 27 → **y = 27** |
| `q = ::value + b;` | d2.q = 8 + 27 = **35** |

`d2.show()` → **`p=7 q=35`** ; sonraki satır → **`6 27 8`**

**3) `d3.update(x, x);`** → iki değer. a = **x'in kendisi**, b = x'in **kopyası** (6).

| Satır | Ne oluyor? |
|---|---|
| `int value = p + q;` | yerel value = 1 + 3 = 4 |
| `a = value;` | **x = 4** |
| `b = ::value;` | b = 8 |
| `::value = b + q;` | global value = 8 + 3 = **11** |
| `p = b;` | d3.p = **8** |

`d3.show()` → **`p=8 q=3`** ; sonraki satır → **`4 27 11`**

**Tuzaklar:**
- Fonksiyonun içinde `int value` tanımlandığı için sadece `value` yazınca **yerel** olan, `::value` yazınca **global** olan kullanılır.
- `main`'deki `cout << value` globali yazar (main'de yerel value yok).
- `update(x, x)`: aynı değişken hem referansa hem kopyaya gidiyor. Kopya, çağrı anındaki değeri (6) alır.
- Bu soruda destructor yok, program sonunda ekstra satır çıkmaz.

---

## Cevap 4

**Output:**

```
C1 | C7 C8 C9 | C0 C4 | D4 D0 D9 D8 D7 D1
```

**Çözüm:**

`Item(int i = 0)`: değer verilmezse id = 0. Constructor `C` + id, destructor `D` + id yazar.

| Satır | Ne oluyor? | Ekran |
|---|---|---|
| `Item a(1);` | a oluşur | `C1` |
| `cout << "\| ";` | | `\|` |
| `Item arr[3] = {7, 8, 9};` | 3 nesne; her değer bir elemana gider | `C7 C8 C9` |
| `cout << "\| ";` | | `\|` |
| `Item b;` | değer yok → id = **0** (varsayılan) | `C0` |
| `Item c(4);` | c oluşur | `C4` |
| `cout << "\| ";` | | `\|` |
| main biter | oluşturulma sırasının **tersi**: c, b, arr, a | `D4 D0 D9 D8 D7 D1` |

**Tuzaklar:**
- `Item b;` satırında parantez yok ama constructor yine çalışır; id varsayılan değeri (0) alır.
- Dizinin elemanları da **kendi içinde ters sırayla** yok olur: önce arr[2] (9), sonra arr[1] (8), en son arr[0] (7).
- Bütün `D` yazıları son `|` işaretinden **sonra** çıkar, çünkü nesneler `main` bitince yok olur.

---

## Cevap 5

**Output:**

```
10 1 3 7
8 20 11
8 2.5 c
```

**Çözüm:**

**1. satır:** Dört farklı `x` var.

| Yazım | Hangi x? | Değer |
|---|---|---|
| `x` | main içindeki yerel | 10 |
| `::x` | global | 1 |
| `A::x` | A namespace'indeki | 3 |
| `B::x` | B namespace'indeki | 7 |

**2. satır:**

| Çağrı | Hesap | Sonuç |
|---|---|---|
| `A::f(4)` | b verilmedi, varsayılan 2 → 4 × 2 | 8 |
| `A::f(4, 5)` | 4 × 5 | 20 |
| `B::f(4)` | a + x; fonksiyon B'nin içinde olduğu için x = **B::x = 7** → 4 + 7 | 11 |

**3. satır:** `bigger` bir template; T, gönderilen değerlere göre belirlenir.

| Çağrı | T | Sonuç |
|---|---|---|
| `bigger(3, 8)` | int | 8 |
| `bigger(2.5, 1.5)` | double | 2.5 |
| `bigger('a', 'c')` | char | c (harfler alfabedeki sıralarına göre karşılaştırılır) |

**Tuzak:** `B::f` içindeki `x`, main'deki 10 ya da global 1 değil; fonksiyonun **kendi namespace'indeki** x'tir.

---

## Cevap 6

| | Sonuç | Neden? |
|---|---|---|
| **a** | **HATA** | Referans, tanımlandığı satırda bir değişkene bağlanmalı. Doğrusu: `int &r = a;` |
| **b** | **HATA** | `const int &x` salt okunurdur; `x = 10;` yazılamaz. (Derste gördüğün "assignment of read-only reference" hatası.) |
| **c** | **HATA** | `const` üyeye constructor gövdesinde atama yapılamaz. Doğrusu: `A(int x) : c(x) { }` |
| **d** | **HATA** | Sonunda `const` olan fonksiyon nesnenin değişkenlerini değiştiremez (`v = v + 1` yasak). |
| **e** | **HATA** | `v` private; `main` içinden `d.v` yazılamaz. Okumak için public bir `getV()` fonksiyonu gerekir. |
| **f** | **HATA** | İki namespace'te de `x` var ve ikisi de `using` ile açılmış. `x` yazınca hangisi olduğu belirsiz. Doğrusu: `first::x` ya da `second::x` |
| **g** | **Hata yok** | Çıktı: `5`. `E e;` → v = 0 (varsayılan); `add(2)` → 2; `add(3)` → 5; `show()` → 5. |

---

## Cevap 7

```cpp
#include <iostream>
using namespace std;

class Vehicle {
private:
    int plateNo;
    double ratePerHour, hours, fee;

public:
    void input() {
        cout << "Input plate no, hourly rate, hours: ";
        cin >> plateNo >> ratePerHour >> hours;
    }

    void calculateFee() {
        fee = ratePerHour * hours;
        if (hours > 10)
            fee = fee * 0.8;
    }

    ~Vehicle() {
        cout << "Fee of vehicle " << plateNo << " is " << fee << endl;
    }
};

int main() {
    const int SIZE = 50;
    int n;

    cout << "Enter number of vehicles (max 50): ";
    cin >> n;

    if (n > SIZE) {
        cout << "Max number of vehicles is 50. Setting n to 50." << endl;
        n = SIZE;
    }

    Vehicle vehicles[n];

    for (int i = 0; i < n; i++) {
        vehicles[i].input();
        vehicles[i].calculateFee();
    }

    return 0;
}
```

**Sample Run:**

```
Enter number of vehicles (max 50): 3
Input plate no, hourly rate, hours: 34 15 4
Input plate no, hourly rate, hours: 6 20 12
Input plate no, hourly rate, hours: 35 10 2.5
Fee of vehicle 35 is 25
Fee of vehicle 6 is 192
Fee of vehicle 34 is 60
```

**Hesaplar:** 15 × 4 = 60 · 20 × 12 = 240, 10 saatten fazla olduğu için 240 × 0.8 = 192 · 10 × 2.5 = 25

**Ek sorunun cevabı:** Sonuçları **destructor** yazdırıyor. `main` bitince dizideki nesneler
**oluşturulma sırasının tersine** yok edilir: önce son eleman, en son ilk eleman. Bu yüzden 35 → 6 → 34 sırası çıkıyor.
(Ex 4'ün örnek çıktısında da 102, 101'den önce yazılıyordu.)

**Dikkat edilecekler:**
- Hocanın Ex 4 çözümüyle **aynı kalıp**: `input()`, hesaplama fonksiyonu, sonucu yazdıran destructor, `Sinif dizi[n];` ve `for` döngüsü.
- `main` içinde sonucu yazdıran bir `cout` yok; yazdırma işi destructor'da.
- `fee = fee * 0.8;` → %20 indirim, ücretin %80'ini almak demek.
- `hours > 10` yazıldı, `>=` değil: soru "**more than** 10 hours" diyor.

---

## Cevap 8

```cpp
#include <iostream>
#include <string>
using namespace std;

class Package {
private:
    int package_id;
    string receiver;
    float weight;
    int fee;

public:
    Package() : package_id(0), weight(0.0), fee(50) {}

    Package(int id, string r, float w) : package_id(id), receiver(r), weight(w) {
        computeFee();
    }

    void read() {
        cout << "Enter package ID, receiver, and weight: ";
        cin >> package_id >> receiver >> weight;
        computeFee();
    }

    void computeFee() {
        fee = 50;
        if (weight >= 20)
            fee += 60;
        else if (weight >= 10)
            fee += 35;
        else if (weight >= 5)
            fee += 15;
    }

    void display() {
        cout << receiver << " pays " << fee << " TL." << endl;
    }

    void displayPackageInfo() {
        cout << package_id << " " << receiver << " " << weight << endl;
    }
};

int main() {
    Package mine(501, "Ayse", 12.5);
    mine.displayPackageInfo();
    mine.display();

    const int SIZE = 50;
    Package packages[SIZE];
    int n;

    cout << "Enter number of packages: ";
    cin >> n;

    if (n > SIZE)
        n = SIZE;

    for (int i = 0; i < n; i++) {
        packages[i].read();
        packages[i].display();
    }

    return 0;
}
```

**Sample Run:**

```
501 Ayse 12.5
Ayse pays 85 TL.
Enter number of packages: 3
Enter package ID, receiver, and weight: 601 Ali 22
Ali pays 110 TL.
Enter package ID, receiver, and weight: 602 Zeynep 7.5
Zeynep pays 65 TL.
Enter package ID, receiver, and weight: 603 Can 3
Can pays 50 TL.
```

**Hesaplar:** 12.5 kg → 50 + 35 = 85 · 22 kg → 50 + 60 = 110 · 7.5 kg → 50 + 15 = 65 · 3 kg → 50

**Dikkat edilecekler:**
- `if / else if / else if` zinciri **büyükten küçüğe** yazılmalı. Tersten yazarsan (önce `>= 5`) 22 kg'lık paket de ilk koşula girer ve sadece 15 TL eklenir.
- `else if` kullanıldığı için sadece **ilk uyan** koşul çalışır. Üç ayrı `if` yazsaydın 22 kg için 60 + 35 + 15 eklenirdi (yanlış).
- `Package packages[SIZE];` satırı 50 nesne için **parametresiz constructor**'ı çağırır. O constructor olmasaydı bu satır hata verirdi.
- Parametreli constructor ve `read()` işlerinin sonunda `computeFee()` çağırıyor; böylece `fee` her zaman güncel.

---

## Cevap 9

```cpp
#include <iostream>
using namespace std;

class Fraction {
private:
    int num, den;
    char fraction_name;

public:
    Fraction(int n = 0, int d = 1, char name = '\0') : num(n), den(d), fraction_name(name) {}

    void display() {
        cout << fraction_name << " = " << num << "/" << den << endl;
    }

    Fraction multiply(const Fraction &f) {
        return Fraction(num * f.num, den * f.den, 'M');
    }

    friend Fraction addFractions(const Fraction &f1, const Fraction &f2);
};

Fraction addFractions(const Fraction &f1, const Fraction &f2) {
    return Fraction(f1.num * f2.den + f2.num * f1.den, f1.den * f2.den, 'S');
}

int main() {
    Fraction A(1, 2, 'A'), B(3, 4, 'B');

    A.display();
    B.display();

    Fraction M = A.multiply(B);
    cout << "A * B = ";
    M.display();

    Fraction S = addFractions(A, B);
    cout << "A + B = ";
    S.display();

    return 0;
}
```

**Output:**

```
A = 1/2
B = 3/4
A * B = M = 3/8
A + B = S = 10/8
```

**Hesaplar:** A × B = (1 × 3) / (2 × 4) = 3/8 · A + B = (1 × 4 + 3 × 2) / (2 × 4) = 10/8

**Dikkat edilecekler:**

| | `multiply` (üye) | `addFractions` (friend) |
|---|---|---|
| Çağrılışı | `A.multiply(B)` | `addFractions(A, B)` |
| Kaç parametre? | 1 (diğeri `A`'nın kendisi) | 2 |
| Birinci kesre erişim | doğrudan `num`, `den` | `f1.num`, `f1.den` |
| Gövdede `Fraction::` var mı? | sınıfın içinde yazıldı | **yok** (üye değil) |

- `friend` kelimesi sadece sınıfın **içindeki** bildirimde yazılır; dışarıdaki gövdede tekrar yazılmaz.
- `return Fraction(..., ..., 'M');` → constructor çağrılarak **yeni bir nesne** oluşturulup döndürülüyor.
- Parametreler `const Fraction &`: kopya yapılmaz ve fonksiyon gelen kesri değiştiremez.

---

## Cevap 10

```cpp
#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string title;
    string author;
    int pages;

public:
    Book() : title(""), author(""), pages(0) {}

    Book& setTitle(string title) {
        this->title = title;
        return *this;
    }

    Book& setAuthor(string author) {
        this->author = author;
        return *this;
    }

    Book& setPages(int pages) {
        this->pages = pages;
        return *this;
    }

    void display() const {
        cout << "Book Details:" << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Pages: " << pages << endl;
    }
};

int main() {
    Book myBook;

    string title, author;
    int pages;

    cout << "Enter book title: ";
    getline(cin, title);

    cout << "Enter author: ";
    getline(cin, author);

    cout << "Enter number of pages: ";
    cin >> pages;

    myBook.setTitle(title).setAuthor(author).setPages(pages);

    cout << endl;
    myBook.display();

    return 0;
}
```

**Sample Run:**

```
Enter book title: Les Miserables
Enter author: Victor Hugo
Enter number of pages: 1462

Book Details:
Title: Les Miserables
Author: Victor Hugo
Pages: 1462
```

**Dikkat edilecekler:**
- Dönüş tipi **`Book&`** ve her fonksiyonun sonunda **`return *this;`** olmalı. Zincirleme bu ikisi sayesinde çalışır.
- Parametre adı ile değişken adı aynı (`title`), bu yüzden `this->title = title;` yazmak **zorunlu**. Sadece `title = title;` yazarsan parametre kendisine atanır, nesne değişmez.
- `getline(cin, title);` boşluklu metni satır sonuna kadar okur. `cin >> title;` sadece ilk kelimeyi (`Les`) alırdı.
- `display() const`: fonksiyon sadece okuyor, değiştirmiyor.
- Zincirleme satırı: `myBook.setTitle(title).setAuthor(author).setPages(pages);`
