#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <QMainWindow>
#include "database.h"
#include "employee.h"
#include "excelmodule.h"
#include "wordmodule.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_comboBox_activated(const QString &arg1);

    void on_search_btn_clicked();

    void on_actionClose_triggered();

    void on_actionSave_as_Excel_triggered();

    void on_actionSave_as_PDF_triggered();

    void on_actionSave_as_Word_triggered();

private:
    Ui::MainWindow *ui;
    std::vector<Employee> vct;
    QStringList titles_lbl;
    DataBase* db;
    ExcelModule* excel;
	QStringList tables;

	/*
	*@[brief:] get column heades in table
	*@[in:] table name 
	*/
	void GetTableHeaders(const QString& table_name);

	/*
	*@[brief:] get tables names that contains in database
	*/
	void GetTables();

	/*
	*@[brief:] print data to pdf file
	*@[in:] 1) pointer to painter, 2,3) position in page, 4) data to print, 5) text color
	*/
	void InsertDataIntoPdf(QPainter* painter, int pos_x, int pos_y, const QString& item, QColor text_color = Qt::black);

	/*
	*@[brief:] set excel table widht
	*@[in:] pointer to ExcelModule object, 2) - column widht
	*/
	void setExcelTableWidth(ExcelModule* p_excel, int width);

    /*
    *@[brief:] write data to pdf file
    */
    void WriteToPDF();

    /*
    *@[brief:] Reset Horizontal Header labels in table, after clearing
    */
    void RestorLabels();

    /*
    *@[brief:] insert text item into the table
    *@[in:] 1) QString data, 2) Row index, 3) ColumnIndex
    */
    void setTextItem(const QString& text, int row_index, int column_index);

    /*
    *@[brief:] insert numbers item into the table
    *@[in:] 1) float data, 2) Row index, 3) ColumnIndex
    */
    void setDigitItem(float number, int row_index, int column_index);

    /*
    *@[brief:] analyze search criterial and create query
    *@[out:] return QString object which contain query
    */
    QString CreateQuery();

	void WriteToFile(AbstractFileModule* pAfm, int row_index, const Employee& item);
};

#endif // MAINWINDOW_H
