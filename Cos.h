#pragma once
#include "Produs.h"
#include "Observer.h"
#include <vector>
#include <string>

using std::vector;

class Cos : public Observable
{
	vector<Produs> cos;
public:
	Cos() = default;
	Cos(const vector<Produs>& v) : cos{ v } {}
	Cos(const Cos& c) : cos{ c.cos } {}
	Cos& operator=(const Cos& c);
	void adauga(const Produs& p);
	void goleste();
	void exp(string nume);
	void genereaza_cos(int nr);
	const vector<Produs>& get_cos() const noexcept;
};