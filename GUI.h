#pragma once
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qmessagebox.h>
#include <qtableview.h>
#include <QtWidgets/qtablewidget.h>
#include "Service.h"
#include "Observer.h"
#include <qpainter>
#include <qimage.h>
#include <qpicture.h>
#include <qwidget.h>
#include <qapplication.h>
#include "MyTableModel.h"

class Gui : public QWidget {
protected:
	Service& serv;
	QHBoxLayout* lymain = new QHBoxLayout;
	QListWidget* lst;
	CustomTableModel* model = new CustomTableModel{ serv.getAll() };
	QTableView* tabel = new QTableView;
	QMessageBox* msg;
	QLineEdit* txtnume;
	QLineEdit* txttip;
	QLineEdit* txtproducator;
	QLineEdit* txtpret;
	QPushButton* adauga_produs;
	QPushButton* sterge_produs;
	QPushButton* modifica_produs;
	QPushButton* filtreaza;
	QPushButton* sorteaza;
	QPushButton* undo;
	QPushButton* exit;
	QPushButton* adauga_cos;
	QPushButton* optiuni_cos;
	QPushButton* table;
	QPushButton* new_cos;
	QPushButton* new_r_cos;
	//QPushButton* genereaza;
	
	void InitGuiCmps();
	void ConnectSignalsSlots();
	void ReloadList(const vector<Produs>& lista);
	void Exception(const string& m);

public:
	Gui(Service& srv) : serv{ srv } {
		InitGuiCmps();
		ConnectSignalsSlots();
		ReloadList(serv.getAll());
	}
};

class CosUi : public QWidget
{
private:
	Service& serv;
	QHBoxLayout* lymain;
	QVBoxLayout* lys;
	QListWidget* lst;
	QPushButton* exit;
	QPushButton* goleste;
	QPushButton* genereaza;
	QPushButton* exporta;
	QLineEdit* txt;
	void init();
	void ReloadCos(const vector<Produs>& cos);
	void connect();

public:
	CosUi(Service& serv) : serv{ serv } {
		init();
		ReloadCos(serv.getAllCos());
		connect();
	}
};

class GuiModifica : public QWidget
{
private:
	Service& serv;
	string nume;
	string tip;
	string pro;
	int pret;
	QVBoxLayout* lymain;
	QLineEdit* txttip;
	QLineEdit* txtpro;
	QLineEdit* txtpret;
	QPushButton* salveaza;
	void init();
	void connect();
	void Exception(const string& m);
public:
	GuiModifica(Service& serv, string nume, string tip, string pro, int pret) : serv{ serv }, nume{ nume }, tip{ tip }, pro{ pro }, pret{ pret } {
		init();
		connect();
	}
};

class Gui2 : public QWidget
{
private:
	QHBoxLayout* lymain;
	Service& serv;
	QTableWidget* table;
	QPushButton* exit;
	void init();
	void connect();
	public:
		Gui2(Service& serv) :serv{ serv } {
			init();
			connect();
		};
};

class CosCRUDGUI : public QWidget, public Observer
{
	QHBoxLayout* lymain;
	QListWidget* lst;
	QPushButton* gol;
	QPushButton* gen;
	QPushButton* exit;
	Cos& cos;
	void init();
	void connect();
	void ReloadList(const vector<Produs>& cos);
public:
	CosCRUDGUI(Cos& serv) : cos{ serv } {
		init();
		connect();
		ReloadList(cos.get_cos());
	}

	void update() override {
		ReloadList(cos.get_cos());
	}

	~CosCRUDGUI()
	{
		cos.RemoveObserver(this);
	}
};

class CosReadOnlyGUI : public QWidget, public Observer
{
	Cos& cos;
	void init();
	void ReloadList(const vector<Produs>& cos);
public:
	CosReadOnlyGUI(Cos& cos) : cos{ cos } {
		cos.AddObserver(this);
	}

	void paintEvent(QPaintEvent* ev) override {

		QPainter p{ this };
		int n = cos.get_cos().size();
		int x = 0, y = 0, cate = 0;
		p.drawEllipse(10, 10, 10, 10);
		for (int i = 1; i <= n; i++)
		{
			p.drawImage(x, y, QImage("buna.png"));
			x += 120;
			cate++;
			if (cate == 5)
			{
				cate = 0;
				x = 0;
				y = y + 120;
			}
		}
	}
	void update() override {
		repaint();
	}
	~CosReadOnlyGUI()
	{
		cos.RemoveObserver(this);
	}
};