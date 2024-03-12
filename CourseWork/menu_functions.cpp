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
#include "termcolor.hpp"
#include <conio.h>


// сколько времени прошло с последнего запуска
long checkHowManyTimeGo(int &entryStatus)
{
	// Открываем файл для чтения
	std::fstream file("Time.txt");

	// Проверяем, удалось ли открыть файл
	if (!file.is_open()) {
		std::cerr << "Error: Unable to open Time.txt" << std::endl;
		return -1; // Возвращаем -1 в случае ошибки
	}

	// Считываем время последнего запуска из файла
	std::string lastExecutionTimeString;
	std::getline(file, lastExecutionTimeString);


	// Преобразуем строку с временем в объект времени
	std::istringstream iss(lastExecutionTimeString);
	std::tm lastExecutionTime = {};
	iss >> std::get_time(&lastExecutionTime, "%Y-%m-%d %H:%M:%S");

	// Получаем текущее время
	std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();

	// Преобразуем время последнего запуска в системное время
	std::time_t lastExecutionTime_t = std::mktime(&lastExecutionTime);
	std::chrono::system_clock::time_point lastExecution = std::chrono::system_clock::from_time_t(lastExecutionTime_t);

	// Рассчитываем разницу во времени
	std::chrono::duration<int> timeSinceLastExecution = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastExecution);

	file.close();

	if (timeSinceLastExecution.count() > 2000)
	{
		entryStatus = 0;
		std::fstream file("entryStatus.txt");

		file << entryStatus;
	}
	// Возвращаем количество секунд, прошедших с последнего запуска
	return timeSinceLastExecution.count();
}



// МЕНЮ АВТОРИЗАЦИИ
void auth(std::vector<Authentication>& authentication, int& tries, int& entryStatus)
{
	do
	{
		std::cout << "----------------------ПРОГРАММА УЧЁТА СТАЖА СОТРУДНИКОВ ПРЕДПРИЯТИЯ------------------------\n";
		std::cout << "1. Вход.\n"
				  << "2. Регистрация.\n\n";

		int choise = checkInput();
		system("cls");
		switch (choise)
		{
		case(AUTH):     checkDataOfUser(authentication, tries, entryStatus); return;
		case(REGISTER): registration(authentication);    return;
		default: std::cout << termcolor::red << "Введите цифру из списка!" << termcolor::reset; Sleep(2000); system("cls");
		}
	} while (true);
}

// РУССКОЕ МЕНЮ
void RusMainMenu(std::vector<Employee>& employee, std::vector<int>& indexes, std::vector<Authentication>& authentication, int& languageStatus)
{
	int choise;
	do
	{
		std::cout << "-------------------------------------УЧЁТ СТАЖА СОТРУДНИКОВ ПРЕДПРИЯТИЯ-----------------------------------------------" << std::endl;
		std::cout << "1. Режим редактирования.\n";
		std::cout << "2. Режим обработки.\n";
		std::cout << "3. Настройки.\n";
		std::cout << "4. Выход.\n\n";

		choise = checkInput();
		system("cls");
		switch (choise)
		{
		case(EDITING_MODE): editingMode(employee); break;
		case(PROCESSING_MODE): processsingMode(employee, indexes); break;
		case(SETTINGS): rusSettings(employee, indexes, authentication, languageStatus); break;
		case(EXIT): break;
		default: std::cout << termcolor::red << "Введите цифру из списка!" << termcolor::reset; Sleep(2000); system("cls");
		}

	} while (choise != 4);
}

// выбор типа сортировки 
void chooseTypeOfSort(std::vector<Employee>& employee)
{
	int choise;

	std::cout << "1. Сортировка по Фамилии.\n";
	std::cout << "2. Сортировка по должности.\n";
	std::cout << "3. Сортировка по стажу.\n\n";

	std::cout << "Выберите критерий, по которому будет осуществлена сортировка: ";
	std::cin >> choise;
	system("cls");

	switch (choise)
	{
	case(1): if (typeOFSorting() == 1) sortWithSurNameUp(employee); else if (typeOFSorting() == 2) sortWithSurNameDown(employee); break;
	case(2): if (typeOFSorting() == 1) sortWithPostUp(employee); else if (typeOFSorting() == 2) sortWithPostDown(employee); break;
	case(3): if (typeOFSorting() == 1) sortWithExperienceUp(employee); else if (typeOFSorting() == 2) sortWithExperienceDown(employee); break;
	case(4):      // доделать
	default: break;
	}
}

// выбор сортировки в порядке убывания или в порядке возрастания
int typeOFSorting()
{
	int typeOfSort;
	std::cout << "1.В порядке возрастания.\n";
	std::cout << "2.В порядке убывания.\n\n";
	std::cout << "В каком порядке вы хотите осуществить сортировку: ";
	std::cin >> typeOfSort;
	system("cls");

	return typeOfSort;
}

// выбор типа поиска
void chooseTypeOfSearch(std::vector<Employee>& employee)
{
	int choise;

	std::cout << "1. Поиск по фамилии.\n";
	std::cout << "2. Поиск по должности.\n";
	std::cout << "3. Поиск по году начала работы.\n\n";

	std::cout << "Выберите критерий, по которому будет осуществлён поиск: ";
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

// редим редактирования
void editingMode(std::vector<Employee>& employee)
{
	int choise;
	do
	{
		std::cout << "------------------------------------------РEЖИМ РЕДАКТИРОВАНИЯ--------------------------------------------------------\n";
		std::cout << "1. Вывод всех сотрудников.\n";
		std::cout << "2. Добавить сотрудника.\n";
		std::cout << "3. Редактировать данные.\n";
		std::cout << "4. Удалить сотрудника.\n";
		std::cout << "5. Вернуться назад.\n\n";

		choise = checkInput();
		system("cls");
		switch (choise)
		{
		case(CHECKING): std::cout << "Вот список всех текущих сотрудников: \n\n"; printAllEmployee(employee); std::cout << "Нажмите любую клавишу для продолжения...";
			_getch(); system("cls"); break;
		case(ADDING):   addNewEmployee(employee);   break;
		case(EDITING):  editEmployee(employee);     break;
		case(DELETING): deleteEmployee(employee);   break;
		case(E_BACK): break;
		default: std::cout << termcolor::red << "Введите цифру из списка!" << termcolor::reset; Sleep(2000); system("cls");
		}

	} while (choise != 5);
}

// режим обработки
void processsingMode(std::vector<Employee>& employee, std::vector<int>& indexes)
{
	int choise;
	do
	{
		std::cout << "---------------------------------------------РЕЖИМ ОБРАБОТКИ-----------------------------------------------------------" << std::endl;
		std::cout << "1. Поиск.\n";
		std::cout << "2. Сортировка.\n";
		std::cout << "3. Поиск сотрудников пенсионного возраста.\n";
		std::cout << "4. Назад.\n\n";

		choise = checkInput();
		system("cls");
		switch (choise)
		{
		case(SEARCH): chooseTypeOfSearch(employee); break;
		case(SORTING): chooseTypeOfSort(employee); break;
		case(INDIVIDUAL_TASK): searchForEmployeesOfRetirementAge(employee, indexes); break;
		case(P_BACK): break;
		default: std::cout << termcolor::red << "Введите цифру из списка!" << termcolor::reset; Sleep(2000); system("cls");
		}

	} while (choise != 4);
}

// настройки
void rusSettings(std::vector<Employee>& employee, std::vector<int>& indexes, std::vector<Authentication>& authentication, int& languageStatus)
{
	int choise;
	do
	{
		std::cout << "----------------------------------------------НАСТРОЙКИ---------------------------------------------------------------\n";
		std::cout << "1. Язык.\n";
		std::cout << "2. Назад.\n";

		choise = checkInput();
		system("cls");
		switch (choise)
		{
		case(LANGUAGE): rusChooseMenuLanguage(employee, indexes, authentication, languageStatus); break;
		case(S_BACK): break;
		default: std::cout << termcolor::red << "Введите цифру из списка!" << termcolor::reset; Sleep(2000); system("cls");
		}

	} while (choise != 2);
}

// возврыщает 1 - русский язык, 2 - английский язык
void rusChooseMenuLanguage(std::vector<Employee>& employee, std::vector<int>& indexes, std::vector<Authentication>& authentication, int &languageStatus)
{
	int choise;
	do 
	{
		std::cout << "----------------------------------------------НАСТРОЙКИ ЯЗЫКА---------------------------------------------------------\n";
		std::cout << "1. Русский.\n";
		std::cout << "2. English.\n";

		choise = checkInput();
		system("cls");

		if (choise == 1 or choise == 2)
		{
			if (choise == 1)
				languageStatus = 0;
			else if (choise == 2)
				languageStatus = 1;

			writeLanguageInFile(languageStatus);

			std::cout << "Переключение языка";
			for (int i = 0; i < 3; i++)
			{
				Sleep(600);
				std::cout << ".";
			}
			system("cls");

			std::cout << termcolor::green << "Переключение прошло успешно!" << termcolor::reset;
			Sleep(2000);
			system("cls");

			turnMenuLanguge(choise, employee, indexes, authentication, languageStatus);
			return;
		}
		else
		{
			std::cout << termcolor::red << "Выберите цифру из списка!" << termcolor::reset;
			Sleep(1300);
			system("cls");
		}
	} while (true);
}

// перекулючение меню на другой язык
void turnMenuLanguge(int choise, std::vector<Employee>& employee, std::vector<int>& indexes, std::vector<Authentication>& authentication, int& languageStatus)
{
	if (choise == 1)
		RusMainMenu(employee, indexes, authentication, languageStatus);
	else if (choise == 2)
		EngMainMenu(employee, indexes, authentication, languageStatus);
}


//АНГЛИЙСКОЕ МЕНЮ
void EngMainMenu(std::vector<Employee>& employee, std::vector<int>& indexes, std::vector<Authentication>& authentication, int& languageStatus)
{
	int choise;
	do
	{
		std::cout << "-------------------------------ACCOUNTING THE EXPERIENCE OF EMPLOYEES OF THE ENTERPRISE---------------------------------" << std::endl;
		std::cout << "1. Edit mode.\n";
		std::cout << "2. Processing mode.\n";
		std::cout << "3. Settings.\n";
		std::cout << "4. Exit.\n\n";

		choise = engCheckInput();
		system("cls");
		switch (choise)
		{
		case(EDITING_MODE): EngEditingMode(employee); break;
		case(PROCESSING_MODE): EngProcesssingMode(employee, indexes); break;
		case(SETTINGS): engSettings(employee, indexes, authentication, languageStatus); break;
		case(EXIT): break;
		default: std::cout << termcolor::red << "Choose number from list!" << termcolor::reset; Sleep(2000); system("cls");
		}

	} while (choise != 4);
}

// выбор типа сортировки 
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

// выбор сортировки в порядке убывания или в порядке возрастания
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

// выбор типа поиска
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

// режим редактирования
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

		choise = engCheckInput();
		system("cls");
		switch (choise)
		{
		case(CHECKING): std::cout << "Here is a list of all current employees:\n\n"; printAllEmployee(employee); break;
		case(ADDING):   engAddNewEmployee(employee);   break;
		case(EDITING):  engEditEmployee(employee);     break;
		case(DELETING): engDeleteEmployee(employee);   break;
		case(E_BACK): break;
		default: std::cout << termcolor::red << "Choose number from list!" << termcolor::reset; Sleep(2000); system("cls");
		}

	} while (choise != 5);
}

// режим обработки
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

		choise = engCheckInput();
		system("cls");
		switch (choise)
		{
		case(SEARCH): chooseTypeOfSearch(employee); break;
		case(SORTING): chooseTypeOfSort(employee); break;
		case(INDIVIDUAL_TASK): searchForEmployeesOfRetirementAge(employee, indexes); break;
		case(P_BACK): break;
		default: std::cout << termcolor::red << "Choose number from list!" << termcolor::reset; Sleep(2000); system("cls");
		}

	} while (choise != 4);
}

// выбор языка 
void engChooseMenuLanguage(std::vector<Employee>& employee, std::vector<int>& indexes, std::vector<Authentication>& authentication, int &languageStatus)
{
	int choise;
	do
	{
		std::cout << "-----------------------------------------SETTINGS OF LANGUAGE----------------------------------------------------\n";
		std::cout << "1. Русский.\n";
		std::cout << "2. English.\n";

		choise = engCheckInput();
		system("cls");

		if (choise == 1 or choise == 2)
		{
			if (choise == 1)
				languageStatus = 0;
			else if (choise == 2)
				languageStatus = 1;

			writeLanguageInFile(languageStatus);

			std::cout << "Switching language";
			for (int i = 0; i < 3; i++)
			{
				Sleep(600);
				std::cout << ".";
			}
			system("cls");

			std::cout << termcolor::green << "The switch was successful!" << termcolor::reset;
			Sleep(2000);
			system("cls");

			turnMenuLanguge(choise, employee, indexes, authentication, languageStatus);
			return;
		}
		else
		{
			std::cout << termcolor::red << "Choose number from list!" << termcolor::reset;
			Sleep(1300);
			system("cls");
		}
	} while (true);
}

// настройки
void engSettings(std::vector<Employee>& employee, std::vector<int>& indexes, std::vector<Authentication>& authentication, int& languageStatus)
{

	int choise;

	do
	{
		std::cout << "----------------------------------------------SETTINGS---------------------------------------------------------------\n";
		std::cout << "1. Language.\n";
		std::cout << "2. Back.\n";

		choise = checkInput();
		system("cls");
		switch (choise)
		{
		case(LANGUAGE): engChooseMenuLanguage(employee, indexes, authentication, languageStatus); break;
		case(S_BACK): break;
		default: std::cout << termcolor::red << "Choose number from list!" << termcolor::reset; Sleep(2000); system("cls");
		}

	} while (choise != 2);
}