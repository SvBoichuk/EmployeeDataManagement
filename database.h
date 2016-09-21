#ifndef DATABASE_H
#define DATABASE_H

#include <exception>
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QTableView>
#include <stdlib.h>

#include "employee.h"

#define PORT 3306
#define USERNAME "root"
#define LOCALHOST "localhost"
#define IP_ADDR "46.201.115.123"

class DataBase
{
private:
    QSqlDatabase db_;
    QString host_name_;
    QString user_name_;
    QString password_;
    QString db_name_;
    QString db_driver_;
    
public:
    DataBase() = delete;
    DataBase(const DataBase&) = delete;
    DataBase& operator= (const DataBase&) = delete;
    DataBase(const QString &dbName,const QString &pass,const QString &driver = "QMYSQL",const QString &usr_name = USERNAME,const QString &host = LOCALHOST);

    /*
    *@[brief:] get reference to QSqlDataBase object
    *@[out:] reference to QSqlDataBase object
    */
    QSqlDatabase& GetDB() { return db_; }

    /*
    *@[brief:] this 4 functions returns DB: name, host, driver, user name
    */
    QString GetDbName()   const { return db_name_; }
    QString GetDbDriver() const { return db_driver_; }
    QString GetUserName() const { return user_name_; }
    QString GetHostName() const { return host_name_; }
	
	QStringList GetTables() const { return db_.tables(); };
	QStringList GetTableColumnHeaders(const QString& tableName);

    /*
    *@[brief:] execute query in db and pushing read values in vector
    *@[in:] 1)SQL query as QString object, 2)tabel view widget to display query result
    *@[out:] return true if query is success, else - return false
    */
    bool ExecQuery(const QString& query, std::vector<Employee>& vect_empl);

    ~DataBase();
};

class DBException : public std::exception
{
private:
    QString msg;
public:
    explicit DBException(QString str) : msg(str) {}
    DBException(const DBException&) = default;

    /*
    *@[brief:] return text message with exception information
    *@[out:] QString odject with exception info
    */
    const char* what() const noexcept { return msg.toStdString().c_str(); }
    ~DBException() {}
};


#endif // DATABASE_H
