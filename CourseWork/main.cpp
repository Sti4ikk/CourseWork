#include "all_headers.h"
 

std::vector<Employee> employee;
std::vector<Authentication> authentication;
// вектор для хранения индексов сотрдуников пенсионного возраста
std::vector<int> indexes;

int main()
{
	setlocale(0, "rus");
	int tries = 0;
	int entryStatus;
	// записываем в переменную 0 или 1, чтобы знать ,на какаом языке запсукать прогу(0 - русский, 1 - английский)
	int languageStatus;
	std::fstream file1("language.txt");
	file1 >> languageStatus;
	file1.close();


	// запись данных в векторы 
	writingToVectorsFromFileAuth(authentication);
	writingToVectorsFromFileEmployee(employee);


	employee.reserve(50);
	authentication.reserve(20);

	// смотрим, сколько прошло с поледнего запуска
	long seconds = checkHowManyTimeGo(entryStatus);
	// записываем новое время запуска в файл
	secondsSinceLastExecution(entryStatus);

	std::ifstream file("entryStatus.txt");
	file >> entryStatus;

	if (seconds >= 2000 or entryStatus == 0)
		auth(authentication, tries, entryStatus);

	if (tries > 4)
	{
		std::cout << "Слишком много попыток входа,попробуйте позже.";
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