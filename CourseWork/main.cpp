#include "all_headers.h"

std::vector<Employee> employee;
std::vector<Authentication> authentication;
// ������ ��� �������� �������� ����������� ����������� ��������
std::vector<int> indexes;

int main()
{
	setlocale(0, "rus");
	int tries = 0;
	int entryStatus;


	// ������ ������ � ������� 
	writingToVectorsFromFileAuth(authentication);
	writingToVectorsFromFileEmployee(employee);


	employee.reserve(50);
	authentication.reserve(20);

	// �������, ������� ������ � ��������� �������
	long seconds = checkHowManyTimeGo(entryStatus);
	// ���������� ����� ����� ������� � ����
	secondsSinceLastExecution(entryStatus);

	std::ifstream file("entryStatus.txt");
	file >> entryStatus;

	if (seconds >= 30 or entryStatus == 0)
		auth(authentication, tries, entryStatus);

	if (tries > 4)
	{
		std::cout << "������� ����� ������� �����,���������� �����.";
		return -1;
	}

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

	RusMainMenu(employee, indexes, authentication);

	return 0;
}