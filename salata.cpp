#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

class Owoc{
	string  nazwa;
	double ilosc;
	double cena;
public:
  void setOwoc(string nazwa, double ilosc, double cena);
  string getNazwa();
  double getIlosc();
  double getCena();
  //Konstruktor
  Owoc() = default;
  Owoc(string nazwa, double ilosc, double cena);
  double wartosc();
  
};

class Zamowienie{
	vector<Owoc> listaOwocow;
	int nrZamowienia;
public:
  void dodajOwoc(string nazwa, double ilosc = 0, double cena = 0);
  void usunOwoc(string nazwa);
  void usunOwoc(int index);
  vector<Owoc> getListaOwocow();
  int getNrZamowienia();
  //Konstruktor
  Zamowienie() = default;
  Zamowienie(int nrZamowienia);
  double wartoscZamowienia();
  void wypiszZamowienie();
  int liczbaOwocow();
};


int main()
{	 
	fstream plik;
    string n;
    double i;
    double c;
	Zamowienie zamowienie(1);
    
    //wczytanie danych z pliku
    plik.open("stanMagazynu.txt", ios::in);
    while(!plik.eof()){
        plik >> n >> i >> c;
        zamowienie.dodajOwoc(n,i,c);
    }
    plik.close();

	zamowienie.wypiszZamowienie();
	zamowienie.usunOwoc("Apple");
	zamowienie.usunOwoc(2);
	cout << endl;
	zamowienie.wypiszZamowienie();
 
    return 0;
}

void Owoc::setOwoc(string nazwa, double ilosc, double cena){
	this -> nazwa = nazwa;
	this -> ilosc = ilosc;
	this -> cena =  cena;
}

 Owoc::Owoc(string nazwa, double ilosc, double cena){
	Owoc::setOwoc(nazwa, ilosc, cena);
 }

double Owoc::wartosc(){
return ilosc * cena;
}

string Owoc::getNazwa(){
return nazwa;
}

double Owoc::getIlosc(){
return ilosc;
}

double Owoc::getCena(){
return cena;
}

Zamowienie::Zamowienie(int nrZamowienia){
	this -> nrZamowienia = nrZamowienia;
}

void Zamowienie::dodajOwoc(string nazwa, double ilosc, double cena){
		listaOwocow.emplace_back(Owoc(nazwa, ilosc, cena));
}

vector<Owoc> Zamowienie::getListaOwocow(){
	return listaOwocow;
}

int Zamowienie::getNrZamowienia(){
	return nrZamowienia;
}

double Zamowienie::wartoscZamowienia(){
	double suma = 0;
	for(auto &owoc : listaOwocow){
		suma += owoc.wartosc();
	}
	return suma;
}

int Zamowienie::liczbaOwocow(){
	return listaOwocow.size();
}

void Zamowienie::wypiszZamowienie(){
	int i = 1;
	cout << "Zamowienie nr: " << nrZamowienia << endl;
	for(auto &owoc : listaOwocow){
		cout << i++ << " " << owoc.getNazwa() << " " << owoc.getIlosc() << " " << owoc.getCena()
		 << " " << owoc.wartosc() << endl;
	}
	cout << "------------------------------------------------------------" << endl;
	cout << "Wartosc zamowienia: " << wartoscZamowienia() << endl;
}

void Zamowienie::usunOwoc(string nazwa){
	int i = 0;
	for(auto &owoc : listaOwocow){
		if(owoc.getNazwa() == nazwa){
			break;
		}
		i++;
	}
	listaOwocow.erase(listaOwocow.begin()+ i, listaOwocow.begin() + i + 1);
}

void Zamowienie::usunOwoc(int index){
	listaOwocow.erase(listaOwocow.begin() + (index - 1));
}