//Source.h

#include <iostream>
#include <string>
#include "Header.h"
using namespace std;

void citaj_traku(char *traka)
{
	cout << "\nPopunite traku ( n za kraj unosa ):" << endl;
	int i = 0;
	while (true)
	{

		cin >> traka[i];
		if (traka[i++] == 'n') break;
	}
	traka[--i] = 'b';
	for (int j = 0; j < 5; j++)traka[i++] = 'b';
	traka[i] = '\0';

}

void nula()
{
	char traka[100];
	
	citaj_traku(traka);

	Masina nul(traka);

	nul += algoritam('1', 0, 1, 'b', 1);
	nul += algoritam('1', 1, 1, 'b', 1); 
	nul += algoritam('b', 1, 0, '1', -1,nullptr,true);

	while (nul.radi());
	cout << "\nRESENJE:" << endl;
	int i = 0;
	while (traka[i] != '\0') cout << traka[i++];
	cout << endl;
}

void sledbenik()
{
	char traka[100];
	
	citaj_traku(traka);

	Masina nul(traka);

	nul += algoritam('1', 0, 1, '1', 1);
	nul += algoritam('1', 1, 1, '1', 1);
	nul += algoritam('b', 1, 0, '1', 1, nullptr, true);

	while (nul.radi());
	cout << "\nRESENJE:" << endl;
	int i = 0;
	while (traka[i] != '\0') cout << traka[i++];
	cout << endl;
}

void prva_proj()
{
	char traka[100];
	citaj_traku(traka);
	Masina nul(traka);

	nul += algoritam('1', 0, 1, '1', 1);
	nul += algoritam('1', 1, 1, '1', 1);
	nul += algoritam('0', 1, 2, 'b', 1);
	nul += algoritam('1', 2, 2, 'b', 1);
	nul += algoritam('b', 2, 0, 'b', -1,nullptr,true);

	while (nul.radi());
	cout << "\nRESENJE:" << endl;
	int i = 0;
	while (traka[i] != '\0') cout << traka[i++];
	cout << endl;
}

void zbir()
{
	char traka[100];
	
	citaj_traku(traka);

	Masina nul(traka);

	nul += algoritam('1', 0, 1, '1', 1);
	nul += algoritam('1', 1, 1, '1', 1);
	nul += algoritam('0', 1, 2, '1', 1);
	nul += algoritam('1', 2, 2, '1', 1);
	nul += algoritam('b', 2, 3, 'b',-1);
	nul += algoritam('1', 3, 4, 'b', -1);
	nul += algoritam('1', 4, 0, 'b', -1,nullptr,true);

	while (nul.radi());
	cout << "\nRESENJE:" << endl;
	int i = 0;
	while (traka[i] != '\0') cout << traka[i++];
	cout << endl;
}



int main()
{
	cout << "***DOBRODOŠLI U SIMULATOR TOURING-OVA MAŠINE***\n\n\n" << endl;
	while (true)
	{
		cout << "Da li zelite da izvrsite svoj program ili neki program iz memorije?\n0-VAS PROGRAM\n1-PROGRAM IZ MEMORIJE\nIZBOR:\t" << endl;
		int o; cin >> o;
		if (!o)
		{
			char traka[100];

			Masina nul(traka);
			nul.popuni();

			citaj_traku(traka);

			while (nul.radi());
			cout << "\nRESENJE:" << endl;
			int i = 0;
			while (traka[i] != '\0') cout << traka[i++];
			cout << endl;

		}
		else
		{
			cout << "\n\nIzaberite:\n0-NULA F-JE\n1-SLEDBENIK F-JE\n2-PRVA PROJEKCIJA\n3-ZBIR" << endl;
			cin >> o;
			switch (o)
			{
			case 0: nula(); break;
			case 1: sledbenik(); break;
			case 2: prva_proj(); break;
			case 3: zbir(); break;
			}
		}
		cout << "\n\nDa li zelite da izvrsite novu simulaciju ( 0-ne  1-da )?" << endl;
		cin >> o; if (!o) break;

	}
	cout << "\nDOVIDJENJA" << endl;
}