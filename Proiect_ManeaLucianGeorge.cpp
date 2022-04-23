#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

class ProdusAbstract
{
public:
  virtual ~ProdusAbstract(){};

  virtual void salvareInCSV(ofstream &outputFile) = 0;
};

enum TipProdus
{
  basic,
  electrocasnic,
  vestimentar
};

class Produs : public ProdusAbstract
{
private:
  static int contorId;
  int id;
  string nume;
  string descriere;
  int pret;

protected:
  TipProdus tip;

public:
  Produs() : id(contorId)
  {
    this->tip = basic;
    this->nume = "Nume";
    this->descriere = "Descriere";
    this->pret = 0;
    contorId++;
  }

  Produs(string nume, string descriere, int pret) : id(contorId)
  {
    this->tip = basic;
    this->nume = nume;
    this->descriere = descriere;
    this->pret = pret;
    contorId++;
  }

  ~Produs() {}

  int getId()
  {
    return this->id;
  }

  void setNume(string nume)
  {
    this->nume = nume;
  }

  string getNume()
  {
    return this->nume;
  }

  void setDescriere(string descriere)
  {
    this->descriere = descriere;
  }

  int getPret()
  {
    return this->pret;
  }

  void setPret(int pret)
  {
    this->pret = pret;
  }

  string getDescriere()
  {
    return this->descriere;
  }

  void operator==(Produs &p)
  {
    if (this->id == p.id)
    {
      cout << "Produsele '" << this->getNume() << "' si '" << p.getNume() << "' sunt identice." << endl;
    }
    else
    {
      cout << "Produsele '" << this->getNume() << "' si '" << p.getNume() << "' nu sunt identice." << endl;
    }
  }

  void operator<(Produs &p)
  {
    if (this->pret == p.pret)
    {
      cout << "Produsele au acelasi pret" << endl;
    }
    if (this->pret > p.pret)
    {
      cout << "Produsul " << this->nume << " este mai scump decat produsul " << p.nume << endl;
    }
    else
    {
      cout << "Produsul " << p.nume << " este mai scump decat produsul " << this->nume << endl;
    }
  }

  friend istream &operator>>(istream &input, Produs &p)
  {
    cout << "Numele produsului: ";
    getline(input >> ws, p.nume);
    cout << "Descrierea produsului: ";
    getline(input >> ws, p.descriere);
    cout << "Pretul produsului: ";
    input >> p.pret;

    return input;
  }

  friend ofstream &operator<<(ofstream &o, Produs &p)
  {
    o << "------------------" << endl;
    o << "Produsul: " << p.id << endl;
    o << "Nume: " << p.nume << endl;
    o << "Descriere: " << p.descriere << endl;
    o << "Pret: " << p.pret << endl;

    return o;
  }

  void salvareInCSV(ofstream &outputFile)
  {
    outputFile << this->tip << ',';
    outputFile << this->id << ',';
    outputFile << this->nume << ',';
    outputFile << this->descriere << ',';
    outputFile << this->pret << endl;
  }
};
int Produs::contorId = 0;

class ProdusElectrocasnic : public Produs
{
private:
  int luniGarantie;
  string eficientaEnergetica;

public:
  ProdusElectrocasnic() : Produs()
  {
    this->tip = electrocasnic;
    this->luniGarantie = 0;
    this->eficientaEnergetica = "X";
  }

  ProdusElectrocasnic(string nume, string descriere, int pret, int luniGarantie, string eficienta) : Produs(nume, descriere, pret)
  {
    this->tip = electrocasnic;
    this->luniGarantie = luniGarantie;
    this->setEficientaEnergetica(eficienta);
  }

  ~ProdusElectrocasnic(){};

  void setLuniGarantie(int luniGarantie)
  {
    if (luniGarantie >= 0 && luniGarantie <= 36)
    {
      this->luniGarantie = luniGarantie;
    }
    else
    {
      cout << "Produsul '" << this->getNume() << "' nu poate avea mai puțin de 1 lună garanție sau mai mult de 36 de luni." << endl;
    }
  }

  int getLuniGarantie()
  {
    return this->luniGarantie;
  }

  void setEficientaEnergetica(string eficienta)
  {
    if (regex_match(eficienta, regex("[a-gA-G]")) || regex_match(eficienta, regex("(a|A)(\\+|\\+\\+)$")))
    {
      this->eficientaEnergetica = eficienta;
    }
    else
    {
      cout << "Eficienta pentru produsul '" << this->getNume() << "' este invalida. Aceasta trebuie sa fie intre G-A++." << endl;
    }
  }

  string getEficientaEnergetica()
  {
    return this->eficientaEnergetica;
  }

  friend istream &operator>>(istream &input, ProdusElectrocasnic &p)
  {
    input >> (Produs &)p;
    cout << "Luni garantie: ";
    input >> p.luniGarantie;
    cout << "Grad de eficienta: ";
    input >> p.eficientaEnergetica;

    return input;
  }

  friend ofstream &operator<<(ofstream &o, ProdusElectrocasnic &p)
  {
    o << (Produs &)p;
    o << "Luni garantie: " << p.luniGarantie << endl;
    o << "Eficienta energetica: " << p.eficientaEnergetica << endl;
    o << "------------------" << endl;

    return o;
  }

  void salvareInCSV(ofstream &outputFile)
  {
    outputFile << this->tip << ',';
    outputFile << this->getId() << ',';
    outputFile << this->getNume() << ',';
    outputFile << this->getDescriere() << ',';
    outputFile << this->getPret() << ',';
    outputFile << this->luniGarantie << ',';
    outputFile << this->eficientaEnergetica << endl;
  }
};

enum Sex
{
  masculin,
  feminin,
  universal
};

string SexStrings[] = {
    "masculin",
    "feminin",
    "universal"};

class ProdusVestimentar : public Produs
{
private:
  Sex sex;
  string materialPrincipal;

public:
  ProdusVestimentar() : Produs()
  {
    this->tip = vestimentar;
    this->sex = universal;
    this->materialPrincipal = "Material";
  }

  ProdusVestimentar(string nume, string descriere, int pret, Sex sex, string materialPrincipal) : Produs(nume, descriere, pret)
  {
    this->tip = vestimentar;
    this->sex = sex;
    this->materialPrincipal = materialPrincipal;
  }

  ~ProdusVestimentar() {}

  Sex getSex()
  {
    return this->sex;
  }

  void setSex(Sex &s)
  {
    this->sex = s;
  }

  string getMaterialPrincipal()
  {
    return this->materialPrincipal;
  }

  void setMaterialPrincipal(string materialPrincipal)
  {
    this->materialPrincipal = materialPrincipal;
  }

  friend istream &operator>>(istream &input, ProdusVestimentar &p)
  {
    input >> (Produs &)p;
    cout << "Produsul este pentru: " << endl;
    cout << "1. Masculin" << endl
         << "2. Feminin" << endl
         << "3. Universal" << endl;
    int aux;
    cin >> aux;
    switch (aux)
    {
    case 1:
      p.sex = masculin;
      break;
    case 2:
      p.sex = feminin;
      break;
    case 3:
      p.sex = universal;
      break;
    default:
      p.sex = universal;
    }
    cout << "Materialul principal al produsului: ";
    getline(input >> ws, p.materialPrincipal);

    return input;
  }

  friend ofstream &operator<<(ofstream &o, ProdusVestimentar &p)
  {
    o << (Produs &)p;
    o << "Sex: " << SexStrings[p.sex] << endl;
    o << "Material principal: " << p.materialPrincipal << endl;
    o << "------------------" << endl;

    return o;
  }

  void salvareInCSV(ofstream &outputFile)
  {
    outputFile << this->tip << ',';
    outputFile << this->getId() << ',';
    outputFile << this->getNume() << ',';
    outputFile << this->getDescriere() << ',';
    outputFile << this->getPret() << ',';
    outputFile << this->sex << ',';
    outputFile << this->materialPrincipal << endl;
  }
};

enum StatusComanda
{
  neplasata,
  in_procesare,
  livrata
};

string StatusComandaStrings[] = {
    "neplasata",
    "in procesare",
    "livrata"};

class Comanda
{
private:
  static int contorId;
  int id;
  int nrProduse;
  int pretTotal = 0;
  vector<Produs> produse;
  StatusComanda status;

protected:
  void notificaInregistrarea()
  {
    cout << "S-a inregistrat comanda cu ID-ul " << this->id << "." << endl;
  }

public:
  Comanda() : id(contorId)
  {
    this->notificaInregistrarea();
    this->status = neplasata;
    contorId++;
  }

  Comanda(int nrProduse, Produs *produse) : id(contorId)
  {
    this->notificaInregistrarea();
    this->nrProduse = nrProduse;
    for (int i = 0; i < nrProduse; i++)
    {
      this->produse[i] = produse[i];
      this->pretTotal += produse[i].getPret();
    }
    this->status = neplasata;
    contorId++;
  }

  ~Comanda(){};

  int getId()
  {
    return this->id;
  }

  void getNumeProduse()
  {
    cout << "Produsele pentru comanda cu ID-ul " << this->id << " sunt urmatoarele: ";
    for (int i = 0; i < produse.size(); i++)
    {
      if (i == produse.size() - 1)
      {
        cout << produse[i].getNume();
      }
      else
      {
        cout << produse[i].getNume() << ", ";
      }
    }
    cout << endl;
  }

  int getPretComanda()
  {
    return this->pretTotal;
  }

  void adaugaProdus(Produs &p)
  {
    this->produse.push_back(p);
    cout << "Produsul " << p.getNume() << " a fost adaugat la comanda cu ID-ul " << this->id << "." << endl;
    this->pretTotal += p.getPret();
  }

  vector<Produs> getProduse()
  {
    return this->produse;
  }

  void setStatusComanda(StatusComanda status)
  {
    this->status = status;
  }

  friend ofstream &operator<<(ofstream &o, Comanda &c)
  {
    o << "------------------" << endl;
    o << "Comanda cu ID-ul " << c.id << endl;
    o << "Status: " << StatusComandaStrings[c.status] << endl;
    o << "Au fost comandate urmatoarele produse: " << endl;
    for (int i = 0; i < c.getProduse().size(); i++)
    {
      o << i + 1 << ". " << c.getProduse()[i].getNume() << " - "
        << c.getProduse()[i].getDescriere() << " - "
        << c.getProduse()[i].getPret() << " RON" << endl;
    }
    o << "Pret total: " << c.getPretComanda() << " RON" << endl;
    o << "------------------" << endl
      << endl;

    return o;
  }

  void salvareInCSV(ofstream &o)
  {
    o << this->id << ",";
    o << this->status << ",";
    o << this->pretTotal << endl;
  }

  void citesteDinCSV(ifstream &inputFile)
  {
    while (inputFile.good())
    {
      string line;
      getline(inputFile, line, ',');
      cout << line << endl;
    }
  }
};
int Comanda::contorId = 0;

void creareProdus(vector<Produs> &v)
{
  int tipProdus;
  int salvare;

  cout << "Ce tip de produs doriti sa creati?" << endl;
  cout << "1. Produs" << endl
       << "2. Produs electrocasnic" << endl
       << "3. Produs vestimentar" << endl;
  cin >> tipProdus;

  switch (tipProdus)
  {
  case 1:
  {
    Produs p;
    cin >> p;
    v.push_back(p);
    ofstream file("produse.txt", ios::app);
    file << p;
    ofstream fileCSV("produse.csv", ios::app);
    p.salvareInCSV(fileCSV);
  }
  break;

  case 2:
  {
    ProdusElectrocasnic p;
    cin >> p;
    v.push_back(p);
    ofstream file("produse.txt", ios::app);
    file << p;
    ofstream fileCSV("produse.csv", ios::app);
    p.salvareInCSV(fileCSV);
  }
  break;

  case 3:
  {
    ProdusVestimentar p;
    cin >> p;
    v.push_back(p);
    ofstream file("produse.txt", ios::app);
    file << p;
    ofstream fileCSV("produse.csv", ios::app);
    p.salvareInCSV(fileCSV);
  }
  break;

  default:
  {
    cout << "Tipul produsului este invalid." << endl;
  }
  break;
  }
}

void cumparareProdus(vector<Produs> &v, Comanda &c)
{
  int produsAles;
  int continuare;

  cout << "Alegeti ce produs doriti sa comandati:" << endl;

  for (int i = 0; i < v.size(); i++)
  {
    cout << i + 1 << ". " << v[i].getNume() << endl;
  }

  cin >> produsAles;

  c.adaugaProdus(v[produsAles - 1]);

  cout << "Doriti sa mai adaugati produse?" << endl;
  cout << "1. Da" << endl
       << "2. Nu" << endl;
  cin >> continuare;

  switch (continuare)
  {
  case 1:
  {
    cumparareProdus(v, c);
  }
  break;
  case 2:
  {
    c.getNumeProduse();
    c.getPretComanda();
    c.setStatusComanda(in_procesare);
    ofstream fileCSV("comenzi.csv", ios::app);
    c.salvareInCSV(fileCSV);
  }
  break;
  }
}

void creareComanda(vector<Produs> &v)
{
  int continuare;
  int produsAles;
  int salvare;

  Comanda c;

  cumparareProdus(v, c);

  cout << "Doriti sa salvati comanda?" << endl;
  cout << "1. Da" << endl
       << "2. Nu" << endl;
  cin >> salvare;

  switch (salvare)
  {
  case 1:
  {
    ofstream file;
    file.open("comenzi.txt", ios::app);
    file << c;
  }
  break;
  }
}

void incepereOperatiune(vector<Produs> &v)
{
  int continuare;

  int tipOperatiune;

  cout << "Ce operatiune doriti sa efectuati?" << endl;
  cout << "1. Creare produs" << endl
       << "2. Creare comanda " << endl;
  cin >> tipOperatiune;

  switch (tipOperatiune)
  {
  case 1:
  {
    creareProdus(v);
  }
  break;
  case 2:
  {
    creareComanda(v);
  }
  break;

  default:
  {
    cout << "Operatiune invalida." << endl;
    incepereOperatiune(v);
  }
  break;
  }

  cout << "Doriti sa continuati?" << endl;
  cout << "1. Da" << endl
       << "2. Nu" << endl;
  cin >> continuare;

  switch (continuare)
  {
  case 1:
    incepereOperatiune(v);
    break;
  }
}

int main()
{
  vector<Produs> listaProduse;
  
  incepereOperatiune(listaProduse);

  cout << "O zi buna!" << endl;

  return 0;
}