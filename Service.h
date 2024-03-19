#pragma once

#include "Repository.h"
#include "Validator.h"
#include <string>
#include <vector>
#include <functional>
#include "Cos.h"
#include "Undo.h"
#include <map>

using std::function;
using std::map;
using std::make_unique;
using std::unique_ptr;

class Service
{
	Repo& rep;
	ProdusValidator& val;
	Cos& cos;
	map<string, int> stats;
	vector<unique_ptr<UndoAction>> undoActions;

	vector<Produs> generalSort(bool (*maiMic)(const Produs&, const Produs&));
	/*
		Functie de sortare generala
		maiMic - functie ce compara doua obiecte de tip Produs
		returneaza o lista sortata dupa un criteriu dat ca parametru
	*/
	vector<Produs> filtreaza(function<bool(const Produs&)> fct);
	/*
		Functie generala de filtrare
		returneaza doar produsele care trec de filtru (fct(produs) == true)
	*/
public:
	Service(Repo& rep, ProdusValidator& val, Cos& cos) : rep{ rep }, val{ val }, cos{ cos } {}

	Service(const Service& serv) = delete; //nu permitem copierea de obiecte Service

	const vector<Produs>& getAll() noexcept
	{
		/*
			returneaza toate produsele in ordinea adaugarii
		*/
		return rep.get_all();
	}

	const vector<Produs>& getAllCos() noexcept
	{
		/*
			returneaza toate produsele din cos
		*/
		return cos.get_cos();
	}

	void adauga_produs(const string& nume, const string& tip, const string& producator, int pret);
	/*
		Adauga un produs nou
		arunca exceptie daca nu se poate salva sau nu este valid
	*/

	void sterge_produs(const string& nume, const string& tip, const string& producator, int pret);
	/*
		Sterge un produs
		arunca exceptie daca produsul nu exista in baza de date
	*/

	void modifica_produs(const string& nume, const string& tip, const string& producator, int pret, const string& numen, const string& tipn, const string& producatorn, int pretn);
	/*
		Modifica un produs existent
		arunca exceptie daca produsul nu exista in baza de date sau datele introduse nu sunt valide
	*/

	void goleste_cos();
	/*
		Goleste cosul
	*/

	void adauga_cos(const string& nume);
	/*
		Adauga un produs in cos
	*/

	void genereaza_cos(int nr);
	/*
		Genereaza un cos cu nr produse
	*/

	void exporta_cos(const string& numeFisier);
	/*
		Exporta cosul in fisier
	*/

	vector<Produs> sortbynume();
	/*
		Sorteaza dupa nume
	*/

	vector<Produs> sortbypret();
	/*
		Sorteaza dupa pret
	*/

	vector<Produs> sortcompus();
	/*
		Sorteaza dupa nume si tip;
	*/

	vector<Produs> filtrarepret(int pret);
	/*
		Filtreaza dupa pret
	*/

	vector<Produs> filtrareproducator(const string& producator);
	/*
		Filtreaza dupa producator
	*/

	vector<Produs> filtrarenume(const string& nume);
	/*
		Filtreaza dupa nume
	*/

	vector<Produs> cautare(const string& nume);
	/*
		returneaza o lista cu obiectul cautat
	*/

	void adaugaStatistica(const string& nume);
    /*
		Adauga o statistica
	*/

	map<string, int> getStats();
	/*
		returneaza toate statisticile
	*/

	void eliminaStatistica(const string& nume);
	/*
		Elimina o statistica
	*/

	void undo();
	/*
		Face undo la ultima operatie
	*/
	Cos& getCos()
	{
		return cos;
	}
};

void testService();