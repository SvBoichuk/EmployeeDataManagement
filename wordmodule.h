#ifndef WORDMODULE_H
#define WORDMODULE_H

#include "AbstractFileModule.h"

class WordModule : public AbstractFileModule
{
private:
    QAxObject* activeDocument;
    QAxObject* newTable;
    QAxObject* table;
	QAxObject* Cell;
	QAxObject* CellRange;
public:
    WordModule();

	WordModule(const WordModule&) = delete;
	WordModule& operator= (const WordModule&) = delete;

    /*
    *@[brief:] create table in file
    *@[in:] rows and columns number
    */
    void CreateTable(int rows, int columns);

    /*
    *@[brief:] insert data into table
    *@[in:] row&column index and item
    */
	virtual bool InsertItem(int row_index, int column_index, QVariant item);

    ~WordModule();
};

#endif // WORDMODULE_H
