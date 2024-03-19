#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;

class Produs
{
	string nume;
	string tip;
	string producator;
	int pret;
public:
	Produs() = default;
	Produs(const string name, const string type, const string producer, int price) : nume{ name }, tip{ type }, producator{ producer }, pret{ price } {}
	//Produs(const Produs& p) :nume{p.nume}, tip{p.tip}, producator{p.producator}, pret{p.pret} {
		//cout << "!!!!!!!!!!!!!!!!!!!!!!\n";*/
	Produs(const Produs& p) : nume{ p.nume }, tip{ p.tip }, producator{ p.producator }, pret{ p.pret } {} // constructor de copiere

	string get_nume() const
	{
		return nume;
	}

	string get_tip() const
	{
		return tip;
	}

	string get_producator() const
	{
		return producator;
	}

	int get_pret() const
	{
		return pret;
	}
};

bool cmpnume(const Produs& p1, const Produs& p2);
/*
	Compara dupa nume
	return: true daca p1.nume e mai mic decat p2.nume
*/

bool cmppret(const Produs& p1, const Produs& p2);
/*
	Compara dupa pret
	return: true daca p1.pret e mai mic decat p2.pret
*/

bool cmpcompus(const Produs& p1, const Produs& p2);
/*
	Compara dupa nume + tip
	return: 1 daca p1.nume e mai mic decat p2.nume (daca sunt egale, returneaza true daca p1.tip e mai mic decat p2.tip
*/