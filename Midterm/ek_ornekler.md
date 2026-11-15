# CENG241 – Ek Örnekler

Bu dosyadaki örneklerin **hepsi** derste, lab'larda ve recitation'da gördüğün konulardan.
**Yeni konu yok**; aynı konuların farklı örnekleri var.
Bütün kodlar derlenip çalıştırıldı; çıktılar gerçek çıktılardır.

**Nasıl çalışmalısın?** Önce kodu oku ve çıktıyı **tahmin et**, sonra aşağıdaki çıktıyla karşılaştır.

| Örnek | Konu | Bu konuyu nerede gördün? |
|---|---|---|
| 1 | Yerel ve global değişken, `::` | ders (`::x` örneği), Ex 3 |
| 2 | Template + referans | ders (`sum` template'i, `f(int, int&)`) |
| 3 | Aynı isimli fonksiyonlar + varsayılan parametre | Labwork 1 (Calculator), ders (`f(int x=1, int y=5)`) |
| 4 | Struct template | Labwork 1 (TelemetryProcessor) |
| 5 | `const` ve referans üye: initialization list | ders (class R, class S) |
| 6 | Dinamik bellek kullanan sınıf | ders (class B, `parr`), Labwork 2 |
| 7 | Zincirlemede `&` unutulursa | Labwork 3, Ex 7, personType |
| 8 | Yeni nesne döndüren fonksiyon | Ex 6, ders (Complex `add`) |
| 9 | `const` referans parametre ve `const` fonksiyon | Ex 6, Labwork 4, personType |
| 10 | `.` , `->` ve `(*p).` | ders (Rational) |
| 11 | Friend class | ders (class A / class B) |
| 12 | İki sınıfın ortak friend fonksiyonu | ders (Complex `add`, `class B;` ön bildirimi) |

---

## Örnek 1 – Yerel ve global değişken, `::`

```cpp
#include <iostream>
using namespace std;

int x = 1;

void change() {
    int x = 5;
    ::x = ::x + x;
    cout << x << " " << ::x << endl;
}

int main() {
    int x = 2;

    change();
    cout << x << " " << ::x << endl;

    change();
    cout << x << " " << ::x << endl;

    return 0;
}
```

**Çıktı:**

```
5 6
2 6
5 11
2 11
```

**Ne öğretiyor?**

Üç tane `x` var: global (1), `change` fonksiyonunun yereli (5), `main`'in yereli (2).

| Satır | Ne oluyor? | Ekran |
|---|---|---|
| 1. `change()` | yerel x = 5; global x = 1 + 5 = 6 | `5 6` |
| `cout` (main) | main'in x'i 2, global 6 | `2 6` |
| 2. `change()` | yerel x **yeniden** 5; global x = 6 + 5 = 11 | `5 11` |
| `cout` (main) | main'in x'i hâlâ 2, global 11 | `2 11` |

- Sadece `x` yazınca **o fonksiyonun yereli**, `::x` yazınca **global** kullanılır.
- Yerel değişken fonksiyon **her çağrıldığında baştan** oluşur (hep 5).
- Global değişken değerini **korur** (1 → 6 → 11).
- `change` fonksiyonu `main`'in yerel x'ine (2) **hiç dokunamaz**.

---

## Örnek 2 – Template + referans

```cpp
#include <iostream>
using namespace std;

template <class T>
void swapValues(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

template <class T>
void noSwap(T a, T b) {
    T temp = a;
    a = b;
    b = temp;
}

int main() {
    int a = 3, b = 7;
    noSwap(a, b);
    cout << a << " " << b << endl;

    swapValues(a, b);
    cout << a << " " << b << endl;

    double c = 1.5, d = 2.5;
    swapValues(c, d);
    cout << c << " " << d << endl;

    return 0;
}
```

**Çıktı:**

```
3 7
7 3
2.5 1.5
```

**Ne öğretiyor?**

İki fonksiyonun gövdesi **aynı**; tek fark parametrelerdeki `&`.

- `noSwap(T a, T b)`: `&` yok. Sadece **kopyalar** yer değiştirir; main'deki a ve b aynı kalır → `3 7`.
- `swapValues(T &a, T &b)`: `&` var. main'deki değişkenlerin **kendileri** yer değiştirir → `7 3`.
- Aynı fonksiyon `int` için de `double` için de çalışıyor: **template** sayesinde (T = int, sonra T = double).

---

## Örnek 3 – Aynı isimli fonksiyonlar + varsayılan parametre

```cpp
#include <iostream>
using namespace std;

int area(int side) { return side * side; }
int area(int w, int h) { return w * h; }
double area(double r) { return 3.14 * r * r; }

void print(int a, int b = 10, int c = 100) {
    cout << a << " " << b << " " << c << endl;
}

int main() {
    cout << area(4) << endl;
    cout << area(4, 5) << endl;
    cout << area(2.0) << endl;

    print(1);
    print(1, 2);
    print(1, 2, 3);

    return 0;
}
```

**Çıktı:**

```
16
20
12.56
1 10 100
1 2 100
1 2 3
```

**Ne öğretiyor?**

**Function overloading:** Üç tane `area` var. Derleyici, gönderilen değerlerin **sayısına ve tipine** bakarak seçer.

| Çağrı | Çalışan fonksiyon | Sonuç |
|---|---|---|
| `area(4)` | `area(int side)` | 4 × 4 = 16 |
| `area(4, 5)` | `area(int w, int h)` | 4 × 5 = 20 |
| `area(2.0)` | `area(double r)` | 3.14 × 2 × 2 = 12.56 |

**Tuzak:** `area(2)` yazsaydın (noktasız) **int** sürümü çalışır ve 4 çıkardı. `2.0` yazdığın için double sürümü çalıştı.

**Varsayılan parametre:** Gönderilen değerler **soldan sağa** yerleşir, eksik kalanlar varsayılan değeri alır.

| Çağrı | a | b | c |
|---|---|---|---|
| `print(1)` | 1 | 10 (varsayılan) | 100 (varsayılan) |
| `print(1, 2)` | 1 | 2 | 100 (varsayılan) |
| `print(1, 2, 3)` | 1 | 2 | 3 |

---

## Örnek 4 – Struct template

```cpp
#include <iostream>
using namespace std;

template <class T>
struct Pair {
    T first;
    T second;

    T sum() { return first + second; }

    void swapItems() {
        T temp = first;
        first = second;
        second = temp;
    }
};

int main() {
    Pair<int> p;
    p.first = 3;
    p.second = 9;
    cout << p.sum() << endl;

    Pair<double> d;
    d.first = 1.5;
    d.second = 2.25;
    d.swapItems();
    cout << d.first << " " << d.second << " " << d.sum() << endl;

    return 0;
}
```

**Çıktı:**

```
12
2.25 1.5 3.75
```

**Ne öğretiyor?**

Labwork 1'deki `TelemetryProcessor<double>` ile aynı kalıp.

- `template <class T>` struct'ın üstüne yazılır; içerideki bütün `T`'ler sonradan seçilen tipe dönüşür.
- Nesne oluştururken tipi **sen yazarsın**: `Pair<int>`, `Pair<double>`.
- `struct` olduğu için üyeler varsayılan olarak **public**; `p.first = 3;` diye doğrudan erişebiliyoruz.

| Nesne | T | first, second | İşlem | Ekran |
|---|---|---|---|---|
| `Pair<int> p` | int | 3, 9 | `sum()` → 3 + 9 | `12` |
| `Pair<double> d` | double | 1.5, 2.25 | `swapItems()` → 2.25, 1.5; `sum()` → 3.75 | `2.25 1.5 3.75` |

---

## Örnek 5 – `const` ve referans üye: initialization list

```cpp
#include <iostream>
using namespace std;

class Account {
    const int id;
    int balance;
    int &ref;

public:
    Account(int i, int b) : id(i), balance(b), ref(balance) { }

    void deposit(int amount) { ref += amount; }

    void show() const { cout << id << " " << balance << endl; }
};

int main() {
    Account a(101, 50);
    a.show();

    a.deposit(25);
    a.show();

    return 0;
}
```

**Çıktı:**

```
101 50
101 75
```

**Ne öğretiyor?**

- `const int id;` ve `int &ref;` üyelerine değer **sadece initialization list** ile verilebilir. Constructor'ın gövdesinde `id = i;` yazsaydın hata verirdi (derste gördüğün `class R` örneği).
- `ref(balance)`: `ref`, `balance`'ın **takma adı** oldu. `ref += amount;` yazınca `balance` da artıyor (50 → 75).
- `id` const olduğu için program boyunca **değiştirilemez**.
- `show() const`: fonksiyon sadece okuyor.

---

## Örnek 6 – Dinamik bellek kullanan sınıf

```cpp
#include <iostream>
using namespace std;

class Scores {
    int *arr;
    int size;

public:
    Scores(int n) {
        size = n;
        arr = new int[n];
        for (int i = 0; i < size; i++)
            arr[i] = 0;
        cout << "allocated " << size << endl;
    }

    ~Scores() {
        delete[] arr;
        cout << "freed " << size << endl;
    }

    void set(int index, int value) {
        if (index >= 0 && index < size)
            arr[index] = value;
        else
            cout << "Index out of bounds!" << endl;
    }

    int total() {
        int t = 0;
        for (int i = 0; i < size; i++)
            t += arr[i];
        return t;
    }
};

int main() {
    Scores s(3);

    s.set(0, 70);
    s.set(1, 85);
    s.set(2, 90);
    s.set(5, 100);

    cout << s.total() << endl;

    return 0;
}
```

**Çıktı:**

```
allocated 3
Index out of bounds!
245
freed 3
```

**Ne öğretiyor?**

Derste gördüğün `class B` (`parr`) ve Labwork 2 ile aynı kalıp.

| Satır | Ne oluyor? | Ekran |
|---|---|---|
| `Scores s(3);` | constructor: `size = 3`, `new int[3]`, hepsi 0 yapılır | `allocated 3` |
| `s.set(0, 70);` … `s.set(2, 90);` | dizi: 70, 85, 90 | |
| `s.set(5, 100);` | 5, geçerli indeks değil (0–2) | `Index out of bounds!` |
| `s.total()` | 70 + 85 + 90 | `245` |
| main biter | destructor: `delete[] arr` | `freed 3` |

- Bellek **constructor'da alınır**, **destructor'da geri verilir**. `main`'de `delete` yazmaya gerek kalmaz.
- `size = n;` satırı unutulursa sınır kontrolü çalışmaz (derste konuştuğumuz hata).
- Destructor mesajı **en sonda** çıkar, çünkü `s` ancak `main` bitince yok olur.

---

## Örnek 7 – Zincirlemede `&` unutulursa

```cpp
#include <iostream>
using namespace std;

class Counter {
    int n;
public:
    Counter() : n(0) {}
    Counter& addRef() { n++; return *this; }
    Counter addCopy() { n++; return *this; }
    int get() const { return n; }
};

int main() {
    Counter c1, c2;

    c1.addRef().addRef().addRef();
    c2.addCopy().addCopy().addCopy();

    cout << c1.get() << endl;
    cout << c2.get() << endl;
    return 0;
}
```

**Çıktı:**

```
3
1
```

**Ne öğretiyor?**

İki fonksiyonun gövdesi **aynı**; tek fark dönüş tipindeki `&`.

- `Counter& addRef()`: nesnenin **kendisini** döndürür. Üç çağrı da c1 üzerinde çalışır → **3**.
- `Counter addCopy()`: nesnenin **kopyasını** döndürür. İlk çağrı c2'yi 1 yapar; ikinci ve üçüncü çağrılar **kopyalar** üzerinde çalışır, c2'ye ulaşmaz → **1**.

```
c2.addCopy()      → c2.n = 1, kopya döner
  .addCopy()      → kopyanın n'si 2 olur (c2 değil!)
  .addCopy()      → başka bir kopyanın n'si 3 olur
```

**Sonuç:** Zincirleme için dönüş tipi mutlaka `Sinif&` olmalı. Labwork 3, Labwork 4 ve Ex 7'de bu yüzden `&` vardı.

---

## Örnek 8 – Yeni nesne döndüren fonksiyon

```cpp
#include <iostream>
using namespace std;

class Money {
    int lira;
public:
    Money(int l = 0) : lira(l) {}
    Money add(const Money &m) const { return Money(lira + m.lira); }
    void display() const { cout << lira << " TL" << endl; }
};

int main() {
    Money a(10), b(20), c(5);

    Money total = a.add(b);
    total.display();

    a.add(b).add(c).display();

    a.display();
    return 0;
}
```

**Çıktı:**

```
30 TL
35 TL
10 TL
```

**Ne öğretiyor?**

Ex 6'daki `addition()` ve dersteki `Complex add` ile aynı kalıp: fonksiyon, sonucu taşıyan **yeni bir nesne** döndürür.

- `a.add(b)` → 10 + 20 = 30 liralık **yeni** bir Money döner. `a` ve `b` **değişmez**.
- `a.add(b).add(c).display();` → dönen 30'luk nesnenin üstüne `add(c)` çağrılır (35), onun üstüne `display()`.
- Son satır kanıt: `a` hâlâ **10 TL**.

**Örnek 7 ile farkı:**

| Amaç | Dönüş tipi | Örnek |
|---|---|---|
| Aynı nesneyi değiştirip zincirlemek | `Sinif&` + `return *this;` | `setBrand`, `upgradeDamage` |
| Yeni bir sonuç nesnesi üretmek | `Sinif` + `return Sinif(...);` | `addition`, `crossProduct`, `add` |

---

## Örnek 9 – `const` referans parametre ve `const` fonksiyon

```cpp
#include <iostream>
using namespace std;

class Temp {
    int deg;
public:
    Temp(int d) : deg(d) {}
    int get() const { return deg; }
    void set(int d) { deg = d; }
};

void print(const Temp &t) {
    cout << t.get() << endl;
    // t.set(0);    // HATA: t const, set() ise const bir fonksiyon degil
}

int main() {
    Temp a(25);
    print(a);

    a.set(26);
    print(a);

    return 0;
}
```

**Çıktı:**

```
25
26
```

**Ne öğretiyor?**

- `void print(const Temp &t)`: `&` olduğu için kopya yapılmaz, `const` olduğu için fonksiyon t'yi **değiştiremez**.
- Böyle bir parametreyle sadece **sonunda `const` olan** fonksiyonlar çağrılabilir: `t.get()` olur, `t.set(0)` **hata verir**.
- `main` içindeki `a` const değil; `a.set(26)` serbest.

**Neden önemli?** Ex 6'da `addition(const Vector3D &v)`, Labwork 4'te `inspectWeaponLore(const EnchantedWeapon &weapon)` vardı. Bu yüzden `get...()` ve `display()` gibi **sadece okuyan** fonksiyonların sonuna `const` yazılır (personType ve Ex 7'deki gibi).

---

## Örnek 10 – `.` , `->` ve `(*p).`

```cpp
#include <iostream>
using namespace std;

class Lamp {
    bool on;
public:
    Lamp() { on = false; }
    void toggle() { on = !on; }
    void show() {
        if (on)
            cout << "ON" << endl;
        else
            cout << "OFF" << endl;
    }
};

int main() {
    Lamp lamp;
    lamp.toggle();
    lamp.show();

    Lamp *p = new Lamp;
    p->show();
    p->toggle();
    (*p).show();

    Lamp *arr = new Lamp[2];
    arr[1].toggle();
    arr[0].show();
    arr[1].show();

    delete p;
    delete[] arr;

    return 0;
}
```

**Çıktı:**

```
ON
OFF
ON
OFF
ON
```

**Ne öğretiyor?**

Dersteki `Rational` örneğiyle aynı kalıp.

| Elinde ne var? | Örnek | Nasıl kullanılır? |
|---|---|---|
| Nesnenin **kendisi** | `Lamp lamp;` | `lamp.show()` |
| Nesnenin **adresi** | `Lamp *p = new Lamp;` | `p->show()` |
| Dizinin bir **elemanı** | `arr[1]` | `arr[1].show()` |

- **`p->show()` ile `(*p).show()` aynı şeydir.** `*p` "p'nin gösterdiği nesne" demek; `->` bunun kısa yazımı. (`this->x` ile `(*this).x` de aynıdır.)
- `new Lamp[2]` iki lamba oluşturur; ikisi de constructor'dan dolayı kapalı (OFF) başlar.
- `new` ile alınan tek nesne `delete`, dizi `delete[]` ile geri verilir.

| Satır | Ekran |
|---|---|
| `lamp.toggle(); lamp.show();` | `ON` |
| `p->show();` | `OFF` (yeni lamba kapalı) |
| `p->toggle(); (*p).show();` | `ON` |
| `arr[1].toggle(); arr[0].show();` | `OFF` (arr[0]'a dokunulmadı) |
| `arr[1].show();` | `ON` |

---

## Örnek 11 – Friend class

```cpp
#include <iostream>
using namespace std;

class Teacher;

class Student {
    int grade;
public:
    Student() { grade = 0; }
    void show() { cout << "Grade: " << grade << endl; }
    friend class Teacher;
};

class Teacher {
public:
    void giveGrade(Student &s, int g) { s.grade = g; }
};

int main() {
    Student st;
    Teacher t;

    st.show();
    t.giveGrade(st, 85);
    st.show();

    return 0;
}
```

**Çıktı:**

```
Grade: 0
Grade: 85
```

**Ne öğretiyor?**

Dersteki `class A` / `class B` örneğiyle aynı kalıp.

- `grade` private; `main` ona doğrudan erişemez.
- `friend class Teacher;` → Teacher sınıfının **bütün fonksiyonları** Student'ın private üyelerine erişebilir. Bu yüzden `s.grade = g;` hata vermiyor.
- `giveGrade(Student &s, int g)`: `&` olduğu için **asıl** öğrencinin notu değişiyor (0 → 85).
- Arkadaşlık **tek yönlüdür**: Teacher, Student'ın private'larını görür; Student, Teacher'ınkileri göremez.

---

## Örnek 12 – İki sınıfın ortak friend fonksiyonu

```cpp
#include <iostream>
using namespace std;

class Square;

class Rectangle {
    int w, h;
public:
    Rectangle(int a, int b) : w(a), h(b) {}
    friend bool sameArea(const Rectangle &r, const Square &s);
};

class Square {
    int side;
public:
    Square(int s) : side(s) {}
    friend bool sameArea(const Rectangle &r, const Square &s);
};

bool sameArea(const Rectangle &r, const Square &s) {
    return r.w * r.h == s.side * s.side;
}

int main() {
    Rectangle r(2, 8);
    Square s1(4), s2(5);

    if (sameArea(r, s1))
        cout << "Same area" << endl;
    else
        cout << "Different area" << endl;

    if (sameArea(r, s2))
        cout << "Same area" << endl;
    else
        cout << "Different area" << endl;

    return 0;
}
```

**Çıktı:**

```
Same area
Different area
```

**Ne öğretiyor?**

`sameArea` fonksiyonu **iki farklı sınıfın** private değişkenlerine erişiyor (`r.w`, `r.h` ve `s.side`). Bunun için **her iki sınıf da** onu `friend` ilan etmeli.

- **`class Square;` satırı burada şart.** `Rectangle` sınıfının içinde `Square` ismi geçiyor ama `Square` daha aşağıda tanımlı.
- Fonksiyon `bool` döndürüyor ve `if` içinde doğrudan kullanılıyor (Labwork 2'deki `exceedsRiskLimit` gibi).
- Hesap: 2 × 8 = 16; 4 × 4 = 16 (aynı), 5 × 5 = 25 (farklı).

---
---

## Hızlı tekrar: sınavda en çok düşülen tuzaklar

**Constructor / destructor**
- Nesne oluşturulurken **kaç değer** verildiğine bak; ona uyan constructor çalışır.
- Değer eksikse **varsayılan değer** kullanılır (`int = 4` gibi).
- Destructor'lar **oluşturulma sırasının tersine** çalışır (dizinin elemanları da).
- `Sinif arr[5];` yazınca her eleman için **parametresiz** (ya da varsayılan değerli) constructor çalışır.

**Referans ve kopya**
- `int &x` → asıl değişken değişir. `int x` → sadece kopya değişir.
- `const int &x` → asıl değişken gelir ama **değiştirilemez**.
- Referans, tanımlandığı satırda bağlanmak zorundadır (`int &r;` hata).

**Global / yerel**
- Aynı isimde yerel değişken varsa sadece isim yazınca **yerel**, `::isim` yazınca **global** kullanılır.
- Global değişken **tek bir kutudur**; her yerde o anki son değeri görülür.

**Üye değişkenler**
- Her nesnenin **kendi** a'sı, b'si vardır. `obj1.f()` içindeki a → obj1'in a'sı.
- `const` ve referans üyelere sadece **initialization list** ile değer verilir.
- `private` üyelere `main`'den erişilemez; get/set fonksiyonları ya da friend gerekir.

**Zincirleme**
- Dönüş tipi `Sinif&`, son satır `return *this;`.
- Parametre adı değişken adıyla aynıysa `this->` **zorunlu**.

**Friend**
- Sınıfın üyesi değildir: `this` yoktur, **nokta olmadan** çağrılır, gövdesinde `Sinif::` yazılmaz.
- `friend` kelimesi sadece sınıfın içindeki bildirimde yazılır.

**Varsayılan parametre**
- Gönderilen değerler **soldan sağa** yerleşir; eksik kalanlar varsayılan değeri alır.
- Varsayılan değer sadece **bildirimde** yazılır, dışarıdaki gövdede tekrar yazılmaz.

**Dinamik bellek**
- `new ...[n]` ile alınan yer `delete[]`, `new ...` ile alınan tek nesne `delete` ile geri verilir.
- Sınıf içinde `new` kullanıldıysa `delete` **destructor'da** yazılır.
