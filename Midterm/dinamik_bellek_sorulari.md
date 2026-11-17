# CENG241 – Dinamik Bellek Soruları

Bu dosyadaki 6 sorunun hepsi **dinamik bellek** (`new` / `delete`) konusunda.
Özellikle sınavda en çok çıkan kalıp: **constructor'da `new`, destructor'da `delete`**
(Labwork 2, Labwork 4 ve dersteki `class B` örneği).

Bütün kodlar derlenip çalıştırıldı; cevaplardaki çıktılar gerçek çıktılardır.
Kod yazma sorularının cevapları bellek kontrol aracıyla da denendi: ayrılan belleğin hepsi geri veriliyor.

**Önce kendin çöz, sonra en alttaki CEVAPLAR bölümüne bak.**

| Soru | Tür | Konu |
|---|---|---|
| 1 | Çıktı bulma | constructor'da `new`, destructor'da `delete[]`, yok olma sırası |
| 2 | Çıktı bulma | `new` ile nesne, `->`, nesne dizisi |
| 3 | Çıktı bulma | sınır kontrolü (`setValue`) |
| 4 | Hata bulma | `delete` unutmak, `delete` / `delete[]`, `size`, `.` / `->` |
| 5 | Kod yazma | sayı dizisi tutan sınıf (Labwork 2 tarzı) |
| 6 | Kod yazma | `char*` isim tutan sınıf (Labwork 4 tarzı, daha kısa) |

---

# SORULAR

## Soru 1

What is the output of the following program?

```cpp
#include <iostream>
using namespace std;

class Box {
    int *p;
    int size;
public:
    Box(int n) {
        size = n;
        p = new int[size];
        for (int i = 0; i < size; i++)
            p[i] = (i + 1) * 10;
        cout << "new " << size << endl;
    }
    ~Box() {
        delete[] p;
        cout << "delete " << size << endl;
    }
    int sum() {
        int t = 0;
        for (int i = 0; i < size; i++)
            t += p[i];
        return t;
    }
};

int main() {
    Box a(2), b(3);
    cout << a.sum() << " " << b.sum() << endl;
    return 0;
}
```

---

## Soru 2

What is the output of the following program?

```cpp
#include <iostream>
using namespace std;

class Rational {
    int num, den;
public:
    Rational() { num = 1; den = 1; }
    Rational(int a, int b) : num(a), den(b) { }
    void set(int a, int b) { num = a; den = b; }
    void display() { cout << num << "/" << den << endl; }
};

int main() {
    Rational *p = new Rational;
    Rational *q = new Rational(2, 5);
    p->display();
    q->set(4, 7);
    q->display();

    Rational *arr = new Rational[3];
    arr[2].set(9, 2);
    arr[0].display();
    arr[2].display();

    delete p;
    delete q;
    delete[] arr;
    return 0;
}
```

---

## Soru 3

What is the output of the following program?

```cpp
#include <iostream>
using namespace std;

class List {
    int *data;
    int size;
public:
    List(int n) {
        size = n;
        data = new int[size];
        for (int i = 0; i < size; i++)
            data[i] = 0;
        cout << "List of " << size << " created" << endl;
    }
    ~List() {
        delete[] data;
        cout << "List of " << size << " deleted" << endl;
    }
    void setValue(int index, int value) {
        if (index >= 0 && index < size)
            data[index] = value;
        else
            cout << "Index " << index << " out of bounds!" << endl;
    }
    int getValue(int index) { return data[index]; }
};

int main() {
    List l(4);
    l.setValue(0, 5);
    l.setValue(3, 8);
    l.setValue(4, 9);
    l.setValue(-1, 2);
    cout << l.getValue(0) + l.getValue(3) << endl;
    return 0;
}
```

---

## Soru 4

Aşağıdaki 4 kod parçasının her birinde **bir yanlışlık** var. Ne yanlış ve nasıl düzeltilir?

**a)**

```cpp
class A {
    int *p;
public:
    A(int n) { p = new int[n]; }
};
```

**b)**

```cpp
class A {
    int *p;
public:
    A(int n) { p = new int[n]; }
    ~A() { delete p; }
};
```

**c)**

```cpp
class B {
    int *parr;
    int size;
public:
    B(int x) { parr = new int[x]; }
    ~B() { delete[] parr; }
    void setValue(int index, int value) {
        if (index >= 0 && index < size)
            parr[index] = value;
    }
};
```

**d)**

```cpp
int main() {
    Rational *q = new Rational(3, 4);
    q.display();
    delete q;
}
```

---

## Soru 5

Write a C++ program to store the grades of a classroom.
Define a **class Classroom** including the following:

**Data Members:** *grades* (a pointer to an integer array), *count* (number of students)

**Member Functions:**
- **Constructor Classroom(int):** Stores the number of students and **dynamically allocates** an array for the grades.
- **Destructor (~Classroom()):** Frees the allocated memory and prints a message.
- **setGrade(int, int):** Sets the grade at the given index. If the index is invalid, prints "Invalid index!".
- **average():** Returns the average of the grades.
- **highest():** Returns the highest grade.

In the main function, ask the number of students, create a Classroom object, read the grades,
and print the average and the highest grade.

**Türkçesi:** Sınıftaki öğrencilerin notlarını tutan program. Notlar için yer **constructor'da `new`** ile ayrılacak,
**destructor'da `delete[]`** ile geri verilecek. Ortalama ve en yüksek not bulunacak.

Sample Run:

```
Enter number of students: 4
Enter grade 1: 70
Enter grade 2: 85
Enter grade 3: 90
Enter grade 4: 61
Average: 76.5
Highest: 90
[INFO] Memory for 4 grades freed.
```

---

## Soru 6

Write a C++ program for an animal shelter.
Define a **class Pet** including the following:

**Data Members:** *age* (int), *name* (char*)

**Member Functions:**
- **Constructor Pet(int, const char*):** The parameter names must be the same as the data members, so use the **this pointer**. **Dynamically allocate** memory for the name and copy it.
- **Destructor (~Pet()):** Prints "<name> left the shelter." and frees the memory.
- **display():** Prints "<name> is <age> years old."

In the main function, read the names and ages of two pets, create two Pet objects, and display them.

**Türkçesi:** Labwork 4'ün **kısa hali**. İsim `char*`; constructor'da `new` ile yer ayrılıp kopyalanacak,
destructor'da geri verilecek. Parametre isimleri değişkenlerle aynı olduğu için `this->` gerekli.

Sample Run:

```
Enter first pet name and age: Pamuk 3
Enter second pet name and age: Karabas 5
Pamuk is 3 years old.
Karabas is 5 years old.
Karabas left the shelter.
Pamuk left the shelter.
```

---
---

# CEVAPLAR

## Cevap 1

**Output:**

```
new 2
new 3
30 60
delete 3
delete 2
```

**Çözüm:**

| Satır | Ne oluyor? | Ekran |
|---|---|---|
| `Box a(2)` | size = 2, `new int[2]`, dizi: 10, 20 | `new 2` |
| `b(3)` | size = 3, `new int[3]`, dizi: 10, 20, 30 | `new 3` |
| `a.sum()` | 10 + 20 | `30` |
| `b.sum()` | 10 + 20 + 30 | `60` |
| main biter | önce **b** yok olur (sonra doğdu) | `delete 3` |
| | sonra **a** yok olur | `delete 2` |

**Dizinin içi nasıl doldu?** `p[i] = (i + 1) * 10;`
- i = 0 → 1 × 10 = 10
- i = 1 → 2 × 10 = 20
- i = 2 → 3 × 10 = 30

**Tuzak:** Her nesnenin **kendi** dizisi var. a'nınki 2 kutulu, b'ninki 3 kutulu.

---

## Cevap 2

**Output:**

```
1/1
4/7
1/1
9/2
```

**Çözüm:**

| Satır | Ne oluyor? | Ekran |
|---|---|---|
| `new Rational` | parametresiz constructor → 1/1 | |
| `new Rational(2, 5)` | parametreli constructor → 2/5 | |
| `p->display();` | | `1/1` |
| `q->set(4, 7);` | q artık 4/7 | |
| `q->display();` | | `4/7` |
| `new Rational[3]` | 3 nesne, **hepsi** parametresiz constructor → 1/1 | |
| `arr[2].set(9, 2);` | sadece arr[2] değişti | |
| `arr[0].display();` | arr[0]'a dokunulmadı | `1/1` |
| `arr[2].display();` | | `9/2` |

**Tuzaklar:**
- `p` ve `q` **adres** tuttuğu için `->` kullanılır.
- `arr[2]` ise dizideki **nesnenin kendisi**, bu yüzden `.` kullanılır.
- `p` ve `q` tek nesne → `delete`; `arr` dizi → `delete[]`.

---

## Cevap 3

**Output:**

```
List of 4 created
Index 4 out of bounds!
Index -1 out of bounds!
13
List of 4 deleted
```

**Çözüm:**

| Satır | Ne oluyor? | Ekran |
|---|---|---|
| `List l(4);` | size = 4, `new int[4]`, hepsi 0 | `List of 4 created` |
| `setValue(0, 5)` | 0 geçerli (0–3 arası) → data[0] = 5 | |
| `setValue(3, 8)` | 3 geçerli → data[3] = 8 | |
| `setValue(4, 9)` | 4 geçersiz (4 < 4 yanlış) | `Index 4 out of bounds!` |
| `setValue(-1, 2)` | −1 geçersiz (−1 >= 0 yanlış) | `Index -1 out of bounds!` |
| `getValue(0) + getValue(3)` | 5 + 8 | `13` |
| main biter | destructor | `List of 4 deleted` |

**Tuzak:** 4 elemanlı dizide geçerli indeksler **0, 1, 2, 3**. 4 geçerli **değil**.

---

## Cevap 4

**a) Destructor yok.**
`new` ile alınan yer hiçbir zaman geri verilmiyor: **memory leak**. Düzeltme:

```cpp
~A() { delete[] p; }
```

**b) `delete` yerine `delete[]` olmalı.**
Yer `new int[n]` ile, yani **dizi** olarak alındı. Köşeli parantezle alınan, köşeli parantezle geri verilir:

```cpp
~A() { delete[] p; }
```

**c) `size` hiç doldurulmamış.**
Constructor'da `size`'a değer verilmediği için içinde rastgele bir sayı var; sınır kontrolü yanlış çalışır.
(Derste konuştuğumuz hata.) Düzeltme:

```cpp
B(int x) {
    size = x;
    parr = new int[x];
}
```

**d) Pointer ile nokta kullanılmış.**
`q` bir **adres** tutuyor; adres üzerinden fonksiyon çağırmak için `->` gerekir. Bu kod derlenmez. Düzeltme:

```cpp
q->display();
```

---

## Cevap 5

```cpp
#include <iostream>
using namespace std;

class Classroom {
    int *grades;
    int count;

public:
    Classroom(int n) {
        count = n;
        grades = new int[count];
    }

    ~Classroom() {
        delete[] grades;
        cout << "[INFO] Memory for " << count << " grades freed." << endl;
    }

    void setGrade(int index, int value) {
        if (index >= 0 && index < count)
            grades[index] = value;
        else
            cout << "Invalid index!" << endl;
    }

    double average() {
        double total = 0;
        for (int i = 0; i < count; i++)
            total += grades[i];
        return total / count;
    }

    int highest() {
        int max = grades[0];
        for (int i = 1; i < count; i++)
            if (grades[i] > max)
                max = grades[i];
        return max;
    }
};

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    Classroom c(n);

    for (int i = 0; i < n; i++) {
        int g;
        cout << "Enter grade " << i + 1 << ": ";
        cin >> g;
        c.setGrade(i, g);
    }

    cout << "Average: " << c.average() << endl;
    cout << "Highest: " << c.highest() << endl;

    return 0;
}
```

**Dikkat edilecekler:**
- `count = n;` satırı **unutulmamalı**; yoksa diğer fonksiyonlardaki döngüler kaç kere döneceğini bilemez.
- `new` constructor'da, `delete[]` destructor'da.
- Destructor'ı **çağırmıyoruz**; `main` bitince kendiliğinden çalışıyor. Bu yüzden mesaj en son satırda.
- `average()` içinde `total` **double**. int olsaydı bölme sonucu küsuratsız çıkardı (76.5 yerine 76).
- `highest()`: önce ilk notu en büyük kabul et, sonra diğerleriyle karşılaştır.
- Notlar dışarıda (`main`'de) okunuyor ve `setGrade` ile nesneye veriliyor, çünkü `grades` **private**.

**Hesap:** (70 + 85 + 90 + 61) / 4 = 306 / 4 = **76.5**; en yüksek **90**.

---

## Cevap 6

```cpp
#include <iostream>
using namespace std;

class Pet {
    int age;
    char *name;

public:
    Pet(int age, const char *name) {
        this->age = age;

        int len = 0;
        while (name[len] != '\0')
            len++;

        this->name = new char[len + 1];
        for (int i = 0; i < len; i++)
            this->name[i] = name[i];
        this->name[len] = '\0';
    }

    ~Pet() {
        cout << name << " left the shelter." << endl;
        delete[] name;
    }

    void display() {
        cout << name << " is " << age << " years old." << endl;
    }
};

int main() {
    char name1[30], name2[30];
    int age1, age2;

    cout << "Enter first pet name and age: ";
    cin >> name1 >> age1;
    cout << "Enter second pet name and age: ";
    cin >> name2 >> age2;

    Pet p1(age1, name1);
    Pet p2(age2, name2);

    p1.display();
    p2.display();

    return 0;
}
```

**Dikkat edilecekler:**
- Parametre isimleri değişkenlerle aynı (`age`, `name`), bu yüzden `this->age`, `this->name` **zorunlu**.
- İsim için yer: harf sayısı **+ 1** (`'\0'` için). "Pamuk" → 5 harf → `new char[6]`.
- Kopyalama döngüsünden sonra sonuna `'\0'` konuyor; yoksa `cout` ismin nerede bittiğini bilemez.
- Destructor'da önce ismi **yazdırıp** sonra `delete[]` yapıyoruz. Tersini yapsaydık silinmiş bir şeyi yazdırmaya çalışırdık.
- p2 sonra oluştuğu için **önce** p2 yok olur: önce "Karabas left", sonra "Pamuk left".
