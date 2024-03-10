#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "structs.h"
#include "prototypes.h"
#include "enums.h"
#include <Windows.h>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>


//�����������
void auth(std::vector<Authentication> &authentication, int &tries)
{
	std::cout << "----------------------��������� �ר�� ����� ����������� �����������------------------------\n";
	std::cout << "1. ����.\n"
			  << "2. �����������.\n\n"
			  << "��� �����: ";
	int choise;
	std::cin >> choise;
	switch (choise)
	{
	case(AUTH):     checkDataOfUser(authentication, tries); break;
	case(REGISTER): registration(authentication);    break;
	default: break;
	}
}


long checkHowManyTimeGo()
{
	// ��������� ���� ��� ������
	std::fstream file("Time.txt");

	// ���������, ������� �� ������� ����
	if (!file.is_open()) {
		std::cerr << "Error: Unable to open last_execution.txt" << std::endl;
		return -1; // ���������� -1 � ������ ������
	}

	// ��������� ����� ���������� ������� �� �����
	std::string lastExecutionTimeString;
	std::getline(file, lastExecutionTimeString);


	// ����������� ������ � �������� � ������ �������
	std::istringstream iss(lastExecutionTimeString);
	std::tm lastExecutionTime = {};
	iss >> std::get_time(&lastExecutionTime, "%Y-%m-%d %H:%M:%S");

	// �������� ������� �����
	std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();

	// ����������� ����� ���������� ������� � ��������� �����
	std::time_t lastExecutionTime_t = std::mktime(&lastExecutionTime);
	std::chrono::system_clock::time_point lastExecution = std::chrono::system_clock::from_time_t(lastExecutionTime_t);

	// ������������ ������� �� �������
	std::chrono::duration<int> timeSinceLastExecution = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastExecution);

	file.close();
	// ���������� ���������� ������, ��������� � ���������� �������
	return timeSinceLastExecution.count();
}


// ������� ����
void RusMainMenu(std::vector<Employee>& employee, std::vector<int>& indexes, std::vector<Authentication>& authentication)
{
	int choise;
	do
	{
		std::cout << "-------------------------------------�ר� ����� ����������� �����������-----------------------------------------------" << std::endl;
		std::cout << "1. ����� ��������������.\n";
		std::cout << "2. ����� ���������.\n";
		std::cout << "3. ���������.\n";
		std::cout << "4. �����.\n\n";

		std::cout << "��� �����: ";
		std::cin >> choise;

		system("cls");
		switch (choise)
		{
		case(EDITING_MODE): editingMode(employee); break;
		case(PROCESSING_MODE): processsingMode(employee, indexes); break;
		case(SETTINGS): rusSettings(employee, indexes, authentication); break;
		default: break;
		}

	} while (choise != 4);
}

void chooseTypeOfSort(std::vector<Employee>& employee)
{
	int choise;

	std::cout << "1. ���������� �� �������.\n";
	std::cout << "2. ���������� �� ���������.\n";
	std::cout << "3. ���������� �� �����.\n\n";

	std::cout << "�������� ��������, �� �������� ����� ������������ ����������: ";
	std::cin >> choise;
	system("cls");

	switch (choise)
	{
	case(1): if (typeOFSorting() == 1) sortWithSurNameUp(employee); else if (typeOFSorting() == 2) sortWithSurNameDown(employee); break;
	case(2): if (typeOFSorting() == 1) sortWithPostUp(employee); else if (typeOFSorting() == 2) sortWithPostDown(employee); break;
	case(3): if (typeOFSorting() == 1) sortWithExperienceUp(employee); else if (typeOFSorting() == 2) sortWithExperienceDown(employee); break;
	case(4):      // ��������
	default: break;
	}
}
// ����� ���������� � ������� �������� ��� � ������� �����������
int typeOFSorting()
{
	int typeOfSort;
	std::cout << "1.� ������� �����������.\n";
	std::cout << "2.� ������� ��������.\n\n";
	std::cout << "� ����� ������� �� ������ ����������� ����������: ";
	std::cin >> typeOfSort;
	system("cls");

	return typeOfSort;
}
void chooseTypeOfSearch(std::vector<Employee>& employee)
{
	int choise;

	std::cout << "1. ����� �� �������.\n";
	std::cout << "2. ����� �� ���������.\n";
	std::cout << "3. ����� �� ���� ������ ������.\n\n";

	std::cout << "�������� ��������, �� �������� ����� ���������� �����: ";
	std::cin >> choise;
	system("cls");

	switch (choise)
	{
	case(1): searchForSurName(employee); std::cout << std::endl; break;
	case(2): searchForPost(employee); std::cout << std::endl; break;
	case(3): searchForStartDate(employee); std::cout << std::endl; break;
	default: break;
	}
}
// ����� ��������������
void editingMode(std::vector<Employee>& employee)
{
	int choise;
	do
	{
		std::cout << "------------------------------------------�E��� ��������������--------------------------------------------------------\n";
		std::cout << "1. ����� ���� �����������.\n";
		std::cout << "2. �������� ����������.\n";
		std::cout << "3. ������������� ������.\n";
		std::cout << "4. ������� ����������.\n";
		std::cout << "5. ��������� �����.\n\n";

		std::cout << "��� �����: ";
		std::cin >> choise;

		system("cls");
		switch (choise)
		{
		case(CHECKING): std::cout << "��� ������ ���� ������� �����������: \n\n"; printAllEmployee(employee); break;
		case(ADDING):   addNewEmployee(employee);   break;
		case(EDITING):  editEmployee(employee);     break;
		case(DELETING): deleteEmployee(employee);   break;
		case(E_BACK):
		default: break;
		}

	} while (choise != 5);
}
// ����� ���������
void processsingMode(std::vector<Employee>& employee, std::vector<int>& indexes)
{
	int choise;
	do
	{
		std::cout << "---------------------------------------------����� ���������-----------------------------------------------------------" << std::endl;
		std::cout << "1. �����.\n";
		std::cout << "2. ����������.\n";
		std::cout << "3. ����� ����������� ����������� ��������.\n";
		std::cout << "4. �����.\n\n";

		std::cout << "��� �����: ";
		std::cin >> choise;

		system("cls");
		switch (choise)
		{
		case(SEARCH): chooseTypeOfSearch(employee); break;
		case(SORTING): chooseTypeOfSort(employee); break;
		case(INDIVIDUAL_TASK): searchForEmployeesOfRetirementAge(employee, indexes); break;
		case(P_BACK):
		default: break;
		}

	} while (choise != 4);
}

void rusSettings(std::vector<Employee>& employee, std::vector<int>& indexes, std::vector<Authentication>& authentication)
{

	int choise;

	do
	{
		std::cout << "----------------------------------------------���������---------------------------------------------------------------\n";
		std::cout << "1. ����.\n";
		std::cout << "2. �����.\n";

		std::cout << "��� �����: ";
		std::cin >> choise;

		system("cls");
		switch (choise)
		{
		case(LANGUAGE): rusChooseMenuLanguage(employee, indexes, authentication); break;
		case(S_BACK):
		default: break;
		}

	} while (choise != 2);
}

// ���������� 1 - ������� ����, 2 - ���������� ����
void rusChooseMenuLanguage(std::vector<Employee>& employee, std::vector<int>& indexes, std::vector<Authentication>& authentication)
{
	int choise;
	std::cout << "----------------------------------------------��������� �����---------------------------------------------------------\n";
	std::cout << "1. �������.\n";
	std::cout << "2. English.\n";

	std::cout << "�������� ����: ";
	std::cin >> choise;
	system("cls");

	std::cout << "������������ �����";
	for (int i = 0; i < 3; i++)
	{
		Sleep(600);
		std::cout << ".";
	}
	system("cls");
	std::cout << "������������ ������ �������!";
	Sleep(2500);
	system("cls");

	turnMenuLanguge(choise, employee, indexes, authentication);
}

void turnMenuLanguge(int choise, std::vector<Employee>& employee, std::vector<int>& indexes, std::vector<Authentication>& authentication)
{
	if (choise == 1)
		RusMainMenu(employee, indexes, authentication);
	else if (choise == 2)
		EngMainMenu(employee, indexes, authentication);
}


//���������� ����
void EngMainMenu(std::vector<Employee>& employee, std::vector<int>& indexes, std::vector<Authentication>& authentication)
{
	int choise;
	do
	{
		std::cout << "-------------------------------ACCOUNTING THE EXPERIENCE OF EMPLOYEES OF THE ENTERPRISE---------------------------------" << std::endl;
		std::cout << "1. Edit mode.\n";
		std::cout << "2. Processing mode.\n";
		std::cout << "3. Settings.\n";
		std::cout << "4. Exit.\n\n";

		std::cout << "Your choise: ";
		std::cin >> choise;

		system("cls");
		switch (choise)
		{
		case(EDITING_MODE): EngEditingMode(employee); break;
		case(PROCESSING_MODE): EngProcesssingMode(employee, indexes); break;
		case(SETTINGS): engSettings(employee, indexes, authentication); break;
		default: break;
		}

	} while (choise != 4);
}

void EngChooseTypeOfSort(std::vector<Employee>& employee)
{
	int choise;

	std::cout << "1. Sort by surname.\n";
	std::cout << "2. Sort by position.\n";
	std::cout << "3. Sorting by experience.\n\n";

	std::cout << "Select the criterion by which to sort: ";
	std::cin >> choise;
	system("cls");

	switch (choise)
	{
	case(1): if (typeOFSorting() == 1) sortWithSurNameUp(employee); else if (typeOFSorting() == 2) sortWithSurNameDown(employee); break;
	case(2): if (typeOFSorting() == 1) sortWithPostUp(employee); else if (typeOFSorting() == 2) sortWithPostDown(employee); break;
	case(3): if (typeOFSorting() == 1) sortWithExperienceUp(employee); else if (typeOFSorting() == 2) sortWithExperienceDown(employee); break;
	case(4):
	default: break;
	}
}
// ����� ���������� � ������� �������� ��� � ������� �����������
int EngTypeOFSorting()
{
	int typeOfSort;
	std::cout << "1. In ascending order.\n";
	std::cout << "2. In descending order.\n\n";
	std::cout << "In what order do you want to sort: ";
	std::cin >> typeOfSort;
	system("cls");

	return typeOfSort;
}
void EngChooseTypeOfSearch(std::vector<Employee>& employee)
{
	int choise;

	std::cout << "1. Search by last name.\n";
	std::cout << "2. Search by position.\n";
	std::cout << "3. Search by start year.\n\n";

	std::cout << "Select the criterion by which the search will be carried out : ";
	std::cin >> choise;
	system("cls");

	switch (choise)
	{
	case(1): searchForSurName(employee); std::cout << std::endl; break;
	case(2): searchForPost(employee); std::cout << std::endl; break;
	case(3): searchForStartDate(employee); std::cout << std::endl; break;
	default: break;
	}
}
// ����� ��������������
void EngEditingMode(std::vector<Employee>& employee)
{
	int choise;
	do
	{
		std::cout << "----------------------------------------------EDITING MODE-----------------------------------------------------------\n";
		std::cout << "1. Print all employees.\n";
		std::cout << "2. Add new employee.\n";
		std::cout << "3. Edit info.\n";
		std::cout << "4. Delete employee.\n";
		std::cout << "5. Back.\n\n";

		std::cout << "Your choise: ";
		std::cin >> choise;

		system("cls");
		switch (choise)
		{
		case(CHECKING): std::cout << "Here is a list of all current employees:\n\n"; printAllEmployee(employee); break;
		case(ADDING):   engAddNewEmployee(employee);   break;
		case(EDITING):  engEditEmployee(employee);     break;
		case(DELETING): engDeleteEmployee(employee);   break;
		case(E_BACK):
		default: break;
		}

	} while (choise != 5);
}
// ����� ���������
void EngProcesssingMode(std::vector<Employee>& employee, std::vector<int>& indexes)
{
	int choise;
	do
	{
		std::cout << "---------------------------------------------PROCESSING MODE-----------------------------------------------------------" << std::endl;
		std::cout << "1. Search.\n";
		std::cout << "2. Sorting.\n";
		std::cout << "3. Search for employees of retirement age.\n";
		std::cout << "4. Back.\n\n";

		std::cout << "Your choice: ";
		std::cin >> choise;

		system("cls");
		switch (choise)
		{
		case(SEARCH): chooseTypeOfSearch(employee); break;
		case(SORTING): chooseTypeOfSort(employee); break;
		case(INDIVIDUAL_TASK): searchForEmployeesOfRetirementAge(employee, indexes); break;
		case(P_BACK):
		default: break;
		}

	} while (choise != 4);
}

void engChooseMenuLanguage(std::vector<Employee>& employee, std::vector<int>& indexes, std::vector<Authentication>& authentication)
{
	int choise;
	std::cout << "1. Russian.\n";
	std::cout << "2. English.\n";
	std::cout << "Choose language: ";
	std::cin >> choise;
	system("cls");

	std::cout << "Switching language";
	for (int i = 0; i < 3; i++)
	{
		Sleep(600);
		std::cout << ".";
	}
	system("cls");
	std::cout << "The switch was successful!";
	Sleep(2500);
	system("cls");

	turnMenuLanguge(choise, employee, indexes, authentication);
}

void engSettings(std::vector<Employee>& employee, std::vector<int>& indexes, std::vector<Authentication>& authentication)
{

	int choise;

	do
	{
		std::cout << "----------------------------------------------SETTINGS---------------------------------------------------------------\n";
		std::cout << "1. Language.\n";
		std::cout << "2. Back.\n";

		std::cout << "Your choise: ";
		std::cin >> choise;

		system("cls");
		switch (choise)
		{
		case(LANGUAGE): engChooseMenuLanguage(employee, indexes, authentication); break;
		case(S_BACK):
		default: break;
		}

	} while (choise != 2);
}