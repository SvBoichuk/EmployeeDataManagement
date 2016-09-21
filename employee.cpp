#include "employee.h"

Employee::Employee()
{

}

Employee::Employee(const EmployeeData &d)
{
    data = d;
}

Employee::Employee(const QString &f_name, const QString &m_name, const QString &l_name, int range, float tariff, int shop_numb)
{
    data.first_name = f_name;
    data.middle_name = m_name;
    data.last_name = l_name;
    data.range = range;
    data.tariff = tariff;
    data.shop_number = shop_numb;
}

Employee::Employee(Employee && other)
{
	data = std::move(other.data);
}

Employee & Employee::operator=(Employee && other)
{
	data = std::move(other.data);
	return *this;
}

Employee::~Employee()
{
}
