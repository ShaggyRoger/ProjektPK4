#include "pch.h"
#include "Naglowki.h"

Grafika::Grafika()
{
	Vector2f pozycja_(0, 0);
	pozycja = pozycja_;
}

void Grafika::rysuj(RenderWindow& okno) const
{
	okno.draw(*this);
}


Postac::Postac() : Grafika()
{

	if (grafika[0].loadFromFile("postac_przod.png") != true)
		blad_wczytywania();

	if (grafika[1].loadFromFile("postac_lewy.png") != true)
		blad_wczytywania();

	if (grafika[2].loadFromFile("postac_prawy.png") != true)
		blad_wczytywania();

	if (grafika[3].loadFromFile("postac_tyl.png") != true)
		blad_wczytywania();

	this->setTexture(grafika[0]);
}

void Postac::podmien_grafiki(int kierunek)
{
	switch (kierunek)
	{
	case 0:
	{
		this->setTexture(grafika[0]);
	}
	break;

	case 1:
	{
		this->setTexture(grafika[1]);
	}
	break;

	case 2:
	{
		this->setTexture(grafika[2]);
	}
	break;

	case 3:
	{
		this->setTexture(grafika[3]);
	}
	break;
	}
}
//-----------------------------WORKZONE--------------------------
Tlo_menu::Tlo_menu() : Sprite()
{
	Texture buff;

	if (buff.loadFromFile("bckgrnd1_1.png") != true) 
		blad_wczytywania();
	else zaw.push_back(buff);
	if (buff.loadFromFile("bckgrnd1_2.png") != true)
		blad_wczytywania();
	else zaw.push_back(buff);
	if (buff.loadFromFile("bckgrnd1_3.png") != true)
		blad_wczytywania();
	else zaw.push_back(buff);
	if (buff.loadFromFile("bckgrnd1_4.png") != true)
		blad_wczytywania();
	else zaw.push_back(buff);
	if (buff.loadFromFile("lvl1_1.png") != true)
		blad_wczytywania();
	else zaw.push_back(buff);
	if (buff.loadFromFile("lvl1_2.png") != true)
		blad_wczytywania();
	else zaw.push_back(buff);
	if (buff.loadFromFile("lvl1_3.png") != true)
		blad_wczytywania();
	else zaw.push_back(buff);
	if (buff.loadFromFile("lvl1_4.png") != true)
		blad_wczytywania();
	else zaw.push_back(buff);
	
	this->setTexture(zaw[0]);
}
void Tlo_menu::podmianka(int i) {

	Texture buff;
	this->setTexture(zaw[i]);
}
//-----------------------------WORKZONE--------------------------
Sciana::Sciana() : Grafika()
{
	if (grafika.loadFromFile("sciana.png") != true)
		blad_wczytywania();

	this->setTexture(grafika);
}



Skrzynia::Skrzynia() : Grafika()
{
	if (grafika[0].loadFromFile("skrzynia.png") != true)
		blad_wczytywania();

	if (grafika[1].loadFromFile("wlozona_skrzynia.png") != true)
		blad_wczytywania();

	this->setTexture(grafika[0]);
}


void Skrzynia::podmien_grafiki(int liczba)
{
	switch (liczba)
	{
	case 0:
		this->setTexture(grafika[0]);
		break;

	case 1:
		this->setTexture(grafika[1]);
		break;
	}
}


Miejsca_na_skrzynie::Miejsca_na_skrzynie() : Grafika()
{
	if (grafika.loadFromFile("miejsca_na_skrzynie.png") != true)
		blad_wczytywania();

	this->setTexture(grafika);
}


Tlo::Tlo() : Grafika()
{
	if (grafika.loadFromFile("tlo.png") != true)
		blad_wczytywania();

	this->setTexture(grafika);
}