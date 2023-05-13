#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

template <typename T>
class Stack
{
private:
    struct Node
    {
        T data;
        Node *next;
    };
    Node *top_;

public:
    int size;
    Stack() : top_(nullptr) { this->size = 0; }

    ~Stack()
    {
        while (!empty())
        {
            pop();
        }
    }

    void push(T val)
    {
        Node *node = new Node{val, top_};
        top_ = node;
        this->size += 1;
    }

    void pop()
    {
        if (empty())
        {
            throw std::out_of_range("Stack is empty");
        }

        Node *old_top = top_;
        top_ = top_->next;
        this->size -= 1;
        delete old_top;
    }

    T &top()
    {
        if (empty())
        {
            throw std::out_of_range("Stack is empty");
        }

        return top_->data;
    }

    T &second()
    {
        if (empty())
        {
            throw std::out_of_range("Stack is empty");
        }

        return top_->next->data;
    }
    T &third()
    {
        if (empty())
        {
            throw std::out_of_range("Stack is empty");
        }

        return top_->next->next->data;
    }

    const T &top() const
    {
        if (empty())
        {
            throw std::out_of_range("Stack is empty");
        }

        return top_->data;
    }

    bool empty() const
    {
        return top_ == nullptr;
    }
};

template <typename T>
class Queue
{
private:
    struct Node
    {
        T data;
        Node *next;
    };

    Node *front_;
    Node *back_;

public:
    int size;
    Queue() : front_(nullptr), back_(nullptr) { this->size = 0; }

    ~Queue()
    {
        while (!empty())
        {
            pop();
        }
    }

    void push(T val)
    {
        Node *node = new Node{val, nullptr};
        if (empty())
        {
            front_ = node;
        }
        else
        {
            back_->next = node;
        }
        back_ = node;
        this->size += 1;
    }

    void pop()
    {
        if (empty())
        {
            throw std::out_of_range("Queue is empty");
        }

        Node *old_front = front_;
        front_ = front_->next;
        delete old_front;
        this->size -= 1;
        if (empty())
        {
            back_ = nullptr;
        }
    }

    T &front()
    {
        if (empty())
        {
            throw std::out_of_range("Queue is empty");
        }

        return front_->data;
    }

    const T &front() const
    {
        if (empty())
        {
            throw std::out_of_range("Queue is empty");
        }

        return front_->data;
    }

    bool empty() const
    {
        return front_ == nullptr;
    }
};

struct Arac
{
    int aracNo;
    int arizaNo;
    string plaka;
    int tamirSuresi;
    double gelisSaati;
    double cikisSaati;
    bool isWaiting = false;

    Arac() {}
    Arac(int aracNo, int arizaNo, string plaka, int tamirSuresi, double gelisSaati)
    {
        this->aracNo = aracNo;
        this->arizaNo = arizaNo;
        this->plaka = plaka;
        this->tamirSuresi = tamirSuresi;
        this->gelisSaati = gelisSaati;
    }
};

void printArac(const Arac &arac)
{
    cout << "Arac No: " << arac.aracNo << endl;
    cout << "Ariza No: " << arac.arizaNo << endl;
    cout << "Plaka: " << arac.plaka << endl;
    cout << "Tamir Suresi: " << arac.tamirSuresi << endl;
    cout << "Gelis Saati: " << arac.gelisSaati << endl;
    cout << "Cikis Saati: " << arac.cikisSaati << endl;
}

bool same(double a, double b)
{
    double epsilon = 0.0001;

    return abs(a - b) < epsilon;
}

void incrTime(double &time)
{
    int tam = time;
    double noktali = time - tam;
    noktali += 0.01;
    if (same(noktali, 0.6))
    {
        tam++;
        noktali = 0.0;
    }
    time = tam + noktali;
}

Arac araclar[50];
int aracSayisi = 0;

void readAraclar()
{
    ifstream file;
    string line, value;

    // araclar = new Arac;

    file.open("arac.txt");
    while (file >> line)
    {
        stringstream ss(line);

        getline(ss, value, '-');
        araclar[aracSayisi].aracNo = atoi(value.c_str());

        getline(ss, value, '-');
        araclar[aracSayisi].arizaNo = atoi(value.c_str());

        getline(ss, value, '-');
        value.replace(value.find(":"), 1, ".");
        araclar[aracSayisi].gelisSaati = stod(value);

        getline(ss, value, '-');
        araclar[aracSayisi].tamirSuresi = atoi(value.c_str());

        getline(ss, value, '-');
        araclar[aracSayisi].plaka = atoi(value.c_str());

        aracSayisi++;
        // araclar = (Arac *)realloc(araclar, (aracSayisi + 1) * sizeof(Arac));
    }
    file.close();
}

class TamirAtolyesi
{
public:
    Stack<Arac> mekanikIstasyon;
    Stack<Arac> elektrikIstasyon;
    Stack<Arac> kaportaIstasyon;

    Queue<Arac> mekanikBekleme;
    Queue<Arac> elektrikBekleme;
    Queue<Arac> kaportaBekleme;

    TamirAtolyesi() {}

    // void SirayaAl(const string &dosyaAdi)
    // {
    //     ifstream dosya(dosyaAdi);

    //     if (!dosya.is_open())
    //     {
    //         cout << "Dosya acilamadi!" << endl;
    //         return;
    //     }

    //     int aracNo, arizaNo, tamirSuresi;
    //     string plaka;
    //     string saat;
    //     char delim; //"-"

    //     while (dosya >> aracNo >> delim >> arizaNo >> delim >> saat >> delim >> tamirSuresi >> delim >> plaka)
    //     {
    //         Arac *yeniArac = new Arac(plaka, tamirSuresi);
    //         yeniArac->arizaNo = arizaNo;
    //         yeniArac->plaka = plaka;
    //         yeniArac->tamirSuresi = tamirSuresi;

    //         switch (arizaNo)
    //         {
    //         case 1: // Kaporta
    //             if (kaportaBekleme.empty())
    //             {
    //                 kaportaBekleme.push(yeniArac);
    //             }
    //             else
    //             {
    //                 Arac *iter = kaportaBekleme.front();
    //                 while (iter->next != nullptr)
    //                 {
    //                     iter = iter->next;
    //                 }
    //                 iter->next = yeniArac;
    //             }
    //             break;
    //         case 2: // Elektrik
    //             if (elektrikBekleme.empty())
    //             {
    //                 elektrikBekleme.push(yeniArac);
    //             }
    //             else
    //             {
    //                 Arac *iter = elektrikBekleme.front();
    //                 while (iter->next != nullptr)
    //                 {
    //                     iter = iter->next;
    //                 }
    //                 iter->next = yeniArac;
    //             }
    //             break;
    //         case 3: // Mekanik
    //             if (mekanikBekleme.empty())
    //             {
    //                 mekanikBekleme.push(yeniArac);
    //             }
    //             else
    //             {
    //                 Arac *iter = mekanikBekleme.front();
    //                 while (iter->next != nullptr)
    //                 {
    //                     iter = iter->next;
    //                 }
    //                 iter->next = yeniArac;
    //             }
    //             break;
    //         default:
    //             cout << "Hatali ariza numarasi: " << arizaNo << endl;
    //             break;
    //         }
    //     }

    //     dosya.close();
    // }

    // void TamirEt()
    // {
    //     double saat = 08.00;

    //     while (saat < 20.00)
    //     {

    //         bool tamirBitti = false;

    //         if (!mekanikBekleme.empty())
    //         {
    //             tamirBitti = true;
    //             Arac *tamirEdilen = mekanikBekleme.front();
    //             mekanikBekleme.pop();
    //             cout << saat << " - " << tamirEdilen->plaka << " araci mekanik istasyonda tamir ediliyor." << endl;
    //             tamirEdilen->tamirSuresi--;
    //             if (tamirEdilen->tamirSuresi == 0)
    //             {
    //                 delete tamirEdilen;
    //             }
    //             else
    //             {
    //                 // tamirEdilen->next = nullptr;
    //                 if (mekanikIstasyon.empty())
    //                 {
    //                     mekanikIstasyon.push(tamirEdilen);
    //                 }
    //                 else
    //                 {
    //                     // tamirEdilen->next = mekanikIstasyon.top();
    //                     mekanikIstasyon.push(tamirEdilen);
    //                 }
    //             }
    //         }
    //         cout << endl;

    //         if (!elektrikBekleme.empty())
    //         {
    //             tamirBitti = true;
    //             Arac *tamirEdilen = elektrikBekleme.front();
    //             elektrikBekleme.pop();
    //             cout << saat << ":" << tamirEdilen->plaka << " araci elektrik istasyonda tamir ediliyor." << endl;
    //             tamirEdilen->tamirSuresi--;
    //             if (tamirEdilen->tamirSuresi == 0)
    //             {
    //                 delete tamirEdilen;
    //             }
    //             else
    //             {
    //                 // tamirEdilen->next = nullptr;
    //                 if (elektrikIstasyon.empty())
    //                 {
    //                     elektrikIstasyon.push(tamirEdilen);
    //                 }
    //                 else
    //                 {
    //                     // tamirEdilen->next = elektrikIstasyon.top();
    //                     elektrikIstasyon.push(tamirEdilen);
    //                 }
    //             }
    //         }
    //         cout << endl;

    //         if (!kaportaBekleme.empty())
    //         {
    //             tamirBitti = true;
    //             Arac *tamirEdilen = kaportaBekleme.front();
    //             kaportaBekleme.pop();
    //             cout << saat << ":" << tamirEdilen->plaka << " araci kaporta istasyonda tamir ediliyor." << endl;
    //             tamirEdilen->tamirSuresi--;
    //             if (tamirEdilen->tamirSuresi == 0)
    //             {
    //                 delete tamirEdilen;
    //             }
    //             else
    //             {
    //                 // tamirEdilen->next = nullptr;
    //                 if (kaportaIstasyon.empty())
    //                 {
    //                     kaportaIstasyon.push(tamirEdilen);
    //                 }
    //                 else
    //                 {
    //                     // tamirEdilen->next = kaportaIstasyon.top();
    //                     kaportaIstasyon.push(tamirEdilen);
    //                 }
    //             }
    //         }

    //         if (tamirBitti)
    //         {
    //             cout << "Tamirat islemi tamamlandi." << endl;
    //             break;
    //         }
    //     }
    //     incrTime(saat);
    // }
};

void check_for_arac(TamirAtolyesi &tamirAtolyesi, Arac araclar[], double saat)
{
    for (int i = 0; i < aracSayisi; i++)
    {
        if ((araclar[i].gelisSaati < saat || same(araclar[i].gelisSaati, saat)) && !araclar[i].isWaiting)
        {
            switch (araclar[i].arizaNo)
            {
            case 1:
                tamirAtolyesi.kaportaBekleme.push(araclar[i]);
                araclar[i].isWaiting = true;
                cout << "entered new arac into kaportaBekleme: " << saat << "-" << araclar[i].aracNo << endl;
                break;

            case 2:
                tamirAtolyesi.elektrikBekleme.push(araclar[i]);
                araclar[i].isWaiting = true;
                cout << "entered new arac into elektrikBekleme: " << saat << "-" << araclar[i].aracNo << endl;
                break;

            case 3:
                tamirAtolyesi.mekanikBekleme.push(araclar[i]);
                araclar[i].isWaiting = true;
                cout << "entered new arac into mekanikBekleme: " << saat << "-" << araclar[i].aracNo << endl;
                break;

            default:
                break;
            }
        }
    }
}

void chech_for_istasyon(Stack<Arac> istasyon, Queue<Arac> bekleme, string name)
{
    cout << "Checking: " << name << endl;
    if (istasyon.size < 3 && bekleme.size != 0)
    {
        Arac arac = bekleme.front();
        cout << "Arac No: " << arac.aracNo << " entring " << name << endl;
        istasyon.push(arac);
        bekleme.pop();
        Arac arac2 = bekleme.front();
        cout << "Arac No: " << arac2.aracNo << " entring " << name << endl;
    }
}

int main()
{
    readAraclar();
    double saat = 08.00;
    TamirAtolyesi tamirAtolyesi;

    while (saat < 20.00)
    {
        check_for_arac(tamirAtolyesi, araclar, saat);
        cout << tamirAtolyesi.elektrikBekleme.size << endl;
        cout << tamirAtolyesi.mekanikBekleme.size << endl;
        cout << tamirAtolyesi.kaportaBekleme.size << endl;
        chech_for_istasyon(tamirAtolyesi.elektrikIstasyon, tamirAtolyesi.elektrikBekleme, "Elektrik");
        chech_for_istasyon(tamirAtolyesi.mekanikIstasyon, tamirAtolyesi.mekanikBekleme, "Mekanik");
        chech_for_istasyon(tamirAtolyesi.kaportaIstasyon, tamirAtolyesi.kaportaBekleme, "Kaporta");

        incrTime(saat);
        cout << saat << endl;
    }

    // tamirAtolyesi.SirayaAl("arac.txt");
    // tamirAtolyesi.TamirEt();

    return 0;
}
