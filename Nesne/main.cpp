#include <iostream>
#include <string>
#include <vector>
using namespace std;

//oyunun grafik fonksiyonu
void grafikGoster(const string& dusmanIsim, int dusmanCan, int oyuncuCan) {
    cout << "-----------------------------------------\n-----------------------------------------" << endl;
    cout << "                                      " << endl;
    cout << "   <"<< dusmanIsim << ">              <SEN>              " << endl;
    cout << "     X                    O                " << endl;
    cout << "    /|\\                  /|\\             " << endl;
    cout << "    / \\                  / \\             " << endl;
    cout << "                                       " << endl;
    cout << dusmanIsim << "'in cani:       senin canin: " << endl;
    cout << "     " << dusmanCan << "                  " << oyuncuCan << endl;
    cout << "                              " << endl;
    cout << "-----------------------------------------\n-----------------------------------------" << endl;
}

// Temel Karakter sinifi
class Karakter {
protected:
    string isim;
    int can;
    int saldiriGucu;

public:
    Karakter(string i, int c, int sg) : isim(i), can(c), saldiriGucu(sg) {}

    string isimAl() { return isim; }
    int canAl() { return can; }

    void hasarAl(int hasar) {
        can -= hasar;
        if (can < 0) can = 0;
    }

    bool hayattaMi() { return can > 0; }

    virtual void saldir(Karakter& hedef) {
        hedef.hasarAl(saldiriGucu);
        cout << isim << ", " << hedef.isimAl() << "'e " << saldiriGucu << " hasar verdi." << endl;
    }
};

// Oyuncu sinifi (Karakter'den turetilmis)
class Oyuncu : public Karakter {
private:
    int iksirler;

public:
    Oyuncu(string i, int c, int sg) : Karakter(i, c, sg), iksirler(3) {}

    void iyilestir() {
        if (iksirler > 0) {
            can += 20;
            iksirler--;
            cout << isim << " 20 can iyilesti. Kalan iksir: " << iksirler << endl;
        } else {
            cout << "Hic iksir kalmadi!" << endl;
        }
    }

    void saldir(Karakter& hedef) override {
        Karakter::saldir(hedef);
    }
};

// Dusman sinifi (Karakter'den turetilmis)
class Dusman : public Karakter {
public:
    Dusman(string i, int c, int sg) : Karakter(i, c, sg) {}

    void tehditEt() {
        cout << isim << ": 'Beni yenemezsin!' dedi." << endl;
    }
};

// Oyun sinifi
class Oyun {
private:
    Oyuncu oyuncu;
    vector<Dusman> dusmanlar;

public:
    Oyun(string oyuncuIsim) : oyuncu(oyuncuIsim, 100, 15) {
        dusmanlar.push_back(Dusman("YILAN", 50, 10));
        dusmanlar.push_back(Dusman("DEV", 80, 12));
        dusmanlar.push_back(Dusman("Ejderha", 150, 20));
    }

    void basla() {
        cout << "Oyuna hos geldin, " << oyuncu.isimAl() << "!" << endl;

        for (size_t i = 0; i < dusmanlar.size(); i++) {
            Dusman& dusman = dusmanlar[i];
            cout << "Vahsi bir " << dusman.isimAl() << " ortaya cikti!" << endl;
            dusman.tehditEt();


            while (oyuncu.hayattaMi() && dusman.hayattaMi()) {
                
                grafikGoster(dusman.isimAl(), dusman.canAl(), oyuncu.canAl());

                cout << "Bir eylem sec: (1) Saldir (2) iyiles" << endl;
                string secim;
                while (true) {
                    cin >> secim;
                    if (secim == "1" || secim == "2") {
                        break;} 
					else {
                        cout << "Gecersiz secim! Lutfen 1 veya 2'yi secin." << endl;
                    }
                }

                if (secim == "1") {
                    oyuncu.saldir(dusman);
                } else if (secim == "2") {
                    oyuncu.iyilestir();
                }

                if (dusman.hayattaMi()) {
                    dusman.saldir(oyuncu);
                }
            }

            if (!oyuncu.hayattaMi()) {
                cout << dusman.isimAl() << " tarafindan yenildin! Oyun bitti." << endl;
                return;
            } else {
                cout << dusman.isimAl() << "'i yendin!" << endl;
            }
        }

        cout << "Tebrikler, " << oyuncu.isimAl() << "! Tum dusmanlari yendin!" << endl;
    }
};

int main() {
    string oyuncuIsim;
    cout << "Karakterinin adini gir: ";
    cin >> oyuncuIsim;

    Oyun oyun(oyuncuIsim);
    oyun.basla();

    return 0;
}
