#pragma once
#include "Service.h"

class UndoAction {
public:
	virtual void doUndo() {};  virtual ~UndoAction() {};
};

class UndoAdauga : public UndoAction {
private:
	Produs produsAdaugat;
	Repo& rep;
public:
	UndoAdauga(Repo& rep, const Produs& p) : rep{ rep }, produsAdaugat{ p } {}
	void doUndo() override {
		rep.sterge(produsAdaugat);
	}
};

class UndoSterge : public UndoAction {
private:
	Produs produsSters;
	Repo& rep;
public:
	UndoSterge(Repo& rep, const Produs& p) : rep{ rep }, produsSters{ p } {}
	void doUndo() override {
		rep.store(produsSters);
	}
};

class UndoModifica : public UndoAction {
private:
	Produs produsModificat;
	Produs ProdusVechi;
	Repo& rep;
public:
	UndoModifica(Repo& rep, const Produs& p1, const Produs& p2) : rep{ rep }, produsModificat{ p1 }, ProdusVechi{ p2 } {}
	void doUndo() override {
		rep.modifica(produsModificat, ProdusVechi);
	}
};