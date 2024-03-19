#include "Cos.h"
#include <fstream>
#include <random>

using std::ofstream;

void Cos::adauga(const Produs& p)
{
	cos.push_back(p);
	notify();
}

void Cos::goleste()
{
	cos.clear();
	notify();
}

void Cos::exp(string nume)
{
	ofstream f(nume);
	f << "<html>";
	f << "<body>";
	f << "<table style=\"border:1px solid black;margin-left:auto;margin-right:auto;\">";
	f << "<tr>";
	f << "<td>" << "Nume" << "</td>";
	f << "<td>" << "Tip" << "</td>";
	f << "<td>" << "Producator" << "</td>";
	f << "<td>" << "Pret" << "</td>";
	f << "</tr>";
	for (const auto& c: cos)
	{
		f << "<tr>";
		f << "<td>" << c.get_nume() << "</td>";
		f << "<td>" << c.get_tip() << "</td>";
		f << "<td>" << c.get_producator() << "</td>";
		f << "<td>" << c.get_pret() << "</td>";
		f << "</tr>";
	}
	f << "</table>";
	f << "</body>";
	f << "</html>";
	f.close();
}

const vector<Produs>& Cos::get_cos() const noexcept
{
	return cos;
}

Cos& Cos::operator=(const Cos& c)
{
	cos = c.cos;
	return *this;
}

void Cos::genereaza_cos(int nr)
{
	cos.clear();
	for (int j = 0; j < nr; j++)
	{
		char v[] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
		string nume = "aaaaaaa";
		string tip = "aaaaaaa";
		string producator = "aaaaaaaaaa";
		int pret = rand() % 100;
		for (int i = 0; i < 5; i++)
		{
			nume[i] = v[rand() % 26];
			tip[i] = v[rand() % 26];
			producator[i] = v[rand() % 26];
		}
		Produs p{ nume,tip,producator,pret };
		cos.push_back(p);
	}
	notify();
}
