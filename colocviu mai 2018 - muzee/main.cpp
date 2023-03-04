#include <iostream>
#include <vector>
#include <string>
#include "util/IoBase.h"
#include "util/functions.h"
using namespace std;
class Vizitator: public IoBase{
private:
    string nume;
    int varsta;
    string categorie;
public:
    Vizitator();
    ~Vizitator();

    Vizitator(const string &nume, int varsta, const string &categorie);

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

    const string &getCategorie() const;

    void setCategorie(const string &categorie);

};
Vizitator::Vizitator() {
    nume="";
    varsta=0;
    categorie="";
}

Vizitator::~Vizitator() {
    nume.clear();
    varsta=0;
    categorie.clear();
}


istream &Vizitator::read(istream &is) {
    IoBase::read(is);
    cout<<"Numele vizitatorului:\n";
    is.get();
    getline(is,nume);
    cout<<"Varsta vizitatorului:\n";
    is>>varsta;
    cout<<"Categoria din care face parte vizitatorul(copil/tanar/batran):\n";
    is>>categorie;
    return is;
}

ostream &Vizitator::write(ostream &os) const {
    IoBase::write(os);
    os<<"Nume: "<<nume<<"\n";
    os<<"Varsta: "<<varsta<<"\n";
    os<<"Categorie: "<<categorie<<"\n";
    return os;
}

Vizitator::Vizitator(const string &nume, int varsta, const string &categorie) : nume(nume), varsta(varsta),
                                                                                categorie(categorie) {}

const string &Vizitator::getCategorie() const {
    return categorie;
}

void Vizitator::setCategorie(const string &categorie) {
    Vizitator::categorie = categorie;
}

class Evenimente: public IoBase{
protected:

    string titlu;
    vector<Vizitator*>vizitatori;
public:
    Evenimente()=default;

    Evenimente(const string &titlu, const vector<Vizitator*> &vizitatori) : titlu(titlu), vizitatori(vizitatori) {}

    istream &read(istream &is) override {
        IoBase::read(is);
        cout<<"Titlul evenimentului este:\n";
        is.get();
        getline(is,titlu);
        int nr;
        while(true){
            try{
                cout<<"Numarul de vizitatori:\n";
                is>>nr;
                if(nr<0)
                    throw string ("Nu e bine!");
                else
                    break;
            }
            catch (string s){
                cout<<s<<"\n";
            }
        }
        cout<<"Vizitatori:\n";
        for(int i=0; i<nr; i++){
            Vizitator *x=new Vizitator;
            is>>*x;
            vizitatori.push_back(x);
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        os<<"Titlul: "<<titlu<<"\n";
        os<<"Vizitatori:\n";
        for(int i=0; i<vizitatori.size(); i++){
            os<<"Vizitator "<<i<<":\n";
            os<<*vizitatori[i]<<"\n";
        }
        return os;
    }
};

class Evenimente_gratuite:public Evenimente{
public:
    Evenimente_gratuite()=default;

    Evenimente_gratuite(const string &titlu, const vector<Vizitator *> &vizitatori) : Evenimente(titlu, vizitatori) {}

    istream &read(istream &is) override {
        Evenimente::read(is);
        return is;
    }

    ostream &write(ostream &os) const override {
        Evenimente::write(os);
        return os;
    }
};

class Evenimente_temporare:public Evenimente{
private:
    double pret_intrare;
    bool disponibil;
    int zi_final,luna_final, an_final;
public:
    Evenimente_temporare()=default;

    Evenimente_temporare(const string &titlu, const vector<Vizitator *> &vizitatori, double pretIntrare,
                         bool disponibil, int ziFinal, int lunaFinal, int anFinal);

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
};

istream &Evenimente_temporare::read(istream &is) {
    Evenimente::read(is);
    cout<<"Pret:\n";
    is>>pret_intrare;
    int ok;
    cout<<"Introduceti 1-daca evenimentul este disponibil si 0 daca nu este disponibil:\n";
    is>>ok;
    if(ok==1) {
        cout << "Data:\n";
        cout << "An:\n";
        bool bisect = 0;
        int an;
        int zile[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        is >> an;
        is.get();
        if ((an % 4 == 0 && an % 100 != 0) || an % 400 == 0)
            bisect = 1;
        this->an_final = an;
        cout << "Luna:\n";
        int luna;
        while (true) {
            try {
                is >> luna;
                is.get();
                if (luna < 1 || luna > 12)
                    throw string("Luna invalida!");
                else break;
            }
            catch (string s) {
                cout << s << '\n';
            }
        }
        this->luna_final = luna;
        cout << "Ziua\n";
        int zi;
        while (true) {
            try {
                is >> zi;
                is.get();
                if (zi < 1 || (luna == 2 && bisect == 1 && zi > 29) || zi > zile[luna])
                    throw string("Zi invalida!");
                else break;
            }
            catch (string s) {
                cout << s << '\n';
            }
        }
        this->zi_final = zi;
    }
    return is;
}

ostream &Evenimente_temporare::write(ostream &os) const {
    Evenimente::write(os);
    os<<"Pret: "<<pret_intrare<<"\n";
    os<<"Disponibilitate:\n";
    if(disponibil==1) {
        os << "Evenimentul este disponibil.\n";
        os << "Data: " << zi_final << "/" << luna_final << "/" << an_final << "\n";
    }
    else
        os<<"Evenimentul nu este disponibil.\n";
    return os;
}

Evenimente_temporare::Evenimente_temporare(const string &titlu, const vector<Vizitator *> &vizitatori,
                                           double pretIntrare, bool disponibil, int ziFinal, int lunaFinal, int anFinal)
        : Evenimente(titlu, vizitatori), pret_intrare(pretIntrare), disponibil(disponibil), zi_final(ziFinal),
          luna_final(lunaFinal), an_final(anFinal) {}

class Evenimente_speciale:public Evenimente{
private:
    vector<string> institutii;
public:
    Evenimente_speciale()=default;

    Evenimente_speciale(const string &titlu, const vector<Vizitator *> &vizitatori, const vector<string> &institutii);

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
};
istream &Evenimente_speciale::read(istream &is) {
    Evenimente::read(is);
    int nr;
    while(true){
        try{
            cout<<"Numarul de institutii:\n";
            is>>nr;
            if(nr<0)
                throw string ("Nu e bine!");
            else
                break;
        }
        catch (string s){
            cout<<s<<"\n";
        }
    }
    cout<<"Institutii\n";
    for(int i=0; i<nr; i++){
        string x;
        is>>x;
        institutii.push_back(x);
    }    return is;
}

ostream &Evenimente_speciale::write(ostream &os) const {
    Evenimente::write(os);
    os<<"Institutii:\n";
    for(int i=0; i<institutii.size(); i++){
        os<<"Intitutia "<<i<<":\n";
        os<<institutii[i]<<"\n";
    }
    return os;
}

Evenimente_speciale::Evenimente_speciale(const string &titlu, const vector<Vizitator *> &vizitatori,
                                         const vector<string> &institutii) : Evenimente(titlu, vizitatori),
                                                                             institutii(institutii) {}
class Muzeu: public IoBase{
private:
    string adresa;
    int interval_orar;
    vector<shared_ptr<Evenimente>> evenimente;
public:
    Muzeu()=default;

    Muzeu(const string &adresa, int intervalOrar, const vector<shared_ptr<Evenimente>> &evenimente);

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
};
istream &Muzeu::read(istream &is) {
    IoBase::read(is);
    cout<<"Adresa:\n";
    is.get();
    getline(is,adresa);
    cout<<"Intervalul orar de disponibilitate:\n";
    is>>interval_orar;
    int nr;
    while(true){
        try{
            cout<<"Numarul de evenimente:\n";
            is>>nr;
            if(nr<0)
                throw string ("Nu e bine!");
            else
                break;
        }
        catch (string s){
            cout<<s<<"\n";
        }
    }
    for(int i=0; i<nr; i++){
        int tip;
        cout<<"Introduceti tipul de eveniment: 1-gratuit, 2-temporar, 3-special.\n";
        is>>tip;
        if(tip<0||tip>3){
            cout<<"Tip invalid!\n";
            cout<<"Reintrodu tipul evenimentului!\n";
            is>>tip;
        }else{
            if(tip==1){
                Evenimente_gratuite p;
                is>>p;
                evenimente.emplace_back(make_shared<Evenimente_gratuite>(p));
            }else if(tip==2){
                Evenimente_temporare p;
                is>>p;
                evenimente.emplace_back(make_shared<Evenimente_temporare>(p));
            }else if(tip==3){
                Evenimente_speciale p;
                is>>p;
                evenimente.emplace_back(make_shared<Evenimente_speciale>(p));
            }
        }
    }
    return is;
}

ostream &Muzeu::write(ostream &os) const {
    IoBase::write(os);
    os<<"Adresa: "<<adresa<<"\n";
    os<<"Muzeul este deschis "<<interval_orar<<" ore.\n";
    for(const auto& i: evenimente){
        auto *asEvenimente_gratuite=dynamic_cast<Evenimente_gratuite*>(i.get());
        auto *asEvenimente_temporare=dynamic_cast<Evenimente_temporare*>(i.get());
        auto *asEvenimente_speciale=dynamic_cast<Evenimente_speciale*>(i.get());
        if(asEvenimente_gratuite){
            cout<<*asEvenimente_gratuite;
        }else if(asEvenimente_temporare){
            cout<<*asEvenimente_temporare;
        }else if(asEvenimente_speciale){
            cout<<*asEvenimente_speciale;
        }
    }
    return os;
}
Muzeu::Muzeu(const string &adresa, int intervalOrar, const vector<shared_ptr<Evenimente>> &evenimente) : adresa(adresa),
                                                                                                         interval_orar(
                                                                                                                 intervalOrar),
                                                                                                         evenimente(
                                                                                                                 evenimente) {}
class BaseMenu {
public:
    virtual void listOptions() {}

    virtual int chooseOption(int first, int last) {}

    virtual void mainLoop() {}
};

class SimpleMenu : public BaseMenu {
private:
    vector<Muzeu*> muzee;
public:
    void listOptions() override {
        cout << "1. Adauga muzeu." << '\n';
        cout << "2. Afisare muzee(include vizitatori si evenimente)." << '\n';
        cout << "3. Afisarea cerintelor in ghidaj." << '\n';
        cout << "4. Afisare muzeelor care nu au disponibilitate permanenta" << '\n';
        cout << "5. Iesire." << '\n';
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

    void option1();

    void option2();

    void option3();

    void option4();

    void mainLoop() override {
        while (true) {
            int option = chooseOption(1, 5);
            if (option == 1) {
                option1();
            } else if (option == 2) {
                option2();
            } else if (option == 3) {
                option3();
            }else if (option == 4) {
                option4();
            }else if (option == 5) {
                break;
            }
        }
        cout << '\n'
             << "---------------------------------"
             << '\n'
             << "Programul s-a incheiat cu success";
    }

};

void SimpleMenu::option1() {
    Muzeu *c=new Muzeu;
    cout<<"Muzeu:\n";
    cin>>*c;
    muzee.push_back(c);
}

void SimpleMenu::option2() {
    for(int i=0; i<muzee.size(); i++){
        cout<<"Muzeu "<<i<<":\n";
        cout<<*muzee[i]<<"\n";
    }
    cout<<"\n";
}

void SimpleMenu::option3() {
}

void SimpleMenu::option4() {
}

int main() {
    SimpleMenu menu;
    menu.mainLoop();
}