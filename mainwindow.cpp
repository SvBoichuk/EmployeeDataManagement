#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QRegExp>
#include <QPdfWriter>
#include <QPainter>
#include <QVariant>
#include <exception>

#define MAX_COLUMN 6
#define DB_NAME "task_lbtz"
#define DB_PASS "mysqlpass"
#define DB_TABLE_NAME "staff"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->value_le->setReadOnly(true);
    this->setFixedSize(640,360);

	try {
		db = new DataBase(QString(DB_NAME), QString(DB_PASS));
	}
	catch (const DBException& exc)
	{
		QMessageBox::critical(this, "Error", QString(exc.what()));
	}

	GetTables();
	GetTableHeaders(tables.at(0));

    /*Setup table setting*/
    ui->tableWidget->setColumnCount(titles_lbl.size());
    RestorLabels();

    int width = ui->tableWidget->width() / ui->tableWidget->columnCount() - 3;
    for(int i = 0 ; i < ui->tableWidget->columnCount(); i++)
    {
        ui->tableWidget->setColumnWidth(i,width);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    ui->value_le->clear();

    if(arg1 == "Name" || arg1 == "Surname") {
        ui->value_le->setReadOnly(false);
        ui->value_le->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z]{1,32}"),this));
    }
    else if(arg1 == "Rang" || arg1 == "Shop number") {
        ui->value_le->setReadOnly(false);
        ui->value_le->setValidator(new QRegExpValidator(QRegExp("[0-9]{4,8}"),this));
    }
    else {
        ui->value_le->setReadOnly(true);
    }
}

void MainWindow::on_search_btn_clicked()
{
    vct.clear();
    ui->tableWidget->clear();

    if(db->ExecQuery(CreateQuery(),vct)) {
        ui->tableWidget->setRowCount(static_cast<int>(vct.size()));
        QMessageBox::information(this,"Info", QString("Find ") + QString::number(vct.size()) + " records.");
    }
    else if(vct.empty()) {
        QMessageBox::information(this,"Info","No search value!");
    }

    for(int row_index = 0 ; row_index < ui->tableWidget->rowCount(); row_index++)
    {
        setTextItem (vct[row_index].GetFirstName(), row_index,0);
        setTextItem (vct[row_index].GetMiddleName(), row_index,1);
        setTextItem (vct[row_index].GetLastName(), row_index,2);
        setDigitItem(vct[row_index].GetRang(),row_index,3);
        setDigitItem(vct[row_index].GetTariff(),row_index,4);
        setDigitItem(vct[row_index].GetShopNumber(),row_index,5);
    }

    RestorLabels();
}

void MainWindow::RestorLabels()
{
    ui->tableWidget->setHorizontalHeaderLabels(titles_lbl);
}

void MainWindow::setTextItem(const QString &text, int row_index, int column_index)
{
    QTableWidgetItem* name_item = new QTableWidgetItem(text);
    name_item->setFlags(name_item->flags() ^ Qt::ItemIsEditable);
    ui->tableWidget->setItem(row_index,column_index,name_item);
}

void MainWindow::setDigitItem(float number, int row_index, int column_index)
{
    QTableWidgetItem* shop_item = new QTableWidgetItem(tr("%1").arg(number) );
    shop_item->setFlags(shop_item->flags() ^ Qt::ItemIsEditable);
    ui->tableWidget->setItem(row_index,column_index,shop_item);
}

QString MainWindow::CreateQuery()
{
    QString sql_query;
    QString type = ui->comboBox->currentText();

    if(type == "Name") {
        sql_query = QString("SELECT * FROM staff WHERE first_name = '" + ui->value_le->text() + "';");
    }
    else if(type == "Surname") {
        sql_query = QString("SELECT * FROM staff WHERE last_name = '" + ui->value_le->text() + "';");
    }
    else if(type == "Rang") {
        sql_query = QString("SELECT * FROM staff WHERE rang = '" + ui->value_le->text() + "';");
    }
    else if(type == "Shop number") {
        sql_query = QString("SELECT * FROM staff WHERE shop_number = '" + ui->value_le->text() + "';");
    }
    else sql_query = QString("SELECT * FROM staff;");

    return sql_query;
}

void MainWindow::WriteToFile(AbstractFileModule * pAfm, int row_index, const Employee & item)
{
	pAfm->InsertItem(row_index, 1, item.GetFirstName());
	pAfm->InsertItem(row_index, 2, item.GetMiddleName());
	pAfm->InsertItem(row_index, 3, item.GetLastName());
	pAfm->InsertItem(row_index, 4, item.GetRang());
	pAfm->InsertItem(row_index, 5, item.GetTariff());
	pAfm->InsertItem(row_index, 6, item.GetShopNumber());
}

void MainWindow::on_actionClose_triggered()
{
    this->close();
}

void MainWindow::on_actionSave_as_Excel_triggered()
{
    QString file_path = QFileDialog::getSaveFileName(this, tr("SaveFile") ,"","*.xlsx");

    if(file_path.isEmpty())
         return;

    excel = new ExcelModule();
	setExcelTableWidth(excel, 30);
    excel->writeTitles(titles_lbl);

    int row_index = 2;
    for(int i = 0; i < vct.size(); i++)
    {
		WriteToFile(excel, row_index, vct[i]);
        row_index++;
    }

    excel->SaveAs(file_path);
    QMessageBox::information(this,"Info","Data saved!");
    delete excel;
}

void MainWindow::GetTableHeaders(const QString & table_name)
{
	titles_lbl = db->GetTableColumnHeaders(table_name);
}

void MainWindow::GetTables()
{
	tables = db->GetTables();
}

void MainWindow::InsertDataIntoPdf(QPainter* painter, int pos_x, int pos_y, const QString & item, QColor text_color)
{
	painter->setPen(text_color);
	painter->drawText(pos_x, pos_y, item);
}

void MainWindow::setExcelTableWidth(ExcelModule * p_excel, int width)
{
	p_excel->setColumnWidth("A1", width);
	p_excel->setColumnWidth("B1", width);
	p_excel->setColumnWidth("C1", width);
	p_excel->setColumnWidth("D1", width);
	p_excel->setColumnWidth("E1", width);
	p_excel->setColumnWidth("F1", width);
}

void MainWindow::WriteToPDF()
{
    QString file_path = QFileDialog::getSaveFileName(this, tr("Save file"), "", "*.pdf");

    if(file_path.isEmpty())
         return;

	if (QFile::exists(file_path))
	{
		if (!QFile::remove(file_path))
		{
            throw "File has been not load!";
		}
	}
	
	int space_size = 200;
    int down = 0;

	QPdfWriter writer(file_path);
	QPainter painter(&writer);

	for (int i = 0; i < titles_lbl.size(); i++)
	{
		InsertDataIntoPdf(&painter, down , space_size, titles_lbl.at(i));
		down += 900;
	}

	space_size = 400;
	down = 0;
	for (int i = 0; i < vct.size(); i++)
	{
		InsertDataIntoPdf(&painter, down, space_size, vct[i].GetFirstName());
		down += 900;
		InsertDataIntoPdf(&painter, down, space_size, vct[i].GetMiddleName());
		down += 900;
		InsertDataIntoPdf(&painter, down, space_size, vct[i].GetLastName());
		down += 900;
		InsertDataIntoPdf(&painter, down, space_size, QString::number(vct[i].GetRang()));
		down += 900;
		InsertDataIntoPdf(&painter, down, space_size, QString::number(vct[i].GetTariff()));
		down += 900;
		InsertDataIntoPdf(&painter, down, space_size, QString::number(vct[i].GetShopNumber()));
		down = 0;
		space_size += 200;
	}

	painter.end();
	QMessageBox::information(this, "Info", "Data saved!");
}

void MainWindow::on_actionSave_as_PDF_triggered()
{
    WriteToPDF();
}

void MainWindow::on_actionSave_as_Word_triggered()
{
    QString file_path = QFileDialog::getSaveFileName(this, tr("SaveFile") ,"","*.docx");

    if(file_path.isEmpty())
         return;

    WordModule* word = new WordModule;

    int rows = static_cast<int>( vct.size() ) + 1;
    int columns = MAX_COLUMN;

    word->CreateTable(rows, columns);

	for (int i = 0; i < titles_lbl.size(); i++) {
		QString tmp = titles_lbl.at(i);
		word->InsertItem(1, (i + 1), tmp);
	}

    for(int i = 0; i < vct.size(); i++) {
		WriteToFile(word, (i + 2), vct[i]);
    }

    word->SaveAs(file_path);
    QMessageBox::information(this,"Info","Data saved!");
    delete word;
}
