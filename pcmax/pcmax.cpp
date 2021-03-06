// pcmax.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <conio.h>
#include <algorithm>
using namespace std;
//funkcja znajdujaca max w tablicy
int maxi(int t[], int m)
{
	int mx = 0;
	for (int i = 0; i < m; i++)
		if (t[i] >= mx)
			mx = t[i];
	return mx;
}
//funkcja znajdujaca indeks pierwszego wolnego procesora, czyli po prostu znajdujaca ten z minimalnym czasem zakonczenia
int wolny(int t[], int m)
{
	int mini = t[0], minID = 0;
	for (int i = 1; i < m; i++)
		if (t[i] < mini) {
			mini = t[i];
			minID = i;
		}
	return minID;
}



/*int maxi(int t[], int m)
{
	int mx = 0;
	for (int i = 0; i < m;i++)
		if (t[i] >= mx)
			mx = t[i];
	return mx;
}*/
int maxid(int t[], int m)
{
	int mx = t[0], maxID = 0;
	for (int i = 1; i < m;i++)
		if (t[i] > mx) {
			mx = t[i];
			maxID = i;
		}
	return maxID;
}

void zad1() {
	//liczba procesorow
	int m;
	//liczba zadan
	int n;
	ofstream instancja("plik.txt");
	cout << "Podaj liczbe procesorow: ";
	cin >> m;
	cout << "Podaj liczbe zadan: ";
	cin >> n;
	int wsp = n - m + 1;
	int *proc = new int[m];
	int *zad = new int[n];

	for (int i = 0; i < m; i++)
		proc[i] = 0;

	srand(time(NULL));
	for (int i = 0; i < wsp; i++) {
		zad[i] = ((rand() % 1000) + 1);
		//cout << i << " " << zad[i] << endl;
	}
	//cout<<endl;
	//cout << "procesory: " << endl;

	int k = 0;
	//cout << "wspolczynik" << wsp << endl;
	for (int i = 0; i < wsp; i += m) {
		for (int j = 0; j < m; j++) {

			proc[j] += zad[k++];
			//cout << "wrzucam zadanie: " << k - 1 << " " << zad[k - 1] << endl;
			if (k > wsp - 1)
				break;
		}
		if (k > wsp - 1)
			break;
	}
	/*for (int i = 0; i < m; i++) {
		cout << i << " " << proc[i] << endl;
	}*/

	int maxx = maxi(proc, m);
	int maxxID = maxid(proc, m);
	//cout << "maxx " << maxxID << " " << maxx << endl;
	maxx += 1;
	proc[maxxID] += 1;

	//zad[n - wsp] = 1;

	k = wsp;
	for (int i = 0; i < m; i++) {
		if (i != maxxID) {
			zad[k] = maxx - proc[i];
			proc[i] += zad[k++];
		}
	}

	cout << "Optimum: " << maxx << endl;
	/*cout << "Tablica procesorow: " << endl;
	for (int i = 0; i < m; i++)
		cout << proc[i] << " ";
	cout << "Tablica zadan: " << endl;
	for (int i = 0; i < n; i++)
		cout << i << " " << zad[i] << " " << endl;*/
	instancja << m << endl << n << endl;
	for (int i = 0; i < n; i++)
		instancja << zad[i] << endl;
}
void zad2() {
	string temp;
	fstream plik;
	//liczba procesorow
	int m;
	//liczba zadan
	int n;
	//zmienna zawierajaca wynik czyli czas zakonczenia wykonywania wszystkich zadan
	int y;

	cout << endl;
	plik.open("plik.txt", ios::in);			//otwiera plik
	if (plik.good())
	{
		cout << "Plik zostal otwarty" << endl;


		plik >> temp;
		m = stoi(temp);
		int *proc = new int[m];
		for (int i = 0; i < m; i++)
		{
			proc[i] = 0;          //zeruje czas zakonczenia wszystkich umieszonych na danym procesorze zadan
		}


		plik >> temp;
		n = stoi(temp);

		int *zad = new int[n];

		for (int k = 0; k < n; k++)
		{
			plik >> temp;
			zad[k] = stoi(temp);
		}
		plik.close();



		sort(zad, zad + n);

		int temp, i, j;
		for (i = 0, j = n - 1; i < n / 2; i++, j--)
		{
			temp = zad[i];
			zad[i] = zad[j];
			zad[j] = temp;
		}

		//for (int i = 0; i < n; i++)
			//printf_s("%d ", zad[i]);

		//algorytm zachalnny
		for (int i = 0; i < n; i++)
		{
			int cyfra = wolny(proc, m);//umieszczam na pierwszym wolnym procesorze dane zadanie
			proc[cyfra] += zad[i];    //czyli po prostu zwiekszam czas zakonczenia wykonywania wszystkich zadan na tym procesorze
			//printf("%d: \t %d\n", proc[cyfra], zad[cyfra]);
		}

		y = maxi(proc, m); //znajduje czas, po ktorym procesor z najpozniejszym zakonczeniem wykonywania zadan wykona wszystkie zqadania czyli wykonywania zadan sie zakonczy

		cout << endl << "Czas zakonczenia wykonywania zadan: " << y;
		delete[] proc;
		delete[] zad;

	}
	else cout << "Error! Nie udalo otworzyc sie pliku!" << endl;

}

int main()
{
	zad1();
	zad2();
	return 0;
}


// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
