#pragma once

#include <ActiveQt\qaxbase.h>
#include <ActiveQt\qaxobject.h>

class AbstractFileModule
{
private:
	/*
	*@[brief:] search and replace '/' symbol by '\\' to fix file path
	*@[in:] input file path
	*@[out:] fixed file path
	*/
	QString FixPath(const QString& file_path);
protected:
	QAxObject* application;
	QAxObject* workDocument;
	QAxObject* newDocument;
public:
	AbstractFileModule();
	
	/*
	*@[brief:] save data in files
	*@[in:] input file path
	*@[out:] return true if data was saved
	*/
	bool SaveAs(const QString& file_path);

	/*
	*@[brief] insert item in table
	*@[in] 1-2) row&column index, 3) inserted item
	*@[out:] return true if item inser
	*/
	virtual bool InsertItem(int row_index, int column_index, QVariant item) = 0;

	virtual ~AbstractFileModule();
};

