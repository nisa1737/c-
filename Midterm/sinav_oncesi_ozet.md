# CENG241 – Sınav Öncesi Özet

Sınavdan önce bilmen gereken her şey, **konu konu**, her birinin **nasıl kullanıldığı** ve **kısa örnekleriyle**.
Sadece derste, lab'larda ve recitation'da gördüğün konular var. Örneklerdeki çıktıların hepsi çalıştırılarak doğrulandı.

**İçindekiler**

1. Temel yazım kuralları
2. Namespace ve `::`
3. Varsayılan parametre
4. Function overloading
5. Template
6. Referans (`&`) ve `const &`
7. Sınıf: class, struct, private, public
8. Constructor
9. Destructor ve yok olma sırası
10. Nesne dizileri
11. Dinamik bellek: `new`, `delete`, `->`
12. `this` pointer
13. Zincirleme (chaining)
14. Yeni nesne döndüren fonksiyon
15. Friend fonksiyon ve friend class
16. Girdi alma: `cin`, `getline`
17. Çıktı sorusu nasıl çözülür?
18. Kod sorusu nasıl yazılır?
19. En sık yapılan hatalar

---

## 1. Temel yazım kuralları

| Kural | Örnek |
|---|---|
| Her program bununla başlar | `#include <iostream>` ve `using namespace std;` |
| `string` kullanacaksan | `#include <string>` |
| `main`'in dönüş tipi yazılır | `int main() { ... return 0; }` |
| Tırnak içi **aynen** yazılır, tırnaksızın **değeri** yazılır | `cout << "x";` → `x` ; `cout << x;` → `5` |
| `endl` ve `"\n"` alt satıra geçirir | `cout << "a" << endl;` |
| Kullanıcı aynı satıra yazsın istiyorsan `endl` koyma | `cout << "Enter: "; cin >> n;` |
| Boşluklar tırnağın **içinde** olmalı | `cout << "Total: " << t;` |
| `class` ve `struct` `};` ile biter | `class A { ... };` |
| Fonksiyonlar `}` ile biter (noktalı virgül yok) | `void f() { ... }` |
| Tırnaklar **düz** olmalı | `"hi"` doğru, `“hi”` yanlış |

---

## 2. Namespace ve `::`

**Ne işe yarar?** İsimleri gruplar; farklı yerlerdeki aynı isimler karışmaz.

```cpp
namespace first { int x = 5; }
int x = 1;              // global

int main() {
    int x = 10;         // yerel
    cout << x << " " << ::x << " " << first::x;   // 10 1 5
}
```

| Yazım | Anlamı |
|---|---|
| `x` | en yakındaki (yerel) x |
| `::x` | **global** x (başında hiçbir şey yok) |
| `first::x` | first namespace'inin içindeki x |

**Sınıf namespace'in içindeyse** (Labwork 1):

```cpp
namespace Math {
    class Calculator { ... };
}
Math::Calculator calc;     // nesne olustururken Math::
calc.add(2, 3);            // sonra nokta ile
```

**Dikkat:** İki namespace'i birden `using` ile açarsan ve ikisinde de aynı isim varsa → **belirsizlik hatası**.

**Kural:** namespace → `::`, nesne → `.`

---

## 3. Varsayılan parametre

**Ne işe yarar?** Değer gönderilmezse kullanılacak değeri belirler.

```cpp
void f(int a, int b = 5, int c = 10) {
    cout << a << " " << b << " " << c << endl;
}

f(1);        // 1 5 10
f(1, 2);     // 1 2 10
f(1, 2, 3);  // 1 2 3
```

**Kurallar:**
- Gönderilen değerler **soldan sağa** yerleşir.
- Varsayılan değerler **sağdan** başlar: `f(int a = 1, int b)` → **HATA**.
- Fonksiyon önce bildirilip sonra tanımlanıyorsa, varsayılan değer **sadece bildirimde** yazılır:

```cpp
int modify(int&, int = 4);              // bildirim: = 4 burada
int Sample::modify(int& m, int n) { }   // tanım: = 4 YOK
```

---

## 4. Function overloading

**Ne işe yarar?** Aynı isimde, **parametreleri farklı** birden fazla fonksiyon yazmayı sağlar.

```cpp
void show(int a)    { cout << "int " << a; }
void show(double a) { cout << "double " << a; }

show(5);     // int 5
show(2.5);   // double 2.5
show(2.0);   // double 2   (noktalı yazıldığı için double)
```

**Derleyici nasıl seçer?** Önce **kaç değer** gönderildiğine, sonra **tipine** (yazılışına) bakar: `5` int, `2.5` / `2.0` double, `'x'` char.

**Dikkat:** Sadece dönüş tipi farklıysa overloading **olmaz**; fark parantezin içinde olmalı.

**Constructor'lar da overload edilir** ("overloaded constructor"): bir sınıfta birden fazla constructor.

---

## 5. Template

**Ne işe yarar?** Kodu **bir kez** yazıp **her tip** için kullanmayı sağlar. `T` bir yer tutucudur.

**Soruda nasıl anlarsın?** Tip yerine **T** yazıyorsa (`calibrationFactor: T`, "a T type variable").

**Fonksiyon template:** T'yi derleyici bulur.

```cpp
template <class T>
T sum(T a, T b) { return a + b; }

sum(2, 3);       // T = int    → 5
sum(2.5, 4.1);   // T = double → 6.6
```

**Struct / class template:** T'yi **sen yazarsın**.

```cpp
template <class T>
struct Box { T value; };

Box<double> b;      // T = double
b.value = 1.5;
```

- `class T` içindeki `class` burada "tip" demek; `typename T` ile aynı.
- Fonksiyon bildirimi ve tanımı ayrıysa `template <class T>` **ikisinin başına da** yazılır.

---

## 6. Referans (`&`) ve `const &`

**Referans = aynı değişkenin ikinci adı.**

```cpp
int k = 5;
int &r = k;     // r, k'nin takma adı
r += 3;
cout << k << " " << r;   // 8 8
```

**Referans tanımlanırken bağlanmalı:** `int &r;` → **HATA**.

**Parametrede:**

```cpp
void byValue(int a) { a = 100; }   // kopya
void byRef(int &a)  { a = 100; }   // aslı

int m = 1;
byValue(m);   // m hâlâ 1
byRef(m);     // m = 100
```

| Yazım | Anlamı | Asıl değişken değişir mi? |
|---|---|---|
| `int a` | kopya | hayır |
| `int &a` | aslı | **evet** |
| `const int &a` | aslı ama dokunma | hayır (değiştirmeye çalışırsan hata) |

**`int &a` parametresine sabit sayı gönderilemez:** `byRef(5);` → **HATA**.

---

## 7. Sınıf: class, struct, private, public

```cpp
class Thermometer {
    double celsius;                     // private (varsayilan)
public:
    void setCelsius(double c) { celsius = c; }       // set: deger yazar
    double getCelsius() const { return celsius; }    // get: deger okur
};

Thermometer t;          // nesne
t.setCelsius(25);       // nokta ile kullanim
```

| Kavram | Anlamı |
|---|---|
| **Sınıf** | kalıp (`Thermometer`) |
| **Nesne** | kalıptan üretilen (`t`) |
| `.` | "-nin": `t.getCelsius()` = t'nin getCelsius'u |
| **private** | sadece sınıfın içinden erişilir |
| **public** | dışarıdan da erişilir |
| UML'de `-` / `+` | private / public |
| `class` | varsayılan **private** |
| `struct` | varsayılan **public** |

**Sonunda `const` olan fonksiyon** nesneyi **değiştiremez**, sadece okur. Get ve display fonksiyonlarına yazılır.

**Fonksiyonu sınıfın dışında tanımlamak:**

```cpp
class Test {
public:
    int getX();          // icerde: bildirim
private:
    int x;
};

int Test::getX() {       // disarda: Sinif:: ile
    return x;
}
```

**Her nesnenin kendi değişkenleri vardır.** `obj1.f()` içindeki değişkenler obj1'inkiler, `obj2.f()` içindekiler obj2'ninkiler.

**UML tablosunu okumak:**

| UML | C++ |
|---|---|
| `- price: double` | `double price;` (private) |
| `+ setPrice(double): void` | `void setPrice(double p)` (public) |
| `+ getPrice(): double` | `double getPrice()` |

---

## 8. Constructor

**Nesne oluştuğu anda kendiliğinden çalışan fonksiyon.** Görevi başlangıç değerlerini vermek.

- Adı sınıfın adıyla **aynı**.
- **Dönüş tipi yok** (`void` bile yazılmaz).
- Sen çağırmazsın.

**Çeşitleri:**

```cpp
class Point {
    int x, y;
public:
    Point() { x = 0; y = 0; }                       // parametresiz (default)
    Point(int a, int b) { x = a; y = b; }            // parametreli
};
```

```cpp
Clock(int h = 0, int m = 0) : hour(h), minute(m) { }   // varsayilan degerli
// Clock c1;  Clock c2(9);  Clock c3(14, 30);  hepsi calisir
```

**Hangisi çalışır?** Nesne oluşturulurken **parantezdeki değer sayısına** bak:

```cpp
Point p1;          // 0 deger → Point()
Point p2(3, 5);    // 2 deger → Point(int, int)
```

**Initialization list** (`:` ile):

```cpp
S(int a, int b) : x(a), y(b) { }    // x = a, y = b
```

`const` ve **referans** üyelere değer **sadece initialization list** ile verilebilir:

```cpp
class Order {
    const int orderNo;
public:
    Order(int n) : orderNo(n) { }       // DOGRU
    // Order(int n) { orderNo = n; }    // HATA
};
```

**Constructor overloading:** aynı sınıfta birden fazla constructor; her biri nesneyi farklı kurar.

---

## 9. Destructor ve yok olma sırası

**Nesne yok olurken kendiliğinden çalışan fonksiyon.** Görevi temizlik (`delete`) ve son mesaj.

- Adı `~` + sınıfın adı: `~Tag()`
- Dönüş tipi yok, parametre yok.
- **Sen çağırmazsın.** `main` bitince (nesne `main` içindeyse) kendiliğinden çalışır.

```cpp
class Tag {
    int id;
public:
    Tag(int i) : id(i) { cout << "C" << id << " "; }
    ~Tag() { cout << "D" << id << " "; }
};

int main() {
    Tag t1(1);
    Tag t2(2);
    cout << "| ";
}
// Cikti: C1 C2 | D2 D1
```

**EN ÖNEMLİ KURAL:** Nesneler **oluşturulma sırasının tersine** yok olur. Son doğan, ilk ölür (tabak yığını).

- Sırayı bulmak için **nesnelerin tanımlandığı satıra** bak (`Box b1(5), b2(1, 4);` → b1 sonra b2 doğar → önce **b2** ölür). Hangi fonksiyonun önce çağrıldığı önemli değil.
- Dizinin elemanları da tersten ölür: `arr[2]`, `arr[1]`, `arr[0]`.
- Destructor'daki **global değişken**, o anki **son değeriyle** yazılır.

---

## 10. Nesne dizileri

```cpp
Item a[3] = { Item(1, 5), Item(2), 3 };   // her eleman icin ayri constructor
Item b[2];                                 // degersiz → her biri default constructor
```

| Eleman | Verilen | Çalışan constructor |
|---|---|---|
| a[0] | `Item(1, 5)` | 2 parametreli |
| a[1] | `Item(2)` | 1 değer, diğeri varsayılan |
| a[2] | `3` | `Item(3)`'ün kısa yazımı |
| b[0], b[1] | yok | parametresiz / tamamı varsayılan |

- `Item b[2];` yazabilmek için constructor'ın **değersiz çağrılabilmesi** şart. Yoksa **hata**.
- Dizi tanımlama kalıbı: `Tip isim[boyut];` → `int sayilar[5];`, `Vehicle vehicles[n];`
- Elemanı kullanmak: `a[i].show();` = "i'inci elemanın show'u".

---

## 11. Dinamik bellek: `new`, `delete`, `->`

**Ne zaman?** Boyut **program çalışırken** belli oluyorsa (kullanıcı giriyorsa).

```cpp
int n;
cin >> n;
int *arr = new int[n];   // n kutuluk yer al, adresini arr'a koy
arr[0] = 5;              // normal dizi gibi kullan
delete[] arr;            // isin bitince geri ver
```

| Yer alırken | Geri verirken |
|---|---|
| `new int[n]` (dizi) | `delete[] p;` |
| `new Rational` (tek nesne) | `delete p;` |

**`*` sadece tanımlarken yazılır:**

```cpp
int *scores;              // tanimlama: yildiz var
scores = new int[5];      // kullanim: yildiz yok
```

**Nesne için `new` ve `->`:**

```cpp
Rational *q = new Rational(3, 4);
q->display();             // adresle calisirken ok: ->
delete q;
```

| Elinde ne var? | Nasıl kullanılır? |
|---|---|
| nesnenin kendisi (`Rational r;`) | `r.display()` |
| nesnenin adresi (`Rational *q`) | `q->display()` (ya da `(*q).display()`) |
| dizinin elemanı (`arr[1]`) | `arr[1].display()` |

**Sınıfın içinde (en çok sorulan kalıp):** constructor'da `new`, destructor'da `delete`.

```cpp
class Scores {
    int *arr;
    int size;
public:
    Scores(int n) {
        size = n;              // UNUTMA
        arr = new int[size];
    }
    ~Scores() {
        delete[] arr;
    }
};
```

**`char*` metin kopyalamak** (Labwork 4): say → yer ayır (+1) → kopyala → sonuna `'\0'`.

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
~Label() { delete[] text; }
```

- `'\0'` metnin bittiğini gösterir; bu yüzden **+1** kutu.
- Diziler `=` ile kopyalanmaz; harf harf kopyalanır.
- `new` ile alınan yer geri verilmezse → **memory leak**.

---

## 12. `this` pointer

`this` = fonksiyonun o an çalıştığı **nesnenin adresi**. "Ben" demek.

| Yazım | Anlamı |
|---|---|
| `this` | bu nesnenin adresi |
| `this->brand` | bu nesnenin brand'i |
| `*this` | bu nesnenin kendisi |

**Ne zaman zorunlu?** Parametre adı değişken adıyla **aynı** olduğunda:

```cpp
Car& setBrand(string brand) {
    this->brand = brand;   // sol: nesnenin brand'i, sag: parametre
    return *this;
}
```

`this->` yazmazsan `brand = brand;` olur: parametre kendine atanır, nesne **değişmez**.

- Bilgiyi `main`'den sınıfa **parametre** getirir; `this` sadece **hangi nesneye** yazılacağını söyler.
- Soru "parameter names must be the same as the data members" diyorsa `this->` **zorunlu**.

---

## 13. Zincirleme (chaining)

**Ne işe yarar?** Aynı nesne üzerinde birden fazla fonksiyonu **tek satırda** art arda çağırmayı sağlar.

```cpp
c.setBrand("TOGG").setYear(2026);
```

**İki şart:**
1. Dönüş tipi **`Sinif&`**
2. Son satır **`return *this;`**

```cpp
Car& setYear(int year) {
    this->year = year;
    return *this;      // "al, yine ben"
}
```

- `void` olsaydı zincir kurulamazdı.
- `&` unutulursa (`Car setYear(...)`) zincirin devamı **kopya** üzerinde çalışır; asıl nesne değişmez.
- Fonksiyon bir şeyi reddetse bile (ör. "Playlist is full!") `return *this;` yapmalı.

---

## 14. Yeni nesne döndüren fonksiyon

**Ne işe yarar?** İki nesneden **yeni bir sonuç** üretmek (toplama, çarpma...).

```cpp
class Money {
    int lira;
public:
    Money(int l = 0) : lira(l) {}
    Money add(const Money &m) const {
        return Money(lira + m.lira);   // yeni nesne
    }
};

Money m1(10), m2(20);
Money m3 = m1.add(m2);     // 30; m1 ve m2 degismez
```

| Amaç | Dönüş tipi | Son satır |
|---|---|---|
| Aynı nesneyi değiştirip zincirlemek | `Sinif&` | `return *this;` |
| Yeni bir sonuç üretmek | `Sinif` | `return Sinif(...);` |

---

## 15. Friend fonksiyon ve friend class

**Friend** = sınıfın üyesi **olmayan** bir fonksiyona private'lara erişme izni vermek.

```cpp
class Pen {
    string color;
public:
    Pen(string c) : color(c) {}
    friend bool sameColor(const Pen &p1, const Pen &p2);   // 1) icerde: izin
};

bool sameColor(const Pen &p1, const Pen &p2) {             // 2) disarda: govde
    return p1.color == p2.color;
}

sameColor(a, b);                                           // 3) nokta YOK
```

**3 kural:**
1. İçeride başına `friend` yazılır.
2. Gövdede `friend` ve `Pen::` **yok** (üye değil).
3. **Nokta olmadan** çağrılır.

- `this` **yok**; nesnelere **parametrelerle** ulaşır. Kaç nesne lazımsa o kadar parametre.
- `const Pen &` zorunlu değil, iyi alışkanlık; soru/tablo yazıyorsa aynen yaz.

**Ne zaman kullanılır?**
- İki nesne üzerinde eşit çalışan işlem: `add(c1, c2)`, `crossProduct(v, w)`
- Gizli bilgiyi dışarıdan göstermek: `inspectWeaponLore(weapon)`
- İki farklı sınıfın private'larına birden erişmek (iki sınıf da friend yapar)

**Friend class:** başka bir sınıfın **bütün** fonksiyonlarına izin.

```cpp
class B;              // on bildirim (B asagida tanimli)

class A {
    int x;
    friend class B;   // B, A'nin private'larina erisebilir
};
```

Arkadaşlık **tek yönlü**: B, A'nınkileri görür; A, B'ninkileri göremez.

| | Üye fonksiyon | Friend fonksiyon |
|---|---|---|
| Çağrılışı | `nesne.f()` | `f(nesne)` |
| `this` | var | **yok** |
| Gövdede `Sinif::` | var (dışarıda yazılırsa) | **yok** |

---

## 16. Girdi alma: `cin`, `getline`

| Ne okuyorsun? | Ne kullan? |
|---|---|
| sayı, tek kelime | `cin >> x;` |
| boşluklu metin, `string` | `getline(cin, s);` |
| boşluklu metin, `char` dizisi | `cin.getline(dizi, boyut);` |

`cin >>` **ilk boşlukta durur**: "Victor Hugo" için sadece "Victor" alınır.

**`cin >>`'dan sonra `getline` geliyorsa** araya `cin.ignore();` koy; yoksa `getline` kalan Enter'ı görüp boş döner:

```cpp
cin >> id;
cin.ignore();               // kalan Enter'i at
cin.getline(name, 50);
```

---

## 17. Çıktı sorusu nasıl çözülür?

1. **Bütün değişkenler için kutu çiz:** global değişkenler, `main`'deki değişkenler ve **her nesnenin** değişkenleri ayrı ayrı.
2. **Nesneler oluşurken** kaç değer verildiğine bak → hangi constructor? Constructor'ın içinde `cout` ya da global değişken değişimi var mı?
3. **Fonksiyon çağrılarında:**
   - Noktadan önceki nesne hangisi? → o nesnenin değişkenleri değişir.
   - Parametre `&` mi? → asıl değişken değişir. `&` yok mu? → sadece kopya.
   - Eksik değer var mı? → varsayılan değer.
   - Aynı isimde iki fonksiyon varsa → gönderilen değer sayısına göre seç.
   - Fonksiyonun içinde aynı isimde yerel değişken var mı? → `isim` yerel, `::isim` global.
4. **Satırların sırasına dikkat:** `a = q + 2; q += 2;` → ilk satırda q'nun **eski** değeri kullanılır.
5. **`main` bitince** destructor'ları **ters sırayla** yaz; global değişkenin **son** değerini kullan.
6. **`cout`'larda** boşluklara ve `endl`'lere dikkat; `bool` yazdırılırsa `1` / `0` çıkar.

---

## 18. Kod sorusu nasıl yazılır?

**Sıra:**
1. Soruyu oku, işaretle: değişkenler, fonksiyonlar, örnek çıktı.
2. Sınıfın iskeleti (değişkenler + `};`).
3. Constructor(lar).
4. Fonksiyonlar (sorudaki sırayla).
5. Destructor.
6. `main`: örnek çıktıya bakarak satır satır (`cout` mu, `cin` mi?).
7. Kontrol: `};`, dönüş tipleri, `delete`, çıktı yazıları örnekle **birebir** aynı mı?

**Soruda bu yazıyorsa → bunu kullan:**

| Soruda... | ...kullan |
|---|---|
| "dynamically allocate" | `new` (genelde constructor'da) |
| "free / release the memory" | `delete` / `delete[]` (genelde destructor'da) |
| "parameter names must be the same as the data members" | `this->x = x;` |
| "chainable" / "via chaining" | `Sinif&` + `return *this;` |
| "global constant" | sınıfın dışında `const int ISIM = deger;` |
| "scope resolution operator" | `::ISIM` |
| "friend function" | içeride `friend ...;`, gövde dışarıda |
| "default constructor" | `Sinif() { ... }` |
| "with a default value" | `int x = 0` |
| "returns true if..." | dönüş tipi `bool` |
| "displays" / "returns" (değiştirmeden) | sonuna `const` |
| tip yerine **T** | template |
| `<<struct>>` | `struct` |
| "array for up to 50" | `Sinif dizi[50];` |
| boyut kullanıcıdan geliyor | `new Sinif[n];` + `delete[]` |

**Tip seçimi:** sayarak giden (ID, numara, adet) → `int`; küsuratlı olabilen (para, süre, ortalama) → `double`.

**Parametre gerekir mi?** Değer zaten **nesnenin içindeyse** parametre gerekmez (`calculateSalary()`); dışarıdan geliyorsa gerekir (`setBrand(string b)`).

**İsimler:** Soruda verilen isimleri (sınıf, fonksiyon, değişken) **aynen** kullan; verilmeyenleri (parametre adı, nesne adı) sen seç.

---

## 19. En sık yapılan hatalar

| Hata | Doğrusu |
|---|---|
| `class A { ... }` (noktalı virgül yok) | `class A { ... };` |
| `int &r;` | `int &r = x;` |
| `void f(int a = 1, int b);` | varsayılanlar sağdan: `void f(int a, int b = 1);` |
| `const` üyeye gövdede atama | initialization list: `: c(x)` |
| `this->` olmadan `brand = brand;` | `this->brand = brand;` |
| zincirleme fonksiyon `void` | `Sinif&` + `return *this;` |
| `new int[n]` ile alıp `delete p;` | `delete[] p;` |
| `delete`'i unutmak | destructor'da `delete[]` |
| `size = n;` satırını unutmak | constructor'da `size = n;` |
| pointer ile nokta: `q.display()` | `q->display()` |
| constructor'da `int *arr = new int[n];` (yeni yerel değişken) | `arr = new int[n];` |
| friend gövdesine `Sinif::` yazmak | `bool f(...) { }` |
| friend'i nokta ile çağırmak | `f(a, b);` |
| üç ayrı `if` (hepsi çalışır) | `if / else if` (sadece ilk uyan) |
| `else if` sırası küçükten büyüğe | büyükten küçüğe: önce `>= 3.5`, sonra `>= 3.0` |
| `cin >>` ile boşluklu metin | `getline` |
| destructor'ları oluşma sırasıyla yazmak | **ters** sıra |
| `Sinif dizi[5];` ama default constructor yok | parametresiz ya da tamamı varsayılan constructor ekle |
