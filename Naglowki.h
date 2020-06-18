#pragma once
#include "pch.h"
#include <iostream>
#include <ctime>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include <conio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <Windows.h>
#include <thread>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;
using namespace sf;


class Grafika : public Sprite
{
private:
	Vector2f pozycja;
public:
	Grafika();
	virtual ~Grafika() { delete this; };
	void rysuj(RenderWindow& okno) const;
	Vector2f zwroc_pozycje() const { return pozycja; };
	void aktualizuj_pozycje() { pozycja = this->getPosition(); };
	inline friend void blad_wczytywania()
	{
		cout << "Nie udalo  sie wczytac grafiki. Program zostanie zamkniety!";
		exit(3);
	}
};
class Tlo_menu : public Sprite {
private:
	vector<Texture> zaw;
public:
	Tlo_menu();
	void podmianka(int i);
};

class Postac : public Grafika
{
private:
	Texture grafika[4];
public:
	Postac();
	virtual ~Postac() {};
	void podmien_grafiki(int);
	inline void rusz(Vector2f przemieszczenie_) { this->move(przemieszczenie_); };
};

class Sciana : public Grafika
{
private:
	Texture grafika;
public:
	Sciana();
	virtual ~Sciana() {};
};

class Skrzynia : public Grafika
{
private:
	Texture grafika[2];
public:
	Skrzynia();
	virtual ~Skrzynia() {};
	void podmien_grafiki(int);
	inline void rusz(Vector2f przemieszczenie_) { this->move(przemieszczenie_); };
};

class Miejsca_na_skrzynie : public Grafika
{
private:
	Texture grafika;
public:
	Miejsca_na_skrzynie();
	virtual ~Miejsca_na_skrzynie() {};
};

class Tlo : public Grafika
{
private:
	Texture grafika;
public:
	Tlo();
	virtual ~Tlo() {};
};

class Gra
{
public:
	Tlo* tlo[100];
	Sciana* sciana[60];
	Skrzynia* skrzynia[4];
	Miejsca_na_skrzynie* miejsce_na_skrzynie[4];
	Postac* postac;

	void wybor();
	void StworzObiekty();
	void RozpocznijGre(int);
	char Menu();
	//void ObslugaMenu(char);
	void UstawSzablon();
	void Level1();
	void Level2();
	void Level3();
	void Sprawdz_kolizje_rusz(int);
	void Rysuj_wszystko(RenderWindow&);
	bool Czy_wlozona();
	void O_grze();
	void Wpisz_czas_i_ruch(float, int);
	void Odczytaj_czas_i_ruch();
};

void blad_wczytywania();