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



// проверка правильности ввода данных(вход в систему)            
int checkDataOfUser(std::vector<Authentication>& authentication, int &tries, int &entryStatus)
{
	std::string login;
	std::string password;
	// проверка правильности для вывода сообщение об ошибке
	bool check = false;

	while (true)
	{
		std::cout << "Введите логин:  ";
		std::cin >> login;
		std::cout << "Введите пароль: ";
		std::cin >> password;
		Sleep(700);
		system("cls");

		for (int i = 0; i < authentication.size(); i++)
		{
			if (login == authentication.at(i).login and password == authentication.at(i).password)
			{
				std::cout << termcolor::green << "Вход выполнен успешно!" << termcolor::reset;
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
			std::cout <<termcolor::red<< "Данные неверные. Попробуйте ещё раз..." <<termcolor::reset<< std::endl;
			Sleep(2000);
			system("cls");
		}
	}
}

// проверка доступности логина
int isLoginAvailable(std::string login, std::vector<Authentication>& authentication)
{
	int count = 0;
	for (int i = 0; i < authentication.size(); i++)
	{
		if (login == authentication.at(i).login)
			return 1;
		
		count++;

		if (count == authentication.size())
			return 0;   // если переменная count будет равна длине массива, то логин не повторяется 
	}
}

// проверка на выполнение требований для пароля
int isPasswordGood(std::string password, std::string login)
{
	// счётчик цифр
	int count = 0;

	// проверка на наличие цифры в пароле
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
			break;        // потому что нужна хотя бы Заглавная буква
		}
	}


	if (password.length() >= 6 and count >= 1 and capitalLetter == 1 and checkIfLoginInPassword(login, password))
		return 0; 
	else
		return 1;
}

// подтерждение пароля при регистрации
int confirmPassword(std::string passwordForConfirm, std::string password)
{
	if (password == passwordForConfirm)
		return 0;
	else
		return 1;
}

// проверка, нет ли в пароле логина(для безопасноти) | 1 - не подходи пароль, 0 - подходит
int checkIfLoginInPassword(std::string login, std::string password)
{
	if (password.find(login) != std::string::npos)
		return 0;
	else
		return 1;
}

// регистрация в системе
void registration(std::vector<Authentication>& authentication)
{
	std::string login;
	std::string password;
	std::string passwordForConfirm;

	do
	{
		std::cout << "Введите ваш новый логин: ";
		std::cin >> login;

	} while (isLoginAvailable(login, authentication));   // если она вернет 0, цикл прервётся

	do
	{
		std::cout << "Введите ваш новый пароль: ";
		std::cin >> password;

	} while (isPasswordGood(password, login));  // если она вернет 0, цикл прервётся

	do
	{
		std::cout << "Подтвердите пароль: ";
		std::cin >> passwordForConfirm;
	} while (confirmPassword(passwordForConfirm, password));

	system("cls");
	std::cout << termcolor::green << "Регистрация прошла успешно!" << termcolor::reset;
	Sleep(2000);
	system("cls");

	std::ofstream auth("Authentication_Data.txt", std::ios::app);
	auth << "\n";
	auth << login;
	auth << " ";
	auth << password;
	auth.close();
}




//Вывод всех текущих работников.
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

// добавление нового сотрудника
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

	std::cout << "Введите Фамилию сотрудника: ";
	std::cin >> surName;
	std::cout << "Введите Имя сотрудника: ";
	std::cin >> name;
	std::cout << "Введите Отчество сотрудника: ";
	std::cin >> patronymic;
	std::cout << "Введите Пол сотрудника: ";
	std::cin >> gender;
	std::cout << "Введите Дату рождения сотрудника: ";
	std::cin >> dateOfBirthday;
	std::cout << "Введите Название отдела сотрудника: ";
	std::cin >> departmentName;
	std::cout << "Введите должность сотрудника: ";
	std::cin >> post;
	std::cout << "Введите Дату начала работы сотрудника: ";
	std::cin >> startDate;

	writeInfoOfNewEmployeeInFile(employee, surName, name, patronymic, gender, dateOfBirthday, departmentName, post, startDate);
	writeEmployeeIntoVector(employee, surName, name, patronymic, gender, dateOfBirthday, departmentName, post, startDate);

	system("cls");
	std::cout << termcolor::green << "Добавление прошло успешно!" << termcolor::reset;
	Sleep(1700);
	system("cls");
}

// добавление сотрудника в вектор после добавления нового сотрудника
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

// удаление данных о сотруднике из вектора
void deleteEmployee(std::vector<Employee>& employee)
{
	int number;

	while (true)
	{
		std::cout << "Список сотрудников: \n\n";
		printAllEmployee(employee);

		std::cout << "Введите номер сотрудника из списка для удаления: ";
		std::cin >> number;

		if (std::cin.fail() or (number < 1 or number > employee.size())) // если предыдущее извлечение оказалось неудачным,
		{
			std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
			std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего
			system("cls");
			std::cout << termcolor::red << "Введите номер из списка!" << termcolor::reset;
			Sleep(1700);
			system("cls");
			continue;
		}
		else // если всё хорошо, то возвращаем a
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
		std::cout << termcolor::green << "Удаление прошло успешно!" << termcolor::reset;
		Sleep(2000);
		system("cls");
	}
	else
	{
		system("cls");
		std::cout << termcolor::red << "Удаление не было выполнено!" << termcolor::reset;
		Sleep(2000);
		system("cls");
	}

	writeInToFileAfterDeleteEmployee(employee);
}

// подтверждение операции
int areYouSure()
{
	std::string answer;
	std::cout << "Вы уверены?: ";
	std::cin >> answer;

	if (answer == "Да" or answer == "Yes" or answer == "да" or answer == "yes" or answer == "y" or answer == "Y")
		return 1;
	else
		return 0;
}

// редактирование записей о сотрудниках
void editEmployee(std::vector<Employee>& employee)
{
	int number;
	int answer;
	while (true)
	{
		printAllEmployee(employee);
		std::cout << "Введите номер сотрудника, данные которого хотите отреактировать: ";

		std::cin >> number;
		if (std::cin.fail() or (number < 1 or number > employee.size())) // если предыдущее извлечение оказалось неудачным,
		{
			std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
			std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего
			system("cls");
			std::cout << termcolor::red << "Введите номер из списка!" << termcolor::reset;
			Sleep(1700);
			system("cls");
			continue;
		}
		else // если всё хорошо, то возвращаем a
		{
			system("cls");
			break;
		}
	}

	do
	{
		std::cout << "1. Фамилия" << std::endl;
		std::cout << "2. Имя" << std::endl;
		std::cout << "3. Отчество" << std::endl;
		std::cout << "4. Пол" << std::endl;
		std::cout << "5. День рождения" << std::endl;
		std::cout << "6. Название отдела" << std::endl;
		std::cout << "7. Должность" << std::endl;
		std::cout << "8. Дата начала работы\n" << std::endl;

		std::cout << "Выберите, что хотите изменить: ";

		std::cin >> answer;
		std::cout << std::endl;
		if (std::cin.fail() or (answer < 1 or answer > 8)) // если предыдущее извлечение оказалось неудачным,
		{
			std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
			std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего
			system("cls");
			std::cout << termcolor::red << "Выберите номер из списка!" << termcolor::reset;
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
	std::cout << "Введите корректную информацию: ";
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
	std::cout << termcolor::green << "Редактирование данных прошло успешно!" << termcolor::reset;
	Sleep(1800);
	system("cls");
}




// поиск по фамилии
void searchForSurName(std::vector<Employee>& employee)
{
		std::string surName;
		std::cout << "Введите фамилию сотрудника: ";
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
					std::cout << "Найденный/ые сотрудник/и: \n\n";
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
			std::cout << termcolor::red << "Не найдено сотрудников с такой фамилией!" << termcolor::reset;
			Sleep(1800);
			system("cls");
			return;
		}
		std::cout << "\nНажмите любую клавишу...";
		_getch();

		system("cls");
}

// поиск по должности
void searchForPost(std::vector<Employee>& employee)
{
	std::string post;
	int post1;
	std::cout << "Введите должность сотрудника: ";
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
		// чтобы не было ошибки "переменная не инициализирована"
		post1 = -1;

	// переменная следит, чтобы выводилась надпись, если не найдено нужных сотрудников
	bool isThereAtLeastOne = false;
	//переменная следит, чтобы надпись выводилась лишь раз
	bool onlyOneTime = false; 

	for (int i = 0; i < employee.size(); i++)
	{
		int index = i;
		if (static_cast<int>(employee[i].post) == post1)
		{
			isThereAtLeastOne = true;
			if (!onlyOneTime)
			{
				std::cout << "Найденный/ые сотрудник/и:\n\n";
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
		std::cout << termcolor::red << "Не найдено сотрудников, имеющих данную должность!\n" << termcolor::reset;
		Sleep(2000);
		system("cls");
		return;
	}

	std::cout << "\nНажмите любую клавишу...";
	_getch();
	system("cls");
}

// поиск по дате начала работы
void searchForStartDate(std::vector<Employee>& employee)
{
	int startDate;

	while (true)
	{
		std::cout << "Введите год начала работы сотрудника: ";
		std::cin >> startDate;

		if (std::cin.fail()) // если предыдущее извлечение оказалось неудачным,
		{
			std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
			std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего
			system("cls");
			std::cout << termcolor::red << "Введите корректуню дату!" << termcolor::reset;
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
				std::cout << "Найденный/ые сотрудник/и: \n\n";
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
		std::cout << termcolor::red << "Не найдено сотрудников с данным годом начала работы!\n" << termcolor::reset;
		Sleep(2000);
		system("cls");
		return;
	}

	std::cout << "\nНажмите любую клавишу...";
	_getch();
	system("cls");
}



// сортировка по Фамилии в порядке убывания(пузырьком)
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

// сортировка по Фамилии в порядке возрастания(пузырьком)
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

// поиск наименьшего элемента для сортировки выбором
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

// сортировка по должности в порядке возрастания(методом выбора)
void sortWithPostUp(std::vector<Employee> &employee)
{
	for (int i = 0; i < employee.size(); i++)
	{
		int smallestPosition = findSmallestPosition(employee, i);
		std::swap(employee.at(i), employee.at(smallestPosition));
	}
}

// поиск наибольшего элемента для сортировки выбором
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

// сортировка по должности в порядке убывания(методом выбора)
void sortWithPostDown(std::vector<Employee>& employee)
{
	for (int i = 0; i < employee.size(); i++)
	{
		int biggestPosition = findBiggestPosition(employee, i);
		std::swap(employee.at(i), employee.at(biggestPosition));
	}
}

// функция возвращает целое число типа годМесяцДень
int getNumber(std::vector<Employee>& employee, int index)
{
	std::string number;
	int result;

	// добавил год к number
	number += employee.at(index).startDate.substr(6);
	// добавил месяц
	number += employee.at(index).startDate.substr(3, 2);
	// добавил день
	number += employee.at(index).startDate.substr(0, 2);
	// c_str Возвращает указатель на массив, содержащий последовательность символов, завершающуюся нулем("\0)
	result = atoi(number.c_str());

	return result;
}

// сортировка по стажу в порядке убывания
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

// сортировка по стажу в порядке возрастания
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



// проверка на пол сотрудника
int checkGenderOfEmployee(std::vector<Employee>& employee, const int index)
{
	if (employee.at(index).gender == "Man")
		return 1;
	else if(employee.at(index).gender == "Woman")
		return 0;
}

// вычисляет возраст сотрудника(в годах)
int ageOfEmployee(std::vector<Employee>&employee, const int index)
{
	std::tm timeinfo = {};
	timeinfo.tm_year = atoi(employee.at(index).dateOfBirthday.substr(6).c_str()) - 1900;  // год смещается на 1900
	timeinfo.tm_mon = atoi(employee.at(index).dateOfBirthday.substr(3, 2).c_str()) - 1;
	timeinfo.tm_mday = atoi(employee.at(index).dateOfBirthday.substr(0, 2).c_str());

	std::time_t custom_time = std::mktime(&timeinfo);

	// Получаем текущую дату
	std::time_t end = std::time(nullptr);

	// Рассчитываем возраст
	std::tm end_tm = {};
	localtime_s(&end_tm, &end);
	int years = end_tm.tm_year - timeinfo.tm_year;

	// Проверяем, достигнут ли день рождения в этом году
	if (end_tm.tm_mon < timeinfo.tm_mon or (end_tm.tm_mon == timeinfo.tm_mon && end_tm.tm_mday < timeinfo.tm_mday))
		--years; // Если ещё не достиг, уменьшаем возраст на 1 год

	return years;
}

// Поиск сотрудников с пенсионным возрастом
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

// Вывод сотрудников с пенсионным возрастом
void printEmployeesOfRetirementAge(std::vector<Employee> & employee, std::vector<int> &indexes)
{

	if (indexes.empty())
	{
		std::cout << "Сотрудников пенсионного возраста нет.\n\n";
		return;
	}
		
	std::cout << "Список сорудников пенсионного возраста: \n\n";
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
	std::cout << "Нажмите любую клавишу...";
	_getch();
	system("cls");
}

// получаем стаж сотрудников в годах, месяцах и днях
void getExperienceOfEmployees(std::vector<Employee> const& employee)
{
	for (int i = 0; i < employee.size(); i++)
	{
		// Можно установить start в конкретную дату и время
		std::tm timeinfo = {};
		timeinfo.tm_year = atoi(employee.at(i).startDate.substr(6).c_str()) - 1900;  // год смещается на 1900
		timeinfo.tm_mon = atoi(employee.at(i).startDate.substr(3, 2).c_str()) - 1;
		timeinfo.tm_mday = atoi(employee.at(i).startDate.substr(0, 2).c_str());

		std::time_t custom_time = std::mktime(&timeinfo);

		// Получаем текущую дату
		std::time_t end = std::time(nullptr);

		// Вычисляем разницу в секундах
		std::time_t diff = end - custom_time;

		// Переводим разницу в года, месяцы и дни
		int years = diff / (60 * 60 * 24 * 365);
		int months = (diff % (60 * 60 * 24 * 365)) / (60 * 60 * 24 * 30);
		int days = ((diff % (60 * 60 * 24 * 365)) % (60 * 60 * 24 * 30)) / (60 * 60 * 24);

		std::cout << "Прошло " << years << " лет, "
			<< months << " месяцев, и "
			<< days << " дней." << std::endl;
	}
}



// АНГЛ ФУНКЦИИ

// добавление сотрудника
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

// удаление данных о сотруднике из вектора
void engDeleteEmployee(std::vector<Employee>& employee)
{

	int number;

	while (true)
	{
		std::cout << "List of current employees: \n\n";
		printAllEmployee(employee);

		std::cout << "Enter the employee number from the list to be deleted: ";
		std::cin >> number;
	
		if (std::cin.fail() or (number < 1 or number > employee.size())) // если предыдущее извлечение оказалось неудачным,
		{
			std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
			std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего
			system("cls");
			std::cout << termcolor::red << "Choose number from the list!" << termcolor::reset;
			Sleep(1700);
			system("cls");
			continue;
		}
		else // если всё хорошо, то возвращаем a
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

// подтверждение операции
int engAreYouSure()
{
	std::string answer;
	std::cout << "Are you sure?: ";
	std::cin >> answer;

	if (answer == "Да" or answer == "Yes" or answer == "yes" or answer == "да")
		return 1;
	else
		return 0;
}

// редактирование данных о сотруднике
void engEditEmployee(std::vector<Employee>& employee)
{

	int number;
	int answer;
	while (true)
	{
		printAllEmployee(employee);
		std::cout << "Enter the number of the employee whose details you want to edit: ";

		std::cin >> number;
		if (std::cin.fail() or (number < 1 or number > employee.size())) // если предыдущее извлечение оказалось неудачным,
		{
			std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
			std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего
			system("cls");
			std::cout << termcolor::red << "Choose number from the list!" << termcolor::reset;
			Sleep(1700);
			system("cls");
			continue;
		}
		else // если всё хорошо, то возвращаем a
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
		if (std::cin.fail() or (answer < 1 or answer > 8)) // если предыдущее извлечение оказалось неудачным,
		{
			std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
			std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего
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
		std::cout << "Ваш выбор: ";
		int choise;
		std::cin >> choise;
	
		if (std::cin.fail()) // если предыдущее извлечение оказалось неудачным,
		{
			std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
			std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего
			return -1;
		}
		else // если всё хорошо, то возвращаем a
			return choise;
}

int engCheckInput()
{
	std::cout << "Your choise: ";
	int choise;
	std::cin >> choise;

	if (std::cin.fail()) // если предыдущее извлечение оказалось неудачным,
	{
		std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
		std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего
		return -1;
	}
	else // если всё хорошо, то возвращаем a
		return choise;
}

/*std::string checkInput(std::string variable)
{
	while (true)
	{
		std::cout << "Enter a double value: ";
		std::string variable;
		std::cin >> variable;

		if (std::cin.fail()) // если предыдущее извлечение оказалось неудачным,
		{
			std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
			std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего

		}
		else // если всё хорошо, то возвращаем a
			return variable;
	}
} */