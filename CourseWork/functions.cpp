#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "structs.h"
#include "prototypes.h"
#include "enums.h"
#include <Windows.h>
#include <chrono>
#include "termcolor.hpp"
#include <conio.h>



// �������� ������������ ����� ������(���� � �������)            
int checkDataOfUser(std::vector<Authentication>& authentication, int &tries, int &entryStatus)
{
	std::string login;
	std::string password;
	// �������� ������������ ��� ������ ��������� �� ������
	bool check = false;

	while (true)
	{
		std::cout << "������� �����:  ";
		std::cin >> login;
		std::cout << "������� ������: ";
		std::cin >> password;
		Sleep(700);
		system("cls");

		for (int i = 0; i < authentication.size(); i++)
		{
			if (login == authentication.at(i).login and password == authentication.at(i).password)
			{
				std::cout << termcolor::green << "���� �������� �������!" << termcolor::reset;
				Sleep(2000);
				writeEntryStatus(entryStatus);
				system("cls");
				return 1;
			}
		}
		if (!check)
		{
			tries++;
			if (tries > 4)
				return -100;
			std::cout <<termcolor::red<< "������ ��������. ���������� ��� ���..." <<termcolor::reset<< std::endl;
			Sleep(2000);
			system("cls");
		}
	}
}

// �������� ����������� ������
int isLoginAvailable(std::string login, std::vector<Authentication>& authentication)
{
	int count = 0;
	for (int i = 0; i < authentication.size(); i++)
	{
		if (login == authentication.at(i).login)
			return 1;
		
		count++;

		if (count == authentication.size())
			return 0;   // ���� ���������� count ����� ����� ����� �������, �� ����� �� ����������� 
	}
}

// �������� �� ���������� ���������� ��� ������
int isPasswordGood(std::string password, std::string login)
{
	// ������� ����
	int count = 0;

	// �������� �� ������� ����� � ������
	for (int i = 0; i < password.length(); i++)
	{
		if (isdigit(password[i]))
			count++;
	}


	int capitalLetter = 0;

	for (int i = 0; i < password.length(); i++)
	{
		if (isupper(password[i]))
		{
			capitalLetter++;
			break;        // ������ ��� ����� ���� �� ��������� �����
		}
	}


	if (password.length() >= 6 and count >= 1 and capitalLetter == 1 and checkIfLoginInPassword(login, password))
		return 0; 
	else
		return 1;
}

// ������������ ������ ��� �����������
int confirmPassword(std::string passwordForConfirm, std::string password)
{
	if (password == passwordForConfirm)
		return 0;
	else
		return 1;
}

// ��������, ��� �� � ������ ������(��� �����������) | 1 - �� ������� ������, 0 - ��������
int checkIfLoginInPassword(std::string login, std::string password)
{
	if (password.find(login) != std::string::npos)
		return 0;
	else
		return 1;
}

// ����������� � �������
void registration(std::vector<Authentication>& authentication)
{
	std::string login;
	std::string password;
	std::string passwordForConfirm;

	do
	{
		std::cout << "������� ��� ����� �����: ";
		std::cin >> login;

	} while (isLoginAvailable(login, authentication));   // ���� ��� ������ 0, ���� ��������

	do
	{
		std::cout << "������� ��� ����� ������: ";
		std::cin >> password;

	} while (isPasswordGood(password, login));  // ���� ��� ������ 0, ���� ��������

	do
	{
		std::cout << "����������� ������: ";
		std::cin >> passwordForConfirm;
	} while (confirmPassword(passwordForConfirm, password));

	system("cls");
	std::cout << termcolor::green << "����������� ������ �������!" << termcolor::reset;
	Sleep(2000);
	system("cls");

	std::ofstream auth("Authentication_Data.txt", std::ios::app);
	auth << "\n";
	auth << login;
	auth << " ";
	auth << password;
	auth.close();
}




//����� ���� ������� ����������.
void printAllEmployee(std::vector<Employee> & employee)
{
	for (int i = 0; i < employee.size(); i++)
	{
		if (employee[i].name == "")
			break;

		std::cout <<i+1<<((i<9)? ".  ":". " )<< employee.at(i).surName << " ";
		std::cout << employee.at(i).name << " ";
		std::cout << employee.at(i).patronymic << " ";
		std::cout << employee.at(i).gender << " ";
		std::cout << employee.at(i).dateOfBirthday << " ";
		std::cout << employee.at(i).departmentName << " ";
		if (static_cast<int>(employee.at(i).post) == 1)
			std::cout << "Junior ";
		else if (static_cast<int>(employee.at(i).post) == 2)
			std::cout << "Middle ";
		else if (static_cast<int>(employee.at(i).post) == 3)
			std::cout << "Senior ";
		else if (static_cast<int>(employee.at(i).post) == 4)
			std::cout << "Team Leader ";
		else if (static_cast<int>(employee.at(i).post) == 5)
			std::cout << "Project Manager ";
		else if (static_cast<int>(employee.at(i).post) == 6)
			std::cout << "Director of department ";
		else if (static_cast<int>(employee.at(i).post) == 7)
			std::cout << "Deputy general diretor ";
		else if (static_cast<int>(employee.at(i).post) == 8)
			std::cout << "General Director ";
		std::cout << employee.at(i).startDate << " " << std::endl;
	}
	std::cout << std::endl;
}

// ���������� ������ ����������
void addNewEmployee(std::vector<Employee>& employee)
{
	std::string surName;
	std::string name;
	std::string patronymic;
	std::string gender;
	std::string dateOfBirthday;
	std::string departmentName;
	std::string post;
	std::string startDate;

	std::cout << "������� ������� ����������: ";
	std::cin >> surName;
	std::cout << "������� ��� ����������: ";
	std::cin >> name;
	std::cout << "������� �������� ����������: ";
	std::cin >> patronymic;
	std::cout << "������� ��� ����������: ";
	std::cin >> gender;
	std::cout << "������� ���� �������� ����������: ";
	std::cin >> dateOfBirthday;
	std::cout << "������� �������� ������ ����������: ";
	std::cin >> departmentName;
	std::cout << "������� ��������� ����������: ";
	std::cin >> post;
	std::cout << "������� ���� ������ ������ ����������: ";
	std::cin >> startDate;

	writeInfoOfNewEmployeeInFile(employee, surName, name, patronymic, gender, dateOfBirthday, departmentName, post, startDate);
	writeEmployeeIntoVector(employee, surName, name, patronymic, gender, dateOfBirthday, departmentName, post, startDate);

	system("cls");
	std::cout << termcolor::green << "���������� ������ �������!" << termcolor::reset;
	Sleep(1700);
	system("cls");
}

// ���������� ���������� � ������ ����� ���������� ������ ����������
void writeEmployeeIntoVector(std::vector<Employee>& employee, std::string surName, std::string name, std::string patronymic, std::string gender, std::string dateOfBirthday, std::string departmenrName, std::string post, std::string startDate)
{
	Employee emp;
	emp.surName = surName;
	emp.name = name;
	emp.patronymic = patronymic;
	emp.gender = gender;
	emp.dateOfBirthday = dateOfBirthday;
	emp.departmentName = departmenrName;

	if (post == "Junior")
		emp.post = Post::JUNIOR;
	else if (post == "Middle")
		emp.post = Post::MIDDLE;
	else if (post == "Senior")
		emp.post = Post::SENIOR;
	else if (post == "Team_leader")
		emp.post = Post::TEAM_LEADER;
	else if (post == "Project_manager")
		emp.post = Post::PROJECT_MANAGER;
	else if (post == "Director_of_department")
		emp.post = Post::DIRECTOR_OF_DEPARTMENT;
	else if (post == "Deputy_general_director")
		emp.post = Post::DEPUTY_GENERAL_DIRECTOR;
	else if (post == "General_director")
		emp.post = Post::GENERAL_DIRECTOR;

	emp.startDate = startDate;

	employee.push_back(emp);
}

// �������� ������ � ���������� �� �������
void deleteEmployee(std::vector<Employee>& employee)
{
	int number;

	while (true)
	{
		std::cout << "������ �����������: \n\n";
		printAllEmployee(employee);

		std::cout << "������� ����� ���������� �� ������ ��� ��������: ";
		std::cin >> number;

		if (std::cin.fail() or (number < 1 or number > employee.size())) // ���� ���������� ���������� ��������� ���������,
		{
			std::cin.clear(); // �� ���������� cin � '�������' ����� ������
			std::cin.ignore(32767, '\n'); // � ������� �������� �����������
			system("cls");
			std::cout << termcolor::red << "������� ����� �� ������!" << termcolor::reset;
			Sleep(1700);
			system("cls");
			continue;
		}
		else // ���� �� ������, �� ���������� a
		{
			system("cls");
			break;
		}
	}
	system("cls");

	if (areYouSure())
	{
		employee.erase(employee.begin() + number - 1);
		system("cls");
		std::cout << termcolor::green << "�������� ������ �������!" << termcolor::reset;
		Sleep(2000);
		system("cls");
	}
	else
	{
		system("cls");
		std::cout << termcolor::red << "�������� �� ���� ���������!" << termcolor::reset;
		Sleep(2000);
		system("cls");
	}

	writeInToFileAfterDeleteEmployee(employee);
}

// ������������� ��������
int areYouSure()
{
	std::string answer;
	std::cout << "�� �������?: ";
	std::cin >> answer;

	if (answer == "��" or answer == "Yes" or answer == "��" or answer == "yes" or answer == "y" or answer == "Y")
		return 1;
	else
		return 0;
}

// �������������� ������� � �����������
void editEmployee(std::vector<Employee>& employee)
{
	int number;
	int answer;
	while (true)
	{
		printAllEmployee(employee);
		std::cout << "������� ����� ����������, ������ �������� ������ ��������������: ";

		std::cin >> number;
		if (std::cin.fail() or (number < 1 or number > employee.size())) // ���� ���������� ���������� ��������� ���������,
		{
			std::cin.clear(); // �� ���������� cin � '�������' ����� ������
			std::cin.ignore(32767, '\n'); // � ������� �������� �����������
			system("cls");
			std::cout << termcolor::red << "������� ����� �� ������!" << termcolor::reset;
			Sleep(1700);
			system("cls");
			continue;
		}
		else // ���� �� ������, �� ���������� a
		{
			system("cls");
			break;
		}
	}

	do
	{
		std::cout << "1. �������" << std::endl;
		std::cout << "2. ���" << std::endl;
		std::cout << "3. ��������" << std::endl;
		std::cout << "4. ���" << std::endl;
		std::cout << "5. ���� ��������" << std::endl;
		std::cout << "6. �������� ������" << std::endl;
		std::cout << "7. ���������" << std::endl;
		std::cout << "8. ���� ������ ������\n" << std::endl;

		std::cout << "��������, ��� ������ ��������: ";

		std::cin >> answer;
		std::cout << std::endl;
		if (std::cin.fail() or (answer < 1 or answer > 8)) // ���� ���������� ���������� ��������� ���������,
		{
			std::cin.clear(); // �� ���������� cin � '�������' ����� ������
			std::cin.ignore(32767, '\n'); // � ������� �������� �����������
			system("cls");
			std::cout << termcolor::red << "�������� ����� �� ������!" << termcolor::reset;
			Sleep(1700);
			system("cls");
			continue;
		}
		else
		{
			system("cls");
			break;
		}
	} while (true);

	std::string newInfo;
	std::cout << "������� ���������� ����������: ";
	std::cin >> newInfo;

	switch (answer)
	{
	case(1): employee.at(number - 1).surName = newInfo; break;
	case(2): employee.at(number - 1).name = newInfo; break;
	case(3): employee.at(number - 1).patronymic = newInfo; break;
	case(4): employee.at(number - 1).gender = newInfo; break;
	case(5): employee.at(number - 1).dateOfBirthday = newInfo; break;
	case(6): employee.at(number - 1).departmentName = newInfo; break;
	case(7):
		if (newInfo == "Junior")
		{
			employee.at(number - 1).post = Post::JUNIOR;
			break;
		}
		else if (newInfo == "Middle")
		{
			employee.at(number - 1).post = Post::MIDDLE;
			break;
		}
		else if (newInfo == "Senior")
		{
			employee.at(number - 1).post = Post::SENIOR;
			break;
		}
		else if (newInfo == "Team_leader")
		{
			employee.at(number - 1).post = Post::TEAM_LEADER;
			break;
		}
		else if (newInfo == "Project_manager")
		{
			employee.at(number - 1).post = Post::PROJECT_MANAGER;
			break;
		}
		else if (newInfo == "Director_of_department")
		{
			employee.at(number - 1).post = Post::DIRECTOR_OF_DEPARTMENT;
			break;
		}
		else if (newInfo == "Deputy_general_director")
		{
			employee.at(number - 1).post = Post::DEPUTY_GENERAL_DIRECTOR;
			break;
		}
		else if (newInfo == "General_director")
		{
			employee.at(number - 1).post = Post::GENERAL_DIRECTOR;
			break;
		}
	case(8): employee.at(number - 1).startDate = newInfo; break;
	default: break;
	}

	writeInToFileAfterDeleteEmployee(employee);

	system("cls");
	std::cout << termcolor::green << "�������������� ������ ������ �������!" << termcolor::reset;
	Sleep(1800);
	system("cls");
}




// ����� �� �������
void searchForSurName(std::vector<Employee>& employee)
{
		std::string surName;
		std::cout << "������� ������� ����������: ";
		std::cin >> surName;
		system("cls");

		bool isThereAtLeastOne = false;
		bool onlyOneTime = false;

		for (int i = 0; i < employee.size(); i++)
		{
			int index = i;
			if (employee[i].surName == surName)
			{
				isThereAtLeastOne = true;

				isThereAtLeastOne = true;
				if (!onlyOneTime)
				{
					std::cout << "���������/�� ���������/�: \n\n";
					onlyOneTime = true;
				}

				for (int j = 0; j < 1; j++)
				{
					std::cout << employee.at(index).surName << " ";
					std::cout << employee.at(index).name << " ";
					std::cout << employee.at(index).patronymic << " ";
					std::cout << employee.at(index).gender << " ";
					std::cout << employee.at(index).dateOfBirthday << " ";
					std::cout << employee.at(index).departmentName << " ";

					switch (employee.at(index).post) {
					case Post::JUNIOR:
						std::cout << "Junior ";
						break;
					case Post::MIDDLE:
						std::cout << "Middle ";
						break;
					case Post::SENIOR:
						std::cout << "Senior ";
						break;
					case Post::TEAM_LEADER:
						std::cout << "Team_leader ";
						break;
					case Post::PROJECT_MANAGER:
						std::cout << "Project_manager ";
						break;
					case Post::DIRECTOR_OF_DEPARTMENT:
						std::cout << "Director_of_department ";
						break;
					case Post::DEPUTY_GENERAL_DIRECTOR:
						std::cout << "Deputy_general_director ";
						break;
					case Post::GENERAL_DIRECTOR:
						std::cout << "General_director ";
						break;
					}
					std::cout << employee.at(index).startDate << " " << std::endl;
				}
			}
		}
		if (!isThereAtLeastOne)
		{
			std::cout << termcolor::red << "�� ������� ����������� � ����� ��������!" << termcolor::reset;
			Sleep(1800);
			system("cls");
			return;
		}
		std::cout << "\n������� ����� �������...";
		_getch();

		system("cls");
}

// ����� �� ���������
void searchForPost(std::vector<Employee>& employee)
{
	std::string post;
	int post1;
	std::cout << "������� ��������� ����������: ";
	std::cin >> post;
	system("cls");

	if (post == "Junior")
		post1 = static_cast<int>(Post::JUNIOR);
	else if (post == "Middle")
		post1 = static_cast<int>(Post::MIDDLE);
	else if (post == "Senior")
		post1 = static_cast<int>(Post::SENIOR);
	else if (post == "Team_leader")
		post1 = static_cast<int>(Post::TEAM_LEADER);
	else if (post == "Project_manager")
		post1 = static_cast<int>(Post::PROJECT_MANAGER);
	else if (post == "Director_of_department")
		post1 = static_cast<int>(Post::DIRECTOR_OF_DEPARTMENT);
	else if (post == "Deputy_general_director")
		post1 = static_cast<int>(Post::DEPUTY_GENERAL_DIRECTOR);
	else if (post == "General_director")
		post1 = static_cast<int>(Post::GENERAL_DIRECTOR);
	else
		// ����� �� ���� ������ "���������� �� ����������������"
		post1 = -1;

	// ���������� ������, ����� ���������� �������, ���� �� ������� ������ �����������
	bool isThereAtLeastOne = false;
	//���������� ������, ����� ������� ���������� ���� ���
	bool onlyOneTime = false; 

	for (int i = 0; i < employee.size(); i++)
	{
		int index = i;
		if (static_cast<int>(employee[i].post) == post1)
		{
			isThereAtLeastOne = true;
			if (!onlyOneTime)
			{
				std::cout << "���������/�� ���������/�:\n\n";
				onlyOneTime = true;
			}
			for (int j = 0; j < 1; j++)
			{
				std::cout << employee.at(index).surName << " ";
				std::cout << employee.at(index).name << " ";
				std::cout << employee.at(index).patronymic << " ";
				std::cout << employee.at(index).gender << " ";
				std::cout << employee.at(index).dateOfBirthday << " ";
				std::cout << employee.at(index).departmentName << " ";

				switch (employee.at(index).post)
				{
				case Post::JUNIOR:
					std::cout << "Junior ";
					break;
				case Post::MIDDLE:
					std::cout << "Middle ";
					break;
				case Post::SENIOR:
					std::cout << "Senior ";
					break;
				case Post::TEAM_LEADER:
					std::cout << "Team_leader ";
					break;
				case Post::PROJECT_MANAGER:
					std::cout << "Project_manager ";
					break;
				case Post::DIRECTOR_OF_DEPARTMENT:
					std::cout << "Director_of_department ";
					break;
				case Post::DEPUTY_GENERAL_DIRECTOR:
					std::cout << "Deputy_general_director ";
					break;
				case Post::GENERAL_DIRECTOR:
					std::cout << "General_director ";
					break;
				}

				std::cout << employee.at(index).startDate << std::endl;
			}
		}
	}

	if (!isThereAtLeastOne)
	{
		std::cout << termcolor::red << "�� ������� �����������, ������� ������ ���������!\n" << termcolor::reset;
		Sleep(2000);
		system("cls");
		return;
	}

	std::cout << "\n������� ����� �������...";
	_getch();
	system("cls");
}

// ����� �� ���� ������ ������
void searchForStartDate(std::vector<Employee>& employee)
{
	int startDate;

	while (true)
	{
		std::cout << "������� ��� ������ ������ ����������: ";
		std::cin >> startDate;

		if (std::cin.fail()) // ���� ���������� ���������� ��������� ���������,
		{
			std::cin.clear(); // �� ���������� cin � '�������' ����� ������
			std::cin.ignore(32767, '\n'); // � ������� �������� �����������
			system("cls");
			std::cout << termcolor::red << "������� ���������� ����!" << termcolor::reset;
			Sleep(1500);
			system("cls");
		}
		else
			break;
	}
	system("cls");


	bool isThereAtLeastOne = false;
	bool onlyOneTime = false;

	for (int i = 0; i < employee.size(); i++)
	{
		int index = i;

		if (std::stoi(employee.at(index).startDate.substr(6)) == startDate)
		{
			isThereAtLeastOne = true;

			isThereAtLeastOne = true;
			if (!onlyOneTime)
			{
				std::cout << "���������/�� ���������/�: \n\n";
				onlyOneTime = true;
			}

			for (int j = 0; j < 1; j++)
			{
				std::cout << employee.at(index).surName << " ";
				std::cout << employee.at(index).name << " ";
				std::cout << employee.at(index).patronymic << " ";
				std::cout << employee.at(index).gender << " ";
				std::cout << employee.at(index).dateOfBirthday << " ";
				std::cout << employee.at(index).departmentName << " ";

				switch (employee.at(index).post)
				{
				case Post::JUNIOR:
					std::cout << "Junior ";
					break;
				case Post::MIDDLE:
					std::cout << "Middle ";
					break;
				case Post::SENIOR:
					std::cout << "Senior ";
					break;
				case Post::TEAM_LEADER:
					std::cout << "Team_leader ";
					break;
				case Post::PROJECT_MANAGER:
					std::cout << "Project_manager ";
					break;
				case Post::DIRECTOR_OF_DEPARTMENT:
					std::cout << "Director_of_department ";
					break;
				case Post::DEPUTY_GENERAL_DIRECTOR:
					std::cout << "Deputy_general_director ";
					break;
				case Post::GENERAL_DIRECTOR:
					std::cout << "General_director ";
					break;
				}
				std::cout << employee.at(index).startDate << std::endl;
			}
		}
	}
	if (!isThereAtLeastOne)
	{
		std::cout << termcolor::red << "�� ������� ����������� � ������ ����� ������ ������!\n" << termcolor::reset;
		Sleep(2000);
		system("cls");
		return;
	}

	std::cout << "\n������� ����� �������...";
	_getch();
	system("cls");
}



// ���������� �� ������� � ������� ��������(���������)
void sortWithSurNameDown(std::vector<Employee> & employee)
{
	for (int i = 0; i < employee.size() - 1; i++)
	{
		bool swapped = false;
		int endOfArr = employee.size() - i;
		for (int j = 0; j < endOfArr - 1; j++)
		{

			if (employee.at(j).surName < employee.at(j + 1).surName)
			{
				std::swap(employee.at(j), employee.at(j+1));
				swapped = true;
			}
		}

		if (!swapped)
			break;
	}
}

// ���������� �� ������� � ������� �����������(���������)
void sortWithSurNameUp(std::vector<Employee>& employee)
{
	for (int i = 0; i < employee.size() - 1; i++)
	{
		bool swapped = false;
		int endOfArr = employee.size() - i;
		for (int j = 0; j < endOfArr - 1; j++)
		{
			if (employee.at(j).surName > employee.at(j + 1).surName)
			{
				std::swap(employee.at(j), employee.at(j + 1));
				swapped = true;
			}
		}

		if (!swapped)
		{
			break;
		}
	}
}

// ����� ����������� �������� ��� ���������� �������
int findSmallestPosition(std::vector<Employee> &employee, int startPosition)
{
	int smallestPosition = startPosition;

	for (int i = startPosition; i < employee.size(); i++)
	{
		if (employee.at(i).post < employee.at(smallestPosition).post)
			smallestPosition = i;
	}
	return smallestPosition;
}

// ���������� �� ��������� � ������� �����������(������� ������)
void sortWithPostUp(std::vector<Employee> &employee)
{
	for (int i = 0; i < employee.size(); i++)
	{
		int smallestPosition = findSmallestPosition(employee, i);
		std::swap(employee.at(i), employee.at(smallestPosition));
	}
}

// ����� ����������� �������� ��� ���������� �������
int findBiggestPosition(std::vector<Employee>& employee, int startPosition)
{
	int biggestPosition = startPosition;

	for (int i = startPosition; i < employee.size(); i++)
	{
		if (employee.at(i).post > employee.at(biggestPosition).post)
			biggestPosition = i;
	}
	return biggestPosition;
}

// ���������� �� ��������� � ������� ��������(������� ������)
void sortWithPostDown(std::vector<Employee>& employee)
{
	for (int i = 0; i < employee.size(); i++)
	{
		int biggestPosition = findBiggestPosition(employee, i);
		std::swap(employee.at(i), employee.at(biggestPosition));
	}
}

// ������� ���������� ����� ����� ���� ������������
int getNumber(std::vector<Employee>& employee, int index)
{
	std::string number;
	int result;

	// ������� ��� � number
	number += employee.at(index).startDate.substr(6);
	// ������� �����
	number += employee.at(index).startDate.substr(3, 2);
	// ������� ����
	number += employee.at(index).startDate.substr(0, 2);
	// c_str ���������� ��������� �� ������, ���������� ������������������ ��������, ������������� �����("\0)
	result = atoi(number.c_str());

	return result;
}

// ���������� �� ����� � ������� ��������
void sortWithExperienceDown(std::vector<Employee>& employee)
{
	for (int i = 0; i < employee.size() - 1; i++)
	{
		bool swapped = false;
		int endOfArr = employee.size() - i;
		for (int j = 0; j < endOfArr - 1; j++)
		{

			if (getNumber(employee, j) > getNumber(employee, j + 1))
			{
				std::swap(employee.at(j), employee.at(j + 1));
				swapped = true;
			}
		}

		if (!swapped)
			break;
	}
}

// ���������� �� ����� � ������� �����������
void sortWithExperienceUp(std::vector<Employee>& employee)
{
	for (int i = 0; i < employee.size() - 1; i++)
	{
		bool swapped = false;
		int endOfArr = employee.size() - i;
		for (int j = 0; j < endOfArr - 1; j++)
		{

			if (getNumber(employee, j) < getNumber(employee, j + 1))
			{
				std::swap(employee.at(j), employee.at(j + 1));
				swapped = true;
			}
		}

		if (!swapped)
			break;
	}
}



// �������� �� ��� ����������
int checkGenderOfEmployee(std::vector<Employee>& employee, const int index)
{
	if (employee.at(index).gender == "Man")
		return 1;
	else if(employee.at(index).gender == "Woman")
		return 0;
}

// ��������� ������� ����������(� �����)
int ageOfEmployee(std::vector<Employee>&employee, const int index)
{
	std::tm timeinfo = {};
	timeinfo.tm_year = atoi(employee.at(index).dateOfBirthday.substr(6).c_str()) - 1900;  // ��� ��������� �� 1900
	timeinfo.tm_mon = atoi(employee.at(index).dateOfBirthday.substr(3, 2).c_str()) - 1;
	timeinfo.tm_mday = atoi(employee.at(index).dateOfBirthday.substr(0, 2).c_str());

	std::time_t custom_time = std::mktime(&timeinfo);

	// �������� ������� ����
	std::time_t end = std::time(nullptr);

	// ������������ �������
	std::tm end_tm = {};
	localtime_s(&end_tm, &end);
	int years = end_tm.tm_year - timeinfo.tm_year;

	// ���������, ��������� �� ���� �������� � ���� ����
	if (end_tm.tm_mon < timeinfo.tm_mon or (end_tm.tm_mon == timeinfo.tm_mon && end_tm.tm_mday < timeinfo.tm_mday))
		--years; // ���� ��� �� ������, ��������� ������� �� 1 ���

	return years;
}

// ����� ����������� � ���������� ���������
void searchForEmployeesOfRetirementAge(std::vector<Employee>& employee, std::vector<int> &indexes)
{
	indexes.reserve(employee.size());

	for (int index = 0; index < employee.size(); index++)
	{
		if ((checkGenderOfEmployee(employee, index) and ageOfEmployee(employee, index) >= 63) or (!checkGenderOfEmployee(employee, index) and ageOfEmployee(employee, index) >= 58))
			indexes.push_back(index);
	}

	printEmployeesOfRetirementAge(employee, indexes);
} 

// ����� ����������� � ���������� ���������
void printEmployeesOfRetirementAge(std::vector<Employee> & employee, std::vector<int> &indexes)
{

	if (indexes.empty())
	{
		std::cout << "����������� ����������� �������� ���.\n\n";
		return;
	}
		
	std::cout << "������ ���������� ����������� ��������: \n\n";
	for (int i = 0, j = 0; i < indexes.size(); i++, j++)
	{
		std::cout << employee.at(indexes.at(j)).surName << " ";
		std::cout << employee.at(indexes.at(j)).name << " ";
		std::cout << employee.at(indexes.at(j)).patronymic << " ";
		std::cout << employee.at(indexes.at(j)).gender << " ";
		std::cout << employee.at(indexes.at(j)).dateOfBirthday << " ";
		std::cout << employee.at(indexes.at(j)).departmentName << " ";

		switch (employee.at(indexes.at(j)).post)
		{
		case Post::JUNIOR:
			std::cout << "Junior ";
			break;
		case Post::MIDDLE:
			std::cout << "Middle ";
			break;
		case Post::SENIOR:
			std::cout << "Senior ";
			break;
		case Post::TEAM_LEADER:
			std::cout << "Team_leader ";
			break;
		case Post::PROJECT_MANAGER:
			std::cout << "Project_manager ";
			break;
		case Post::DIRECTOR_OF_DEPARTMENT:
			std::cout << "Director_of_department ";
			break;
		case Post::DEPUTY_GENERAL_DIRECTOR:
			std::cout << "Deputy_general_director ";
			break;
		case Post::GENERAL_DIRECTOR:
			std::cout << "General_director ";
			break;
		}

		std::cout << employee.at(indexes.at(j)).startDate << " " << std::endl;
	}
	std::cout << std::endl;
	std::cout << "������� ����� �������...";
	_getch();
	system("cls");
}

// �������� ���� ����������� � �����, ������� � ����
void getExperienceOfEmployees(std::vector<Employee> const& employee)
{
	for (int i = 0; i < employee.size(); i++)
	{
		// ����� ���������� start � ���������� ���� � �����
		std::tm timeinfo = {};
		timeinfo.tm_year = atoi(employee.at(i).startDate.substr(6).c_str()) - 1900;  // ��� ��������� �� 1900
		timeinfo.tm_mon = atoi(employee.at(i).startDate.substr(3, 2).c_str()) - 1;
		timeinfo.tm_mday = atoi(employee.at(i).startDate.substr(0, 2).c_str());

		std::time_t custom_time = std::mktime(&timeinfo);

		// �������� ������� ����
		std::time_t end = std::time(nullptr);

		// ��������� ������� � ��������
		std::time_t diff = end - custom_time;

		// ��������� ������� � ����, ������ � ���
		int years = diff / (60 * 60 * 24 * 365);
		int months = (diff % (60 * 60 * 24 * 365)) / (60 * 60 * 24 * 30);
		int days = ((diff % (60 * 60 * 24 * 365)) % (60 * 60 * 24 * 30)) / (60 * 60 * 24);

		std::cout << "������ " << years << " ���, "
			<< months << " �������, � "
			<< days << " ����." << std::endl;
	}
}



// ���� �������

// ���������� ����������
void engAddNewEmployee(std::vector<Employee>& employee)
{
	std::string surName;
	std::string name;
	std::string patronymic;
	std::string gender;
	std::string dateOfBirthday;
	std::string departmentName;
	std::string post;
	std::string startDate;

	std::cout << "Enter employee's surname: ";
	std::cin >> surName;
	std::cout << "Enter employee Name: ";
	std::cin >> name;
	std::cout << "Enter the employee's middle name: ";
	std::cin >> patronymic;
	std::cout << "Enter employee gender: ";
	std::cin >> gender;
	std::cout << "Enter the employee's date of birth: ";
	std::cin >> dateOfBirthday;
	std::cout << "Enter the employee's department name: ";
	std::cin >> departmentName;
	std::cout << "Enter the employee's position: ";
	std::cin >> post;
	std::cout << "Enter the employee's start date: ";
	std::cin >> startDate;

	writeInfoOfNewEmployeeInFile(employee, surName, name, patronymic, gender, dateOfBirthday, departmentName, post, startDate);
	writeEmployeeIntoVector(employee, surName, name, patronymic, gender, dateOfBirthday, departmentName, post, startDate);

	system("cls");
	std::cout <<termcolor::green<< "Addition was successful!"<<termcolor::reset;
	Sleep(1700);
	system("cls");
}

// �������� ������ � ���������� �� �������
void engDeleteEmployee(std::vector<Employee>& employee)
{

	int number;

	while (true)
	{
		std::cout << "List of current employees: \n\n";
		printAllEmployee(employee);

		std::cout << "Enter the employee number from the list to be deleted: ";
		std::cin >> number;
	
		if (std::cin.fail() or (number < 1 or number > employee.size())) // ���� ���������� ���������� ��������� ���������,
		{
			std::cin.clear(); // �� ���������� cin � '�������' ����� ������
			std::cin.ignore(32767, '\n'); // � ������� �������� �����������
			system("cls");
			std::cout << termcolor::red << "Choose number from the list!" << termcolor::reset;
			Sleep(1700);
			system("cls");
			continue;
		}
		else // ���� �� ������, �� ���������� a
		{
			system("cls");
			break;
		}
	}
	system("cls");

	if (engAreYouSure())
	{
		employee.erase(employee.begin() + number - 1);
		system("cls");
		std::cout << termcolor::green << "Removal was successful!" << termcolor::reset;
		Sleep(2000);
		system("cls");
	}
	else
	{
		system("cls");
		std::cout << termcolor::red << "Removal was not completed!" << termcolor::reset;
		Sleep(2000);
		system("cls");
	}

	writeInToFileAfterDeleteEmployee(employee);
}

// ������������� ��������
int engAreYouSure()
{
	std::string answer;
	std::cout << "Are you sure?: ";
	std::cin >> answer;

	if (answer == "��" or answer == "Yes" or answer == "yes" or answer == "��")
		return 1;
	else
		return 0;
}

// �������������� ������ � ����������
void engEditEmployee(std::vector<Employee>& employee)
{

	int number;
	int answer;
	while (true)
	{
		printAllEmployee(employee);
		std::cout << "Enter the number of the employee whose details you want to edit: ";

		std::cin >> number;
		if (std::cin.fail() or (number < 1 or number > employee.size())) // ���� ���������� ���������� ��������� ���������,
		{
			std::cin.clear(); // �� ���������� cin � '�������' ����� ������
			std::cin.ignore(32767, '\n'); // � ������� �������� �����������
			system("cls");
			std::cout << termcolor::red << "Choose number from the list!" << termcolor::reset;
			Sleep(1700);
			system("cls");
			continue;
		}
		else // ���� �� ������, �� ���������� a
		{
			system("cls");
			break;
		}
	}
	
	do
	{
		std::cout << "1. Surname" << std::endl;
		std::cout << "2. Name" << std::endl;
		std::cout << "3. Patronymic" << std::endl;
		std::cout << "4. Gender" << std::endl;
		std::cout << "5. Date of birthday" << std::endl;
		std::cout << "6. Name of department" << std::endl;
		std::cout << "7. Post" << std::endl;
		std::cout << "8. Start date\n" << std::endl;

		std::cout << "Choose what you want to edit: ";

		std::cin >> answer;
		std::cout << std::endl;
		if (std::cin.fail() or (answer < 1 or answer > 8)) // ���� ���������� ���������� ��������� ���������,
		{
			std::cin.clear(); // �� ���������� cin � '�������' ����� ������
			std::cin.ignore(32767, '\n'); // � ������� �������� �����������
			system("cls");
			std::cout << termcolor::red << "Choose number from the list!" << termcolor::reset;
			Sleep(1700);
			system("cls");
			continue;
		}
		else
		{
			system("cls");
			break;
		}
	} while (true);

	std::string newInfo;
	std::cout << "Please enter correct information: ";
	std::cin >> newInfo;

	switch (answer)
	{
	case(1): employee.at(number - 1).surName = newInfo; break;
	case(2): employee.at(number - 1).name = newInfo; break;
	case(3): employee.at(number - 1).patronymic = newInfo; break;
	case(4): employee.at(number - 1).gender = newInfo; break;
	case(5): employee.at(number - 1).dateOfBirthday = newInfo; break;
	case(6): employee.at(number - 1).departmentName = newInfo; break;
	case(7):
		if (newInfo == "Junior")
		{
			employee.at(number - 1).post = Post::JUNIOR;
			break;
		}
		else if (newInfo == "Middle")
		{
			employee.at(number - 1).post = Post::MIDDLE;
			break;
		}
		else if (newInfo == "Senior")
		{
			employee.at(number - 1).post = Post::SENIOR;
			break;
		}
		else if (newInfo == "Team_leader")
		{
			employee.at(number - 1).post = Post::TEAM_LEADER;
			break;
		}
		else if (newInfo == "Project_manager")
		{
			employee.at(number - 1).post = Post::PROJECT_MANAGER;
			break;
		}
		else if (newInfo == "Director_of_department")
		{
			employee.at(number - 1).post = Post::DIRECTOR_OF_DEPARTMENT;
			break;
		}
		else if (newInfo == "Deputy_general_director")
		{
			employee.at(number - 1).post = Post::DEPUTY_GENERAL_DIRECTOR;
			break;
		}
		else if (newInfo == "General_director")
		{
			employee.at(number - 1).post = Post::GENERAL_DIRECTOR;
			break;
		}
	case(8): employee.at(number - 1).startDate = newInfo; break;
	default: break;
	}

	writeInToFileAfterDeleteEmployee(employee);

	system("cls");
	std::cout <<termcolor::green<< "Data editing was successful!"<<termcolor::reset;
	Sleep(1800);
	system("cls");
}

int checkInput()
{
		std::cout << "��� �����: ";
		int choise;
		std::cin >> choise;
	
		if (std::cin.fail()) // ���� ���������� ���������� ��������� ���������,
		{
			std::cin.clear(); // �� ���������� cin � '�������' ����� ������
			std::cin.ignore(32767, '\n'); // � ������� �������� �����������
			return -1;
		}
		else // ���� �� ������, �� ���������� a
			return choise;
}

int engCheckInput()
{
	std::cout << "Your choise: ";
	int choise;
	std::cin >> choise;

	if (std::cin.fail()) // ���� ���������� ���������� ��������� ���������,
	{
		std::cin.clear(); // �� ���������� cin � '�������' ����� ������
		std::cin.ignore(32767, '\n'); // � ������� �������� �����������
		return -1;
	}
	else // ���� �� ������, �� ���������� a
		return choise;
}

/*std::string checkInput(std::string variable)
{
	while (true)
	{
		std::cout << "Enter a double value: ";
		std::string variable;
		std::cin >> variable;

		if (std::cin.fail()) // ���� ���������� ���������� ��������� ���������,
		{
			std::cin.clear(); // �� ���������� cin � '�������' ����� ������
			std::cin.ignore(32767, '\n'); // � ������� �������� �����������

		}
		else // ���� �� ������, �� ���������� a
			return variable;
	}
} */