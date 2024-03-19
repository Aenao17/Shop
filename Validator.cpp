#include "Validator.h"
#include <assert.h>
#include <sstream>

void ProdusValidator::validate(const  Produs& p)
{
	vector<string>msgs;
	if (p.get_pret() < 0) msgs.push_back("Pret negativ!");
	if (p.get_nume().size() == 0) msgs.push_back("Nume vid!");
	if (p.get_tip().size() == 0) msgs.push_back("Tip vid!");
	if (p.get_producator().size() == 0) msgs.push_back("Producator vid!");
	if (msgs.size() > 0)
	{
		throw validateException(msgs);
	}
}

ostream& operator<<(ostream& out, const validateException& ex)
{
	for (const auto& msg: ex.msgs)
	{
		out << msg << " ";
	}
	return out;
}

void testValidator()
{
	ProdusValidator v;
	Produs p{ "","","",-1 };
	try
	{
		v.validate(p);
	}
	catch (const validateException& ex)
	{
		std::stringstream sout;
		sout << ex;
		const auto mesaj = sout.str();
		assert(mesaj.find("negativ") >= 0);
		assert(mesaj.find("vid") >= 0);
	}
}