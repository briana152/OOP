#include <iostream>
#include <memory>
#include <vector>


using namespace std;

class IoBase {
private:
public:
    // metoda citire
    virtual istream &read(istream &is) {
        return is;
    }
    // metoda scriere
    virtual ostream &write(ostream &os) {
        return os;
    }

    friend ostream &operator<<(ostream &os, IoBase &base) {
        return base.write(os);
    }

    friend istream &operator>>(istream &is, IoBase &base) {
        return base.read(is);
    }
};


class Proprietate : public IoBase{
protected:
    string adresa;
    double suprafata;
    double chirie;

public:
    istream &read(istream &is) override;

    ostream &write(ostream &os) override;

    Proprietate();

    Proprietate(const string &adresa, double suprafata, double chirie);

    double getSuprafata() const;

    double getChirie() const;

};
Proprietate::Proprietate() {
    adresa="";
    suprafata=0;
    chirie=0;
}
istream &Proprietate::read(istream &is) {
    IoBase::read(is);

    cout << "Adresa completa a locuitei:\n";
    is.get();
    getline(is,adresa);
    cout << "Suprafata locuibila(mp):\n";
    is >> suprafata;
    cout << "Chirie per mp:\n";
    is >> chirie;

    return is;
}

ostream &Proprietate::write(ostream &os) {
    IoBase::write(os);

    os << "Adresa locuintei:\n";
    os << adresa << '\n';
    os << "Suprafata locuibila:\n";
    os << suprafata << '\n';
    os << "Chiria per mp:\n";
    os << chirie << '\n';

    return os;
}

Proprietate::Proprietate(const string &adresa, double suprafata, double chirie) : adresa(adresa), suprafata(suprafata),
                                                                                  chirie(chirie) {}

double Proprietate::getSuprafata() const {
    return suprafata;
}

double Proprietate::getChirie() const {
    return chirie;
}

class Casa : public Proprietate{
private:
    int niveluri;
    double curte;

public:
    istream &read(istream &is) override;

    ostream &write(ostream &os) override;

    Casa();

    double getCurte() const;
};
Casa::Casa() : Proprietate() {
    niveluri=0;
    curte=0;
}
istream &Casa::read(istream &is) {
    Proprietate::read(is);

    cout << "Numar niveluri:\n";
    is >> niveluri;
    cout << "Suprafata curte:\n";
    is >> curte;

    return is;
}

ostream &Casa::write(ostream &os) {
    Proprietate::write(os);

    os << "Niveluri:\n";
    os << niveluri << '\n';
    os << "Suprafata curtii:\n";
    os << curte << '\n';

    return os;
}

double Casa::getCurte() const {
    return curte;
}

class Apartament : public Proprietate{
private:
    int etaj;
    int nrcamere;

public:
    istream &read(istream &is) override;

    ostream &write(ostream &os) override;

    Apartament();

};
Apartament::Apartament() : Proprietate() {
    etaj=0;
    nrcamere=0;
}
istream &Apartament::read(istream &is) {
    Proprietate::read(is);

    cout << "Etajul la care se afla:\n";
    is >> etaj;
    cout << "Numarul de camere:\n";
    is >> nrcamere;

    return is;
}

ostream &Apartament::write(ostream &os) {
    Proprietate::write(os);

    os << "Etaj:\n";
    os << etaj << '\n';
    os << "Camere:\n";
    os << nrcamere << '\n';

    return os;
}

class Contract : public IoBase{
protected:
    string numeClient;
    int lunaInceput;
    int lunaSfarsit;
    int anInceput;
    int anSfarsit;
    vector<shared_ptr<Proprietate> > proprietati;

public:
    istream &read(istream &is) override;

    ostream &write(ostream &os) override;

    Contract();

    virtual int calculeazaDiscount();
    virtual double calculeazaChirie();

    const vector<shared_ptr<Proprietate>> &getProprietati() const;

    void setProprietati(const vector<shared_ptr<Proprietate>> &proprietati);

};

istream &Contract::read(istream &is) {
   IoBase::read(is);

   cout << "Numele clientului:\n";
   is.get();
   getline(is,numeClient);
   cout << "Data la care a fost semnat contractul:\n";
   cout << "luna:\n";
   is >> lunaInceput;
   cout << "anul:\n";
   is >> anInceput;
   cout << "Data la care se sfarseste contractul:\n";
   cout << "luna:\n";
   is >> lunaSfarsit;
   cout << "anul:\n";
   is >> anSfarsit;

   return is;
}

ostream &Contract::write(ostream &os) {
    IoBase::write(os);

    os << "Numele clientului:\n";
    os << numeClient << '\n';
    os << "Data la care a fost semnat contractul:";
    os << lunaInceput << "." << anInceput << '\n';
    os << "Data la care se sfarseste contractul:";
    os << lunaSfarsit << "." << anSfarsit << '\n';
    os << "Proprietate:\n";
    for(const auto &i: proprietati){
        auto *casa=dynamic_cast<Casa*>(i.get());
        auto *apartament=dynamic_cast<Apartament*>(i.get());
        if(casa)
            os << *casa;
        else if(apartament)
            os << *apartament;
    }
    os << "\n";

    return os;
}

Contract::Contract() : proprietati() {}

int Contract::calculeazaDiscount() {
    int discount;
    if((anSfarsit - anInceput == 2 && lunaSfarsit >= lunaInceput) || anSfarsit - anInceput > 2 || (anInceput - anSfarsit == 1 && (lunaInceput == 1 && lunaSfarsit == 12)))
        discount = 0.1;
    else if((anSfarsit - anInceput == 1 && lunaSfarsit >= lunaInceput) || (anSfarsit - anInceput == 2 && lunaSfarsit < lunaInceput) || (anSfarsit - anSfarsit == 0 && (lunaInceput == 1 && lunaSfarsit == 12)))
        discount = 0.05;
    else
        discount = 0;
    return discount;
}

double Contract::calculeazaChirie() {
    double chirie;
    double discount;
    discount = calculeazaDiscount();
    for(const auto &i: proprietati){
        auto *casa=dynamic_cast<Casa*>(i.get());
        auto *apartament=dynamic_cast<Apartament*>(i.get());
        if(casa){
            chirie += casa->getChirie() * (casa->getSuprafata() + 0.2 * casa->getCurte()) * (1 - discount);;
        }else if(apartament){
            chirie += casa->getChirie() * casa->getSuprafata() * (1 - discount);
        }
    }
}

const vector<shared_ptr<Proprietate>> &Contract::getProprietati() const {
    return proprietati;
}

void Contract::setProprietati(const vector<shared_ptr<Proprietate>> &proprietati) {
    Contract::proprietati = proprietati;
}


class VanzareCumparare : public Contract{
private:

public:
    istream &read(istream &is) override;

    ostream &write(ostream &os) override;

    double calculeazaChirie() override;

    int calculeazaDiscount() override;


};

istream &VanzareCumparare::read(istream &is) {
    cout << "Numele clientului:\n";
    is.get();
    getline(is,numeClient);
    cout << "Data la care se va plati prima factura:\n";
    cout << "luna:\n";
    is >> lunaInceput;
    cout << "anul:\n";
    is >> anInceput;
    cout << "Data la care se va plati ultima factura:\n";
    cout << "luna:\n";
    is >> lunaSfarsit;
    cout << "anul:\n";
    is >> anSfarsit;

    return is;
}

ostream &VanzareCumparare::write(ostream &os) {
    os << "Numele clientului:\n";
    os << numeClient << '\n';
    os << "Data primei facturi:";
    os << lunaInceput << "." << anInceput << '\n';
    os << "Data ultimei facturi:";
    os << lunaSfarsit << "." << anSfarsit << '\n';
    os << "Proprietate:\n";
    for(const auto &i: proprietati){
        auto *casa=dynamic_cast<Casa*>(i.get());
        auto *apartament=dynamic_cast<Apartament*>(i.get());
        if(casa)
            os << *casa;
        else if(apartament)
            os << *apartament;
    }
    os << "\n";

    return os;
}

int VanzareCumparare::calculeazaDiscount() {
    int discount;
    int nr;
    if(anSfarsit == anInceput && lunaSfarsit == lunaInceput)
        discount = 0.1;
    else {
        nr = (12 * (anSfarsit - anInceput)) + (12 - lunaInceput + lunaSfarsit);
        if(nr <= 60 )
            discount = 0.07;
        else if( nr >60 && nr <= 120)
            discount = 0.05;
        else discount = 0;
    }
    return discount;
}

double VanzareCumparare::calculeazaChirie() {
    double chirie;
    double discount;
    discount = calculeazaDiscount();
    for (int i = 0; i < proprietati.size(); ++i) {
        chirie += 240 * proprietati[i]->getChirie() * (1 - discount);
    }

}

class BaseMenu {
public:
    virtual void listOptions() {}

    virtual int chooseOption(int first, int last) {}

    virtual void mainLoop() {}
};

class SimpleMenu : public BaseMenu {
private:
    vector<shared_ptr<Contract> > contracte;
    vector<shared_ptr<Proprietate> > proprietatiDinContract;
public:
    void listOptions()  override {
        cout << "1. Citire n proprietati sau a n contracte." << '\n';
        cout << "2. Afisare n proprietati sau n contracte grupate dupa tip." << '\n';
        cout << "3. Afisare n proprietati sau n contracte grupate dupa situatie." << '\n';
        cout << "4. Afisarea sumei totale incasate de firma. " << '\n';
        cout << "5. Gata" << '\n';
    }

    int chooseOption(int first, int last) override {
        int option = -1;
        while (option < first || option > last) {
            cout << '\n';
            cout << "Pentru a rula comanda, alegeti un numar intre "
                 << first << " si " << last << '\n';
            listOptions();
            cout << "Alegere: ";
            cin >> option;
        }
        return option;
    }

    void citire() {
        int n;
        int tip1;
        int tip2;
        cout << "Ce doriti sa adaugati? Introduceti 1 pentru proprietati si 2 pentru contracte.\n";
        cin >> tip1;
        if(tip1 == 1){
            cout << "Cate proprietati doriti sa adaugati?\n";
            cin >> n;
            for (int i = 0; i < n; ++i) {
                cout << "Introduceti 1 pentru casa si 2 pentru apartament.\n";
                cin >> tip2;
                if(tip2 == 1){
                    Casa p;
                    cin >> p;
                    proprietatiDinContract.push_back(make_shared<Casa>(p));
                }else if(tip2 == 2){
                    Apartament p;
                    cin >> p;
                    proprietatiDinContract.push_back(make_shared<Apartament>(p));
                }

            }
        }else if(tip1 == 2){
            cout << "Cate contracte doriti sa adugati?\n";
            cin >> n;
            int tip3;
            for (int i = 0; i < n; ++i) {
                cout << "Ce tip de contract semnati?";
                cout << "Introduceti 1 pentru contract de inchiriere si 2 pentru contract d vanzare-cumparare.\n";
                cin >> tip3;
                if(tip3 == 1){
                    Contract c;
                    cin >> c;
                    cout << "Ce proprietate se stipuleaza in contract?\n";
                    cout << "Toate proprietatile libere:\n";
                    for (int j = 1; j <= proprietatiDinContract.size(); j++) {
                        cout << j << "." << *proprietatiDinContract[j-1] << '\n';
                    }
                    int ord;
                    cout << "Care dintre cele de mai sus (introduceti nr de ord)\n";
                    cin >> ord;
                    std::vector<shared_ptr<Proprietate>> aux1 = c.getProprietati();
                    aux1.push_back(proprietatiDinContract[ord-1]);
                    c.setProprietati(aux1);
                    contracte.emplace_back(make_shared<Contract>(c));
                }else if(tip3 == 2){
                    VanzareCumparare c;
                    cin >> c;
                    cout << "Ce proprietate se stipuleaza in contract?\n";
                    cout << "Toate proprietatile libere:\n";
                    for (int j = 1; j <= proprietatiDinContract.size(); j++) {
                        cout << j << "." << *proprietatiDinContract[j-1] << '\n';
                    }
                    int ord;
                    cout << "Care dintre cele de mai sus (introduceti nr de ord)\n";
                    cin >> ord;
                    std::vector<shared_ptr<Proprietate>> aux2 = c.getProprietati();
                    aux2.push_back(proprietatiDinContract[ord-1]);
                    c.setProprietati(aux2);
                    contracte.emplace_back(make_shared<VanzareCumparare>(c));
                }

            }
        }
    }

    void afisareTip() {
        int tip;
        cout << "Ce doriti sa afisati? Introduceti 1 pentru a vedea toate proprietatile si 2 pentru a vedea toate contractele semnate\n";
        cin >> tip;
        if(tip == 1){
            cout << "Case:\n";
            for(const auto &i: proprietatiDinContract){
                shared_ptr<Casa> casa = dynamic_pointer_cast<Casa>(i);
                if(casa)
                    cout << *casa << '\n';
            }
            cout << "Apartamente:\n";
            for(auto i: proprietatiDinContract){
                shared_ptr<Apartament> apartament = dynamic_pointer_cast<Apartament>(i);
                if(apartament)
                    cout << *apartament << '\n';
            }

            }else if(tip == 2){
            cout << "Inch:\n";
            for(auto i:contracte){
                shared_ptr<Contract> inch = dynamic_pointer_cast<Contract>(i);
                if(inch)
                    cout << *inch << '\n';
            }
            cout << "Vanz:\n";
            for(auto i:contracte){
                shared_ptr<VanzareCumparare> vanz = dynamic_pointer_cast<VanzareCumparare>(i);
                if(vanz)
                    cout << *vanz << '\n';
            }
        }
        }


    void afisareSituatie() {
        cout << "coming soon";

    }

    void SumaTotala() {
        cout << "coming soon";

    }

    void mainLoop() override {
        while (true) {
            int option = chooseOption(1, 5);
            if (option == 1) {
                citire();
            } else if (option == 2) {
                afisareTip();
            } else if (option == 3) {
                afisareSituatie();
            } else if (option == 4) {
                SumaTotala();
            } else if (option == 5) {
                break;
            }
        }
        cout << '\n'
             << "---------------------------------"
             << '\n'
             << "Programul s-a incheiat cu success <3";
    }

};

int main() {

    SimpleMenu menu;
    menu.mainLoop();
    return 0;
}