#ifndef EXCELMODULE_H
#define EXCELMODULE_H

#include "AbstractFileModule.h"

#define START_INDEX 1

class ExcelModule : public AbstractFileModule
{
private:
    QAxObject* mSheets;
    QAxObject* sheet;
	QAxObject* cell;
    /*
    *@[brief:] clear all data in file
    */
    void ClearFile();
public:
    ExcelModule();

	ExcelModule(const ExcelModule&) = delete;
	ExcelModule& operator= (const ExcelModule&) = delete;

    /*
    *@[brief:] setup horizontal table labels
    *@[in:] labels
    *@[out:] return true if setup is success
    */
    bool writeTitles(const QStringList& titlesList);

    /*
    *@[brief:] redefinition base class function
    */
	virtual bool InsertItem(int row_index, int column_index, QVariant item);

    /*setup some table proprties*/
    void setColumnWidth(const QString& range, int width);
    void setRowHeight(const QString& range, int height);
    void setBackgrounColor(QColor backgroun_color, int row_index, int column_index);
    void setFontColor(QColor font_color, int row_index, int column_index);

    ~ExcelModule();
};

#endif // EXCELMODULE_H
