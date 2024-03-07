#include "all_headers.h"

std::vector<Employee> employee;
std::vector<Authentication> authentication;
// вектор для хранения индексов сотрдуников пенсионного возраста
std::vector<int> indexes;

int main()
{
	setlocale(0, "rus");
	
	employee.reserve(50);
	authentication.reserve(20);

	writingToVectorsFromFileAuth(authentication);
	writingToVectorsFromFileEmployee(employee);
	//checkDataOfUser(authentication);
	//registration(authentication);
	//addNewEmployee(employee);
	//deleteEmployee(employee);
	//editEmployee(employee);
	//searchForSurName(employee);
	//searchForPost(employee);
	//searchForStartDate(employee);
	//sortWithSurNameDown(employee);
	//sortWithSurNameUp(employee);
	//sortWithPostDown(employee);
	//sortWithExperienceDown(employee);
	//printAllEmployee(employee);
	//getExperienceOfEmployees(employee);
	//searchForEmployeesOfRetirementAge(employee, indexes);
	//printEmployeesOfRetirementAge(employee, indexes);

	mainMenu(employee, indexes);

	return 0;
}