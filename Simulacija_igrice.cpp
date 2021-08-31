#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Igrac{
	public:
		int energija;
		int zivot;
		Igrac(){
			this->energija = 10;
		}
};

class Mrav{
protected:
	int prioritet;
	int energija;
	int napad;
public:
	virtual void KreirajMrava() = 0;
};
class CrveniMrav: public Mrav {
	public:
	int a = 0;
	CrveniMrav()
		{
		prioritet = 4;	
		energija = 4;
		napad = 4;
		}
	void KreirajMrava() {
		if(a==0)
		{
		cout << "Crveni mrav je kreiran! Energija" << " " << energija << " " << "Napad" << " " << napad << endl;
		a++;
		}
		else cout << "Crveni mrav vec postoji!" << endl;
		}
};
class PlaviMrav: public Mrav {
	public:
	PlaviMrav(){
		prioritet = 2;
		energija = 2;
		napad = 2;
	}
	void KreirajMrava(){
			cout << "Plavi mrav je kreiran! Energija" << " " << energija << " " << "Napad" << " " << napad << endl;
	}
};
class ZutiMrav: public Mrav {
	public:
	ZutiMrav(){
		prioritet = 1;
		energija = 1;
		napad = 1;
	}
	void KreirajMrava(){
			cout << "Zuti mrav je kreiran! Energija" << " " << energija << " " << "Napad" << " " << napad << endl;
	}
};
class FabrikaMrava {
	public:
	virtual Mrav* napraviCrvenog() = 0;
	virtual Mrav* napraviPlavog() = 0;
	virtual Mrav* napraviZutog() = 0;
};
class FabrikaSvihMrava : public FabrikaMrava{
	public:
	Mrav* napraviCrvenog(){
		return new CrveniMrav;
	}
	Mrav* napraviPlavog(){
		return new PlaviMrav;
	}
	Mrav* napraviZutog(){
		return new ZutiMrav;
	}
};
class Armija 
{
	protected:
		string a_boja;
		int a_energija;
		vector<Armija*> a_jedinice;
	public:
		typedef vector<Armija*>:: iterator ArmijaIter;
		Armija() {}
		Armija(string boja, int energija) :  a_boja(boja), a_energija(energija){}
		virtual ~Armija(){
			for (ArmijaIter it = a_jedinice.begin(); it != a_jedinice.end(); ++it) {
            delete *it;
		}
	}
    virtual void dodaj(Armija *armija);
    virtual void izbrisi(Armija *armija);
    virtual int izracunajEnergiju();
};
void Armija::dodaj(Armija *armija) {
   	a_jedinice.push_back(armija);
}


void Armija::izbrisi(Armija *armija) {
    for (ArmijaIter it = a_jedinice.begin(); it != a_jedinice.end(); ++it) {
        if (*it == armija) {
            a_jedinice.erase(it);
            return;
        }
    }
}

int Armija::izracunajEnergiju() {
    int energija = a_energija;
    for (ArmijaIter it = a_jedinice.begin(); it != a_jedinice.end(); ++it) {
        energija += (*it)->izracunajEnergiju();
    }
    return energija;
}
int main(){
	bool crveni = true;
	int a = 0;
	FabrikaMrava* fabrika = new FabrikaSvihMrava();
	Igrac igrac;
	int energija = igrac.energija;
	int energija_armije = 0;
	cout << "Igraceva Pocetna Energija: "<< energija << endl;
	int armija = 0;
	cout << "Unesi broj mrava:" << "\n" << endl;
	cin >> armija;
	Mrav* mravi[armija];
	mravi[0] = fabrika->napraviCrvenog(); 
	mravi[0]->KreirajMrava();
	string b;
	Armija* armijaa = new Armija("CRVENI", 4);
	if(energija>=0)
	{
	for(int i=1; i<armija; i++ )
	{
	cout << "Izaberite CRVENI, PLAVI ili ZUTI mrav " << endl;
	cin >> b;
	if ( b == "CRVENI")
	{
	if(crveni == false)
	{
	if(energija >= 4)
	{
	mravi[i] = fabrika->napraviCrvenog(); 
	mravi[i]->KreirajMrava();
	crveni = true;
	energija = energija - 4;
	armijaa->dodaj(new Armija("CRVENI", 4));
	//armijaa->dodaj(crveni);
	}
	else{
		cout << "NEMATE DOVOLJNO ENERGIJE" << endl;
		i--;
	}
	}
	else {
		cout << "Crveni mrav vec postoji, samo jedan je dozvoljen" << endl;
		i--;
	}
	}
	if( b == "PLAVI")
	{
	if(energija >= 2)
	{
	mravi[i] = fabrika->napraviPlavog(); 
	mravi[i]->KreirajMrava();
	energija = energija - 2;
	armijaa->dodaj(new Armija("PLAVI", 2));
	//armijaa->dodaj(plavi);
	cout << "Trenutna energija: " << energija << endl;
	}
	else {
		cout << "NEMATE DOVOLJNO ENERGIJE" << endl;
		i--;
	}
	}
	if (b == "ZUTI")
	{
	if(energija >= 1)
	{
	mravi[i] = fabrika->napraviZutog(); 
	mravi[i]->KreirajMrava();
	energija = energija - 1;
	armijaa->dodaj(new Armija("ZUTI", 1));
	//armijaa->dodaj(zuti);
	cout << "Trenutna energija: " << energija << endl;
	}
	else{
		cout << "NEMATE DOVOLJNO ENERGIJE" << endl;
		i--;
	}
	}
	if (b != "ZUTI" && b!= "CRVENI" && b!= "PLAVI")
	{
		cout << "POGRESAN UNOS, IZABERTE PLAVOG, CRVENOG ILI ZUTOG" << endl;
		i--;
	}

	}
	}
	else{
		cout << "Vasa energija je 0" << endl;
	}
	
	cout << "Trenutno imate na raspolaganju armiju sa energijom:" << armijaa->izracunajEnergiju() << endl;
	cout << "unesite NAPAD da bi ste napali armiju" << endl;
	string napad;
	cin >> napad;
	int izbor;
	if(napad == "NAPAD")
	{
		cout << "Za napad crvenog taster 1 " << "\n " << "Za napad plavog taster 2" << "\n" << "Za napad zutog taster 3" << endl;
		cin >> izbor;
		switch(izbor)
		{
		case 1 :
			//armijaa->izbrisi(crveni);
			//delete crveni;
			cout << "Crveni mrav je primio udarac, trenutno imate na raspolaganju armiju sa energijom:" << armijaa->izracunajEnergiju() << endl;
			break;
		case 2 :
			cout << "Plavi mrav je primio udarac, trenutno imate na raspolaganju armiju sa energijom:" << armijaa->izracunajEnergiju() << endl;
			//armijaa->izbrisi(plavi);
			//delete plavi;
			break;
		case 3 :
			cout << "Zuti mrav je primio udarac, trenutno imate na raspolaganju armiju sa energijom:" << armijaa->izracunajEnergiju() << endl;
			//armijaa->izbrisi(zuti);
			//delete zuti;
			break;
		default:
			cout << "Niste izabrali" << endl;
		}
	}
	else cout << "GAME OVER" << endl;
}
