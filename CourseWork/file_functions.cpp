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

// запись в файл состояния входа
void writeEntryStatus(int& entryStatus)
{
	entryStatus = 1;
	std::fstream file("entryStatus.txt");

	file << entryStatus;
}

// запись данных из файла в вектор auth
void writingToVectorsFromFileAuth(std::vector<Authentication>& authentication)
{
	std::ifstream auth("Authentication_Data.txt");

	int i = 0;
	while (!auth.eof())
	{
		Authentication authen;
		auth >> authen.login;
		auth >> authen.password;

		authentication.push_back(authen);
		i++;
	}
	auth.close();
}

// запись данных из файла в вектор employee
void writingToVectorsFromFileEmployee(std::vector<Employee>& employee)
{
	std::ifstream empl("Employee_Data.txt");
	int j = 0;
	while (!empl.eof())
	{
		Employee emp;
		std::string post1;

		empl >> emp.surName;
		empl >> emp.name;
		empl >> emp.patronymic;
		empl >> emp.gender;
		empl >> emp.dateOfBirthday;
		empl >> emp.departmentName;
		empl >> post1;

		if (post1 == "Junior")
			emp.post = Post::JUNIOR;
		else if (post1 == "Middle")
			emp.post = Post::MIDDLE;
		else if (post1 == "Senior")
			emp.post = Post::SENIOR;
		else if (post1 == "Team_leader")
			emp.post = Post::TEAM_LEADER;
		else if (post1 == "Project_manager")
			emp.post = Post::PROJECT_MANAGER;
		else if (post1 == "Director_of_department")
			emp.post = Post::DIRECTOR_OF_DEPARTMENT;
		else if (post1 == "Deputy_general_director")
			emp.post = Post::DEPUTY_GENERAL_DIRECTOR;
		else if (post1 == "General_director")
			emp.post = Post::GENERAL_DIRECTOR;

		empl >> emp.startDate;

		employee.push_back(emp);

		j++;
	}
	empl.close();
}

// запись в файл нового сотрудника
void writeInfoOfNewEmployeeInFile(std::vector<Employee>& employee, std::string surName, std::string name, std::string patronymic, std::string gender, std::string dateOfBirthday, std::string departmenrName, std::string post, std::string startDate)
{
	std::ofstream empl("Employee_Data.txt", std::ios::app);
	empl << "\n";
	empl << surName << " ";
	empl << name << " ";
	empl << patronymic << " ";
	empl << gender << " ";
	empl << dateOfBirthday << " ";
	empl << departmenrName << " ";
	empl << post << " ";
	empl << startDate;

	empl.close();
}

// запись данных в файл сотрудников из вектора
void writeInToFileAfterDeleteEmployee(std::vector<Employee>& employee)
{
	std::ofstream empl("Employee_Data.txt");

	for (int i = 0; i < employee.size(); i++)
	{
		empl << employee.at(i).surName << " ";
		empl << employee.at(i).name << " ";
		empl << employee.at(i).patronymic << " ";
		empl << employee.at(i).gender << " ";
		empl << employee.at(i).dateOfBirthday << " ";
		empl << employee.at(i).departmentName << " ";

		if (static_cast<int>(employee.at(i).post) == 1)
			empl << "Junior ";
		else if (static_cast<int>(employee.at(i).post) == 2)
			empl << "Middle ";
		else if (static_cast<int>(employee.at(i).post) == 3)
			empl << "Senior ";
		else if (static_cast<int>(employee.at(i).post) == 4)
			empl << "Team_leader ";
		else if (static_cast<int>(employee.at(i).post) == 5)
			empl << "Project_manager ";
		else if (static_cast<int>(employee.at(i).post) == 6)
			empl << "Director_of_department ";
		else if (static_cast<int>(employee.at(i).post) == 7)
			empl << "Deputy_general_diretor ";
		else if (static_cast<int>(employee.at(i).post) == 8)
			empl << "General_director ";

		empl << employee.at(i).startDate << std::endl;

	}

	empl.close();
}

// запись в файл текущее время для будущих запусков
void secondsSinceLastExecution(int& entryStatus)
{
	int secondsSinceLastExecution = checkHowManyTimeGo(entryStatus);
	if (secondsSinceLastExecution != -1) {
		std::cout << "Time since last execution: " << secondsSinceLastExecution << " seconds" << std::endl;
	}

	// Сохраняем текущее время в файл для будущих запусков
	std::ofstream file("Time.txt");
	if (file.fail()) {
		std::cerr << "Ошибка! Не удалось откурыть файл 'Time.txt' для записи" << std::endl;
	}
	else {
		auto now = std::chrono::system_clock::now();
		std::time_t now_t = std::chrono::system_clock::to_time_t(now);
		struct tm timeinfo;
		localtime_s(&timeinfo, &now_t);
		char time_buffer[20];
		std::strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
		file << time_buffer;
		file.close(); // Закрываем файл после записи данных
	}
}

// проверка состояния языка
void writeLanguageInFile(int &languageStatus)
{
	std::fstream file("language.txt");
	file << languageStatus;
	file.close();
}