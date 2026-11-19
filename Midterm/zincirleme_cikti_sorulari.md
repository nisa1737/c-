# Zincirleme (Chaining) Çıktı Soruları Nasıl Çözülür?

Bütün örnekler derlenip çalıştırıldı; çıktılar gerçek çıktılardır.

---

## Yöntem: 4 adım

**Adım 1 – Her fonksiyonun dönüş tipine bak**

| Dönüş tipi | Ne olur? |
|---|---|
| `Sinif&` + `return *this;` | **aynı nesne** geri döner → zincir **asıl nesne** üzerinde devam eder |
| `Sinif` (`&` **yok**) + `return *this;` | **kopya** döner → zincirin **geri kalanı kopya** üzerinde çalışır, asıl nesne **değişmez** |
| `void` | hiçbir şey dönmez → zincirin **en sonunda** olabilir, arkasına başka fonksiyon gelemez |

**Adım 2 – Zinciri soldan sağa, tek tek çalıştır**

```cpp
c.add(3).times(4).add(-5);
```

Bunu kafanda şöyle aç:

```
1) c.add(3)
2) c.times(4)
3) c.add(-5)
```

Her adımdan sonra **nesnenin kutusunu güncelle**.

**Adım 3 – Fonksiyonların içindeki `cout`'ları ve `if`'leri unutma**

Zincirdeki her fonksiyon çalışırken içindeki `cout` da çalışır. Sınır kontrolü (`if (level > limit)`) varsa her adımda kontrol et.

**Adım 4 – Zincirden sonraki satırlar ve destructor'lar**

Zincir bitince nesnenin son halini yaz. Program bitince destructor'lar **ters sırayla** çalışır.

---

## Örnek 1 – Temel zincir

```cpp
#include <iostream>
using namespace std;

class Counter {
    int n;
public:
    Counter(int x = 0) : n(x) {}
    Counter& add(int k) {
        n += k;
        cout << "add " << n << endl;
        return *this;
    }
    Counter& times(int k) {
        n *= k;
        cout << "times " << n << endl;
        return *this;
    }
    void show() const { cout << "n = " << n << endl; }
};

int main() {
    Counter c(2);
    c.add(3).times(4).add(-5);
    c.show();
    return 0;
}
```

**Çıktı:**

```
add 5
times 20
add 15
n = 15
```

**Çözüm:**

Dönüş tipleri: `add` → `Counter&`, `times` → `Counter&`. Hepsi **aynı nesneyi** döndürüyor; zincir baştan sona **c** üzerinde çalışır.

| Adım | İşlem | c.n | Ekran |
|---|---|---|---|
| başlangıç | `Counter c(2);` | 2 | |
| 1 | `add(3)` | 2 + 3 = **5** | `add 5` |
| 2 | `.times(4)` | 5 × 4 = **20** | `times 20` |
| 3 | `.add(-5)` | 20 − 5 = **15** | `add 15` |
| sonra | `c.show();` | 15 | `n = 15` |

---

## Örnek 2 – `&` unutulursa (sınavın en sevdiği tuzak)

```cpp
#include <iostream>
using namespace std;

class Box {
    int v;
public:
    Box(int x) : v(x) {}
    Box& inc() { v++; return *this; }
    Box dbl() { v *= 2; return *this; }
    void show() const { cout << v << endl; }
};

int main() {
    Box b(1);
    b.inc().dbl().inc().inc();
    b.show();
    return 0;
}
```

**Çıktı:**

```
4
```

**Çözüm:**

Dönüş tiplerine bak: `inc` → `Box&` (aynı nesne), ama **`dbl` → `Box`** (`&` yok, **kopya**).

| Adım | İşlem | Kim üzerinde? | b.v | Kopyanın v'si |
|---|---|---|---|---|
| başlangıç | `Box b(1);` | | 1 | |
| 1 | `b.inc()` | **b** | **2** | |
| 2 | `.dbl()` | **b** | **4** | → b'nin **kopyası** döner (v = 4) |
| 3 | `.inc()` | **kopya** | 4 (değişmedi) | 5 |
| 4 | `.inc()` | **kopya** | 4 (değişmedi) | 6 |
| sonra | `b.show();` | **b** | **4** | |

`dbl()` kendi işini **b üzerinde** yapıyor (b = 4), ama geriye **kopya** veriyor. O andan sonraki her şey kopyaya oluyor; kopya da satır bitince kayboluyor.

**Kural:** Zincirde `&`'siz bir fonksiyon gördüğün an, **ondan sonrakiler asıl nesneyi değiştirmez**.

---

## Örnek 3 – Sınav tarzı: sınır kontrolü, global değişken, destructor

```cpp
#include <iostream>
using namespace std;

int limit = 10;

class Tank {
    char name;
    int level;
public:
    Tank(char n, int l = 0) : name(n), level(l) { cout << name << " created" << endl; }
    ~Tank() { cout << name << " " << level << endl; }

    Tank& fill(int k) {
        level += k;
        if (level > ::limit) {
            cout << "overflow" << endl;
            level = ::limit;
        }
        return *this;
    }

    Tank& drain(int k) {
        level -= k;
        if (level < 0)
            level = 0;
        return *this;
    }
};

int main() {
    Tank a('A', 4), b('B');
    a.fill(3).drain(5).fill(9);
    limit = 20;
    b.fill(12).fill(6).drain(1);
    cout << "end" << endl;
    return 0;
}
```

**Çıktı:**

```
A created
B created
overflow
end
B 17
A 10
```

**Çözüm:**

**Nesneler oluşuyor:**

| Satır | Ne oluyor? | Ekran |
|---|---|---|
| `Tank a('A', 4)` | a.level = 4 | `A created` |
| `b('B')` | level verilmedi → varsayılan **0** | `B created` |

**1. zincir: `a.fill(3).drain(5).fill(9);`** (limit = 10)

| Adım | İşlem | a.level | Ekran |
|---|---|---|---|
| 1 | `fill(3)` | 4 + 3 = **7** (10'u geçmedi) | |
| 2 | `.drain(5)` | 7 − 5 = **2** | |
| 3 | `.fill(9)` | 2 + 9 = 11 → 10'u geçti → **10** | `overflow` |

**`limit = 20;`** → global sınır artık 20.

**2. zincir: `b.fill(12).fill(6).drain(1);`** (limit = 20)

| Adım | İşlem | b.level | Ekran |
|---|---|---|---|
| 1 | `fill(12)` | 0 + 12 = **12** | |
| 2 | `.fill(6)` | 12 + 6 = **18** (20'yi geçmedi) | |
| 3 | `.drain(1)` | 18 − 1 = **17** | |

**`cout << "end"`** → `end`

**main biter, destructor'lar ters sırayla:** b sonra doğdu → önce **`B 17`**, sonra **`A 10`**.

**Tuzaklar:**
- `limit` iki zincir arasında değişti: 1. zincirde 10, 2. zincirde **20**. b 18'e çıktığında taşmadı.
- `overflow` mesajı **sadece bir kez** çıktı (a'nın son adımında).
- Destructor'lar nesnelerin **son** halini yazıyor.

---

## Özet: zincir çıktı sorusunda kontrol listesi

1. Her fonksiyonun dönüş tipi `Sinif&` mi, `Sinif` mı, `void` mu?
2. Zinciri **soldan sağa** aç; her adımda nesnenin kutusunu güncelle.
3. `&`'siz bir fonksiyondan sonra gelenler **kopyayı** değiştirir.
4. Fonksiyonların içindeki `cout` ve `if`'leri her adımda kontrol et.
5. Zincirler arasında global değişken değişiyor mu?
6. En sonda destructor'lar **ters sırayla**.
