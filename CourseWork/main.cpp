#include "all_headers.h"

std::vector<Employee> employee;
std::vector<Authentication> authentication;

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
	//searchForEmployeesOfRetirementAge(employee);


	return 0;
}