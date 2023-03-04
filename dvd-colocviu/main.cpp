#include <iostream>
#include <memory>
#include <vector>
#include <string>

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

class Produse : public IoBase{
protected:
    static int nr;
    int id;
    int cantitate;
    double pret;
public:
    Produse();

    istream &read(istream &is) override;

    ostream &write(ostream &os) override;
};
int Produse::nr = 0;
Produse::Produse() {
    ++nr;
    id=nr;
}
istream &Produse::read(istream &is) {
    IoBase::read(is);
    cout << "cantitate:\n";
    is >> cantitate;
    cout << "pret:\n";
    is >> pret;
    return is;
}

ostream &Produse::write(ostream &os) {
    IoBase::write(os);
    os << "cantitate: " << cantitate << "\n";
    os << "pret: " << pret << "\n";
    return os;

}

class Carti : public Produse{
private:
    string titlu;
    vector<string> autori;
public:
    istream &read(istream &is) override;

    ostream &write(ostream &os) override;

    Carti();
};
Carti::Carti() {}
istream &Carti::read(istream &is) {
    cout<<"carte\n";
    Produse::read(is);
    cout << "titlul:\n";
    is.get();
    getline(is,titlu);
    int var;
    cout << "Cati autori au lucrat la aceasta carte?\n";
    is >> var;
    for (int i = 0; i < var; ++i) {
        cout << "numele autorului:\n";
        string s;
        is.get();
        getline(is,s);
        autori.push_back(s);
    }
    return is;
}

ostream &Carti::write(ostream &os) {
    cout << "Carte, ID" << id << "\n";
    Produse::write(os);
    os << "titlu: " << titlu << "\n";
    os << "toti autorii:\n";
    for (int i = 0; i < autori.size(); ++i) {
        cout << i+1 << "." << autori[i] << "\n";
    }
    cout << "\n";
    return os;
}

class DVD : public Produse{
protected:
    int minute;
public:
    DVD();

    istream &read(istream &is) override;

    ostream &write(ostream &os) override;
};
DVD::DVD() {}

istream &DVD::read(istream &is) {
    Produse::read(is);
    cout << "cate minute dureaza dvd-ul?\n";
    is >> minute;
    return is;
}

ostream &DVD::write(ostream &os) {
    Produse::write(os);
    cout << "dureaza " << minute << " minute\n";
    return os;
}

class DVDmuzica : public DVD{
private:
    string album;
    vector<string> intrepreti;
public:

    DVDmuzica();

    istream &read(istream &is) override;

    ostream &write(ostream &os) override;
};
DVDmuzica::DVDmuzica() {}

istream &DVDmuzica::read(istream &is) {
    cout << "dvd muzica\n";
    DVD::read(is);
    cout << "titlul albumului:\n";
    is.get();
    getline(is, album);
    int var;
    cout << "cati interpreti sunt?\n";
    is >> var;
    for (int i = 0; i < var; ++i) {
        cout << "numele interpretului:\n";
        string s;
        is.get();
        getline(is,s);
        intrepreti.push_back(s);
    }
    return is;
}

ostream &DVDmuzica::write(ostream &os) {
    os << "DVD muzica, ID" << id << "\n";
    DVD::write(os);
    os << "titltul alblumului: " << album << "\n";
    os << "toti interpretii:\n";
    for (int i = 0; i < intrepreti.size(); ++i) {
        cout << i+1 << "." << intrepreti[i] << "\n";
    }
    return os;
}

class DVDfilm : public DVD{
private:
    string film;
    string gen;
public:
    DVDfilm();

    istream &read(istream &is) override;

    ostream &write(ostream &os) override;
};
DVDfilm::DVDfilm() {}

istream &DVDfilm::read(istream &is) {
    cout << "dvd film\n";
    DVD::read(is);
    cout << "numele filmului:\n";
    is.get();
    getline(is,film);
    cout << "genul filmului:\n";
    getline(is, gen);
    return is;
}

ostream &DVDfilm::write(ostream &os) {
    os << "DVD film, ID" << id << "\n";
    DVD::write(os);
    os << "numele filmului: " << film << "\n";
    os << "genul: " << gen << "\n";
    return os;
}

class ObiecteColectie : public Produse{
protected:
    string denumire;
public:
    ObiecteColectie();

    istream &read(istream &is) override;

    ostream &write(ostream &os) override;

};
ObiecteColectie::ObiecteColectie() {}

istream &ObiecteColectie::read(istream &is) {
    Produse::read(is);
    cout << "denumire:\n";
    is.get();
    getline(is,denumire);
    return is;
}

ostream &ObiecteColectie::write(ostream &os) {
    Produse::write(os);
    os << "denumire: " << denumire << "\n";
    return os;
}

class Figurina : public ObiecteColectie{
private:
    string categorie;
    string brand;
    string material;
public:
    Figurina();

    istream &read(istream &is) override;

    ostream &write(ostream &os) override;
};
Figurina::Figurina() {}

istream &Figurina::read(istream &is) {
    cout << "figurina\n";
    ObiecteColectie::read(is);
    cout << "categorie:\n";
    is.get();
    getline(is,categorie);
    cout << "brand:\n";
    getline(is,brand);
    cout << "material";
    getline(is,material);
    return is;
}

ostream &Figurina::write(ostream &os) {
    os << "Figurina, ID" << id << "\n";
    ObiecteColectie::write(os);
    os << "categorie: " << categorie << "\n";
    os << "brand: " << brand << "\n";
    os << "material: " << material << "\n";
    return os;
}

class Poster : public ObiecteColectie{
private:
    string format;
public:
    Poster();

private:
    istream &read(istream &is) override;

    ostream &write(ostream &os) override;
};
Poster::Poster() {}

istream &Poster::read(istream &is) {
    cout << "poster\n";
    ObiecteColectie::read(is);
    cout << "format(A3/A4 etc)\n";
    is.get();
    getline(is,format);
    return is;
}

ostream &Poster::write(ostream &os) {
    os << "Poster, ID" << id << "\n";
    ObiecteColectie::write(os);
    os << "format: " << format << "\n";
    return os;
}


class Aplicatie{
private:
    vector<shared_ptr<Produse> > produse;
    static Aplicatie* instance;
    Aplicatie()=default;
public:
    static Aplicatie* getInstance() {
        if (instance == nullptr) return new Aplicatie();
        return instance;
    }

    void citesteProduse();
    void afiseazaProduse();
    void editareProduse(int);
    void carteNume(string);
    void ordonarePret();
    void cantMax();

    ~Aplicatie(){}
};

Aplicatie* Aplicatie::instance = nullptr;

void Aplicatie::citesteProduse() {
    int nr;
    int tip1;
    cout << "Cate produse introduceti?\n";
    cin >> nr;
    for (int i = 0; i < nr; ++i) {
        cout << "Ce fel de produs este? 1 pentru carte, 2 pentru DVD cu muzica, 3 pentru DVD cu film, 4 pentru figurina si 5 pentru poster\n";
        cin >> tip1;
        if (tip1 == 1){
            Carti c;
            cin >> c;
            produse.push_back(make_shared<Carti>(c));
        }else if(tip1 == 2){
            DVDmuzica m;
            cin >> m;
            produse.push_back(make_shared<DVDmuzica>(m));
        }else if(tip1 == 3){
            DVDfilm f;
            cin >> f;
            produse.push_back(make_shared<DVDfilm>(f));
        } else if(tip1 == 4){
            Figurina j;
            cin >> j;
            produse.push_back(make_shared<Figurina>(j));
        } else if(tip1 == 5){
            Poster p;
            cin >> p;
            produse.push_back(make_shared<Poster>(p));
        }
    }

}

void Aplicatie::afiseazaProduse() {
    for(const auto &i: produse){
        shared_ptr<Carti> carti = dynamic_pointer_cast<Carti>(i);
        shared_ptr<DVDmuzica> dvDmuzica = dynamic_pointer_cast<DVDmuzica>(i);
        shared_ptr<DVDfilm> dvDfilm = dynamic_pointer_cast<DVDfilm>(i);
        shared_ptr<Figurina> figurina = dynamic_pointer_cast<Figurina>(i);
        shared_ptr<Poster> poster = dynamic_pointer_cast<Poster>(i);

        if(carti)
            cout << *carti << "\n";
        else if(dvDmuzica)
            cout << *dvDmuzica << "\n";
        else if(dvDfilm)
            cout << *dvDfilm << "\n";
        else if(figurina)
            cout << *figurina << "\n";
        else if(poster)
            cout << *poster << "\n";
    }
}

void Aplicatie::editareProduse(int nr) {
    cout << "coming soon\n";
}

void Aplicatie::carteNume(string nume) {
    cout << "coming soon\n";
}

void Aplicatie::ordonarePret() {
   cout<<"coming soon";
}

void Aplicatie::cantMax() {
    cout <<"coming soon\n";
}

int main()
{
    Aplicatie* A = A->getInstance();
    int var;
    while (true){
        cout << "1. citirea a n produse\n";
        cout << "2. afișarea produselor citite\n";
        cout << "3. editarea unui produs\n";
        cout << "4. ordonarea crescătoare a produselor după preț\n";
        cout << "5. căutarea unei cărți după titlu\n";
        cout << "6. afișarea produsului cu cea mai mare cantitate disponibilă.\n";
        cout << "7. Inchide meniu\n";
        cin >> var;
        if (var == 1) A->citesteProduse();
        else if (var == 2) A->afiseazaProduse();
        else if (var == 3) A->editareProduse(2);
        else if (var == 4) A->ordonarePret();
        else if(var == 5){
            int nr;
            cout << "Introduceti numele cartii pe care o cautati: ";
            string s;
            cin >> s;
            A->carteNume(s);
        }else if(var == 6) A->cantMax();
        else {
            cout << "Programul s-a incheiat cu succes!\n";
            cout << "----------------------------------------------------------\n";
            break;
        }
    }
    return 0;
}


