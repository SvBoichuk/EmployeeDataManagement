#include "database.h"
#include <QtSql/QSqlError>
#include <QtSql/QSqlTableModel>
#include <QDebug>

DataBase::DataBase(const QString &dbName,const QString &pass,const QString &driver,const QString &usr_name,const QString &host) :
    db_name_(dbName), password_(pass), db_driver_(driver), user_name_(usr_name), host_name_(host)
{
    db_ = QSqlDatabase::addDatabase(driver);
    db_.setDatabaseName(db_name_);
    db_.setHostName(host_name_);
    db_.setPassword(password_);
    db_.setUserName(user_name_);
	db_.setPort(PORT);

    if(db_.open())
        qDebug() << "Database is open!";
    else throw DBException(QString("Can't open database!\n" + db_.lastError().text() ));
}

QStringList DataBase::GetTableColumnHeaders(const QString & tableName)
{
	QSqlQuery getHeaders = QSqlQuery(db_);
	QStringList tableHeaders;

	if (getHeaders.exec(QString("DESC " + tableName + QString(";"))))
	{
		while (getHeaders.next())
		{
			tableHeaders.push_back(getHeaders.value(0).toString());
		}
	}

	return tableHeaders;
}


bool DataBase::ExecQuery(const QString &query, std::vector<Employee>& vect_empl)
{
    EmployeeData data;
    QSqlQuery sql_query = QSqlQuery(db_);
    bool query_status = false;
    if (sql_query.exec(query))
    {
        query_status = true;

        while(sql_query.next())
        {
            data.first_name = sql_query.value(0).toString();
            data.middle_name = sql_query.value(1).toString();
            data.last_name = sql_query.value(2).toString();
            data.range = sql_query.value(3).toInt();
            data.tariff = sql_query.value(4).toFloat();
            data.shop_number = sql_query.value(5).toInt();

            vect_empl.push_back(Employee(data));
        }

    }
    else query_status = false;

    return query_status;
}

DataBase::~DataBase()
{
}
