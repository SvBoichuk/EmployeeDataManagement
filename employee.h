#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>

struct EmployeeData{
    QString first_name;
    QString middle_name;
    QString last_name;
    int range;
    float tariff;
    int shop_number;
};

class Employee
{
private:
    EmployeeData data;
public:
    Employee();
    explicit Employee(const EmployeeData&);
    Employee(const QString& f_name, const QString& m_name, const QString& l_name, int range, float tariff, int shop_numb);
    Employee(const Employee&) = default;
    Employee& operator= (const Employee&) = default;
	Employee(Employee&& other);
	Employee& operator= (Employee&& other);

    /*Get function members*/
    QString GetFirstName() const { return data.first_name; }
    QString GetMiddleName() const { return data.middle_name; }
    QString GetLastName() const { return data.last_name; }
    int     GetRang() const { return data.range; }
    float   GetTariff() const { return data.tariff; }
    int     GetShopNumber()const {return data.shop_number; }

    /*Set function members*/
    void SetFirstName(const QString& f_name) { data.first_name = f_name; }
    void SetMiddleName(const QString& m_name) { data.middle_name = m_name; }
    void SetLastName(const QString& l_name) { data.last_name = l_name; }
    void SetRange(int range) { data.range = range; }
    void SetTarrif(float tarrif) { data.tariff = tarrif; }
    void SetFirstName(int shop_numb) { data.shop_number = shop_numb; }

    ~Employee();

};

#endif // EMPLOYEE_H
