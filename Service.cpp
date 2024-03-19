#include "Service.h"
#include <functional>
#include <assert.h>
#include <algorithm>

using std::sort;

vector<Produs>Service::generalSort(bool(*maiMic)(const Produs&, const Produs&))
{
	vector<Produs> v{ rep.get_all() };//facem o copie
	sort(v.begin(), v.end(), maiMic);
	return v;
}

void Service::adauga_produs(const string& nume, const string& tip, const string& producator, int pret)
{
	Produs p{ nume,tip,producator,pret };
	val.validate(p);
	adaugaStatistica(p.get_tip());
	rep.store(p);
	undoActions.push_back(make_unique<UndoAdauga>(rep, p));
}

void Service::sterge_produs(const string& nume, const string& tip, const string& producator, int pret)
{
	Produs p{ nume,tip,producator,pret };
	val.validate(p);
	eliminaStatistica(p.get_tip());
	rep.sterge(p);
	undoActions.push_back(make_unique<UndoSterge>(rep, p));
}

void Service::modifica_produs(const string& nume, const string& tip, const string& producator, int pret, const string& numen, const string& tipn, const string& producatorn, int pretn)
{
	Produs p1{ nume,tip,producator,pret };
	val.validate(p1);
	Produs p2{ numen,tipn,producatorn,pretn };
	val.validate(p2);
	eliminaStatistica(p1.get_tip());
	adaugaStatistica(p2.get_tip());
	rep.modifica(p1, p2);
	undoActions.push_back(make_unique<UndoModifica>(rep, p2, p1));
}

vector<Produs> Service::sortbynume()
{
	return generalSort(cmpnume);
}

vector<Produs> Service::sortbypret()
{

	return generalSort(cmppret);
}

vector<Produs> Service::sortcompus()
{
	return generalSort(cmpcompus);
}

vector<Produs> Service::filtreaza(function<bool(const Produs&)> fct)
{
	vector<Produs> rez;
	for (const auto& produs: rep.get_all())
	{
		if (fct(produs))
		{
			rez.push_back(produs);
		}
	}
	return rez;
}

vector<Produs> Service::filtrarenume(const string& nume)
{
	return filtreaza([nume](const Produs& p) {//functie lambda
		return p.get_nume() == nume;
		});
}

vector<Produs> Service::filtrarepret(int pret)
{
	return filtreaza([pret](const Produs& p) {
		return p.get_pret() == pret;
		});
}

vector<Produs> Service::filtrareproducator(const string& producator)
{
	return filtreaza([producator](const Produs& p) {
		return p.get_producator() == producator;
		});
}

vector<Produs> Service::cautare(const string& nume)
{
	vector<Produs> rez;
	for (const auto& p: rep.get_all())
	{
		if (p.get_nume() == nume)
		{
			rez.push_back(p);
			break;
		}
	}
	return rez;
}

void Service::adauga_cos(const string& nume)
{
	vector<Produs> rez = cautare(nume);
	if (rez.size() == 0)
	{
		throw RepoException("Nu exista produsul cu numele dat!");
	}
	cos.adauga(rez[0]);
}

void Service::goleste_cos()
{
	cos.goleste();
}

void Service::genereaza_cos(int nr)
{
	cos.genereaza_cos(nr);
}

void Service::exporta_cos(const string& nume_fisier)
{
	cos.exp(nume_fisier);
}

void Service::adaugaStatistica(const string& nume)
{
	auto v = stats.find(nume);
	if (v != stats.end())
		v->second++;
	else
		stats.insert(std::make_pair(nume, 1));
}

void Service::eliminaStatistica(const string& nume)
{
	stats[nume]--;
}

map <string, int> Service::getStats()
{
	return stats;
}

void Service::undo()
{
	if (undoActions.empty())
	{
		throw RepoException("Nu se mai poate face undo!");
	}
	undoActions.back()->doUndo();
	undoActions.pop_back();
}

void TestAdauga()
{
	Repo rep;
	ProdusValidator val;
	Cos cos;
	Service serv{ rep, val,cos };
	try
	{
		serv.undo(); assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}
	serv.adauga_produs("Lays", "chips", "Lays Romania", 10);
	assert(serv.getAll().size() == 1);

	try
	{
		serv.adauga_produs("", "", "", -1); assert(false);
	}
	catch (validateException&)
	{
		assert(true);
	}

	try
	{
		serv.adauga_produs("Lays", "chips", "Lays Romania", 10); assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}

	serv.undo();
	assert(serv.getAll().size() == 0);

}

void TestFiltrare()
{
	Repo rep;
	ProdusValidator val;
	Cos cos;
	Service serv{ rep,val,cos };

	serv.adauga_produs("Lays", "chips", "Orbit Romania", 10);
	serv.adauga_produs("Fanta", "suc", "Cola", 5);
	serv.adauga_produs("Fanta", "guma", "Orbit Romania", 5);

	assert(serv.filtrarenume("Fanta").size() == 2);
	assert(serv.filtrarepret(5).size() == 2);
	assert(serv.filtrareproducator("Orbit Romania").size() == 2);
	assert(serv.filtrarenume("Cola").size() == 0);
}

void TestSortare()
{
	Repo rep;
	ProdusValidator val;
	Cos cos;
	Service serv{ rep,val,cos };

	serv.adauga_produs("Lays", "chips", "Lays Romania", 10);
	serv.adauga_produs("Orbit", "suc", "Cola", 5);
	serv.adauga_produs("Orbit", "guma", "Orbit Romania", 7);

	auto primul = serv.sortbynume()[0];
	assert(primul.get_nume() == "Lays");

	primul = serv.sortbypret()[0];
	assert(primul.get_tip() == "suc");

	primul = serv.sortcompus()[1];
	assert(primul.get_tip() == "guma");

	vector<Produs> rez;
	rez = serv.cautare("Lays");
	assert(rez.size() == 1);
	rez = serv.cautare("Chio");
	assert(rez.size() == 0);

	serv.adauga_cos("Lays");
	assert(serv.getAllCos().size() == 1);
	serv.goleste_cos();
	serv.genereaza_cos(2);
	assert(serv.getAllCos().size() == 2);
	serv.exporta_cos("cos.txt");
	Cos d;
	d = cos;
	map< string, int > stats = serv.getStats();
	try
	{
		serv.adauga_cos("Dre");
	}
	catch (RepoException&)
	{
		assert(true);
	}
}

void TestModifica()
{
	Repo rep;
	ProdusValidator val;
	Cos cos;
	Service serv{ rep,val,cos };

	serv.adauga_produs("Lays", "chips", "Lays Romania", 10);
	serv.adauga_produs("Orbit", "suc", "Cola", 5);
	serv.adauga_produs("Orbit", "guma", "Orbit Romania", 7);

	serv.modifica_produs("Orbit", "guma", "Orbit Romania", 7, "Orebit", "suec", "Colllla", 10);
	assert(serv.getAll()[serv.getAll().size() - 1].get_pret() == 10);
	try
	{
		serv.modifica_produs("Orbit", "guma", "Orbit Romania", 7, "Orbit", "suc", "Cola", 10); assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}
	serv.undo();
	assert(serv.getAll()[serv.getAll().size() - 1].get_pret() == 7);
}

void TestSterge()
{
	Repo rep;
	ProdusValidator val;
	Cos cos;
	Service serv{ rep,val,cos };

	serv.adauga_produs("Lays", "chips", "Lays Romania", 10);
	serv.adauga_produs("Orbit", "suc", "Cola", 5);
	serv.adauga_produs("Orbit", "guma", "Orbit Romania", 7);

	assert(serv.getAll().size() == 3);

	serv.sterge_produs("Orbit", "suc", "Cola", 5);

	assert(serv.getAll().size() == 2);

	try
	{
		serv.sterge_produs("ceva", "ceva", "nimic", 10); assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}

	serv.undo();
	assert(serv.getAll().size() == 3);
}

void testService()
{
	TestAdauga();
	TestFiltrare();
	TestSortare();
	TestModifica();
	TestSterge();
}