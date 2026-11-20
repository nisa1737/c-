# Constructor ve Destructor Çıktı Soruları

Constructor değerleri **artırıyor**, destructor **azaltıyor**; program bitince değerler **0'a iniyor**.
3 soru; her birinin cevabı ve adım adım çözümü hemen altında. Bütün kodlar derlenip çalıştırıldı.

**Hatırla:**
- Constructor, nesne **oluşunca** çalışır.
- Destructor, nesne **yok olunca** çalışır; `main` içindeki nesneler `main` bitince yok olur.
- Yok olma sırası, oluşma sırasının **tersidir**.
- Global değişken **tek bir kutudur**; her nesne aynı kutuyu değiştirir.

---

## Soru 1

What is the output of the following program?

```cpp
#include <iostream>
using namespace std;

int alive = 0;

class Robot {
    int id;
public:
    Robot(int i = 0) : id(i) {
        alive++;
        cout << "C" << id << " alive=" << alive << endl;
    }
    ~Robot() {
        alive--;
        cout << "D" << id << " alive=" << alive << endl;
    }
};

int main() {
    Robot r1(1);
    Robot arr[2] = {2, 3};
    Robot r4;
    cout << "main ends, alive=" << alive << endl;
    return 0;
}
```

### Cevap

```
C1 alive=1
C2 alive=2
C3 alive=3
C0 alive=4
main ends, alive=4
D0 alive=3
D3 alive=2
D2 alive=1
D1 alive=0
```

### Çözüm

`alive`, o an **kaç robotun yaşadığını** sayıyor: constructor 1 artırıyor, destructor 1 azaltıyor.

**Doğum:**

| Satır | Robot | alive | Ekran |
|---|---|---|---|
| `Robot r1(1);` | id 1 | 0 → **1** | `C1 alive=1` |
| `Robot arr[2] = {2, 3};` | id 2 | 1 → **2** | `C2 alive=2` |
| | id 3 | 2 → **3** | `C3 alive=3` |
| `Robot r4;` | değer yok → id **0** | 3 → **4** | `C0 alive=4` |
| `cout` | | 4 | `main ends, alive=4` |

**Ölüm** (`main` biter, **ters sırayla**: r4 → arr[1] → arr[0] → r1):

| Robot | alive | Ekran |
|---|---|---|
| id 0 (r4) | 4 → **3** | `D0 alive=3` |
| id 3 (arr[1]) | 3 → **2** | `D3 alive=2` |
| id 2 (arr[0]) | 2 → **1** | `D2 alive=1` |
| id 1 (r1) | 1 → **0** | `D1 alive=0` |

**Tuzaklar:**
- Destructor'da önce `alive--`, **sonra** `cout` var; bu yüzden azalmış değer yazılıyor.
- `Robot r4;` için id varsayılan **0**.
- Dizinin elemanları da tersten ölür: önce 3, sonra 2.

---

## Soru 2

What is the output of the following program?

```cpp
#include <iostream>
using namespace std;

int total = 0;

class Wallet {
    char owner;
    int money;
public:
    Wallet(char o, int m = 10) : owner(o), money(m) {
        total += money;
        cout << owner << " +" << money << " total=" << total << endl;
    }
    ~Wallet() {
        total -= money;
        cout << owner << " -" << money << " total=" << total << endl;
    }
    void spend(int k) {
        if (k > money)
            k = money;
        money -= k;
        total -= k;
        cout << owner << " spent " << k << endl;
    }
};

int main() {
    Wallet a('A', 50), b('B');
    a.spend(20);
    b.spend(15);
    cout << "total=" << total << endl;
    return 0;
}
```

### Cevap

```
A +50 total=50
B +10 total=60
A spent 20
B spent 10
total=30
B -0 total=30
A -30 total=0
```

### Çözüm

`total`, bütün cüzdanlardaki **toplam parayı** tutuyor.

**Doğum:**

| Satır | Ne oluyor? | a.money | b.money | total | Ekran |
|---|---|---|---|---|---|
| `Wallet a('A', 50)` | a doğar | 50 | | **50** | `A +50 total=50` |
| `b('B')` | para verilmedi → varsayılan **10** | 50 | 10 | **60** | `B +10 total=60` |

**Harcamalar:**

| Satır | Ne oluyor? | a.money | b.money | total | Ekran |
|---|---|---|---|---|---|
| `a.spend(20)` | 20 ≤ 50, harcanır | **30** | 10 | **40** | `A spent 20` |
| `b.spend(15)` | 15 > 10 → **k = 10** (sadece olan kadar) | 30 | **0** | **30** | `B spent 10` |
| `cout` | | | | 30 | `total=30` |

**Ölüm** (ters sıra: önce b, sonra a):

| Nesne | Ne oluyor? | total | Ekran |
|---|---|---|---|
| b | b'de **0** lira var, 0 çıkarılır | 30 | `B -0 total=30` |
| a | a'da 30 lira var | 30 − 30 = **0** | `A -30 total=0` |

**Tuzaklar:**
- `b.spend(15)`: b'nin sadece 10 lirası var; `if` k'yı 10'a düşürür. Ekrana `spent 15` değil **`spent 10`** çıkar.
- Destructor nesnenin **o anki** parasını çıkarır (başlangıçtakini değil): b için 0, a için 30.
- Sonunda `total` tam **0** oluyor, çünkü eklenen her para bir yerde geri çıkarıldı.

---

## Soru 3

What is the output of the following program?

```cpp
#include <iostream>
using namespace std;

int g = 3;

class Cell {
    int v;
public:
    Cell(int x) { v = x; g += x; }
    Cell(int x, int y) : v(x * y) { g = 0; }
    ~Cell() {
        cout << v << " " << g << endl;
        g -= v;
    }
    void step(int &a, int b = 2) {
        a += v;
        v -= b;
        b = 0;
    }
};

int main() {
    int p = 1;
    Cell c1(4), c2(2, 3);
    c1.step(p);
    c2.step(p, 5);
    cout << p << " " << g << endl;
    return 0;
}
```

### Cevap

```
11 0
1 0
2 -1
```

### Çözüm

**Parçaları tanı:**

| Parça | Ne yapıyor? |
|---|---|
| `Cell(int x)` | **1 sayı** ile: v = x, **g'ye x ekler** |
| `Cell(int x, int y)` | **2 sayı** ile: v = x × y, **g'yi 0 yapar** |
| `~Cell()` | **önce** v ve g'yi yazar, **sonra** g'den v'yi çıkarır |
| `step(int &a, int b = 2)` | a referans, b kopya; b verilmezse 2 |

**Başlangıç:** g = 3, p = 1

**Doğum:**

| Satır | Çalışan constructor | v | g |
|---|---|---|---|
| `Cell c1(4)` | 1 sayılı | c1.v = **4** | 3 + 4 = **7** |
| `c2(2, 3)` | 2 sayılı | c2.v = 2 × 3 = **6** | **0** |

**`c1.step(p);`** → a = **p'nin kendisi**, b = **2** (varsayılan), v = **c1'in** v'si

| Satır | Sonuç |
|---|---|
| `a += v;` | p = 1 + 4 = **5** |
| `v -= b;` | c1.v = 4 − 2 = **2** |
| `b = 0;` | sadece kopya değişir, hiçbir etkisi yok |

**`c2.step(p, 5);`** → a = p'nin kendisi, b = **5**, v = **c2'nin** v'si

| Satır | Sonuç |
|---|---|
| `a += v;` | p = 5 + 6 = **11** |
| `v -= b;` | c2.v = 6 − 5 = **1** |

**`cout << p << " " << g`** → **`11 0`**

**Ölüm** (ters sıra: önce c2, sonra c1):

| Nesne | Ekrana yazılan (önce) | Sonra g |
|---|---|---|
| c2 | v = 1, g = 0 → **`1 0`** | 0 − 1 = **−1** |
| c1 | v = 2, g = −1 → **`2 -1`** | −1 − 2 = −3 (yazılmıyor) |

**Tuzaklar:**
- `c2(2, 3)` constructor'ı g'yi **sıfırlıyor**; c1'in eklediği 4 kayboluyor.
- Destructor'da `cout` **önce**, `g -= v` **sonra**. Bu yüzden c2 yazarken g hâlâ 0; c1 yazarken g, c2'nin destructor'ı yüzünden **−1** olmuş.
- `b = 0;` satırı hiçbir şeyi değiştirmiyor, çünkü b bir **kopya**.
- Son değer (−3) ekrana **hiç yazılmıyor**, çünkü ondan sonra `cout` yok.

---

## Bu tür sorularda kontrol listesi

1. **Constructor'ların içine bak:** global değişkeni artırıyor mu, sıfırlıyor mu, ekrana yazıyor mu?
2. **Hangi constructor?** Parantezdeki değer sayısına bak; eksik değer varsa varsayılan değeri kullan.
3. **Fonksiyon çağrılarında:** hangi nesnenin değişkenleri değişiyor, parametre `&` mi?
4. **Destructor'ın içinde sıraya bak:** önce `cout` mu, önce değişiklik mi? Önce değişiklik varsa **değişmiş** değer yazılır.
5. **Destructor'lar ters sırayla:** her biri global değişkeni değiştiriyorsa, bir sonraki destructor **değişmiş** değeri görür.
