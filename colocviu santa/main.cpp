#include <iostream>
#include <memory>
#include <vector>
#include "util/IoBase.h"
#include "util/functions.h"

using namespace std;

class Jucarie : public IoBase {
protected:
    string denumire, tip;
    int volum;
    // ALt + INsert
    // Ctrl+O
public:

    Jucarie();
    virtual ~Jucarie();

    Jucarie(const string &denumire, const string &tip, int volum);

    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;
};
istream &Jucarie :: read(istream &is) {
    IoBase::read(is);
    cout << "denumire: \n";
    is >> denumire;
    cout << "tip: \n";
    is >> tip;
    cout << "volum: \n";
    is >> volum;
    return is;
    }

ostream &Jucarie :: write(ostream &os) const {
    IoBase::write(os);
    os << "Denumire: \n" << denumire << endl;
    os << "Tip: \n" << tip << endl;
    os << "Volum: \n" << volum << endl;
    return os;
    }

Jucarie::Jucarie() {}

Jucarie::~Jucarie() {
    volum=0;
    denumire.clear();
    tip.clear();
}

Jucarie::Jucarie(const string &denumire, const string &tip, int volum) : denumire(denumire), tip(tip), volum(volum) {}



class Clasica : public Jucarie {
private:
    string material, culoare;
public:
    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;
    Clasica()=default;



};

istream &Clasica::read(istream &is) {
    Jucarie::read(is);
    cout << "material: \n";
    is >> material;
    cout << "culoare: \n";
    is >> culoare;
    return is;
}

ostream &Clasica::write(ostream &os) const {
    Jucarie::write(os);
    os << "material: \n" << material << endl;
    os << "culoare: \n"<< culoare << endl;
    return os;
}



class  Educativa : public virtual Jucarie {
protected:
    string abilitateDezvoltata;
public:
    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;


    Educativa()=default;

};

istream &Educativa::read(istream &is) {
    Jucarie::read(is);
    cout <<"Abilitate dezvoltata: \n";
    is >> abilitateDezvoltata;
    return is;
}

ostream &Educativa::write(ostream &os) const {
     Jucarie::write(os);
     os << "Abilitate dezvoltata: \n"<< abilitateDezvoltata << endl;
     return os;
}


class Electronica : public virtual Jucarie {
protected:
    int numarBaterii;
public:
    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;
    Electronica()=default;

};

istream &Electronica::read(istream &is) {
    Jucarie::read(is);
    cout << "Numarul de baterii: \n";
    is >> numarBaterii;
    return is;
}

ostream &Electronica::write(ostream &os) const {
   Jucarie::write(os);
   os << "Numarul de baterii: \n"<< numarBaterii << endl;
    return os;
}



class Moderna : public Educativa, public Electronica {
    string brand, model;
    // TODO numarul de baterii sa fie 1
    //  -> parametrii default
    // transmitem 1 la numarul de baterii
public:

    Moderna()=default;

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

};

istream &Moderna::read(istream &is) {
    Jucarie::read(is);
    this->numarBaterii=1;
    this->abilitateDezvoltata="generala";
    return is;
}

ostream &Moderna::write(ostream &os) const {
    Jucarie::write(os);
    os<<"Numar baterii: " << numarBaterii << "\n";
    os<<"Abilitate dezvoltata: " << abilitateDezvoltata << "\n";
    return os;
}

// class Copil de baza
//    -->  Cuminte, Neastamparat

class Copil : public IoBase{

protected:
    static int id;
    int varsta;
    int numarFapteBune;
    int cod;
    string nume;
    string prenume;
    string adresa;
    vector<shared_ptr<Jucarie> > jucarii;
public:
    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

    Copil():jucarii(){
        ++id;
        cod=id;
        varsta=0;
        numarFapteBune=0;
        nume="";
        prenume="";
        adresa="";
    };

    virtual ~Copil();

};

istream &Copil::read(istream &is) {
    IoBase::read(is);
    cout << "Nume: \n";
    is.get();
    getline(is, nume);
    cout << "Prenume: \n";
    is.get();
    getline(is, prenume);
    cout << "Adresa: \n";
    is.get();
    getline(is,adresa);
    cout << "Varsta: \n";
    is >> varsta;
    cout << "Cate fapte bune are: \n";
    while(true){
        try{
            cout << "Cate fapte bune are: \n";
            is >> numarFapteBune;
            if(numarFapteBune<0)
                throw string ("Nu e bine!");
            else
                break;
        }
        catch (string s){
            cout<<s<<"\n";
        }
    }
    if(numarFapteBune==0)
        cout << "Nu primeste jucarii pt ca nu a facut fapte bune!\n";
    else
        cout << "Aveti de introdus "<< numarFapteBune << " jucarii\n";
    for(int i=0;i<numarFapteBune;i++){
        int tip;
        if(i==0)
            cout << "Prima jucarie:\n";
        else if(i==numarFapteBune-1)
            cout << "Ultima jucarie:\n";
        else
            cout << "A " << i << " a jucarie:\n";
        cout << "Ce fel de jucarie este \n";
        cout << "Introduceti 1 pt jucarie clasica, 2 pt educativa, 3 pt electornica si 4 pt moderna! \n";
        is >> tip;
        if (tip==1){
            Clasica j;
            is >> j;
            jucarii.emplace_back(make_shared<Clasica>(j));
        }
        else if(tip==2){
            Educativa j;
            is >> j;
            jucarii.emplace_back(make_shared<Educativa>(j));
        }
        else if(tip==3){
            Electronica j;
            is >> j;
            jucarii.emplace_back(make_shared<Electronica>(j));
        }
        else if(tip==4){
            Moderna j;
            is >> j;
            jucarii.emplace_back(make_shared<Moderna>(j));
        }
    }

}

ostream &Copil::write(ostream &os) const {
    IoBase::write(os);
    os << "Nume: " << nume << endl;
    os << "Prenume: " << prenume << endl;
    os << "Adresa: " << adresa << endl;
    os << "Varsta: " << varsta << endl;
    os << "A facut " << numarFapteBune <<" fapte bune si a primit jucariile:\n";
    for(const auto& i: jucarii){
        auto *jucarie_clasica=dynamic_cast<Clasica*>(i.get());
        auto *jucarie_educativa=dynamic_cast<Educativa*>(i.get());
        auto *jucarie_electronica=dynamic_cast<Electronica*>(i.get());
        auto *jucarie_moderna=dynamic_cast<Moderna*>(i.get());
        if(jucarie_clasica){
            cout<<*jucarie_clasica;
        }else if(jucarie_educativa){
            cout<<*jucarie_educativa;
        }else if(jucarie_electronica){
            cout<<*jucarie_electronica;
        }
    }
}

int Copil::id=0;




class CopilCuminte : public Copil{
private:
    int numarDulciuri;
};
class CopilNeastamparat : public Copil{

private:
    int numarCarbuni;
};
// TODO Pentru orice copil cuminte, numărul de fapte bune este cel puțin 10, în caz contrar, programul realizat trebuie să afişeze un mesaj corespunzător şi să îi permită lui Moş Crăciun să reintroducă valoarea.


// Meniu

// Ati lucrat meniuri din Lab 8?
// Mai exact CrudMenu?

// functie de citire a unui copil, ca shared_ptr

shared_ptr<Copil> citireCopil() {
    // citim tipul de copil
    cout << "Tipul Copil (1=cuminte, 2=neastamparat)";
    int tip;
    cin >> tip;

    // alocam shared_ptr ul
    shared_ptr<Copil> c;
    if (tip == 1) {
        c = make_shared<CopilCuminte>();
    } else if (tip == 2) {
        c = make_shared<CopilNeastamparat>();
    }

    // citim virtual pe shared_ptr<Copil> pe care l-am alocat
    cin >> *c;

}

class Meniu {
private:
    vector<shared_ptr<Copil> > copii;
public:
    // afisam toate optiunile
    void listeazaOptiuni() {
        cout << "1. Citire n copii cu cate m cadouri" << '\n';
        cout << "2. Citire n copii cu cate m cadouri" << '\n';
        cout << "7. Stop" << '\n';

    }

    // alegem o optiune

    int alegeOptiune() {
        int option;

        while (option < 1 && option > 7 ) {
            cout << "Alegeti optiunea intre 1 si 7!" << '\n';

            cout << "Option: ";
            cin >> option;
        }
        return option;
    }

    // un main loop
    void run() {
        // meniul interactiv
        while(true) {
            listeazaOptiuni();
            // alegem optiune
            int option = alegeOptiune();
            if (option == 1) {
                citireCopii();
            } else if (option == 2) {
                afisareCopii();
            } else if (option == 7) {
                break;
            }
        }
    }

    // pentru fiecare optiune cream o functie

    void citireCopii() {
        int n;
        cin >> n;
        // citirea a n copii

//        copii.clear();

        for (int i = 0; i < n; ++i) {
            copii.push_back(
                    citireCopil()
            );
        }
    }

    void afisareCopii() {
        // afisarea copiilor:
        cout << "Cei " << '\n' << " copii sunt:" << '\n';
        for (int i = 0; i < copii.size(); ++i) {
            cout << *copii[i] << '\n';
        }

    }



};

int main() {
    Moderna m;
    cin>>m;
    cout<<m;
    return 0;
}
