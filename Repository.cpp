#include "Repository.h"
#include <assert.h>
#include <iostream>
#include <sstream>

using std::ostream;
using std::stringstream;

void Repo::store(const Produs& p)
{
	if (exist(p))
	{
		throw RepoException("Exista deja un produs cu aceste date!");
	}
	lista.push_back(p);
}

void Repo::sterge(const Produs& p)
{
	if (!exist(p))
	{
		throw RepoException("Produsul nu exista in baza de date!");
	}
	vector <Produs> nou;
	for (const auto& pro: lista)
	{
		if (!(pro.get_nume() == p.get_nume() && pro.get_pret() == p.get_pret()))
		{
			nou.push_back(pro);
		}
	}
	lista.clear();
	lista= nou;
}

void Repo::modifica(Produs& p, const Produs& p2)
{
	if (!exist(p))
	{
		throw RepoException("Produsul nu exista in baza de date!");
	}
	sterge(p);
	store(p2);
}

bool Repo::exist(const Produs& p) const
{
	try {
		find(p.get_nume(), p.get_tip(), p.get_producator());
		return true;
	}
	catch (RepoException&)
	{
		return false;}
}

const Produs& Repo::find(string nume, string tip, string producator) const
{
	for (const auto& p: lista)
	{
		if (p.get_nume() == nume && p.get_tip() == tip && p.get_producator() == producator)
		{
			return p;
		}
	}
	throw RepoException("Nu exista acest produs!");}

const vector<Produs>& Repo::get_all() const noexcept
{
	return lista;
}

ostream& operator<<(ostream& out, const RepoException& ex) {
	out << ex.msg;
	return out;
}





void testAdauga()
{
	Repo rep;
	rep.store(Produs{ "Coca Cola", "suc", "The Coca Cola Company", 5 });
	assert(rep.get_all().size() == 1);
	assert(rep.find("Coca Cola", "suc", "The Coca Cola Company").get_pret() == 5);

	rep.store(Produs{ "Pepsi", "suc", "Pepsico", 5 });
	rep.store(Produs{ "Pepsi", "suc1", "Pepsico", 1 });
	rep.store(Produs{ "Pepsi", "suc2", "Pepsico", 2 });
	rep.store(Produs{ "Pepsi", "suc3", "Pepsico", 3 });
	rep.store(Produs{ "Pepsi", "suc4", "Pepsico", 4 });
	rep.store(Produs{ "Pepsi", "suc5", "Pepsico", 6 });
	rep.store(Produs{ "Pepsi", "suc6", "Pepsico", 7 });
	rep.store(Produs{ "Pepsi", "suc8", "Pepsico", 8 });
	rep.store(Produs{ "Pepsi", "suc7", "Pepsico", 9 });
	rep.store(Produs{ "Pepsi", "suc9", "Pepsico", 10 });
	assert(rep.get_all().size() == 11);

	try {
		rep.store(Produs{ "Coca Cola", "suc", "The Coca Cola Company", 5 }); assert(false);
	}
	catch (const RepoException&) {
		assert(true);
	}

	try
	{
		rep.find("Fanta", "suc", "Fanta"); assert(false);
	}
	catch (const RepoException& e)
	{
		stringstream os;
		os << e;
		assert(os.str().find("exista") >= 0);
	}
}

void testCauta()
{
	Repo rep;
	rep.store(Produs{ "Coca Cola", "suc", "The Coca Cola Company", 5 });
	rep.store(Produs{ "Pepsi", "suc", "Pepsico", 5 });

	Produs p = rep.find("Coca Cola", "suc", "The Coca Cola Company");
	assert(p.get_nume() == "Coca Cola");
	assert(p.get_pret() == 5);
	assert(p.get_producator() == "The Coca Cola Company");
	assert(p.get_tip() == "suc");

	try
	{
		rep.find("CCC", "suc", "dsadas"); assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}
}

void testSterge()
{
	Repo rep;
	rep.store(Produs{ "Coca Cola", "suc", "The Coca Cola Company", 5 });
	rep.store(Produs{ "Pepsi", "suc", "Pepsico", 5 });

	Produs p = Produs{ "Pepsi", "suc", "Pepsico", 5 };

	rep.sterge(p);

	assert(rep.get_all().size() == 1);
	try
	{
		p = Produs{ "Pepsi", "ceva", "Pep", 5 };
		rep.sterge(p); assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}
}

void testModifica()
{
	Repo rep;
	Produs p1 = Produs{ "Coca Cola", "suc", "The Coca Cola Company", 5 };
	Produs p2 = Produs{ "Pepsi", "suc", "Pepsico", 5 };
	Produs p3 = Produs{ "ceva", "ceva", "nimic", 0 };

	rep.store(p1);
	rep.modifica(p1, p2);
	assert(rep.get_all()[0].get_nume() == "Pepsi");
	try
	{
		rep.modifica(p3, p2); assert(false);
	}
	catch (RepoException& ex)
	{
		string msg = ex.getMsg();
		assert(true);
	}
}

void testeRepo()
{
	testAdauga();
	testCauta();
	testSterge();
	testModifica();
}