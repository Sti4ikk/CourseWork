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
	// ���������� � ���������� 0 ��� 1, ����� ����� ,�� ������ ����� ��������� �����(0 - �������, 1 - ����������)
	int languageStatus;
	std::fstream file1("language.txt");
	file1 >> languageStatus;
	file1.close();


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

	if (seconds >= 2000 or entryStatus == 0)
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

	if(languageStatus == 0)
		RusMainMenu(employee, indexes, authentication, languageStatus);
	else if (languageStatus == 1)
		EngMainMenu(employee, indexes, authentication, languageStatus);


	return 0;
}