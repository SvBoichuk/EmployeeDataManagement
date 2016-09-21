#include "wordmodule.h"

#include <QMessageBox>
#include <QFile>
#include <exception>

#define DEFAULT_TABLE_BEHAVIOR 1
#define DEFAULT_FIT_BEHAIVOR 1


WordModule::WordModule() : AbstractFileModule(), table(nullptr), newTable(nullptr), Cell(nullptr), CellRange(nullptr)
{
    application = new QAxObject("Word.Application");
    workDocument = application->querySubObject("Documents()");
    newDocument = workDocument->querySubObject("Add()");
    activeDocument = application->querySubObject("ActiveDocument()");
}

void WordModule::CreateTable(int rows, int columns)
{
    table = activeDocument->querySubObject("Tables()");
    newTable = table->querySubObject("Add(Range, NumRows, NumColumns, DefaultTableBehavior, AutoFitBehavior)", activeDocument->dynamicCall("Range()"),
                                     rows, columns, DEFAULT_TABLE_BEHAVIOR, DEFAULT_FIT_BEHAIVOR);
}

bool WordModule::InsertItem(int row_index, int column_index, QVariant data)
{
    Cell = newTable->querySubObject("Cell(Row, Column)", row_index, column_index);
    CellRange = Cell->querySubObject("Range()");
    CellRange->dynamicCall("InsertAfter(Text)", data);

    delete CellRange;
    delete Cell;

	return true;
}

WordModule::~WordModule()
{
    delete newTable;
    delete table;
    delete activeDocument;
    newDocument->dynamicCall("Close(QVariant)", QVariant(true) );
    delete newDocument;
    delete workDocument;
    application->dynamicCall("Quit()");
    delete application;
}
