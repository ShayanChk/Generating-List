//Name: Shayan Chabook
//student ID: 159844208
//email:schabook@myseneca.ca
//7/23/2022
#include "GeneratingList.h"
#include "EmpProfile.h"
#include "WritingRecord.h"

using namespace std;

namespace sdds {
	GeneratingList<EmployeeWage> writeRaw(const GeneratingList<Employee>& emp, const GeneratingList<Salary>& sal) {
	
		GeneratingList<EmployeeWage> activeEmp;


		for (size_t i = 0; i < emp.size(); i++)
		{

			for (size_t j = 0; j < sal.size(); j++)
			{
				if (emp[i].id == sal[j].id)
				{
					EmployeeWage* potentialEmp = nullptr;

					try
					{
						if (!activeEmp.Luhn(emp[i].id)) 
						{
							throw std::string{ "*** SIN number is invalid ***" };
						}

						potentialEmp = new EmployeeWage(emp[i].name, sal[j].salary);

						potentialEmp->rangeValidator();

						activeEmp += potentialEmp;

						delete potentialEmp;
					}
					catch (const string& err)
					{
						delete potentialEmp;

						throw err;
					}
				}
			}
		}

		return activeEmp;
		
	}


GeneratingList<EmployeeWage> writeSmart(const GeneratingList<Employee>& emp, const GeneratingList<Salary>& sal)
{
	GeneratingList<EmployeeWage> activeEmp;

	for (size_t i = 0u; i < emp.size(); i++)
	{
		for (size_t j = 0u; j < sal.size(); j++)
		{
			if (emp[i].id == sal[j].id)
			{
				std::string sin = emp[i].id;

				std::string name = emp[i].name;

				double salary = sal[j].salary;

				try
				{
					if (activeEmp.Luhn(sin) == false)
					{
						throw std::string("*** Bad ID ");
					}

					std::unique_ptr<EmployeeWage> employee = std::unique_ptr<EmployeeWage>(new EmployeeWage(name, salary));

					employee->rangeValidator();

					activeEmp += std::move(employee);

				}
				catch (const string& err)
				{
					throw err;
				}
			}
		}
	}

	return activeEmp;

  }
}