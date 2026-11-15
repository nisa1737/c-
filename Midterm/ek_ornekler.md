# CENG241 – Ek Örnekler (Başka ne öğrenebilirim?)

Bu dosyadaki örnekler, derste ve recitation'da gördüğün konuların **bir adım ötesini** gösteriyor.
Her biri küçük, tek bir fikri anlatıyor ve sınavda "çıktı nedir?" ya da "hata nerede?" diye sorulabilecek türden.
Bütün kodlar derlenip çalıştırıldı; çıktılar gerçek çıktılardır.

**Nasıl çalışmalısın?** Önce kodu oku ve çıktıyı **tahmin et**, sonra aşağıdaki çıktıyla karşılaştır.

| Örnek | Konu | Zorluk |
|---|---|---|
| 1 | İç içe bloklarda aynı isimli değişkenler (`::`) | kolay |
| 2 | Template + referans: iki değişkeni yer değiştirme | kolay |
| 3 | Nesneyi fonksiyona göndermek: kopya mı, kendisi mi? | orta |
| 4 | Zincirlemede `&` unutulursa ne olur? | orta |
| 5 | Yeni nesne döndüren fonksiyon | orta |
| 6 | `const` nesne ve `const` fonksiyon | orta |
| 7 | `new` ile oluşturulan nesne `delete` edilmezse | orta |
| 8 | `->` ile `(*p).` ve pointer / referans parametre | orta |
| 9 | İki sınıfın ortak friend fonksiyonu | zor |
| 10 | `static` üye (muhtemelen sıradaki konu) | ileri |

---

## Örnek 1 – İç içe bloklarda aynı isimli değişkenler

```cpp
#include <iostream>
using namespace std;

int x = 1;

int main() {
    int x = 2;
    {
        int x = 3;
        cout << x << " " << ::x << endl;
        ::x = 10;
    }
    cout << x << " " << ::x << endl;
    return 0;
}
```

**Çıktı:**

```
3 1
2 10
```

**Ne öğretiyor?**

Üç tane `x` var: global (1), main'in yereli (2), bloğun yereli (3).

- Sadece `x` yazınca **en yakındaki** kullanılır: bloğun içinde 3, bloğun dışında 2.
- `::x` her zaman **global** olanı verir.
- Blok içinde `::x = 10;` global x'i değiştirdi; main'in yerel x'i (2) **etkilenmedi**.
- Bloğun x'i (3), blok bitince yok oldu.

`::` ile main'in yerel x'ine ulaşmanın yolu **yoktur**; `::` sadece globale gider.

---

## Örnek 2 – Template + referans: yer değiştirme

```cpp
#include <iostream>
using namespace std;

template <class T>
void swapValues(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

template <class T, class U>
void printPair(T a, U b) {
    cout << a << " - " << b << endl;
}

int main() {
    int a = 3, b = 7;
    swapValues(a, b);
    cout << a << " " << b << endl;

    double c = 1.5, d = 2.5;
    swapValues(c, d);
    cout << c << " " << d << endl;

    printPair(5, 2.5);
    printPair('A', 10);
    return 0;
}
```

**Çıktı:**

```
7 3
2.5 1.5
5 - 2.5
A - 10
```

**Ne öğretiyor?**

- `swapValues(T &a, T &b)`: Parametreler **referans** olduğu için main'deki değişkenler gerçekten yer değiştirir. `&` olmasaydı sadece kopyalar değişirdi ve çıktı `3 7` olurdu.
- Aynı fonksiyon hem `int` hem `double` için çalışıyor: template sayesinde.
- `template <class T, class U>`: **iki farklı tip** almak için iki yer tutucu. `printPair(5, 2.5)` çağrısında T = int, U = double.

**Dikkat:** `swapValues(a, c)` (biri int, biri double) **hata verir**; ikisi de aynı `T` olmak zorunda.

---

## Örnek 3 – Nesneyi fonksiyona göndermek: kopya mı, kendisi mi?

```cpp
#include <iostream>
using namespace std;

class Box {
    int v;
public:
    Box(int x) : v(x) { cout << "C" << v << endl; }
    ~Box() { cout << "D" << v << endl; }
    void set(int x) { v = x; }
    int get() const { return v; }
};

void byValue(Box b) { b.set(99); }
void byRef(Box &b) { b.set(99); }

int main() {
    Box a(1);

    byValue(a);
    cout << a.get() << endl;

    byRef(a);
    cout << a.get() << endl;

    return 0;
}
```

**Çıktı:**

```
C1
D99
1
99
D99
```

**Ne öğretiyor?**

`int` için öğrendiğin kural nesneler için de aynen geçerli.

| Satır | Ne oluyor? | Ekran |
|---|---|---|
| `Box a(1);` | a oluşur | `C1` |
| `byValue(a);` | a'nın **kopyası** oluşur, kopya 99 yapılır, fonksiyon bitince **kopya yok olur** | `D99` |
| `cout << a.get()` | a değişmedi | `1` |
| `byRef(a);` | a'nın **kendisi** 99 yapılır, yok olan bir şey yok | |
| `cout << a.get()` | a değişti | `99` |
| main biter | a yok olur | `D99` |

**İlginç nokta:** Kopya oluşurken ekrana `C` **yazılmadı** ama yok olurken `D99` yazıldı. Çünkü kopyalar, derleyicinin kendiliğinden yazdığı ayrı bir constructor ile (copy constructor) oluşturulur ve o ekrana bir şey yazmaz. Destructor ise kopya için de çalışır.

**Sınavda nasıl sorulur?** "Kaç tane D satırı çıkar?" Cevap: nesne sayısı + **değerle gönderilen her çağrı için 1 tane daha**.

---

## Örnek 4 – Zincirlemede `&` unutulursa ne olur?

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
- `Counter addCopy()`: nesnenin **kopyasını** döndürür. İlk çağrı c2'yi 1 yapar; ikinci ve üçüncü çağrılar **geçici kopyalar** üzerinde çalışır ve c2'ye ulaşmaz → **1**.

```
c2.addCopy()      → c2.n = 1, kopya döner
  .addCopy()      → kopyanın n'si 2 olur (c2 değil!)
  .addCopy()      → başka bir kopyanın n'si 3 olur
```

**Sonuç:** Zincirleme için dönüş tipi mutlaka `Sinif&` olmalı. Labwork 3, Labwork 4 ve Ex 7'de bu yüzden `&` vardı.

---

## Örnek 5 – Yeni nesne döndüren fonksiyon

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

Ex 6'daki `addition()` ve Soru 9'daki `multiply()` ile aynı kalıp: fonksiyon, sonucu taşıyan **yeni bir nesne** döndürür.

- `a.add(b)` → 10 + 20 = 30 liralık **yeni** bir Money döner. `a` ve `b` **değişmez**.
- `a.add(b).add(c).display();` → dönen 30'luk nesnenin üstüne `add(c)` çağrılır (35), onun üstüne `display()`.
- Son satır kanıt: `a` hâlâ **10 TL**.

**Örnek 4 ile farkı:** Orada amaç **aynı nesneyi değiştirmekti**, bu yüzden `&` gerekiyordu. Burada amaç **yeni bir sonuç üretmek**, bu yüzden `&` yok ve olmamalı.

| Amaç | Dönüş tipi | Örnek |
|---|---|---|
| Aynı nesneyi değiştirip zincirlemek | `Sinif&` + `return *this;` | `setBrand`, `upgradeDamage` |
| Yeni bir sonuç nesnesi üretmek | `Sinif` + `return Sinif(...);` | `addition`, `crossProduct`, `add` |

---

## Örnek 6 – `const` nesne ve `const` fonksiyon

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
    // t.set(0);    // HATA: const nesne ile const olmayan fonksiyon cagrilamaz
}

int main() {
    Temp a(25);
    const Temp b(30);

    a.set(26);
    // b.set(31);   // HATA: b const

    print(a);
    print(b);
    return 0;
}
```

**Çıktı:**

```
26
30
```

**Ne öğretiyor?**

- `const Temp b(30);` → b **değiştirilemez** bir nesne.
- `const` bir nesne ile sadece **sonunda `const` olan** fonksiyonlar çağrılabilir: `b.get()` olur, `b.set(31)` **hata verir**.
- `void print(const Temp &t)`: Parametre `const` referans olduğu için fonksiyonun içinde t de const sayılır. `t.get()` olur, `t.set(0)` **hata verir**.

**Neden önemli?** Ex 6'da `addition(const Vector3D &v)` ve Labwork 4'te `inspectWeaponLore(const EnchantedWeapon &weapon)` vardı. Böyle bir parametreyle çağıracağın fonksiyonların `const` olması gerekir. Bu yüzden `get...()` ve `display()` gibi **sadece okuyan** fonksiyonların sonuna `const` yazmak iyi bir alışkanlıktır.

---

## Örnek 7 – `new` ile oluşturulan nesne `delete` edilmezse

```cpp
#include <iostream>
using namespace std;

class A {
    int id;
public:
    A(int i) : id(i) { cout << "C" << id << endl; }
    ~A() { cout << "D" << id << endl; }
    void show() const { cout << "id=" << id << endl; }
};

int main() {
    A a(1);
    A *p = new A(2);
    A *q = new A(3);

    p->show();
    delete q;

    cout << "main bitiyor" << endl;
    return 0;
}
```

**Çıktı:**

```
C1
C2
C3
id=2
D3
main bitiyor
D1
```

**Ne öğretiyor?**

| Nesne | Nasıl oluştu? | Ne zaman yok oldu? |
|---|---|---|
| `a` (id 1) | normal | main bitince, kendiliğinden → `D1` |
| id 3 | `new` | `delete q;` yazılınca → `D3` |
| id 2 | `new` | **hiç yok olmadı** (`delete p;` yazılmamış) |

Çıktıda **`D2` yok**. `new` ile oluşturulan nesnenin destructor'ı sadece `delete` yazılırsa çalışır. Yazılmazsa bellek geri verilmez: **memory leak**.

**Sınavda nasıl sorulur?** Çıktı sorusunda `new` ile oluşturulan ama `delete` edilmeyen bir nesne koyarlar; onun destructor satırını **yazmaman** gerekir.

---

## Örnek 8 – `->` ile `(*p).` ve pointer / referans parametre

```cpp
#include <iostream>
using namespace std;

class Lamp {
    bool on;
public:
    Lamp() : on(false) {}
    void toggle() { on = !on; }
    void show() const {
        if (on)
            cout << "ON" << endl;
        else
            cout << "OFF" << endl;
    }
};

void switchByPointer(Lamp *l) { l->toggle(); }
void switchByReference(Lamp &l) { l.toggle(); }

int main() {
    Lamp lamp;
    Lamp *p = &lamp;

    p->show();
    (*p).toggle();
    lamp.show();

    switchByPointer(&lamp);
    lamp.show();

    switchByReference(lamp);
    lamp.show();
    return 0;
}
```

**Çıktı:**

```
OFF
ON
OFF
ON
```

**Ne öğretiyor?**

- `Lamp *p = &lamp;` → `&lamp`, lamp'in **adresi** demek. p artık lamp'i gösteriyor.
- **`p->toggle()` ile `(*p).toggle()` tamamen aynı şeydir.** `->`, `(*p).` yazımının kısa yoludur. (`this->x` ile `(*this).x` de aynıdır.)
- Bir nesneyi fonksiyona **değiştirilebilir** şekilde göndermenin iki yolu var:

| | Pointer ile | Referans ile |
|---|---|---|
| Parametre | `Lamp *l` | `Lamp &l` |
| Çağrı | `switchByPointer(&lamp);` | `switchByReference(lamp);` |
| İçeride kullanım | `l->toggle();` | `l.toggle();` |

İkisi de **asıl lambayı** değiştirir. Lamba dört satırda sırayla OFF → ON → OFF → ON oluyor.

Labwork 3'teki `registerDevice(DeviceMonitor*)` pointer yolunu, `testPassByReference(T&)` referans yolunu kullanıyordu.

---

## Örnek 9 – İki sınıfın ortak friend fonksiyonu

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

- **`class Square;` satırı burada gerçekten şart.** `Rectangle` sınıfının içinde `Square` ismi geçiyor ama `Square` daha aşağıda tanımlı. Bu satır silinirse derleyici hata verir.
- Fonksiyon `bool` döndürüyor ve `if` içinde doğrudan kullanılıyor (Labwork 2'deki `exceedsRiskLimit` gibi).
- Hesap: 2 × 8 = 16; 4 × 4 = 16 (aynı), 5 × 5 = 25 (farklı).

---

## Örnek 10 – `static` üye (muhtemelen sıradaki konu)

> Bu konuyu derste henüz görmediysen midterm'de çıkmaz. Ex 1–3'teki **global sayaç** fikrinin sınıf içine alınmış hali olduğu için buraya ekledim.

```cpp
#include <iostream>
using namespace std;

class Player {
    int id;
    static int count;
public:
    Player() {
        count++;
        id = count;
        cout << "Player " << id << " joined" << endl;
    }
    ~Player() {
        count--;
        cout << "Player " << id << " left" << endl;
    }
    static int getCount() { return count; }
};

int Player::count = 0;

int main() {
    cout << Player::getCount() << endl;

    Player a, b;
    cout << Player::getCount() << endl;

    {
        Player c;
        cout << Player::getCount() << endl;
    }

    cout << Player::getCount() << endl;
    return 0;
}
```

**Çıktı:**

```
0
Player 1 joined
Player 2 joined
2
Player 3 joined
3
Player 3 left
2
Player 2 left
Player 1 left
```

**Ne öğretiyor?**

Normal üye değişkenler (`id`) **her nesnede ayrıdır**. `static` üye değişken (`count`) ise **bütün nesneler için tek bir tanedir**; tıpkı global değişken gibi, ama sınıfın içinde ve private olabilir.

| | `id` (normal) | `count` (static) |
|---|---|---|
| Kaç tane var? | her nesnede ayrı | **tek** |
| Kime ait? | nesneye | sınıfa |
| Nasıl erişilir? | nesne üzerinden (`a.` ile) | `Player::getCount()` (nesne olmadan da) |

- `int Player::count = 0;` → static değişken sınıfın **dışında** bir kez tanımlanıp başlatılır.
- Her constructor `count`'u 1 artırıyor, her destructor 1 azaltıyor. Böylece `count` o an **kaç oyuncu yaşadığını** gösteriyor: 0 → 2 → 3 → 2.
- Blok bitince `c` yok oldu (`Player 3 left`) ve sayı 2'ye düştü.

---
---

## Hızlı tekrar: sınavda en çok düşülen tuzaklar

**Constructor / destructor**
- Nesne oluşturulurken **kaç değer** verildiğine bak; ona uyan constructor çalışır.
- Değer eksikse **varsayılan değer** kullanılır (`int = 4` gibi).
- Destructor'lar **oluşturulma sırasının tersine** çalışır.
- `{ }` bloğundaki nesne, **blok bitince** yok olur.
- `new` ile oluşturulan nesne **sadece `delete` ile** yok olur.
- `Sinif arr[5];` yazabilmek için **parametresiz** (ya da hepsi varsayılan değerli) constructor gerekir.

**Referans ve kopya**
- `int &x` → asıl değişken değişir. `int x` → sadece kopya değişir.
- Nesneyi değerle göndermek **kopya** oluşturur; kopya fonksiyon bitince yok olur (destructor çalışır).
- `int &x` parametresine `5` gibi sabit sayı gönderilemez.

**Global / yerel**
- Aynı isimde yerel değişken varsa sadece isim yazınca **yerel**, `::isim` yazınca **global** kullanılır.
- Global değişken **tek bir kutudur**; her yerde o anki son değeri görülür.

**Üye değişkenler**
- Her nesnenin **kendi** a'sı, b'si vardır. `obj1.f()` içindeki a → obj1'in a'sı.
- `const` ve referans üyelere sadece **initialization list** ile değer verilir.

**Zincirleme**
- Dönüş tipi `Sinif&`, son satır `return *this;`.
- `&` unutulursa zincirin devamı **kopya** üzerinde çalışır.

**Friend**
- Sınıfın üyesi değildir: `this` yoktur, **nokta olmadan** çağrılır, gövdesinde `Sinif::` yazılmaz.
- `friend` kelimesi sadece sınıfın içindeki bildirimde yazılır.

**Varsayılan parametre**
- Varsayılan değerler **sağdan** başlamalı: `f(int a, int b = 2)` olur, `f(int a = 1, int b)` olmaz.
- Varsayılan değer sadece **bildirimde** yazılır, dışarıdaki gövdede tekrar yazılmaz.
