#include "pch.h"
#include "Naglowki.h"


void Gra::StworzObiekty()
{
	thread t1([&] {for (int i = 0; i < 100; ++i) tlo[i] = new Tlo; });
	//for (int i = 0; i < 100; ++i)
	//	tlo[i] = new Tlo;
	thread t2([&] {for (int i = 0; i < 60; ++i) sciana[i] = new Sciana; });
	//for (int i = 0; i < 60; ++i)
		//sciana[i] = new Sciana;
	thread t3([&] {for (int i = 0; i < 4; ++i) skrzynia[i] = new Skrzynia; });
	//for (int i = 0; i < 4; ++i)
		//skrzynia[i] = new Skrzynia;
	thread t4([&] {for (int i = 0; i < 4; ++i) miejsce_na_skrzynie[i] = new Miejsca_na_skrzynie; });
	//for (int i = 0; i < 4; ++i)
		//miejsce_na_skrzynie[i] = new Miejsca_na_skrzynie;

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	postac = new Postac;
}



void Gra::RozpocznijGre(int num)
{
	RenderWindow window{ VideoMode::getDesktopMode(), "Okienko", Style::Fullscreen };
	StworzObiekty();
	UstawSzablon();
	int ruch = 0;
	float czas;
	switch (num)
	{
	case 1:
		Level1();
		break;
	case 2:
		Level2();
		break;
	case 3:
		Level3();
		break;
	}

	while (window.isOpen())
	{
		for (int i = 0; i < 100; ++i)
			tlo[i]->aktualizuj_pozycje();

		for (int i = 0; i < 60; ++i)
			sciana[i]->aktualizuj_pozycje();

		for (int i = 0; i < 4; ++i)
			skrzynia[i]->aktualizuj_pozycje();

		for (int i = 0; i < 4; ++i)
			miejsce_na_skrzynie[i]->aktualizuj_pozycje();

		postac->aktualizuj_pozycje();

		Event windowEvent;

		clock_t start, stop;


		start = clock();
		while (window.pollEvent(windowEvent))
		{
			if (windowEvent.type == Event::Closed)
			{
				window.close();
			}

			if (windowEvent.type == Event::KeyPressed && windowEvent.key.code == Keyboard::Escape)
			{
				window.close();
			}

			if (windowEvent.type == Event::KeyPressed && windowEvent.key.code == Keyboard::Right)
			{
				postac->podmien_grafiki(2);
				Sprawdz_kolizje_rusz(2);
				++ruch;
			}

			if (windowEvent.type == Event::KeyPressed && windowEvent.key.code == Keyboard::Left)
			{
				postac->podmien_grafiki(1);
				Sprawdz_kolizje_rusz(1);
				++ruch;
			}

			if (windowEvent.type == Event::KeyPressed && windowEvent.key.code == Keyboard::Up)
			{
				postac->podmien_grafiki(3);
				Sprawdz_kolizje_rusz(3);
				++ruch;
			}

			if (windowEvent.type == Event::KeyPressed && windowEvent.key.code == Keyboard::Down)
			{
				postac->podmien_grafiki(0);
				Sprawdz_kolizje_rusz(4);
				++ruch;
			}
			Rysuj_wszystko(window);
		}
		stop = clock();
		czas = (double)(stop - start) / CLOCKS_PER_SEC;
		
		if (Czy_wlozona() == true)
		{
			window.close();
			Wpisz_czas_i_ruch(czas, ruch);			
		}
	}
}



char Gra::Menu()
{
	cout << "Wybierz jedna z opcji:\n\n1) Rozpocznij gre\n2) Najlepsze wyniki\n3) O grze\n4) Wyjscie\n";
	char wybor[50];
	cin.getline(wybor, 50);
	int dlugosc = strlen(wybor);
	while (dlugosc > 1 || (wybor[0] != '1' && wybor[0] != '2' && wybor[0] != '3' && wybor[0] != '4'))
	{
		cout << "Niepoprawny wybor!\n";
		Sleep(1500);
		system("cls");
		cout << "Wybierz jedna z opcji:\n\n1) Rozpocznij gre\n2) Najlepsze wyniki\n3) O grze\n4) Wyjscie\n";
		cin.getline(wybor, 50);
		dlugosc = strlen(wybor);
	}
	return wybor[0];
}

void Gra::O_grze()
{
	string text;
	ifstream inFile;
	vector<string> info;
	inFile.exceptions(ifstream::badbit);
	try {
		inFile.open("O_grze.txt");
		while (inFile.good())
		{
			getline(inFile, text);
			info.push_back(text);
			
		}
		for (int i = 0; i < info.size(); ++i) cout << info[i];
		inFile.close();
	}
	catch (const ifstream::failure& e) { cerr << "ERROR" << e.what() << endl; }
}

/*void Gra::ObslugaMenu(char wybor)
{
	switch (wybor)
	{
	case '1':
	{
		Sleep(1500);
		system("cls");
		cout << "Wybierz poziom:\n\n"
			<< "1) Poziom 1\n2) Poziom 2\n3) Poziom 3\n4) Powrot do menu glownego\n";

		char wybor2[50];
		cin.getline(wybor2, 50);
		int dlugosc2 = strlen(wybor2);
		while (dlugosc2 > 1 || (wybor2[0] != '1' && wybor2[0] != '2' && wybor2[0] != '3' && wybor2[0] != '4'))
		{
			cout << "Niepoprawny wybor!\n";
			Sleep(1500);
			system("cls");
			cout << "Wybierz poziom:\n\n"
				<< "1) Poziom 1\n2) Poziom 2\n3) Poziom 3\n4) Powrot do menu glownego\n";
			cin.getline(wybor2, 50);
			dlugosc2 = strlen(wybor2);
		}

		switch (*wybor2)
		{
		case '1':
		{
			RozpocznijGre(1);
			system("cls");
		}
		break;

		case '2':
		{
			RozpocznijGre(2);
			system("cls");
		}
		break;

		case '3':
		{
			RozpocznijGre(3);
			system("cls");
		}
		break;

		case '4':
		{
			Sleep(1500);
			system("cls");
			ObslugaMenu(Menu());
		}
		break;
		}
	}
	break;

	case '2':
	{
		Odczytaj_czas_i_ruch();
		cin.get();
		system("cls");
		ObslugaMenu(Menu());
	}
	break;

	case '3':
	{
		O_grze();
		cin.get();
		system("cls");
		ObslugaMenu(Menu());
	}
	break;

	case '4':
	{
		cout << "Program zostanie zamkniety.\n";
		exit(0);
	}
	break;
	}
}*/



void Gra::UstawSzablon()
{
	//USTAWIANIE TLA
	thread t1([&] {for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
			tlo[i * 10 + j]->setPosition((64 * (i + 1)) - 64, (64 * (j + 1)) - 64);
	}});
	
	int j = 0;
	//USTAWIENIE SCIAN
	thread t2([&] {for (int i = 0; i < 10; ++i)
	{
		sciana[i]->setPosition(j, 0);
		j += 64;
	}});
	
	j = 64;
	thread t3([&] {for (int i = 10; i < 19; ++i)
	{
		sciana[i]->setPosition(0, j);
		j += 64;
	}});
	
	j = 64;
	thread t4([&] {for (int i = 19; i < 27; ++i)
	{
		sciana[i]->setPosition(576, j);
		j += 64;
	}});
	

	j = 0;
	thread t5([&] {for (int i = 27; i < 37; ++i)
	{
		sciana[i]->setPosition(j, 576);
		j += 64;
	}});
	
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	//USTAWIENIE POSTACI
	postac->setPosition(192, 128);
}



void Gra::Sprawdz_kolizje_rusz(int liczba)
{
	for (int i = 0; i < 4; ++i)
		skrzynia[i]->aktualizuj_pozycje();

	postac->aktualizuj_pozycje();

	Vector2f przemieszczenie(0, 0), pion(0, 64), poziom(64, 0);

	if (liczba == 1 || liczba == 2)
	{
		przemieszczenie = poziom;
		if (liczba == 1)
			przemieszczenie.x *= -1;
	}

	else if (liczba == 3 || liczba == 4)
	{
		przemieszczenie = pion;
		if (liczba == 3)
			przemieszczenie.y *= -1;
	}
	//                             | DO POPRAWY |
	// SPRAWDZANIE CZY POSTAC JESLI SIE RUSZY NIE BEDZIE KOLIDOWAC ZE SCIANA 
	int licznik_sciana = 0;
	for (int i = 0; i < 60; ++i)
	{
		if (postac->zwroc_pozycje() != sciana[i]->zwroc_pozycje() - przemieszczenie)
			++licznik_sciana;
	}
	if (licznik_sciana == 60)
	{
		//SPRAWDZANIE KOLIZJI POSTACI ZE SKRZYNKAMI
		int licznik_skrzyn = 4;
		int bufor;
		for (int i = 0; i < 4; ++i)
		{
			skrzynia[i]->aktualizuj_pozycje();
			if (postac->zwroc_pozycje() != skrzynia[i]->zwroc_pozycje() - przemieszczenie)
				--licznik_skrzyn;
			else bufor = i;
		}
		if (licznik_skrzyn == 0) postac->rusz(przemieszczenie);
		else
		{
			//WARUNEK JESLI POSTAC KOLIDUJE ZE SKRZYNIA
			licznik_sciana = 0, licznik_skrzyn = -1;
			for (int j = 0; j < 4; ++j)
			{
				if (skrzynia[bufor]->zwroc_pozycje() != skrzynia[j]->zwroc_pozycje() - przemieszczenie)
					++licznik_skrzyn;
			}

			for (int i = 0; i < 60; ++i)
			{
				if (skrzynia[bufor]->zwroc_pozycje() != sciana[i]->zwroc_pozycje() - przemieszczenie)
					++licznik_sciana;
			}
			if (licznik_sciana == 60 && licznik_skrzyn == 3)
			{
				postac->rusz(przemieszczenie);
				skrzynia[bufor]->rusz(przemieszczenie);
			}
		}
	}
}



bool Gra::Czy_wlozona()
{
	int licznik_wlozonych = 0;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; j++)
		{
			if (skrzynia[i]->zwroc_pozycje() == miejsce_na_skrzynie[j]->zwroc_pozycje())
			{
				++licznik_wlozonych;
				skrzynia[i]->podmien_grafiki(1);
			}
		}
	}
	if (licznik_wlozonych == 4) return true;
	else return false;
}



void Gra::Rysuj_wszystko(RenderWindow& window_)
{
	for (int i = 0; i < 100; ++i)
		tlo[i]->rysuj(window_);

	for (int i = 0; i < 60; ++i)
		sciana[i]->rysuj(window_);

	for (int i = 0; i < 4; ++i)
	{
		//skrzynia[i]->rysuj(window_);
		miejsce_na_skrzynie[i]->rysuj(window_);
		skrzynia[i]->rysuj(window_);
	}
	postac->rysuj(window_);
	window_.display();
}



void Gra::Level1()
{

	int j = 128;
	thread t1([&] {for (int i = 38; i < 43; ++i)
	{
		sciana[i]->setPosition(128, j);
		j += 64;
	}});
	/*for (int i = 38; i < 43; ++i)
	{
		sciana[i]->setPosition(128, j);
		j += 64;
	}*/
	thread t2([&] {for (int i = 43; i < 46; ++i)
	{
		sciana[i]->setPosition(256, j);
		j += 64;
	}});
	/*for (int i = 43; i < 46; ++i)
	{
		sciana[i]->setPosition(256, j);
		j += 64;
	}*/

	j = 192;
	thread t3([&] {for (int i = 46; i < 50; ++i)
	{
		sciana[i]->setPosition(448, j);
		j += 64;
	}});
	/*for (int i = 46; i < 50; ++i)
	{
		sciana[i]->setPosition(448, j);
		j += 64;
	}*/

	sciana[58]->setPosition(256, 192);
	sciana[59]->setPosition(320, 256);

	j = 320;
	thread t4([&] {for (int i = 0; i < 4; ++i)
	{
		miejsce_na_skrzynie[i]->setPosition(j, 64);
		j += 64;
	}});
	/*for (int i = 0; i < 4; ++i)
	{
		miejsce_na_skrzynie[i]->setPosition(j, 64);
		j += 64;
	}*/

	j = 192;
	thread t5([&] {for (int i = 0; i < 4; ++i)
	{
		skrzynia[i]->setPosition(j, 320);
		j += 64;
	}});
	/*for (int i = 0; i < 4; ++i)
	{
		skrzynia[i]->setPosition(j, 320);
		j += 64;
	}*/
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
}



void Gra::Level2()
{
	int j = 64;
	thread t1([&] {for (int i = 38; i < 45; ++i)
	{
		sciana[i]->setPosition(j + 128, 320);
		j += 64;
	}});
	/*for (int i = 38; i < 45; ++i)
	{
		sciana[i]->setPosition(j + 128, 320);
		j += 64;
	}*/

	j = 64;
	thread t2([&] {for (int i = 45; i < 48; ++i)
	{
		sciana[i]->setPosition(256, 128 + j);
		j += 64;
	}});
	/*for (int i = 45; i < 48; ++i)
	{
		sciana[i]->setPosition(256, 128 + j);
		j += 64;
	}*/


	j = 448;
	thread t3([&] {for (int i = 0; i < 2; ++i)
	{
		miejsce_na_skrzynie[i]->setPosition(j, 64);
		j += 64;
	}});
	/*for (int i = 0; i < 2; ++i)
	{
		miejsce_na_skrzynie[i]->setPosition(j, 64);
		j += 64;
	}*/

	j = 448;
	thread t4([&] {for (int i = 2; i < 4; ++i)
	{
		miejsce_na_skrzynie[i]->setPosition(j, 128);
		j += 64;
	}});
	/*for (int i = 2; i < 4; ++i)
	{
		miejsce_na_skrzynie[i]->setPosition(j, 128);
		j += 64;
	}*/

	j = 192;
	thread t5([&] {for (int i = 0; i < 4; ++i)
	{
		skrzynia[i]->setPosition(j, 448);
		j += 64;
	}});
	/*for (int i = 0; i < 4; ++i)
	{
		skrzynia[i]->setPosition(j, 448);
		j += 64;
	}*/
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
}



void Gra::Level3()
{
	sciana[38]->setPosition(128, 192);
	sciana[39]->setPosition(128, 256);
	sciana[40]->setPosition(192, 256);
	sciana[41]->setPosition(256, 256);
	sciana[42]->setPosition(256, 192);
	sciana[43]->setPosition(128, 320);
	sciana[44]->setPosition(256, 320);
	sciana[45]->setPosition(512, 384);
	sciana[46]->setPosition(512, 512);
	sciana[47]->setPosition(448, 384);
	sciana[48]->setPosition(448, 512);
	sciana[49]->setPosition(64, 192);

	miejsce_na_skrzynie[0]->setPosition(192, 192);
	miejsce_na_skrzynie[1]->setPosition(192, 320);
	miejsce_na_skrzynie[2]->setPosition(512, 448);
	miejsce_na_skrzynie[3]->setPosition(64, 128);

	skrzynia[0]->setPosition(256, 128);
	skrzynia[1]->setPosition(256, 384);
	skrzynia[2]->setPosition(448, 320);
	skrzynia[3]->setPosition(320, 256);
}


void Gra::Wpisz_czas_i_ruch(float czas, int ruch)
{
	int czas_i = static_cast<int>(czas);
	ofstream outFile1, outFile2;
	outFile1.exceptions(ofstream::badbit | ofstream::failbit);
	try {
		outFile1.open("Najlepsze_wyniki_czas.txt", ios::app);
		outFile1 << czas_i;
		outFile1.close();

		outFile2.open("Najlepsze_wyniki_ruch.txt", ios::app);
		outFile2 << ruch;
		outFile2.close();
	}
	catch (const ifstream::failure& e) { cerr << "ERROR" << endl; }
	
}


void Gra::Odczytaj_czas_i_ruch()
{
	vector<string> high_r;
	vector<string> high_c;
	vector<int> high2;
	int buff_r, buff_c;
	string buff, buff2;
	ifstream inFile1, inFile2;
	inFile1.exceptions(ifstream::badbit | ifstream::failbit);
	try {
		inFile1.open("Najlepsze_wyniki_czas.txt", ios::in);
		while (!inFile1.eof()) {
			getline(inFile1, buff);
			high_c.push_back(buff);
			
		}
		
		for (int i = 0; i < high_c.size(); ++i) {
			buff_c = atoi(high_c[i].c_str());
			high2.push_back(buff_c);
		}
		sort(high2.begin(), high2.end());
		cout << "Najlepsze wyniki- czas" << endl;
		if (high2.size() < 5)
		for (int i=0; i< high2.size(); ++i) cout << high2[i] << endl;
		else for (int i = 0; i < 5; ++i) cout << high2[i] << endl;
		inFile1.close();
	}
	catch (const ifstream::failure& e) { cerr << "ERROR" << endl; }
	inFile2.exceptions(ifstream::badbit | ifstream::failbit);
		try {
		inFile2.open("Najlepsze_wyniki_ruch.txt", ios::in);
		while (!inFile2.eof()) {
			getline(inFile2, buff2);
			high_r.push_back(buff2);
		}
		vector<int> high3;
		for (int i = 0; i < high_r.size(); ++i) {
			buff_r = atoi(high_r[i].c_str());
			high3.push_back(buff_r);
		}
		sort(high3.begin(), high3.end());
		cout << "Najlepsze wyniki- ruch" << endl;
		if (high3.size() < 5)
		for (int i = 0; i < high3.size(); ++i) cout << high3[i] << endl;
		else for (int i = 0; i < 5; ++i) cout << high3[i] << endl;
		inFile2.close();
	}
	catch (const ifstream::failure& e) { cerr << "ERROR" << endl; }
	
}

void Gra::wybor() {
	RenderWindow menu{ VideoMode::getDesktopMode(), "Menu", Style::Fullscreen };
	Tlo_menu naszSprajt;
	Event zdarzenie;
	int licznik = 0;
	while (menu.isOpen()) {
		
		while (menu.pollEvent(zdarzenie))
		{
			if (zdarzenie.type == Event::Closed)
			{
				menu.close();
			}

			if (zdarzenie.type == Event::KeyPressed && zdarzenie.key.code == Keyboard::Escape)
			{
				menu.close();
			}
			if (zdarzenie.type == Event::KeyPressed && zdarzenie.key.code == Keyboard::Down)
			{
				if (licznik == 3) {
					licznik = 0;
					naszSprajt.podmianka(0);
				}
				else if (licznik == 7) {
					licznik = 4;
					naszSprajt.podmianka(licznik);
				}
				else {
					++licznik;
					naszSprajt.podmianka(licznik);
				}

			}
			if (zdarzenie.type == Event::KeyPressed && zdarzenie.key.code == Keyboard::Up)
			{
				if (licznik == 0) {
					licznik = 3;
					naszSprajt.podmianka(licznik);
				}
				else if (licznik == 4) {
					licznik = 7;
					naszSprajt.podmianka(licznik);
				}
				else {
					--licznik;
					naszSprajt.podmianka(licznik);
				}
				
			}
			if (zdarzenie.type == Event::KeyPressed && zdarzenie.key.code == Keyboard::Enter)
			{
				if (licznik == 0) {
					licznik = 4;
					naszSprajt.podmianka(licznik);
				}
				else if (licznik == 1) { 
					menu.close();
					Odczytaj_czas_i_ruch();
					Sleep(10000);
					system("cls");
					wybor();
				}
				else if (licznik == 2) {
					menu.close();
					O_grze();
					Sleep(10000);
					system("cls");
					wybor();
				}
				else if (licznik == 3) menu.close();
				else if (licznik == 4) {
					menu.close();
					RozpocznijGre(1);
					wybor();
				}
				else if (licznik == 5) { menu.close(); 
				RozpocznijGre(2); 
				wybor();
				}
				else if (licznik == 6) { menu.close(); 
				RozpocznijGre(3); 
				wybor();
				}
				else if (licznik == 7) {
					licznik = 0;
					naszSprajt.podmianka(licznik);
				}
			}
		}
		menu.clear();
		menu.draw(naszSprajt);
		menu.display();
		
	}
}