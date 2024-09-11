#include "table.h"
#include <fstream>
#include <iostream>
#include <string>
int main()
{
	table<int, std::string> tabel;

	std::ifstream fin("date.txt");
	int key;
	std::string cuv;

	while (fin >> key >> cuv) {
		tabel.insertie(key, cuv);
	}
	fin.close();
	std::cout << "sunt";

	//table<int, std::string>::iterator;
	//tabel.afis();

	int contor = 0;
	std::cout << "1. inserati o pereche noua" << std::endl;
	std::cout << "2. cautati dupa cheie" << std::endl;
	std::cout << "3. cautati dupa cheie si valoare" << std::endl;
	std::cout << "4. stergeti un elem" << std::endl;
	std::cout << "5. verificati valoarea dintr-o cheie data" << std::endl;
	std::cout << "6. Afisare tabel" << std::endl;
	std::cout << "7. Afisare tabel folosind iterator" << std::endl;
	std::cout << "8. terminat" << std::endl;
	int comanda;
	while (contor != 1)
	{
		std::cout << std::endl;
		std::cout << "introduceti o comanda noua: ";
		std::cin >> comanda;
		int key1;
		std::string cuv1;
		switch (comanda)
		{
		case 1:
			std::cout << "introduceti cheia si valoarea: ";
			std::cin >> key1;
			std::cin >> cuv1;
			tabel.insertie(key1, cuv1);
			break;
		case 2:
			std::cout << "introduceti cheia cautata: ";
			std::cin >> key1;
			if (tabel.cautareKey(key1))
				std::cout << "Cheia a fost gasita" << std::endl;
			else
				std::cout << "Cheia nu a fost gasita" << std::endl;
			break;
		case 3:
			std::cout << "introduceti cheia si valoarea cautata: ";
			std::cin >> key1 >> cuv1;
			if (tabel.cautare(key1, cuv1))
				std::cout << "Cheia si valoarea au fost gasite" << std::endl;
			else
				std::cout << "Cheia si valoarea nu au fost gasite" << std::endl;
			break;
		case 4:
			std::cout << "introduceti perechea pe care doriti sa o stergeti: ";
			std::cin >> key1 >> cuv1;
			tabel.stergere(key1);
			break;
		case 5:
			std::cout << "introduceti o cheie: ";
			std::cin >> key1;
			try {
				std::string rez = tabel[key1];
				std::cout << "valuarea din cheia data este: " << rez << std::endl;
			}
			catch (const std::runtime_error& e) {
				std::cout << "Erroare: " << e.what() << std::endl;
			}
			break;
		case 6:
			tabel.print();
			break;
		case 7:
			std::cout << "toate elementele din tabel sunt: ";
			/*for (auto it = tabel.begin(); it != tabel.end(); ++it) {
				std::cout << (*it).first << "," << (*it).second << " ";
			}*/
			break;
		case 8:
			contor = 1;
			std::cout << "sfarsit de program" << std::endl;
			break;
		default:
			std::cout << "Aceasta comanda nu exista" << std::endl;
			break;
		}
	}
	return 0;
}