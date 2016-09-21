#include "excelmodule.h"
#include <QMessageBox>
#include <QObject>
#include <QDebug>
#include <QFile>
#include <QString>
#include <exception>

void ExcelModule::ClearFile()
{
    QAxObject* range = sheet->querySubObject("Range(const QVariant&)", QVariant(QString("1:6")));
    range->dynamicCall("Select()");
    range->dynamicCall("Delete");
    delete range;
}

ExcelModule::ExcelModule() : AbstractFileModule()
{
	application = new QAxObject("Excel.Application");
	workDocument = application->querySubObject("Workbooks");
	newDocument = workDocument->querySubObject("Add");
    mSheets = newDocument->querySubObject("Worksheets");
    sheet = mSheets->querySubObject("Add");
}

bool ExcelModule::writeTitles(const QStringList& titlesList)
{
    if(titlesList.empty())
        return false;

    for(int i = 0; i < titlesList.size(); i++) {
        InsertItem(START_INDEX, (i+1) , titlesList[i]);
        setBackgrounColor(Qt::green, START_INDEX, (i+1) );
    }

    return true;
}


bool ExcelModule::InsertItem(int row_index, int column_index, QVariant item)
{
	cell = sheet->querySubObject("Cells(QVariant,QVariant)", row_index, column_index);
	cell->setProperty("Value", item);
	delete cell;

	return true;
}

void ExcelModule::setColumnWidth(const QString &range, int width)
{
    QAxObject* rangec = sheet->querySubObject( "Range(const QVariant&)",QVariant(range));
    QAxObject* obj_width = rangec->querySubObject("Columns");
    obj_width->setProperty("ColumnWidth",width);
}

void ExcelModule::setRowHeight(const QString &range, int height)
{
    QAxObject *rangec = sheet->querySubObject( "Range(const QVariant&)",QVariant(range));
    QAxObject *obj_height = rangec->querySubObject("Rows");
    obj_height->setProperty("RowHeight", height);
}

void ExcelModule::setFontColor(QColor font_color, int row_index, int column_index)
{
    QAxObject* cell=sheet->querySubObject("Cells(QVariant,QVariant)", row_index, column_index);
    QAxObject* font=cell->querySubObject("Font");
    font->setProperty("Color", font_color);

    delete font;
    delete cell;
}

void ExcelModule::setBackgrounColor(QColor backgroun_color, int row_index, int column_index)
{
    QAxObject* cell = sheet->querySubObject("Cells(QVariant,QVariant)", row_index, column_index);
    QAxObject* interior = cell->querySubObject("Interior");
    interior->setProperty("Color", backgroun_color);

    delete interior;
    delete cell;
}

ExcelModule::~ExcelModule()
{
    /*Free memory*/
    delete sheet;
    delete mSheets;
    newDocument->dynamicCall("Close(QVariant)",QVariant(true));
    delete newDocument;
    delete workDocument;
    application->dynamicCall("Quit()");
    delete application;
}
