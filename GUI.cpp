#include "GUI.h"
#include <qdebug.h>
#include <qpalette.h>
#include <qcolor.h>

void Gui::InitGuiCmps()
{
	setLayout(lymain);

	msg = new QMessageBox;

	/*lst = new QListWidget;
	lymain->addWidget(lst);*/
	tabel->setModel(model);
	lymain->addWidget(tabel);

	QVBoxLayout* lydreapta = new QVBoxLayout;

	txtnume = new QLineEdit;
	txttip = new QLineEdit;
	txtproducator = new QLineEdit;
	txtpret = new QLineEdit;
	
	QFormLayout* form = new	QFormLayout;
	form->addRow("Nume", txtnume);
	form->addRow("Tip", txttip);
	form->addRow("Producator",txtproducator);
	form->addRow("Pret",txtpret);
	
	QVBoxLayout* lybtns = new QVBoxLayout;

	lybtns->addLayout(form);
	
	adauga_produs = new QPushButton("Adauga");
	lybtns->addWidget(adauga_produs);
	
	sterge_produs = new QPushButton("Sterge");
	lybtns->addWidget(sterge_produs);

	modifica_produs = new QPushButton("Modifica");
	lybtns->addWidget(modifica_produs);

	filtreaza = new QPushButton("Filtreaza");
	lybtns->addWidget(filtreaza);

	sorteaza = new QPushButton("Sorteaza");
	lybtns->addWidget(sorteaza);

	undo = new QPushButton("Undo");
	lybtns->addWidget(undo);

	adauga_cos = new QPushButton("Adauga in cos");
	lybtns->addWidget(adauga_cos);

	optiuni_cos = new QPushButton("Optiuni cos");
	lybtns->addWidget(optiuni_cos);

	new_cos = new QPushButton("Cos Crud nou");
	lybtns->addWidget(new_cos);

	new_r_cos = new QPushButton("Cos RONLY nou");
	lybtns->addWidget(new_r_cos);

	exit = new QPushButton("Exit");
	lybtns->addWidget(exit);

	//genereaza = new QPushButton("Genereaza");
	//lybtns->addWidget(genereaza);

	table = new QPushButton("Table view");
	//lybtns->addWidget(table);
	
	lymain->addLayout(lybtns);
}

void Gui::ConnectSignalsSlots()
{
	//adauga produs
	QObject::connect(adauga_produs, &QPushButton::clicked, [&](){
		
		QString qnume = txtnume->text();
		QString qtip = txttip->text();
		QString qprod = txtproducator->text();
		QString qpret = txtpret->text();

		string nume = qnume.toStdString();
		string tip = qtip.toStdString();
		string prod = qprod.toStdString();
		int pret = qpret.toInt();
		try
		{
			serv.adauga_produs(nume, tip, prod, pret);
		}
		catch (RepoException& ex)
		{
			Exception(ex.getMsg());
		}
		catch (validateException& ex)
		{
			for (const auto& p : ex.getMsg())
				Exception(p);
		}
		ReloadList(serv.getAll());
		txtnume->setText("");
		txttip->setText("");
		txtproducator->setText("");
		txtpret->setText("");
		});

	
	//exit
	QObject::connect(exit, &QPushButton::clicked, [&]()
		{
			this->close();
		});

	//sterge produs
	QObject::connect(sterge_produs, &QPushButton::clicked, [&]() {

		QString qnume = txtnume->text();
		QString qtip = txttip->text();
		QString qprod = txtproducator->text();
		QString qpret = txtpret->text();

		string nume = qnume.toStdString();
		string tip = qtip.toStdString();
		string prod = qprod.toStdString();
		int pret = qpret.toInt();

		try
		{
			serv.sterge_produs(nume, tip, prod, pret);
			ReloadList(serv.getAll());
		}
		catch (RepoException& ex)
		{
			Exception(ex.getMsg());
		}
		catch (validateException& ex)
		{
			for (const auto& p : ex.getMsg())
				Exception(p);
		}
		});

	//undo
	QObject::connect(undo, &QPushButton::clicked, [&]()
		{
			try
			{
				serv.undo();
				ReloadList(serv.getAll());
			}
			catch (RepoException& ex)
			{
				Exception(ex.getMsg());
			}
		});

	//adauga_cos
	QObject::connect(adauga_cos, &QPushButton::clicked, [&]() {
		QString qnume = txtnume->text();
		QString qtip = txttip->text();
		QString qprod = txtproducator->text();
		QString qpret = txtpret->text();

		string nume = qnume.toStdString();
		string tip = qtip.toStdString();
		string prod = qprod.toStdString();
		int pret = qpret.toInt();

		serv.adauga_cos(nume);

		txtnume->setText("");
		txttip->setText("");
		txtproducator->setText("");
		txtpret->setText("");
		});
	//optiuni cos
	QObject::connect(optiuni_cos, &QPushButton::clicked, [&]() {
		CosUi* gui = new CosUi{ serv };
		gui->show();
		});

	/*//genereaza butoane
	QObject::connect(genereaza, &QPushButton::clicked, [&]() {

		map<string, int> stats = serv.getStats();
		vector<QPushButton*>btnlist;
		int k = 0;
		for (const auto& p : stats)
		{
			QPushButton* btn = new QPushButton(QString::fromStdString(p.first));
			btnlist.push_back(btn);
			lymain->addWidget(btnlist[k]);
			int a = p.second;
			QObject::connect(btnlist[k], &QPushButton::clicked, [&, a]() {
				auto aa = QString::number(a);
				msg->setText(aa);
				msg->show();
				});
			k++;
		}
		});*/

	//modifica
	QObject::connect(modifica_produs, &QPushButton::clicked, [&]() {
		
		QString qnume = txtnume->text();
		QString qtip = txttip->text();
		QString qprod = txtproducator->text();
		QString qpret = txtpret->text();

		string nume = qnume.toStdString();
		string tip = qtip.toStdString();
		string prod = qprod.toStdString();
		int pret = qpret.toInt();

		GuiModifica* gui = new GuiModifica{ serv,nume,tip,prod,pret };
		gui->show();
		ReloadList(serv.getAll());
		txtnume->setText("");
		txttip->setText("");
		txtproducator->setText("");
		txtpret->setText("");
		});

	//sorteaza
	QObject::connect(sorteaza, &QPushButton::clicked, [&]() {
		auto bt = new QVBoxLayout;
		auto by_nume = new QPushButton("Sort by nume");
		auto by_pret = new QPushButton("Sort by pret");
		auto by_compus = new QPushButton("Multiple sort");
		auto exit1 = new QPushButton("Exit");
		bt->addWidget(by_nume);
		bt->addWidget(by_pret);
		bt->addWidget(by_compus);
		bt->addWidget(exit1);
		lymain->addLayout(bt);
		QObject::connect(exit1, &QPushButton::clicked, [exit1,by_nume,by_pret,by_compus, bt]() {
			delete by_nume;
			delete by_pret;
			delete by_compus;
			delete bt;
			delete exit1;
			});
		QObject::connect(by_nume, &QPushButton::clicked, [&]() {
			ReloadList(serv.sortbynume());
			});
		QObject::connect(by_pret, &QPushButton::clicked, [&]() {
			ReloadList(serv.sortbypret());
			});
		QObject::connect(by_compus, &QPushButton::clicked, [&]() {
			ReloadList(serv.sortcompus());
			});
		});

	//filtreaza
	QObject::connect(filtreaza, &QPushButton::clicked, [&]() {
		auto ly = new QVBoxLayout;
		auto txt = new QLineEdit;
		txt = new QLineEdit;
		QFormLayout* f = new QFormLayout;
		f->addRow("Text", txt);

		ly->addLayout(f);
		auto n = new QPushButton("Dupa nume");
		auto p = new QPushButton("Dupa pret");
		auto pp = new QPushButton("Dupa producator");
		auto exit1 = new QPushButton("Exit");
		ly->addWidget(n);
		ly->addWidget(p);
		ly->addWidget(pp);
		ly->addWidget(exit1);
		lymain->addLayout(ly);
		QObject::connect(exit1, &QPushButton::clicked, [exit1, n, p, pp, f, txt, ly]() {
			delete n;
			delete p;
			delete pp;
			f->removeRow(txt);
			delete f;
			delete ly;
			delete exit1;
			});
		QObject::connect(n, &QPushButton::clicked, [&,txt]() {
			string g = txt->text().toStdString();
			ReloadList(serv.filtrarenume(g));
			});
		QObject::connect(p, &QPushButton::clicked, [&,txt]() {
			int g = txt->text().toInt();
			ReloadList(serv.filtrarepret(g));
			});
		QObject::connect(pp, &QPushButton::clicked, [&,txt]() {
			string g = txt->text().toStdString();
			ReloadList(serv.filtrareproducator(g));
			});
		});

	//table view
	QObject::connect(table, &QPushButton::clicked, [&]() {
		Gui2* gui  = new Gui2{ serv };
		gui->show();
		});

	QObject::connect(new_cos, &QPushButton::clicked, [&]() {
		auto gui = new CosCRUDGUI{ serv.getCos() };
		gui->show();
		});
	
	QObject::connect(new_r_cos, &QPushButton::clicked, [&]() {
		auto gui = new CosReadOnlyGUI(serv.getCos());
		gui->show();
		});

	QObject::connect(tabel->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
		if (tabel->selectionModel()->selectedIndexes().isEmpty()) {
			txtnume->setText("");
			txttip->setText("");
			txtpret->setText("");
			txtproducator->setText("");
			return;
		}

		int selected_row = tabel->selectionModel()->selectedIndexes().at(0).row();
		auto first_cel = tabel->model()->index(selected_row, 0);
		auto second_cel = tabel->model()->index(selected_row, 1);

		auto name = tabel->model()->data(first_cel, Qt::DisplayRole).toString();
		auto producer = tabel->model()->data(second_cel, Qt::DisplayRole).toString();

		txtnume->setText(name);
		txtproducator->setText(producer);
		auto produs = serv.cautare(name.toStdString());
		txtpret->setText(QString::number(produs[0].get_pret()));
		txttip->setText(QString::fromStdString(produs[0].get_tip()));
		});
}

void Gui::ReloadList(const vector<Produs>& lista)
{
	//lst->clear();
	//for (const auto& p : lista)
	//{
	//	QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(p.get_nume()));
	//	lst->addItem(item);
	//}
	model->setProduct(lista);
}

void Gui::Exception(const string& m)
{
	QMessageBox::warning(this, "Warning", QString::fromStdString(m));
}

void CosUi::init()
{
	lymain = new QHBoxLayout;
	setLayout(lymain);
	
	lst = new QListWidget;
	lymain->addWidget(lst);

	lys = new QVBoxLayout;
	lymain->addLayout(lys);

	txt = new QLineEdit;
	auto form = new QFormLayout;
	form->addRow("Text", txt);
	lys->addLayout(form);

	goleste = new QPushButton("Goleste cos");
	lys->addWidget(goleste);

	genereaza = new QPushButton("Genereaza cos");
	lys->addWidget(genereaza);

	exporta = new QPushButton("Exporta cos");
	lys->addWidget(exporta);

	exit = new QPushButton("Exit");
	lys->addWidget(exit);
}

void CosUi::ReloadCos(const vector<Produs>& cos)
{
		lst->clear();
		for (const auto& p : cos)
		{
			QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(p.get_nume()));
			lst->addItem(item);
		}
}

void CosUi::connect()
{
	QObject::connect(exit, &QPushButton::clicked, [&]() {
		this->close();
		});
	QObject::connect(goleste, &QPushButton::clicked, [&]() {
		serv.goleste_cos();
		ReloadCos(serv.getAllCos());
		});
	QObject::connect(genereaza, &QPushButton::clicked, [&]() {
		int cate = txt->text().toInt();
		if (cate != 0)
		{
			serv.genereaza_cos(cate);
		}
		ReloadCos(serv.getAllCos());
		});
	QObject::connect(exporta, &QPushButton::clicked, [&]() {
		string fisier = txt->text().toStdString();
		if (fisier != "")
		{
			serv.exporta_cos(fisier);
		}
		});
}

void GuiModifica::init() {
	
	lymain = new QVBoxLayout;
	setLayout(lymain);

	txttip = new QLineEdit;
	txtpro = new QLineEdit;
	txtpret = new QLineEdit;
	QFormLayout* f = new QFormLayout;
	f->addRow("Tip nou", txttip);
	f->addRow("Producator nou", txtpro);
	f->addRow("Pret nou", txtpret);

	lymain->addLayout(f);

	salveaza = new QPushButton("Salveaza");
	lymain->addWidget(salveaza);
}

void GuiModifica::connect() {
	
	QObject::connect(salveaza, &QPushButton::clicked, [&]() {
		QString qtip = txttip->text();
		QString qprod = txtpro->text();
		QString qpret = txtpret->text();

		string tipn = qtip.toStdString();
		string pron = qprod.toStdString();
		int pretn = qpret.toInt();

		if (tipn == "" && pron == "" && pret == 0)
		{
			Exception("Eroare!");
		}
		if (tipn == "")
		{
			tipn = tip;
		}
		if (pron == "") 
		{
			pron = pro;
		}
		if (pretn == 0)
		{
			pretn = pret;
		}

		try {
			serv.modifica_produs(nume, tip, pro, pret, nume, tipn, pron, pretn);
		}
		catch (RepoException& ex)
		{
			Exception(ex.getMsg());
		}
		catch (validateException& ex)
		{
			for (const auto& p : ex.getMsg())
				Exception(p);
		}
		this->close();
		});
}

void GuiModifica::Exception(const string& m)
{
	QMessageBox::warning(this, "Warning", QString::fromStdString(m));
}

void Gui2::init()
{
	lymain = new QHBoxLayout;
	setLayout(lymain);
	table = new QTableWidget;
	lymain->addWidget(table);
	auto v = serv.getAll();

	table->setRowCount(v.size());
	table->setColumnCount(4);
	int i = 0;
	table->setHorizontalHeaderItem(0, new QTableWidgetItem("Nume"));
	table->setHorizontalHeaderItem(1, new QTableWidgetItem("Tip"));
	table->setHorizontalHeaderItem(2, new QTableWidgetItem("Producator"));
	table->setHorizontalHeaderItem(3, new QTableWidgetItem("Pret"));
	for (const auto& p : v)
	{
		table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(p.get_nume())));
		table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(p.get_tip())));
		table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(p.get_producator())));
		table->setItem(i, 3, new QTableWidgetItem(QString::number(p.get_pret())));
		i++;
	}
	exit = new QPushButton("Exit");
	lymain->addWidget(exit);
}

void Gui2::connect()
{
	QObject::connect(exit, &QPushButton::clicked, [&]() {
		this->close();
		});
}

void CosCRUDGUI::init()
{
	lymain = new QHBoxLayout;
	setLayout(lymain);

	lst = new QListWidget;
	lymain->addWidget(lst);

	auto btns = new QVBoxLayout;

	lymain->addLayout(btns);

	gol = new QPushButton("Golire cos");
	btns->addWidget(gol);

	gen = new QPushButton("Genereaza cos");
	btns->addWidget(gen);

	exit = new QPushButton("Exit");
	btns->addWidget(exit);
}

void CosCRUDGUI::ReloadList(const vector<Produs>& lista)
{
	lst->clear();
	for (const auto& p : lista)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(p.get_nume()));
		lst->addItem(item);
	}
}

void CosCRUDGUI::connect()
{
	cos.AddObserver(this);
	QObject::connect(gol, &QPushButton::clicked, [&]() {
		cos.goleste();
		ReloadList(cos.get_cos());
		});
	QObject::connect(gen, &QPushButton::clicked, [&]() {
		cos.genereaza_cos(rand()%20);
		ReloadList(cos.get_cos());
		});
	QObject::connect(exit, &QPushButton::clicked, [&]() {
		this->close();
		});
}