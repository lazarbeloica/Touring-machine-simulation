//Header.h

#include<string>
#include <iostream>
using namespace std;

const int MAX = 50;
char traka_def[MAX] = { 'b', '\0' };
char azbuka_def[4] = { 'b', '0', '1', '\0' };

struct algoritam
{
	char ovaj;
	int st_sad;
	int st_sled;
	char upis;
	int pom;
	algoritam *sled;
	bool pos_p , pos_n ;
	algoritam(char ov = 'b', int ss = 0, int sp = 0, char u = 'b', int p = 1, algoritam *s = nullptr, bool poz = false,bool ne=false) :ovaj(ov), st_sad(ss), st_sled(sp), upis(u), pom(p), sled(s), pos_p(poz), pos_n(ne) {}
	friend bool operator==(algoritam &a1, algoritam &a2){ return (a1.ovaj == a2.ovaj && a1.pom == a2.pom && a1.st_sad == a2.st_sad && a1.st_sled == a2.st_sled && a1.upis == a2.upis && a1.pos_p == a2.pos_p && a1.pos_n == a2.pos_n); }
	void operator=(algoritam &a){ ovaj = a.ovaj; st_sad = a.st_sad; st_sled = a.st_sled; upis = a.upis; pom = a.pom; sled = a.sled; }
	~algoritam(){}
};


class Masina
{
private: int q; //stanja u kojima moze da se nalazi masina
		 char *traka;
		 algoritam *al;
		 int glava;
public:
	Masina(char *tr) : traka(tr), glava(0), q(0)
	{
		al = new algoritam();
	}
	Masina(Masina &m)
	{
		glava = m.glava;
		q = m.q;
		traka = new char[sizeof(m.traka)];
		int i = 0;
		while (m.traka[i] != '\0') { traka[i] = m.traka[i]; i++; }
		traka[i] = '\0';
		al = nullptr;
		algoritam *t=nullptr,*tek = m.al;
		while (tek != nullptr)
		{
			algoritam *novi = new algoritam(tek->ovaj,tek->st_sad,tek->st_sled,tek->upis,tek->pom,nullptr,tek->pos_p,tek->pos_n);
			if (al == nullptr){ tek = al = novi; }
			else{ t->sled = novi; } t = novi;	
		}
	}
	Masina(Masina &&m)
	{
		glava = m.glava;
		q = m.q;
		traka = m.traka; m.traka = nullptr;
		al = m.al; m.al = nullptr;
	}
	~Masina(){ while (al != nullptr){ algoritam *stari = al; stari->sled = nullptr; al = al->sled; delete stari; } }

	void operator=(Masina &m)
	{
		glava = m.glava;
		q = m.q;
		traka = new char[sizeof(m.traka)];
		int i = 0;
		while (m.traka[i] != '\0') { traka[i] = m.traka[i]; i++; }
		traka[i] = '\0';
		al = nullptr;
		algoritam *t = nullptr, *tek = m.al;
		while (tek != nullptr)
		{
			algoritam *novi = new algoritam(tek->ovaj, tek->st_sad, tek->st_sled, tek->upis, tek->pom, nullptr, tek->pos_p, tek->pos_n);
			if (al == nullptr){ tek = al = novi; }
			else{ t->sled = novi; } t = novi;
		}
	}
	void operator=(Masina &&m)
	{
		glava = m.glava;
		q = m.q;
		traka = m.traka; m.traka = nullptr;
		al = m.al; m.al = nullptr;
	}

	Masina& operator+=(algoritam &x)
	{
		algoritam *tek = al;
		while (tek->sled != nullptr)
		{
			if (*tek == x) return *this;
			tek = tek->sled;
		}
		tek->sled = &x;
	}
	algoritam& operator[](char &c)
	{
		algoritam *tek = al;
		while (tek != nullptr)
		{
			if (tek->ovaj == c && q == tek->st_sad)return *tek;
			tek = tek->sled;
		}
		cout << "\nGRESKA: Nije pronadjeno pravilo u algoritmu za dato stanje!" << endl; exit(1);
	}

	bool citaj_algoritam()
	{
		char temp[25];
		cin >> temp;
		if (!strcmp(temp,"STOP")) return false;
		int j = 0;
		while (temp[j++] != 'q');
		char c[2]; c[0] = temp[j]; c[1] = '\0';
		int sad = atoi(c); j++;

		while (temp[j] != ',')j++;
		if (temp[++j] == ' ') while (temp[j] != ' ')j++;
		char pise_trak = temp[j];

		while (temp[j++] != 'q');
		c[0] = temp[j]; c[1] = '\0'; bool poz = false, neg = false; int sl = 0;
		if (temp[j] == '+')poz = true;
		else if (temp[j] == '-')neg = true;
		else sl = atoi(c); j++;

		while (temp[j] != ',')j++;
		if (temp[++j] == ' ') while (temp[j] != ' ')j++;
		char upis_trak = temp[j];

		while (temp[j] != '+' && temp[j] != '-') j++;
		char p[3]; p[0] = temp[j++]; p[1] = temp[j]; p[2] = '\0';
		int pom = atoi(p);

		algoritam *novi = new algoritam(pise_trak, sad, sl, upis_trak, pom, nullptr, poz, neg);

		*this += *novi;
		return true;
	}
	void popuni()
	{
		cout << "\nUnesite algoritam zadatka u formatu: \n\yF(qx,znak_trake)=F(qy,znak_upis,+/-pom)\n\nqx-trenutno stanje\nqy-stanje u koje se prelazi\n+/-pom-pomeraj  glave\nSTOP-za kraj" << endl;
		while (citaj_algoritam());
	}
	bool radi()
	{
		algoritam *sad = &((*this)[traka[glava]]);
		traka[glava] = sad->upis;
		glava += sad->pom;
		q = sad->st_sled;
		if (sad->pos_n || sad->pos_p){ return false; }
		return true;
	}
};