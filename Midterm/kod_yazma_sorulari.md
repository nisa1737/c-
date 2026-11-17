# CENG241 – Konuları Birleştiren Kod Soruları

3 kod yazma sorusu. Her biri birkaç konuyu bir arada kullanıyor; midterm seviyesinde.
Her sorunun altında **"Nasıl düşünmelisin?"** bölümü var: sorudaki hangi cümle sana hangi C++ aracını kullanmanı söylüyor.

Bütün çözümler derlenip çalıştırıldı ve bellek kontrol aracıyla denendi: ayrılan belleğin hepsi geri veriliyor.

**Önce kendin yaz, sonra en alttaki ÇÖZÜMLER bölümüne bak.**

| Soru | Konular |
|---|---|
| 1 – Playlist | constructor'da `new`, destructor'da `delete[]`, `this->`, sınır kontrolü, zincirleme, `const` fonksiyon |
| 2 – Hero | `char*` dinamik isim, `this->`, destructor, zincirleme, global sabit ve `::`, friend fonksiyon |
| 3 – Product | iki constructor (biri varsayılan değerli), `this->`, `new` ile **nesne dizisi**, friend fonksiyon, `const` |

---

# Önce: hangi cümle neyi söylüyor?

Sınavda soruyu okurken bu kelimeleri gördüğünde ne yazacağını bil:

| Soruda bu yazıyorsa... | ...bunu kullan |
|---|---|
| "dynamically allocate" | `new` (genelde constructor'da) |
| "free / release the memory" | `delete` / `delete[]` (genelde destructor'da) |
| "parameter names must be the same as the data members" | `this->degisken = degisken;` |
| "can be called via chaining" / "chainable" | dönüş tipi `Sinif&`, son satır `return *this;` |
| "global constant" | sınıfın dışında `const int ISIM = deger;` |
| "use the (unary) scope resolution operator" | `::ISIM` |
| "friend function" | sınıfın içinde `friend ...;` bildirimi, gövdesi dışarıda (başında `Sinif::` yok) |
| "default constructor" | parametresiz constructor: `Sinif() { ... }` |
| "with default value(s)" | `int stock = 0` gibi varsayılan parametre |
| "displays" / "returns" (değiştirmeden) | fonksiyonun sonuna `const` |
| Sonucu destructor'da yazdırılan bir mesaj | destructor içinde `cout` |

---

# SORULAR

## Soru 1 – Playlist

Write a C++ program for a music player. Define a **class Playlist** including the following:

**Data Members:** *durations* (a pointer to an integer array), *capacity*, *count*

**Member Functions:**
- **Playlist(int capacity):** The parameter name must be the same as the data member. Stores the capacity, sets *count* to 0, and **dynamically allocates** an array of song durations.
- **~Playlist():** Frees the allocated memory and prints `[INFO] Playlist memory freed.`
- **addSong(int):** Adds a song duration to the end of the playlist. If the playlist is full, prints `Playlist is full! Song of X sec not added.` This function must be **chainable**.
- **totalDuration():** Returns the total duration of all songs.
- **display():** Prints the playlist as in the sample run.

In the main function, ask the capacity and create a Playlist. Then ask the number of songs and read their durations.
Finally, add two bonus songs (200 and 150 seconds) **in a single line using chaining**, and display the playlist.

Sample Run:

```
Enter playlist capacity: 4
Enter number of songs: 3
Enter duration of song 1: 210
Enter duration of song 2: 185
Enter duration of song 3: 240

Adding two bonus songs with chaining...
Playlist is full! Song of 150 sec not added.

--- Playlist (4/4) ---
Song 1: 210 sec
Song 2: 185 sec
Song 3: 240 sec
Song 4: 200 sec
Total: 835 sec
[INFO] Playlist memory freed.
```

### Nasıl düşünmelisin?

| Sorudaki ifade | Ne yazacaksın? |
|---|---|
| "dynamically allocates an array" | constructor'da `durations = new int[capacity];` |
| "Frees the allocated memory" | destructor'da `delete[] durations;` |
| "parameter name must be the same" | `this->capacity = capacity;` |
| "If the playlist is full" | `if (count < capacity)` kontrolü |
| "must be chainable" | `Playlist& addSong(int duration)` ve `return *this;` |
| "Returns the total" / "Prints" | `totalDuration() const`, `display() const` |

**İpucu:** `count` iki iş görüyor: hem kaç şarkı olduğunu sayıyor, hem de **yeni şarkının yazılacağı yeri** gösteriyor. 0 şarkı varken yeni şarkı `durations[0]`'a, 1 şarkı varken `durations[1]`'e gider.

---

## Soru 2 – Hero

Write a C++ program for a simple battle game. Define a **class Hero** including the following:

**Data Members:** *name* (char*), *health* (int), *power* (int)

Declare a **global constant** named `MAX_HEALTH` with the value **100**.

**Member Functions:**
- **Hero(const char*, int, int):** The parameter names must be the same as the data members, so use the **this pointer**. **Dynamically allocate** memory for the name and copy it.
- **~Hero():** Prints `<name> left the game.` and frees the memory.
- **takeDamage(int):** Decreases the health. Health cannot go below 0.
- **heal(int):** Increases the health. If the health exceeds `MAX_HEALTH`, prints `Health cannot exceed 100!` and sets it to `MAX_HEALTH`. Use the **unary scope resolution operator** to access the constant.
- **powerUp(int):** Increases the power.
- **display():** Prints the hero's name, health and power.
- *takeDamage(), heal() and powerUp()* must be **chainable**.

**Friend Function:**
- **compareHeroes(const Hero&, const Hero&):** Prints which hero is stronger (has more power), or `They are equally strong.`

In the main function, read two heroes, display them, then apply damage, heal and power bonus to the **first** hero **in a single line using chaining**. Display both heroes again and compare them.

Sample Run:

```
Enter first hero (name health power): Arthas 80 45
Enter second hero (name health power): Jaina 90 50

--- Before Battle ---
Arthas | Health: 80 | Power: 45
Jaina | Health: 90 | Power: 50

Enter damage, heal amount and power bonus for Arthas: 50 80 10
Health cannot exceed 100!

--- After Battle ---
Arthas | Health: 100 | Power: 55
Jaina | Health: 90 | Power: 50

Arthas is stronger.

Jaina left the game.
Arthas left the game.
```

### Nasıl düşünmelisin?

| Sorudaki ifade | Ne yazacaksın? |
|---|---|
| "global constant named MAX_HEALTH" | sınıfın üstüne `const int MAX_HEALTH = 100;` |
| "name (char*)" + "Dynamically allocate" | harfleri say → `new char[harf + 1]` → kopyala → sonuna `'\0'` |
| "frees the memory" | destructor'da `delete[] name;` |
| "parameter names must be the same" | `this->health = health;` |
| "unary scope resolution operator" | `::MAX_HEALTH` |
| "chainable" | `Hero&` döndür, `return *this;` |
| "Friend Function" | sınıfın içinde `friend void compareHeroes(...);` |

**İpucu 1:** Destructor'da önce ismi **yazdır**, sonra sil. Tersini yaparsan silinmiş ismi yazdırmaya çalışırsın.

**İpucu 2:** Destructor mesajlarının sırası: Jaina **sonra** oluştu, **önce** o yok olur.

**Hesap:** Arthas: 80 − 50 = 30 → 30 + 80 = 110 → 100'ü geçti, 100'e çekildi. Güç: 45 + 10 = 55.

---

## Soru 3 – Product

Write a C++ program for a small market. Define a **class Product** including the following:

**Data Members:** *code* (int), *name* (string), *price* (double), *stock* (int)

**Constructors:**
- A **default constructor** that sets all data members to 0 (and the name to an empty string).
- A **parameterized constructor** `Product(int, string, double, int)` where **stock has a default value of 0**. The parameter names must be the same as the data members.

**Member Functions:**
- **read():** Reads the product details from the user.
- **stockValue():** Returns price × stock.
- **display():** Prints the product as in the sample run.

**Friend Function:**
- **isCheaper(const Product&, const Product&):** Returns **true** if the first product is cheaper than the second one.

In the main function:
- Create your own product with the parameterized constructor **without giving the stock** (e.g. 100 Pencil 2.5) and display it.
- Ask the number of products and **dynamically create an array** of Product objects.
- Read all products, find the **cheapest** one using `isCheaper()`, and calculate the **total stock value**.
- Do not forget to free the memory.

Sample Run:

```
100 Pencil 2.5 TL (stock: 0)
Enter number of products: 3
Enter code, name, price, stock: 201 Notebook 45 10
Enter code, name, price, stock: 202 Pen 12.5 40
Enter code, name, price, stock: 203 Eraser 8 25

Cheapest product: 203 Eraser 8 TL (stock: 25)
Total stock value: 1150 TL
```

### Nasıl düşünmelisin?

| Sorudaki ifade | Ne yazacaksın? |
|---|---|
| "default constructor" | `Product() : code(0), name(""), price(0), stock(0) {}` |
| "stock has a default value of 0" | `Product(int code, string name, double price, int stock = 0)` |
| "parameter names must be the same" | `this->code = code;` ... |
| "without giving the stock" | `Product mine(100, "Pencil", 2.5);` (4. değer yok → stock = 0) |
| "dynamically create an array of Product objects" | `Product *products = new Product[n];` |
| "free the memory" | `delete[] products;` |
| "Returns true if..." | dönüş tipi `bool` |
| "Friend Function" | `friend bool isCheaper(...);` |

**İpucu 1:** `new Product[n]` her eleman için **default constructor**'ı çalıştırır. O constructor olmasaydı bu satır hata verirdi. Soru bu yüzden ikisini birden istiyor.

**İpucu 2:** En ucuzu bulmak için: "şimdilik en ucuz 0. ürün" diye başla, sonra her ürünü onunla karşılaştır; daha ucuzunu bulursan **indeksini** güncelle.

**Hesap:** 45 × 10 + 12.5 × 40 + 8 × 25 = 450 + 500 + 200 = **1150**

---
---

# ÇÖZÜMLER

## Çözüm 1 – Playlist

```cpp
#include <iostream>
using namespace std;

class Playlist {
    int *durations;     // sarki surelerini tutan dinamik dizinin adresi
    int capacity;       // en fazla kac sarki sigar
    int count;          // su an kac sarki var

public:
    Playlist(int capacity) {
        this->capacity = capacity;
        count = 0;
        durations = new int[capacity];
    }

    ~Playlist() {
        delete[] durations;
        cout << "[INFO] Playlist memory freed." << endl;
    }

    Playlist& addSong(int duration) {
        if (count < capacity) {
            durations[count] = duration;
            count++;
        }
        else
            cout << "Playlist is full! Song of " << duration << " sec not added." << endl;
        return *this;
    }

    int totalDuration() const {
        int total = 0;
        for (int i = 0; i < count; i++)
            total += durations[i];
        return total;
    }

    void display() const {
        cout << "--- Playlist (" << count << "/" << capacity << ") ---" << endl;
        for (int i = 0; i < count; i++)
            cout << "Song " << i + 1 << ": " << durations[i] << " sec" << endl;
        cout << "Total: " << totalDuration() << " sec" << endl;
    }
};

int main() {
    int capacity, n;

    cout << "Enter playlist capacity: ";
    cin >> capacity;

    Playlist myList(capacity);

    cout << "Enter number of songs: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        int d;
        cout << "Enter duration of song " << i + 1 << ": ";
        cin >> d;
        myList.addSong(d);
    }

    cout << endl << "Adding two bonus songs with chaining..." << endl;
    myList.addSong(200).addSong(150);
    cout << endl;

    myList.display();

    return 0;
}
```

**Nasıl çalışıyor?**

| Adım | Ne oluyor? |
|---|---|
| `Playlist myList(4);` | constructor: capacity = 4, count = 0, `new int[4]` |
| 3 şarkı okunur | `addSong` her seferinde `durations[count]`'a yazar, count'u 1 artırır → count = 3 |
| `addSong(200)` | count (3) < capacity (4) → eklenir, count = 4, **myList** geri döner |
| `.addSong(150)` | count (4) < capacity (4) **yanlış** → "Playlist is full!" mesajı |
| `display()` | 4 şarkı ve toplam (210 + 185 + 240 + 200 = 835) |
| `main` biter | destructor: `delete[]` ve mesaj |

**Önemli noktalar:**
- `addSong` **dolu olsa bile** `return *this;` yapıyor. Yapmasaydı zincirin devamı çalışamazdı.
- `display()` içinde `totalDuration()` çağrılıyor; aynı sınıfın fonksiyonu olduğu için başına nesne adı yazılmıyor.
- `display()` const olduğu için içinden sadece **const** fonksiyonlar çağrılabilir; `totalDuration()` da bu yüzden const.

---

## Çözüm 2 – Hero

```cpp
#include <iostream>
using namespace std;

const int MAX_HEALTH = 100;

class Hero {
    char *name;
    int health;
    int power;

public:
    Hero(const char *name, int health, int power) {
        this->health = health;
        this->power = power;

        int len = 0;
        while (name[len] != '\0')
            len++;

        this->name = new char[len + 1];
        for (int i = 0; i < len; i++)
            this->name[i] = name[i];
        this->name[len] = '\0';
    }

    ~Hero() {
        cout << name << " left the game." << endl;
        delete[] name;
    }

    Hero& takeDamage(int amount) {
        this->health -= amount;
        if (this->health < 0)
            this->health = 0;
        return *this;
    }

    Hero& heal(int amount) {
        this->health += amount;
        if (this->health > ::MAX_HEALTH) {
            cout << "Health cannot exceed " << ::MAX_HEALTH << "!" << endl;
            this->health = ::MAX_HEALTH;
        }
        return *this;
    }

    Hero& powerUp(int amount) {
        this->power += amount;
        return *this;
    }

    void display() const {
        cout << name << " | Health: " << health << " | Power: " << power << endl;
    }

    friend void compareHeroes(const Hero &h1, const Hero &h2);
};

void compareHeroes(const Hero &h1, const Hero &h2) {
    if (h1.power > h2.power)
        cout << h1.name << " is stronger." << endl;
    else if (h2.power > h1.power)
        cout << h2.name << " is stronger." << endl;
    else
        cout << "They are equally strong." << endl;
}

int main() {
    char name1[30], name2[30];
    int health1, power1, health2, power2;

    cout << "Enter first hero (name health power): ";
    cin >> name1 >> health1 >> power1;
    cout << "Enter second hero (name health power): ";
    cin >> name2 >> health2 >> power2;

    Hero h1(name1, health1, power1);
    Hero h2(name2, health2, power2);

    cout << endl << "--- Before Battle ---" << endl;
    h1.display();
    h2.display();

    int damage, healAmount, bonus;
    cout << endl << "Enter damage, heal amount and power bonus for " << name1 << ": ";
    cin >> damage >> healAmount >> bonus;

    h1.takeDamage(damage).heal(healAmount).powerUp(bonus);

    cout << endl << "--- After Battle ---" << endl;
    h1.display();
    h2.display();

    cout << endl;
    compareHeroes(h1, h2);
    cout << endl;

    return 0;
}
```

**Nasıl çalışıyor?**

| Adım | Arthas'ın health / power |
|---|---|
| Başlangıç | 80 / 45 |
| `takeDamage(50)` | 80 − 50 = **30** |
| `.heal(80)` | 30 + 80 = 110 → `::MAX_HEALTH`'ı geçti → mesaj, **100** |
| `.powerUp(10)` | güç 45 + 10 = **55** |

`compareHeroes`: Arthas 55, Jaina 50 → "Arthas is stronger."

`main` bitince: Jaina sonra doğdu → **önce** "Jaina left the game.", sonra "Arthas left the game."

**Önemli noktalar:**
- `compareHeroes` **friend** olduğu için `h1.power` ve `h1.name` gibi private üyelere erişebiliyor. Üye olmadığı için `this` yok; nesnelere **parametrelerle** ulaşıyor.
- Parametreler `const Hero &`: kopya yapılmıyor ve fonksiyon kahramanları değiştiremiyor.
- `main`'deki `name1` dizisi ile nesnenin içindeki `name` **farklı** yerler. Constructor ismi kendi ayırdığı yere kopyaladı; bu yüzden nesnenin kendi `delete[]`'i var.

---

## Çözüm 3 – Product

```cpp
#include <iostream>
#include <string>
using namespace std;

class Product {
    int code;
    string name;
    double price;
    int stock;

public:
    Product() : code(0), name(""), price(0), stock(0) {}

    Product(int code, string name, double price, int stock = 0) {
        this->code = code;
        this->name = name;
        this->price = price;
        this->stock = stock;
    }

    void read() {
        cout << "Enter code, name, price, stock: ";
        cin >> code >> name >> price >> stock;
    }

    double stockValue() const {
        return price * stock;
    }

    void display() const {
        cout << code << " " << name << " " << price << " TL (stock: " << stock << ")" << endl;
    }

    friend bool isCheaper(const Product &a, const Product &b);
};

bool isCheaper(const Product &a, const Product &b) {
    return a.price < b.price;
}

int main() {
    Product mine(100, "Pencil", 2.5);
    mine.display();

    int n;
    cout << "Enter number of products: ";
    cin >> n;

    Product *products = new Product[n];

    for (int i = 0; i < n; i++)
        products[i].read();

    int cheapest = 0;
    double total = 0;
    for (int i = 0; i < n; i++) {
        if (isCheaper(products[i], products[cheapest]))
            cheapest = i;
        total += products[i].stockValue();
    }

    cout << endl << "Cheapest product: ";
    products[cheapest].display();
    cout << "Total stock value: " << total << " TL" << endl;

    delete[] products;

    return 0;
}
```

**Nasıl çalışıyor?**

| Adım | Ne oluyor? |
|---|---|
| `Product mine(100, "Pencil", 2.5);` | 3 değer verildi → stock varsayılan **0** |
| `new Product[3]` | 3 ürün, her biri **default constructor** ile (hepsi 0) |
| `read()` döngüsü | ürünler kullanıcıdan dolduruluyor |
| en ucuzu bulma | başta `cheapest = 0` (Notebook, 45) → Pen 12.5 daha ucuz → `cheapest = 1` → Eraser 8 daha ucuz → `cheapest = 2` |
| toplam | 450 + 500 + 200 = **1150** |
| `delete[] products;` | dizi geri veriliyor |

**Önemli noktalar:**
- `isCheaper` sadece `return a.price < b.price;`. Karşılaştırmanın kendisi zaten `true` ya da `false`, ayrıca `if` yazmaya gerek yok.
- `products[i]` dizideki **nesnenin kendisi**, bu yüzden `.` kullanılıyor (`products[i].read()`). `products` ise adres.
- Varsayılan değer (`int stock = 0`) sadece **bildirimde** yazılır. Constructor sınıfın içinde yazıldığı için tek yer orası.
