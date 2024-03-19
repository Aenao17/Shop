#pragma once
#include "Produs.h"
#include <string>
#include <vector>
#include <ostream>

using std::string;
using std::ostream;
using std::vector;

class Repo
{
protected:
	vector<Produs> lista;
	bool exist(const Produs& p) const;
	/*
	functie privata ce verifica daca p exista deja in repository
	*/
public:
	Repo() = default;
	//nu permitem copierea de obiecte
	Repo(const Repo& repo) = delete;

	void store(const Produs& p);
	/*
	Salvare produs
	arunca exceptie daca mai exista un produs cu acelasi tip, nume si producator
	*/

	void sterge(const Produs& p);
	/*
	Sterge produs
	arunca exceptie produsul nu exista in baza de date
	*/

	void modifica(Produs& p, const Produs& p2);
	/*
	Modifica un produs
	arunca exceptie produsul nu exista in baza de date
	*/

	const Produs& find(string nume, string tip, string producator) const;
	/*
	Cauta
	arunca exceptie daca nu exista produs
	*/

	const vector <Produs>& get_all() const noexcept;
	/*
	returneaza toate produsele salvate
	*/
};

/*
	Folosit pentru a semnala situatii exceptionale care pot aparea in repo
*/
class RepoException
{
	string msg;
public:
	RepoException(string m) : msg{ m } {}
	string getMsg()
	{
		return msg;
	}	
	friend ostream& operator<<(ostream& out, const RepoException& ex);
};

ostream& operator<<(ostream& out, const RepoException& ex);

void testeRepo();