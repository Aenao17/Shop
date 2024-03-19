#include "Produs.h"

bool cmpnume(const Produs& p1, const Produs& p2)
{
	return p1.get_nume() < p2.get_nume();
}

bool cmppret(const Produs& p1, const Produs& p2)
{
	return p1.get_pret() < p2.get_pret();
}

bool cmpcompus(const Produs& p1, const Produs& p2)
{
	if (p1.get_nume() == p2.get_nume())
		return p1.get_tip() < p2.get_tip();
	return p1.get_nume() < p2.get_nume();
}