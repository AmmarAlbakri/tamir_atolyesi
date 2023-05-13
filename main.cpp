#include <iostream>
#include <fstream>
#include <string>

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
    Stack() : top_(nullptr) {}

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
    }

    void pop()
    {
        if (empty())
        {
            throw std::out_of_range("Stack is empty");
        }

        Node *old_top = top_;
        top_ = top_->next;
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
    Queue() : front_(nullptr), back_(nullptr) {}

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
    int arizaNo;
    string plaka;
    int tamirSuresi;
    Arac *next;

    Arac(string plaka, int tamirSuresi)
    {
        this->plaka = plaka;
        this->tamirSuresi = tamirSuresi;
        next = NULL;
    }
};

class TamirAtolyesi
{
private:
    Stack<Arac> mekanikIstasyon;
    Stack<Arac> elektrikIstasyon;
    Stack<Arac> kaportaIstasyon;

    Queue<Arac> mekanikBekleme;
    Queue<Arac> elektrikBekleme;
    Queue<Arac> kaportaBekleme;

public:
    TamirAtolyesi(){}

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

    void SirayaAl(const string &dosyaAdi)
    {
        ifstream dosya(dosyaAdi);

        if (!dosya.is_open())
        {
            cout << "Dosya acilamadi!" << endl;
            return;
        }

        int aracNo, arizaNo, tamirSuresi;
        string plaka;
        string saat;
        char delim; //"-"

        while (dosya >> aracNo >> delim >> arizaNo >> delim >> saat >> delim >> tamirSuresi >> delim >> plaka)
        {
            Arac *yeniArac = new Arac(plaka, tamirSuresi);
            yeniArac->arizaNo = arizaNo;
            yeniArac->plaka = plaka;
            yeniArac->tamirSuresi = tamirSuresi;
            yeniArac->next = NULL;

            switch (arizaNo)
            {
            case 1: // Kaporta
                if (kaportaBekleme == NULL)
                {
                    kaportaBekleme = yeniArac;
                }
                else
                {
                    Arac *iter = kaportaBekleme;
                    while (iter->next != NULL)
                    {
                        iter = iter->next;
                    }
                    iter->next = yeniArac;
                }
                break;
            case 2: // Elektrik
                if (elektrikBekleme == NULL)
                {
                    elektrikBekleme = yeniArac;
                }
                else
                {
                    Arac *iter = elektrikBekleme;
                    while (iter->next != NULL)
                    {
                        iter = iter->next;
                    }
                    iter->next = yeniArac;
                }
                break;
            case 3: // Mekanik
                if (mekanikBekleme == NULL)
                {
                    mekanikBekleme = yeniArac;
                }
                else
                {
                    Arac *iter = mekanikBekleme;
                    while (iter->next != NULL)
                    {
                        iter = iter->next;
                    }
                    iter->next = yeniArac;
                }
                break;
            default:
                cout << "Hatali ariza numarasi: " << arizaNo << endl;
                break;
            }
        }

        dosya.close();
    }

    void TamirEt()
    {
        double saat = 8.0;
        bool infiniteTime = false;

        while (saat < 20.00)
        {
            while (mekanikBekleme != NULL || elektrikBekleme != NULL || kaportaBekleme != NULL)
            {
                bool tamirBitti = true;

                if (mekanikBekleme != NULL)
                {
                    tamirBitti = false;
                    Arac *tamirEdilen = mekanikBekleme;
                    mekanikBekleme = mekanikBekleme->next;
                    cout << saat << ":"
                         << " - " << tamirEdilen->plaka << " araci mekanik istasyonda tamir ediliyor." << endl
                         << tamirEdilen->tamirSuresi--;
                    tamirEdilen->tamirSuresi--;
                    if (tamirEdilen->tamirSuresi == 0)
                    {
                        delete tamirEdilen;
                    }
                    else
                    {
                        tamirEdilen->next = NULL;
                        if (mekanikBekleme == NULL)
                        {
                            mekanikBekleme = tamirEdilen;
                        }
                        else
                        {
                            Arac *iter = mekanikBekleme;
                            while (iter->next != NULL)
                            {
                                iter = iter->next;
                            }
                            iter->next = tamirEdilen;
                        }
                    }
                }
                cout << endl;
                if (elektrikBekleme != NULL)
                {
                    tamirBitti = false;
                    Arac *tamirEdilen = elektrikBekleme;
                    elektrikBekleme = elektrikBekleme->next;
                    cout << saat << ":" << tamirEdilen->plaka << " araci elektrik istasyonda tamir ediliyor." << endl;
                    tamirEdilen->tamirSuresi--;
                    if (tamirEdilen->tamirSuresi == 0)
                    {
                        delete tamirEdilen;
                    }
                    else
                    {
                        tamirEdilen->next = NULL;
                        if (elektrikBekleme == NULL)
                        {
                            elektrikBekleme = tamirEdilen;
                        }
                        else
                        {
                            Arac *iter = elektrikBekleme;
                            while (iter->next != NULL)
                            {
                                iter = iter->next;
                            }
                            iter->next = tamirEdilen;
                        }
                    }
                }
                cout << endl;
                if (kaportaBekleme != NULL)
                {
                    tamirBitti = false;
                    Arac *tamirEdilen = kaportaBekleme;
                    kaportaBekleme = kaportaBekleme->next;
                    cout << saat << ":" << tamirEdilen->plaka << " araci kaporta istasyonda tamir ediliyor." << endl;
                    tamirEdilen->tamirSuresi--;
                    if (tamirEdilen->tamirSuresi == 0)
                    {
                        delete tamirEdilen;
                    }
                    else
                    {
                        tamirEdilen->next = NULL;
                        if (kaportaBekleme == NULL)
                        {
                            kaportaBekleme = tamirEdilen;
                        }
                        else
                        {
                            Arac *iter = kaportaBekleme;
                            while (iter->next != NULL)
                            {
                                iter = iter->next;
                            }
                            iter->next = tamirEdilen;
                        }
                    }
                }

                if (tamirBitti)
                {
                    cout << "Tamirat islemi tamamlandi." << endl;
                    break;
                }
            }
            incrTime(saat);
        }
    }
};

int main()
{
    TamirAtolyesi tamirAtolyesi;
    tamirAtolyesi.SirayaAl("arac.txt");
    tamirAtolyesi.TamirEt();

    return 0;
}