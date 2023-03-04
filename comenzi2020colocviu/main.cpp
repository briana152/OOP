#include <iostream>
#include <memory>
#include <vector>

using namespace std;


class Comanda{
protected:
    static int id;
    int ID;
    string numeClient;
    string adresaClient;
    double pretFinal;
    int timpLivrare;
    vector <pair<string,int>> produse;
public:

    friend istream &operator >> (istream &is, Comanda&ob);
    friend ostream &operator << (ostream &os, Comanda&ob);

    Comanda();
    virtual ~Comanda()=default;

    Comanda(const string &numeClient, const string &adresaClient, double pretFinal, int tipLivrare, const vector<pair<string, int>> &produse);

    int getId();
    int getPret();

    const string &getNumeClient() const;

};

int Comanda::id = 0;
Comanda::Comanda() : produse(){
    id ++;
    ID=id;
}

Comanda::Comanda(const string &numeClient, const string &adresaClient, double pretFinal, int timpLivrare,
                 const vector<pair<string, int>> &produse) : numeClient(numeClient), adresaClient(adresaClient),
                                                             pretFinal(pretFinal), timpLivrare(timpLivrare),
                                                             produse(produse) {}

int Comanda::getId() {
    return ID;
}

int Comanda::getPret() {
    return pretFinal;
}

const string &Comanda::getNumeClient() const {
    return numeClient;
}

istream &operator >>(istream &is, Comanda &ob) {
    cout << "Comanda\n";
    cout << "Numele clientului:\n";
    is.get();
    getline(is, ob.numeClient);
    cout << "Adresa clientului:\n";
    is.get();
    getline(is, ob.adresaClient);
    cout << "Timp de livrare:\n";
    cout << "minute ";
    is >> ob.timpLivrare;
    int nr;
    string produs;
    int cantitate;
    cout << "cate produse sunt in total in cos:";
    is >> nr;
    for (int i = 0; i < nr; ++i) {
        cout << "produs:\n";
        is.get();
        getline(is,produs);
        cout << "cantitate:";
        is >> cantitate;
        ob.produse.push_back(make_pair(produs,cantitate));
        i = i + cantitate - 1;

    }
    cout << "Pret final:\n";
    cout << "lei ";
    is >> ob.pretFinal;

    return is;
}
ostream &operator << (ostream &os, Comanda&ob) {

    os << "Comanda, ID" << ob.ID << "\n";
    os << "Numele clientului: " << ob.numeClient << "\n";
    os << "Adresa: " << ob.adresaClient << "\n";
    os << "Timp de livrare: " << ob.timpLivrare << "minute" << "\n";
    os << "Produse:\n";
    for (int i = 0; i < ob.produse.size(); ++i) {
        os << ob.produse[i].first << "x" << ob.produse[i].second << "\n";

    }
    os << "Pret: " << ob.pretFinal << "lei" << "\n";
    return os;
}

class ComandaMancare : public Comanda{
protected:
    string local;
public:

    friend istream &operator >> (istream &is, ComandaMancare&ob);
    friend ostream &operator << (ostream &os, ComandaMancare&ob);

    ComandaMancare();

};

ComandaMancare::ComandaMancare() {}

istream &operator >> (istream &is, ComandaMancare&ob) {
    cout <<"Comanda mancare\n";
    cout << "Numele clientului:\n";
    is.get();
    getline(is, ob.numeClient);
    cout << "Adresa clientului:\n";
    is.get();
    getline(is, ob.adresaClient);
    cout << "Local:\n";
    is.get();
    getline(is,ob.local);
    cout << "Timp de livrare:\n";
    cout << "minute ";
    is >> ob.timpLivrare;
    int nr;
    string produs;
    int cantitate;
    cout << "cate produse sunt in total in cos:";
    is >> nr;
    for (int i = 0; i < nr; ++i) {
        cout << "produs:\n";
        is.get();
        getline(is,produs);
        cout << "\n";
        cout << "cantitate:";
        is >> cantitate;
        ob.produse.push_back(make_pair(produs,cantitate));
        i = i + cantitate - 1;

    }
    cout << "Pret final:\n";
    cout << "lei ";
    is >> ob.pretFinal;

    return is;
}

ostream &operator << (ostream &os, ComandaMancare&ob) {

    os << "Comanda mancare, ID" << ob.ID << "\n";
    os << "Numele clientului: " << ob.numeClient << "\n";
    os << "Adresa: " << ob.adresaClient << "\n";
    os << "Local: " << ob.local << "\n";
    os << "Timp de livrare: " << ob.timpLivrare << "minute" << "\n";
    for (int i = 0; i < ob.produse.size(); ++i) {
        os << ob.produse[i].first << "x" << ob.produse[i].second << "\n";

    }
    os << "Pret: " << ob.pretFinal << "lei" << "\n";
    return os;

}

class ComandaFastFood : public ComandaMancare{
private:
    double discount;
public:

    friend istream &operator >> (istream &is, ComandaFastFood&ob);
    friend ostream &operator << (ostream &os, ComandaFastFood&ob);

    ComandaFastFood();
};

ComandaFastFood::ComandaFastFood() {}

istream &operator >> (istream &is, ComandaFastFood&ob){
    cout<<"Comanda fastfood\n";
    cout << "Numele clientului:\n";
    is.get();
    getline(is, ob.numeClient);
    cout << "Adresa clientului:\n";
    is.get();
    getline(is, ob.adresaClient);
    cout << "Local:\n";
    is.get();
    getline(is,ob.local);
    cout << "Timp de livrare:\n";
    cout << "minute ";
    is >> ob.timpLivrare;
    int nr;
    string produs;
    int cantitate;
    cout << "cate produse sunt in total in cos:";
    is >> nr;
    for (int i = 0; i < nr; ++i) {
        cout << "produs:\n";
        is.get();
        getline(is,produs);
        cout << "\n";
        cout << "cantitate:";
        is >> cantitate;
        ob.produse.push_back(make_pair(produs,cantitate));
        i = i + cantitate - 1;

    }
    cout << "Discount de:\n";
    cout << "%";
    is >> ob.discount;
    cout << "Pret final:\n";
    cout << "lei ";
    is >> ob.pretFinal;
}

ostream &operator << (ostream &os, ComandaFastFood&ob){
    os << "Comanda mancare, fastfood, ID" << ob.ID << "\n";
    os << "Numele clientului: " << ob.numeClient << "\n";
    os << "Adresa: " << ob.adresaClient << "\n";
    os << "Local: " << ob.local << "\n";
    os << "Timp de livrare: " << ob.timpLivrare << "minute" << "\n";
    for (int i = 0; i < ob.produse.size(); ++i) {
        os << ob.produse[i].first << "x" << ob.produse[i].second << "\n";

    }
    os << "Discount: " << ob.discount <<"%\n";
    os << "Pret: " << ob.pretFinal << "lei" << "\n";
    return os;
}

class ComandaRestaurant : public ComandaMancare{
private:
    bool tacamuri;
public:

    friend istream &operator >> (istream &is, ComandaRestaurant&ob);
    friend ostream &operator << (ostream &os, ComandaRestaurant&ob);

    ComandaRestaurant();
};

ComandaRestaurant::ComandaRestaurant() {}

istream &operator >> (istream &is, ComandaRestaurant&ob){
    cout << "Comanda restaurant\n";
    cout << "Numele clientului:\n";
    is.get();
    getline(is, ob.numeClient);
    cout << "Adresa clientului:\n";
    is.get();
    getline(is, ob.adresaClient);
    cout << "Local:\n";
    is.get();
    getline(is,ob.local);
    cout << "Timp de livrare:\n";
    cout << "minute ";
    is >> ob.timpLivrare;
    int nr;
    string produs;
    int cantitate;
    cout << "cate produse sunt in total in cos:";
    is >> nr;
    for (int i = 0; i < nr; ++i) {
        cout << "produs:\n";
        is.get();
        getline(is,produs);
        cout << "\n";
        cout << "cantitate:";
        is >> cantitate;
        ob.produse.push_back(make_pair(produs,cantitate));
        i = i + cantitate - 1;

    }
    cout << "Doriti tacamuri? 1 pentru DA si 0 pentru NU\n";
    is >> ob.tacamuri;
    cout << "Pret final:\n";
    cout << "lei ";
    is >> ob.pretFinal;
}
ostream  &operator << (ostream &os, ComandaRestaurant&ob){
    os << "Comanda mancare, restaurant, ID" << ob.ID << "\n";
    os << "Numele clientului: " << ob.numeClient << "\n";
    os << "Adresa: " << ob.adresaClient << "\n";
    os << "Local: " << ob.local << "\n";
    os << "Timp de livrare: " << ob.timpLivrare << "minute" << "\n";
    for (int i = 0; i < ob.produse.size(); ++i) {
        os << ob.produse[i].first << "x" << ob.produse[i].second << "\n";

    }
    os << "Tacamuri: ";
    if(ob.tacamuri==1)
        os << "DA\n";
    else
        os << "NU\n";
    os << "Pret: " << ob.pretFinal << "lei" << "\n";
    return os;
}

class ComandaMedicamente : public Comanda{
private:
    vector<pair<string,int>> medicamente;
public:

    friend istream &operator >> (istream &is, ComandaMedicamente&ob);
    friend ostream &operator << (ostream &os, ComandaMedicamente&ob);

    ComandaMedicamente();
};

ComandaMedicamente::ComandaMedicamente() {}

istream &operator >> (istream &is, ComandaMedicamente&ob){
    cout << "Comanda medicamente\n";
    cout << "Numele clientului:\n";
    is.get();
    getline(is, ob.numeClient);
    cout << "Adresa clientului:\n";
    is.get();
    getline(is, ob.adresaClient);
    cout << "Timp de livrare:\n";
    cout << "minute ";
    is >> ob.timpLivrare;
    int nr;
    string produs;
    int cantitate;
    cout << "cate produse sunt in total in cos:";
    is >> nr;
    int tip;
    for (int i = 0; i < nr; ++i) {
        cout << "produs:\n";
        is.get();
        getline(is,produs);
        cout << "\n";
        cout << "cantitate:";
        is >> cantitate;
        ob.produse.push_back(make_pair(produs,cantitate));
        i = i + cantitate - 1;
        cout << "Este antibiotic? 1 pentru DA si 0 petru NU\n";
        is >> tip;
        if(tip == 1)
            ob.medicamente.push_back(make_pair("antibiotic", i));
        else if (tip == 2)
            ob.medicamente.push_back(make_pair("nu este antibiotic", i));

    }
    cout << "Pret final:\n";
    cout << "lei ";
    is >> ob.pretFinal;

    return is;
}
ostream &operator << (ostream &os, ComandaMedicamente&ob){
    os << "Comanda medicamente, ID" << ob.ID << "\n";
    os << "Numele clientului: " << ob.numeClient << "\n";
    os << "Adresa: " << ob.adresaClient << "\n";
    os << "Timp de livrare: " << ob.timpLivrare << "minute" << "\n";
    for (int i = 0; i < ob.produse.size(); ++i) {
        os << ob.produse[i].first << "x" << ob.produse[i].second << ob.medicamente[i].first << "\n";

    }
    os << "Pret: " << ob.pretFinal << "lei" << "\n";
    return os;
}

class ComandaTigari : public Comanda{
private:
    bool clasice;
public:

    friend istream &operator >> (istream &is, ComandaTigari&ob);
    friend ostream &operator << (ostream &os, ComandaTigari&ob);

    ComandaTigari();
};

ComandaTigari::ComandaTigari() {}

istream &operator >> (istream &is, ComandaTigari&ob){
    cout << "Comanda tigari\n";
    cout << "Numele clientului:\n";
    is.get();
    getline(is, ob.numeClient);
    cout << "Adresa clientului:\n";
    is.get();
    getline(is, ob.adresaClient);
    cout << "Timp de livrare:\n";
    cout << "minute ";
    is >> ob.timpLivrare;
    int nr;
    string produs;
    int cantitate;
    cout << "cate produse sunt in total in cos:";
    is >> nr;
    for (int i = 0; i < nr; ++i) {
        cout << "produs:\n";
        is.get();
        getline(is,produs);
        cout << "\n";
        cout << "cantitate:";
        is >> cantitate;
        ob.produse.push_back(make_pair(produs,cantitate));
        i = i + cantitate - 1;

    }
    cout << "Tigari clasice sau rezerve? 1 pentru clasice si 0 pentru rezerve\n";
    is >> ob.clasice;
    cout << "Pret final:\n";
    cout << "lei ";
    is >> ob.pretFinal;

    return is;
}
ostream &operator << (ostream &os, ComandaTigari&ob){
    os << "Comanda tigari, ID" << ob.ID << "\n";
    os << "Numele clientului: " << ob.numeClient << "\n";
    os << "Adresa: " << ob.adresaClient << "\n";
    os << "Timp de livrare: " << ob.timpLivrare << "minute" << "\n";
    for (int i = 0; i < ob.produse.size(); ++i) {
        os << ob.produse[i].first << "x" << ob.produse[i].second << "\n";

    }
    os << "Tip: ";
    if(ob.clasice == 1)
        os << "tigari clasice\n";
    else if(ob.clasice == 0)
        os << "rezerve de tutun pentru dispozitive electronice\n";
    os << "Pret: " << ob.pretFinal << "lei" << "\n";
    return os;
}


class Aplicatie{
private:
    vector<shared_ptr<Comanda> > comenzi;
    static Aplicatie* instance;
    Aplicatie()=default;
public:
    static Aplicatie* getInstance() {
        if (instance == nullptr) return new Aplicatie();
        return instance;
    }

    void citesteComenzi();
    void adaugaComanda();
    void afiseazaComenzi();
    void stergeDupaID(int);
    void cautaDupaID(int);
    void cautaDupaNume(string);
    void Ordoneaza();
    void Gestioneaza();

    ~Aplicatie(){}
};

Aplicatie* Aplicatie::instance = nullptr;

void Aplicatie::citesteComenzi() {
    int nr;
    string tip1;
    string tip2;
    cout << "Cate comenzi cititi?\n";
    cin >> nr;
    for (int i = 0; i < nr; ++i) {
        cout << "Ce comandati? Mancare/medicamente/tigari\n";
        cin.get();
        getline(cin,tip1);
        if (tip1 == "mancare" || tip1 == "Mancare"){
            cout <<"Fast food sau restaurant?\n";
            getline(cin, tip2);
            if(tip2 == "Fast food" || tip2 == "fast food" || tip2 == "fastfood" || tip2 == "Fastfood" || tip2 == "FastFood"){
                ComandaFastFood c;
                cin >> c;
                comenzi.push_back(make_shared<ComandaFastFood>(c));
            }else if(tip2 == "Restaurant" || tip2 == "restaurant"){
                ComandaRestaurant c;
                cin >> c;
                comenzi.push_back(make_shared<ComandaRestaurant>(c));
            }
        }else if(tip1 == "medicamente" || tip1 == "Medicamente"){
            ComandaMedicamente c;
            cin >> c;
            comenzi.push_back(make_shared<ComandaMedicamente>(c));
        }else if(tip1 == "tigari" || tip1 == "Tigari"){
            ComandaTigari c;
            cin >> c;
            comenzi.push_back(make_shared<ComandaTigari>(c));
        }
    }

}

void Aplicatie::adaugaComanda() {
    int tip;
    cout << "Ce fel de comanda sa fie? 1 fastfood, 2 restaurant, 3 medicamente si 4 tigari\n";
    cin >> tip;
    if(tip == 1) {
        ComandaFastFood c;
        cin >> c;
        comenzi.push_back(make_shared<ComandaFastFood>(c));
    }
    else if(tip == 2) {
        ComandaRestaurant c;
        cin >> c;
        comenzi.push_back(make_shared<ComandaRestaurant>(c));
    }
    else if(tip == 3) {
        ComandaMedicamente c;
        cin >> c;
        comenzi.push_back(make_shared<ComandaMedicamente>(c));
    }
    else if(tip == 4) {
        ComandaTigari c;
        cin >> c;
        comenzi.push_back(make_shared<ComandaTigari>(c));
    }
}

void Aplicatie::afiseazaComenzi() {
    for(const auto &i: comenzi){
        shared_ptr<ComandaFastFood> fastfood = dynamic_pointer_cast<ComandaFastFood>(i);
        shared_ptr<ComandaRestaurant> restaurant = dynamic_pointer_cast<ComandaRestaurant>(i);
        shared_ptr<ComandaMedicamente> medicamente = dynamic_pointer_cast<ComandaMedicamente>(i);
        shared_ptr<ComandaTigari> tigari = dynamic_pointer_cast<ComandaTigari>(i);

        if(fastfood)
            cout << *fastfood << "\n";
        else if(restaurant)
            cout << *restaurant << "\n";
        else if(medicamente)
            cout << *medicamente << "\n";
        else if(tigari)
            cout << *tigari << "\n";
    }
}

void Aplicatie::stergeDupaID(int nr) {
    int ok=0;
    if(comenzi.size() == 0) cout <<"Nicio comanda nu a fost plasata\n";

    if(nr > comenzi.size())
        cout << "Comanda nu exista\n";
    else{
        for (int i = 0; i < comenzi.size(); ++i) {
            if(nr == comenzi[i]->getId()){
                comenzi.erase(comenzi.begin()+i);
                ok = 1;
                break;
            }
        }
        if(ok == 1) cout << "Ati sters cu succes o comanda!\n";
        else cout << "Nu a putut fi stearsa comanda din diverse motive.\n";
    }
}

void Aplicatie::cautaDupaID(int nr) {
    int ok = 0;
    if(comenzi.size() == 0) cout <<"Nicio comanda nu a fost plasata\n";

    if (nr > comenzi.size())
        cout << "Comanda nu exista\n";
    else {
        for (int i = 0; i < comenzi.size(); ++i) {
            if (nr == comenzi[i]->getId()) {
                cout <<  "Comanda cu id-ul " << nr << "  a fost gasita\n";
                ok = 1;
                break;
            }
        }
        if(ok == 0)
            cout << "Comanda nu exista\n";
    }
}

void Aplicatie::cautaDupaNume(string nume) {
    int ok = 0;
    if(comenzi.size() == 0) cout <<"Nicio comanda nu a fost plasata\n";

    for (int i = 0; i < comenzi.size(); ++i) {
        if (nume == comenzi[i]->getNumeClient()) {
            cout <<  "Comanda plasata de catre " << nume << "  a fost gasita\n";
            ok = 1;
            break;
        }
    }
    if(ok == 0)
        cout << "Comanda nu exista\n";}

void Aplicatie::Ordoneaza() {
    int opt;
    if(comenzi.size() == 0) cout <<"Nicio comanda nu a fost plasata\n";
    else{
        for (int i = 0; i < comenzi.size()-1; ++i) {
            for (int j = i+1; j < comenzi.size(); ++j) {
                if(comenzi[i]->getPret() < comenzi[j]->getPret())
                    swap(comenzi[i],comenzi[j]);
            }
        }
        for (int i = 0; i < comenzi.size(); ++i) {
            cout << comenzi[i]->getPret() << " ";
        }
        cout << "\n";
    }

}

void Aplicatie::Gestioneaza() {
    cout <<"coming soon\n";
}

int main()
{
    Aplicatie* A = A->getInstance();
    int var;
    while (true){
        cout << "1. Citire comenzi\n";
        cout << "2. Adaugare comanda\n";
        cout << "3. Afiseaza comenzile\n";
        cout << "4. Stergere comanda după ID\n";
        cout << "5. Cautare comanda după ID\n";
        cout << "6. Cautare comanda dupa numele clientului\n";
        cout << "7. Ordonare comenzi dupa pret in mod descrescator.\n";
        cout << "8. Gestionare comenzi\n";
        cout << "9. Inchide meniu\n";
        cin >> var;
        if (var == 1) A->citesteComenzi();
        else if (var == 2) A->adaugaComanda();
        else if (var == 3) A->afiseazaComenzi();
        else if (var == 4) {
            int nr;
            cout << "Introduceti nr comenzii pe care doriti sa o stergeti: ";
            cin >> nr;
            A->stergeDupaID(nr);
        } else if(var == 5){
            int nr;
            cout << "Introduceti nr comenzii pe care doriti sa o cautati: ";
            cin >> nr;
            A->cautaDupaID(nr);
        }else if(var == 6){
            string nume;
            cout << "Introduceti un nume: ";
            cin.get();
            getline(cin,nume);
            A->cautaDupaNume(nume);
        }else if(var == 7) A->Ordoneaza();
        else if(var == 8) A->Gestioneaza();
        else {
            cout << "Programul s-a incheiat cu succes!\n";
            cout << "----------------------------------------------------------\n";
            break;
        }
    }
    return 0;
}


