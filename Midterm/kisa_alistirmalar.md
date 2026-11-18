# CENG241 – Kısa Alıştırmalar

Bu dosyada **22 kısa alıştırma** var. Her biri tek bir konuyu öğretiyor ve genelde sadece **kodun bir parçasını** (bir fonksiyon, bir constructor, birkaç satır) yazmanı istiyor.
Midterm sorularından farklı, hepsi yeni; konular derste, lab'larda ve recitation'da gördüğün konular.

**Soru kısımları (Task) sınavdaki gibi İngilizce, cevaplar ve açıklamalar Türkçe.**

**Nasıl çalışmalısın?**

1. Görevi (Task) oku, kağıda ya da bilgisayara **kendin yaz**.
2. Sonra hemen altındaki **Cevap**'a bak ve karşılaştır.
3. **Neden?** kısmını mutlaka oku; asıl öğreten kısım orası.

**İsimler hakkında:** Soruda adı **verilen** şeyleri (sınıf, fonksiyon, değişken isimleri) aynen kullan.
Soruda adı **verilmeyen** şeylerin (fonksiyon parametreleri, döngü değişkenleri, `main`'deki nesneler) adını **sen seçersin**.
Cevaplardaki `c`, `n`, `t`, `m` gibi isimler benim seçimim; sen farklı bir isim verirsen cevabın yine doğru olur.

Bütün cevaplar derlenip çalıştırıldı; çıktılar gerçek çıktılardır.

| Bölüm | Konu | Alıştırmalar |
|---|---|---|
| 1 | Fonksiyonlar: namespace, varsayılan parametre, overloading, template | 1–4 |
| 2 | Referans (`&`) ve `const &` | 5–6 |
| 3 | Sınıf, private/public, get/set, `const` fonksiyon | 7 |
| 4 | Constructor çeşitleri | 8–10 |
| 5 | Destructor ve yok olma sırası | 11 |
| 6 | Dinamik bellek: `new`, `delete`, `->` | 12–15 |
| 7 | `this` ve zincirleme | 16 |
| 8 | Nesne döndürmek, friend fonksiyon, friend class | 17–19 |
| 9 | Nesne dizileri, struct template, global `::` | 20–22 |

---

# Bölüm 1 – Fonksiyonlar

## Alıştırma 1 – Namespace

**Task:** Write a namespace called `Geometry` that contains:
- a variable `double PI = 3.14;`
- a function `circleArea` that takes the radius and returns the area of the circle (PI × r × r).

Then, in the main function, print the area for r = 2 and the value of PI. (Do **not** use `using namespace Geometry;`.)

**Cevap:**

```cpp
namespace Geometry {
    double PI = 3.14;
    double circleArea(double r) { return PI * r * r; }
}

int main() {
    cout << Geometry::circleArea(2) << endl;
    cout << Geometry::PI << endl;
}
```

**Çıktı:**
```
12.56
3.14
```

**Neden?**
- Namespace'in içindekilere dışarıdan `Geometry::` ile ulaşılır.
- `circleArea` **namespace'in içinde** olduğu için PI'ı `Geometry::` yazmadan kullanabiliyor.

---

## Alıştırma 2 – Varsayılan parametre

**Task:** Write a function `power(base, exp)` that returns base raised to the power exp (use a loop). If `exp` is not provided, it should be **2 by default**.
What are the results of the following calls: `power(5)`, `power(2, 3)`, `power(7, 0)`?

**Cevap:**

```cpp
int power(int base, int exp = 2) {
    int result = 1;
    for (int i = 0; i < exp; i++)
        result *= base;
    return result;
}
```

**Çıktı:** `power(5)` → **25**, `power(2, 3)` → **8**, `power(7, 0)` → **1**

**Neden?**
- `int exp = 2` → değer gönderilmezse exp = 2. `power(5)` = 5 × 5.
- `power(7, 0)`: döngü hiç dönmez, `result` 1 olarak kalır.
- Varsayılan değerler **sağdan** verilir: `int base = 1, int exp` yazılamaz.

---

## Alıştırma 3 – Function overloading

**Task:** Write **two** overloaded functions named `biggest`:
- one takes 2 integers and returns the bigger one,
- the other takes 3 integers and returns the biggest one.

**Hint:** The 3-parameter version can use the 2-parameter version.

**Cevap:**

```cpp
int biggest(int a, int b) {
    if (a > b)
        return a;
    return b;
}

int biggest(int a, int b, int c) {
    return biggest(biggest(a, b), c);
}
```

**Deneme:** `biggest(4, 9)` → **9**, `biggest(4, 9, 6)` → **9**, `biggest(12, 3, 7)` → **12**

**Neden?**
- Aynı isimde iki fonksiyon olabilir; derleyici **kaç değer gönderildiğine** bakıp doğru olanı seçer (Labwork 1'deki `add` gibi).
- `biggest(biggest(a, b), c)`: önce a ile b'nin büyüğü bulunur, sonra o c ile karşılaştırılır.
- Adını `max` koymadık: `using namespace std;` varken `max` ismi std'deki hazır fonksiyonla karışır.

---

## Alıştırma 4 – Template

**Task:** Write a **function template** named `average` that returns the average of two values. Then predict the output of the following lines:

```cpp
cout << average(3, 4) << endl;
cout << average(3.0, 4.0) << endl;
```

**Cevap:**

```cpp
template <class T>
T average(T a, T b) {
    return (a + b) / 2;
}
```

**Çıktı:**
```
3
3.5
```

**Neden?**
- `average(3, 4)` → T = **int**. int bölmede küsurat atılır: 7 / 2 = **3**.
- `average(3.0, 4.0)` → T = **double**: 7.0 / 2 = **3.5**.
- Aynı fonksiyon, gönderilen tipe göre **farklı sonuç** veriyor. Template'in tuzağı bu.

---

# Bölüm 2 – Referans

## Alıştırma 5 – Referans parametre

**Task:** Write a function `sortTwo(a, b)`: if `a` is greater than `b`, it should **swap** them, so that `a` always holds the smaller value after the call. The variables in main must really change, so use **reference parameters**.

**Cevap:**

```cpp
void sortTwo(int &a, int &b) {
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }
}
```

**Deneme:**
```cpp
int x = 9, y = 4;
sortTwo(x, y);
cout << x << " " << y;     // 4 9
```

**Neden?**
- `&` olmasaydı sadece kopyalar yer değiştirirdi; x ve y aynı kalırdı.
- Yer değiştirmek için **üçüncü bir değişken** (`temp`) gerekir. `a = b; b = a;` yazarsan ikisi de aynı sayı olur.

---

## Alıştırma 6 – Referans çıktı sorusu

**Task:** What is the output of the following program?

```cpp
void change(int a, int &b, const int &c) {
    a = a + 10;
    b = b + c;
}

int main() {
    int x = 4;
    int &r = x;
    r += 3;
    x *= 2;
    cout << x << " " << r << endl;

    int p = 1, q = 2, s = 3;
    change(p, q, s);
    cout << p << " " << q << " " << s << endl;
}
```

**Cevap:**
```
14 14
1 5 3
```

**Neden?**
- `r`, x'in **takma adı**. `r += 3` → x = 7; `x *= 2` → x = 14. İkisi aynı kutu, ikisi de 14.
- `int a` → kopya: p **değişmez** (1).
- `int &b` → asıl değişken: q = 2 + 3 = **5**.
- `const int &c` → asıl değişken ama **değiştirilemez**: s hep 3. Fonksiyonun içine `c = 0;` yazsaydın hata verirdi.

---

# Bölüm 3 – Sınıf temelleri

## Alıştırma 7 – Get, set ve const

**Task:** Write a class `Thermometer` with:
- a private data member `double celsius;`
- `setCelsius(double)`: if the value is **less than −273**, it prints `Invalid!` and does **not** change the value.
- `getCelsius()`: returns celsius.
- `toFahrenheit()`: returns celsius × 9 / 5 + 32.
- Functions that only read data must be `const`.

**Cevap:**

```cpp
class Thermometer {
    double celsius;
public:
    void setCelsius(double c) {
        if (c < -273)
            cout << "Invalid!" << endl;
        else
            celsius = c;
    }
    double getCelsius() const { return celsius; }
    double toFahrenheit() const { return celsius * 9 / 5 + 32; }
};
```

**Deneme:**
```cpp
Thermometer t;
t.setCelsius(25);
t.setCelsius(-300);                                          // Invalid!
cout << t.getCelsius() << " " << t.toFahrenheit() << endl;   // 25 77
```

**Neden?**
- `celsius` private olduğu için `main`'den `t.celsius = -300;` yazılamaz. Değer **sadece `setCelsius` üzerinden** değişebiliyor ve o da kontrol ediyor. Encapsulation'ın faydası bu.
- `setCelsius` değiştirdiği için `const` **değil**; get ve toFahrenheit sadece okuduğu için `const`.
- Parametrenin adı (`c`) soruda verilmiyor; **ben seçtim**. `value`, `temp` gibi istediğin ismi verebilirsin. Adını `celsius` koyarsan değişkenle aynı olur; o zaman `this->celsius = celsius;` yazman gerekir.

---

# Bölüm 4 – Constructor

## Alıştırma 8 – Varsayılan değerli constructor

**Task:** Write a class `Clock` with the data members `hour` and `minute`. Write **only one parameterized constructor** that takes the hour and the minute as parameters, **both with a default value of 0**, so that all three lines below work:

```cpp
Clock c1;          // 0:0
Clock c2(9);       // 9:0
Clock c3(14, 30);  // 14:30
```

Use an **initialization list** in the constructor. `display()` prints the time as "hour:minute".

**Cevap:**

```cpp
class Clock {
    int hour, minute;
public:
    Clock(int h = 0, int m = 0) : hour(h), minute(m) { }
    void display() const { cout << hour << ":" << minute << endl; }
};
```

**Çıktı:**
```
0:0
9:0
14:30
```

**Neden?**
- İki parametrenin de varsayılan değeri olduğu için tek constructor 0, 1 ya da 2 değerle çağrılabiliyor.
- Soru bunu açıkça söylemeseydi bile üç satırdan anlaşılırdı: `c3(14, 30)` → 2 parametre gerekli; `c2(9)` ve `c1` → eksik değerler için varsayılan değer gerekli.
- `: hour(h), minute(m)` → initialization list: hour'a h, minute'a m konur.

---

## Alıştırma 9 – Constructor overloading

**Task:** Write **three** constructors for the class `Rectangle`:
- a default constructor → 1 × 1
- a constructor with one parameter (side) → a square: side × side
- a constructor with two parameters (w, h) → w × h

and an `area()` function. What are the areas for `Rectangle r1, r2(5), r3(2, 7);`?

**Cevap:**

```cpp
class Rectangle {
    int width, height;
public:
    Rectangle() { width = 1; height = 1; }
    Rectangle(int side) { width = side; height = side; }
    Rectangle(int w, int h) { width = w; height = h; }
    int area() const { return width * height; }
};
```

**Çıktı:** r1 → **1**, r2 → **25**, r3 → **14**

**Neden?** Hangi constructor'ın çalışacağına **gönderilen değer sayısı** karar verir: 0 değer → ilki, 1 değer → ikincisi, 2 değer → üçüncüsü.

---

## Alıştırma 10 – const üye

**Task:** Write the constructor of the following class:

```cpp
class Order {
    const int orderNo;
    double total;
public:
    // constructor: Order(int n, double t)
    void show() const { cout << "Order " << orderNo << ": " << total << " TL" << endl; }
};
```

**Cevap:**

```cpp
Order(int n, double t) : orderNo(n), total(t) { }
```

**Deneme:** `Order o(1001, 250.5); o.show();` → `Order 1001: 250.5 TL`

**Neden?**
- `orderNo` **const**. const değişkene sonradan atama yapılamaz; değeri **oluşturulduğu anda** verilmeli.
- Bu yüzden **initialization list şart**. Şöyle yazsaydın hata verirdi:
  ```cpp
  Order(int n, double t) { orderNo = n; total = t; }   // HATA
  ```
- Referans üyeler (`int &x;`) için de aynı kural geçerli.

---

# Bölüm 5 – Destructor

## Alıştırma 11 – Doğum ve ölüm sırası

**Task:** What is the output of the following program? (The output is a single line.)

```cpp
class Tag {
    char name;
public:
    Tag(char n) { name = n; cout << "+" << name << " "; }
    ~Tag() { cout << "-" << name << " "; }
};

int main() {
    Tag a('A');
    Tag b('B');
    Tag arr[2] = {'X', 'Y'};
    cout << "| ";
    return 0;
}
```

**Cevap:**
```
+A +B +X +Y | -Y -X -B -A
```

**Neden?**
- Constructor her nesne oluşunca çalışır: A, B, X, Y sırasıyla.
- `main` bitince destructor'lar **tersten** çalışır: en son doğan (Y) ilk ölür.
- Dizinin elemanları da kendi içinde tersten: önce Y, sonra X.
- Bütün `-` işaretleri `|`'dan **sonra**, çünkü hiçbir nesne `main` bitmeden yok olmuyor.

---

# Bölüm 6 – Dinamik bellek

## Alıştırma 12 – Dinamik dizi

**Task:** Fill in the blanks. The user enters n; an array of n elements is created dynamically, filled with 1², 2², 3², ..., printed, and then the memory is freed.

```cpp
int n;
cin >> n;

______________________________     // 1) create the array
for (int i = 0; i < n; i++)
    ______________________________ // 2) store the squares

for (int i = 0; i < n; i++)
    cout << squares[i] << " ";

______________________________     // 3) free the memory
```

**Cevap:**

```cpp
int *squares = new int[n];               // 1
squares[i] = (i + 1) * (i + 1);          // 2
delete[] squares;                        // 3
```

**Çıktı (n = 4):** `1 4 9 16`

**Neden?**
- n çalışırken belli olduğu için normal dizi (`int squares[n];`) yerine `new` kullanılır.
- `new int[n]` **dizi** olduğu için `delete[]` (köşeli parantezli).
- i 0'dan başlıyor; 1² için `(i + 1)` gerekiyor.

---

## Alıştırma 13 – new ile nesne ve `->`

**Task:** The class `Counter` is given. Write the main function: create a Counter object **dynamically** using `new`, call `increment()` twice, print the value, and free the memory.

```cpp
class Counter {
    int value;
public:
    Counter() { value = 0; }
    void increment() { value++; }
    int get() const { return value; }
};
```

**Cevap:**

```cpp
int main() {
    Counter *c = new Counter;
    c->increment();
    c->increment();
    cout << c->get() << endl;     // 2
    delete c;
}
```

**Neden?**
- `c` nesnenin **adresini** tutuyor; adres üzerinden fonksiyon çağırmak için **`->`**. `c.increment()` hata verir.
- `c->increment()` ile `(*c).increment()` aynı şey.
- Tek nesne → `delete` (köşeli parantezsiz).

---

## Alıştırma 14 – Sınıfın içinde dinamik dizi

**Task:** Write the constructor and the destructor of the class below.
- Constructor: stores `size`, **dynamically allocates** the array, and sets all elements to 0.
- Destructor: frees the array and prints `ScoreBoard deleted`.

```cpp
class ScoreBoard {
    int *scores;
    int size;
public:
    // constructor: ScoreBoard(int n)
    // destructor
    void set(int index, int value) {
        if (index >= 0 && index < size)
            scores[index] = value;
    }
    int best() const {
        int max = scores[0];
        for (int i = 1; i < size; i++)
            if (scores[i] > max)
                max = scores[i];
        return max;
    }
};
```

**Cevap:**

```cpp
ScoreBoard(int n) {
    size = n;
    scores = new int[size];
    for (int i = 0; i < size; i++)
        scores[i] = 0;
}

~ScoreBoard() {
    delete[] scores;
    cout << "ScoreBoard deleted" << endl;
}
```

**Deneme:**
```cpp
ScoreBoard sb(3);
sb.set(0, 40);
sb.set(1, 75);
sb.set(2, 60);
cout << sb.best() << endl;     // 75
                               // main bitince: ScoreBoard deleted
```

**Neden?**
- **Constructor'da `new`, destructor'da `delete[]`**: sınavın en sevdiği kalıp.
- `size = n;` unutulursa `set` ve `best` içindeki kontroller çöp değerle çalışır.

---

## Alıştırma 15 – `char*` metin kopyalama

**Task:** Write the constructor of the class `Label`. The parameter name is the same as the data member (`text`), so use the **this pointer**. **Dynamically allocate** exactly enough memory for the text and copy it.

```cpp
class Label {
    char *text;
public:
    // constructor: Label(const char *text)
    ~Label() { delete[] text; }
    void show() const { cout << "[" << text << "]" << endl; }
};
```

**Cevap:**

```cpp
Label(const char *text) {
    int len = 0;
    while (text[len] != '\0')
        len++;

    this->text = new char[len + 1];
    for (int i = 0; i < len; i++)
        this->text[i] = text[i];
    this->text[len] = '\0';
}
```

**Deneme:** `Label l("SALE"); l.show();` → `[SALE]`

**Neden?**
- 4 adım: **say** (4 harf) → **yer ayır** (4 + 1 = 5; +1 `'\0'` için) → **kopyala** → **sonuna `'\0'` koy**.
- `this->text` = nesnenin değişkeni, `text` = parametre.
- Kısa yoldan `this->text = text;` yazamazsın: `const char*` bir `char*`'a atanamaz, derleyici hata verir. Zaten amaç adresi değil **harfleri** kopyalamak; nesnenin kendi metni olmalı ki destructor kendi ayırdığı yeri silsin.

---

# Bölüm 7 – this ve zincirleme

## Alıştırma 16 – Zincirlenebilir set fonksiyonları

**Task:** Write `setBrand` and `setPrice` for the class `Phone`. The parameter names must be the **same** as the data members, and the following line must work:

```cpp
p.setBrand("Nokia").setPrice(5000);
```

```cpp
class Phone {
    string brand;
    int price;
public:
    Phone() : brand(""), price(0) { }
    // setBrand and setPrice
    void show() const { cout << brand << " - " << price << " TL" << endl; }
};
```

**Cevap:**

```cpp
Phone& setBrand(string brand) {
    this->brand = brand;
    return *this;
}

Phone& setPrice(int price) {
    this->price = price;
    return *this;
}
```

**Deneme:** `p.show();` → `Nokia - 5000 TL`

**Neden?**
- Zincirleme için 2 şey şart: dönüş tipi **`Phone&`** ve son satır **`return *this;`**.
- `void` olsaydı `.setPrice(...)` yazılamazdı, çünkü `setBrand` geriye bir şey vermezdi.
- `brand = brand;` yazsaydın parametre kendine atanırdı, nesne değişmezdi; bu yüzden `this->`.

---

# Bölüm 8 – Nesne döndürmek ve friend

## Alıştırma 17 – Yeni nesne döndüren fonksiyon

**Task:** Write the member function `add` for the class `Money`: it takes another Money object and returns the sum of the two as a **new Money object**. Neither object should be **changed**.

```cpp
class Money {
    int lira;
public:
    Money(int l = 0) : lira(l) { }
    // add
    void show() const { cout << lira << " TL" << endl; }
};
```

**Cevap:**

```cpp
Money add(const Money &m) const {
    return Money(lira + m.lira);
}
```

**Deneme:**
```cpp
Money a(30), b(45);
Money c = a.add(b);
c.show();     // 75 TL
a.show();     // 30 TL  (a degismedi)
```

**Neden?**
- `return Money(...)` → constructor çağrılarak **yeni** bir nesne oluşturulup döndürülüyor.
- Dönüş tipi `Money` (`&` yok): yeni bir sonuç üretiyoruz, aynı nesneyi değiştirmiyoruz.
- `const Money &m` → kopya yok ve m değiştirilemez. Sondaki `const` → a da değiştirilemez.
- `m.lira` private olduğu halde erişilebiliyor, çünkü `add` **aynı sınıfın** fonksiyonu.
- Soru parametrenin tam yazılışını vermiyor. `Money add(Money m)` yazsan da **çalışır ve doğrudur**; `const Money &m` sadece daha iyi bir alışkanlık (kopya yapılmaz, m değiştirilemez).

---

## Alıştırma 18 – Friend fonksiyon

**Task:** Add a **friend function** `sameColor` to the class `Pen` that returns `true` if two pens have the same color. Write both the declaration and the definition.

```cpp
class Pen {
    string color;
public:
    Pen(string c) : color(c) { }
    // friend declaration
};
// definition
```

**Cevap:**

```cpp
// sinifin icinde:
friend bool sameColor(const Pen &p1, const Pen &p2);

// sinifin disinda:
bool sameColor(const Pen &p1, const Pen &p2) {
    return p1.color == p2.color;
}
```

**Deneme:**
```cpp
Pen a("blue"), b("red"), c("blue");
cout << sameColor(a, b) << " " << sameColor(a, c);   // 0 1
```

**Neden?**
- `friend` kelimesi **sadece** sınıfın içindeki bildirimde yazılır. Gövdede yok, başında `Pen::` da yok (üye değil).
- Üye olmadığı için `this` yok; nesnelere **parametrelerle** ulaşır ve **nokta olmadan** çağrılır: `sameColor(a, b)`.
- `cout` bir bool yazdırınca `true`/`false` değil **1/0** çıkar.

---

## Alıştırma 19 – Friend class

**Task:** Add **one line** to the class `Safe` so that the class `Locksmith` can read its private member `code`.

```cpp
class Safe {
    int code;
public:
    Safe(int c) : code(c) { }
    // ???
};

class Locksmith {
public:
    void open(const Safe &s) { cout << "Code is " << s.code << endl; }
};
```

**Cevap:**

```cpp
friend class Locksmith;
```

**Deneme:** `Safe s(4321); Locksmith l; l.open(s);` → `Code is 4321`

**Neden?**
- `friend class Locksmith;` → Locksmith'in **bütün fonksiyonları** Safe'in private üyelerine erişebilir.
- Arkadaşlık **tek yönlü**: Safe, Locksmith'in private'larını göremez.
- Bu satırı Locksmith'e değil **Safe'e** yazıyoruz: izni, gizli bilgisi olan sınıf verir.

---

# Bölüm 9 – Nesne dizileri, struct template, global `::`

## Alıştırma 20 – Nesne dizisi

**Task:** What is the output of the following program? (The output is a single line.)

```cpp
class Item {
    int id, qty;
public:
    Item(int i = 0, int q = 1) : id(i), qty(q) { }
    void show() const { cout << id << "x" << qty << " "; }
};

int main() {
    Item a[3] = { Item(1, 5), Item(2), 3 };
    Item b[2];
    for (int i = 0; i < 3; i++)
        a[i].show();
    for (int i = 0; i < 2; i++)
        b[i].show();
}
```

**Cevap:**
```
1x5 2x1 3x1 0x1 0x1
```

**Neden?**

| Eleman | Verilen | id | qty |
|---|---|---|---|
| a[0] | `Item(1, 5)` | 1 | 5 |
| a[1] | `Item(2)` | 2 | 1 (varsayılan) |
| a[2] | `3` (kısa yazım: `Item(3)`) | 3 | 1 (varsayılan) |
| b[0], b[1] | hiçbir şey | 0 | 1 |

`Item b[2];` yazabilmek için constructor'ın **değersiz çağrılabilmesi** gerekiyor; burada iki parametrenin de varsayılan değeri olduğu için sorun yok.

---

## Alıştırma 21 – Struct template

**Task:** Write a **struct template** named `Box` that has a member `value` of type T and a function `doubled()` that returns `value * 2`. Then create one `int` box and one `double` box.

**Cevap:**

```cpp
template <class T>
struct Box {
    T value;
    T doubled() { return value * 2; }
};

int main() {
    Box<int> b1;
    b1.value = 7;
    Box<double> b2;
    b2.value = 1.25;
    cout << b1.doubled() << " " << b2.doubled() << endl;   // 14 2.5
}
```

**Neden?**
- Labwork 1'deki `TelemetryProcessor<double>` ile aynı kalıp.
- Struct template'te tipi **nesneyi oluştururken sen yazarsın**: `Box<int>`, `Box<double>`.
- `struct` olduğu için üyeler varsayılan olarak **public**; `b1.value = 7;` doğrudan yazılabiliyor.

---

## Alıştırma 22 – Aynı isim: üye, parametre, global

**Task:** What is the output of the following program? Be careful: there are **three different things** named `level`.

```cpp
int level = 1;

class Game {
    int level;
public:
    Game(int level) {
        this->level = level;
        ::level = ::level + level;
    }
    void show() const { cout << level << " " << ::level << endl; }
};

int main() {
    Game g1(5);
    g1.show();
    Game g2(10);
    g2.show();
    cout << level << endl;
}
```

**Cevap:**
```
5 6
10 16
16
```

**Neden?**

| Yazım | Hangisi? |
|---|---|
| `::level` | **global** level (en üstteki) |
| `this->level` | **nesnenin** level'ı |
| constructor içinde `level` | **parametre** (en yakındaki) |
| `show()` içinde `level` | **nesnenin** level'ı (show'un parametresi yok) |
| `main` içinde `level` | **global** level (main'de yerel level yok) |

- `g1(5)`: nesnenin level'ı 5; global = 1 + 5 = **6**.
- `g2(10)`: nesnenin level'ı 10; global = 6 + 10 = **16**.
- `main` en sonda global'i yazar: **16**.
