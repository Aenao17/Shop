#pragma once
#include <string>
#include <vector>
#include "Repository.h"

using std::string;
using std::ostream;

class validateException
{
	vector<string>msgs;
public:
	validateException(const vector<string>& errors) : msgs{ errors } {};
	vector<string> getMsg()
	{
		return this->msgs;
	}
	friend ostream& operator<<(ostream& out, const validateException& ex);
};

ostream& operator<<(ostream& out, const validateException& ex);

class ProdusValidator
{
public:
	void validate(const Produs& p);
};

void testValidator();