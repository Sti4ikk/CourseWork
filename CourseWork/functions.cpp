#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "structs.h"
#include "prototypes.h"
#include "enums.h"
#include <Windows.h>


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
void writingToVectorsFromFileEmployee(std::vector<Employee>&employee)
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

// проверка правильности ввода данных(вход в систему)            
int checkDataOfUser(std::vector<Authentication>& authentication)
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

		for (int i = 0; i < authentication.size(); i++)
		{
			if (login == authentication.at(i).login and password == authentication.at(i).password)
			{
				std::cout << "Вход выполнен успешно!";
				return 1;
			}
		}
		if (!check)
		{
			std::cout << "Данные неверные. Попробуйте ещё раз..." << std::endl;
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
int isPasswordGood(std::string password)
{
	std::string digits = "0123456789";
	// счётчик цифр
	int count = 0;

	// проверка на наличие цифры в пароле
	for (int i = 0; i < password.length(); i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (password[i] == digits[j])
			{
				count++;
				break;    // потому что нужна хотя бы одна цифра
			}
		}
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

	if (password.length() >= 6 and count >= 1 and capitalLetter == 1)
		return 0; 
	else
		return 1;
}

// регистрация в системе
void registration(std::vector<Authentication>& authentication)
{
	std::string login;
	std::string password;

	do
	{
		std::cout << "Введите ваш новый логин: ";
		std::cin >> login;

	} while (isLoginAvailable(login, authentication));   // если она вернет 0, цикл прервётся

	do
	{
		std::cout << "Введите ваш новый пароль: ";
		std::cin >> password;

	} while (isPasswordGood(password));  // если она вернет 0, цикл прервётся

	std::ofstream auth("Authentication_Data.txt", std::ios::app);
	auth << "\n";
	auth << login;
	auth << " ";
	auth << password;

	auth.close();
}

//Вывод всех текущих работников.
void printAllEmployee(std::vector<Employee>const & employee)
{
	for (int i = 0; i < employee.size(); i++)
	{
		if (employee[i].name == "")
			break;

		std::cout << employee.at(i).surName << " ";
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
	empl << startDate << " ";

	// запись сотрудника в вектор
	writingToVectorsFromFileEmployee(employee);

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

// удаление данных о сотруднике из вектора
void deleteEmployee(std::vector<Employee>& employee)
{
	printAllEmployee(employee);

	int number;
	std::cout << "Введите номер сотрудника из списка для удаления: ";
	std::cin >> number;

	if (areYouSure())
	{
		employee.erase(employee.begin() + number - 1);
		system("cls");
		std::cout << "Удаление прошло успешно!";
		Sleep(1700);
		system("cls");
	}

	writeInToFileAfterDeleteEmployee(employee);
}

// подтверждение операции
int areYouSure()
{
	std::string answer;
	std::cout << "Вы уверены? ";
	std::cin >> answer;

	if (answer == "Да" or answer == "Yes" or answer == "да" or answer == "yes")
		return 1;
	else
		return 0;
}

// редактирование записей о сотрудниках
void editEmployee(std::vector<Employee>& employee)
{
	printAllEmployee(employee);

	int number;
	std::cout << "Введите номер сотрудника, данные которого хотите отредактировать: ";
	std::cin >> number;

	std::cout << "Выберите, что именно хотите отредактировать: " << std::endl;
	std::cout << "1. Фамилия" << std::endl;
	std::cout << "2. Имя" << std::endl;
	std::cout << "3. Отчество" << std::endl;
	std::cout << "4. Пол" << std::endl;
	std::cout << "5. Дата рождения" << std::endl;
	std::cout << "6. Название отдела" << std::endl;
	std::cout << "7. Должность" << std::endl;
	std::cout << "8. Дата начала работы" << std::endl;

	int answer;
	std::cin >> answer;

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
	default: std::cout<<"Введите цифру из списка!";
	}


	writeInToFileAfterDeleteEmployee(employee);
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
				std::cout << "Найденный/ые сотрудник/и: " << std::endl;
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
		std::cout << "Не найдено сотрудников с такой фамилией!\n";
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
				std::cout << "Найденный/ые сотрудник/и: " << std::endl;
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
		std::cout << "Не найдено сотрудников, имеющих данную должность!" << std::endl;
}

// поиск по дате начала работы
void searchForStartDate(std::vector<Employee>& employee)
{
	int startDate;
	std::cout << "Введите год начала работы сотрудника: ";
	std::cin >> startDate;
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
				std::cout << "Найденный/ые сотрудник/и: " << std::endl;
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
		std::cout << "Не найдено сотрудников с данным годом начала работы!\n";
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
		std::cout << "Сотрудников с пенсионным возрастом нет.\n\n";
		return;
	}
		
	std::cout << "Список сорудников пенсионного возраста: " << std::endl;
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



// англ функции

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
}

// удаление данных о сотруднике из вектора
void engDeleteEmployee(std::vector<Employee>& employee)
{
	std::cout << "List of current employees: \n\n";
	printAllEmployee(employee);

	int number;
	std::cout << "Enter the employee number from the list to be deleted: ";
	std::cin >> number;

	if (engAreYouSure())
	{
		employee.erase(employee.begin() + number - 1);
		system("cls");
		std::cout << "Removal was successful!";
		Sleep(1700);
		system("cls");
	}

	writeInToFileAfterDeleteEmployee(employee);
}

int engAreYouSure()
{
	std::string answer;
	std::cout << "Are you sure? ";
	std::cin >> answer;

	if (answer == "Да" or answer == "Yes" or answer == "yes" or answer == "да")
		return 1;
	else
		return 0;
}

void engEditEmployee(std::vector<Employee>& employee)
{
	printAllEmployee(employee);

	int number;
	std::cout << "Enter the number of the employee whose details you want to edit: ";
	std::cin >> number;

	std::cout << "Choose what you want to edit: " << std::endl;
	std::cout << "1. Surname" << std::endl;
	std::cout << "2. Name" << std::endl;
	std::cout << "3. Patronymic" << std::endl;
	std::cout << "4. Gender" << std::endl;
	std::cout << "5. Date of birthday" << std::endl;
	std::cout << "6. Name of department" << std::endl;
	std::cout << "7. Post" << std::endl;
	std::cout << "8. Start date" << std::endl;

	int answer;
	std::cin >> answer;

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
	default: std::cout << "Enter a number from the list!";
	}

	writeInToFileAfterDeleteEmployee(employee);
}

