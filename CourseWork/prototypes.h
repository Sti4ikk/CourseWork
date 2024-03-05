#pragma once
#include "structs.h"
#include <vector>


void writingToVectorsFromFileAuth(std::vector<Authentication>& authentication);
void writingToVectorsFromFileEmployee(std::vector<Employee>& employee);
int checkDataOfUser(std::vector<Authentication>& authentication);
int isLoginAvailable(std::string login, std::vector<Authentication>& authentication);
int isPasswordGood(std::string password);
void registration(std::vector<Authentication>& authentication);
void printAllEmployee(std::vector<Employee>const& employee);
void addNewEmployee(std::vector<Employee>& employee);
void writeInfoOfNewEmployeeInFile(std::vector<Employee>& employee, std::string surName, std::string name, std::string patronymic, std::string gender, std::string dateOfBirthday, std::string departmenrName, std::string post, std::string startDate);
void deleteEmployee(std::vector<Employee>& employee);
int areYouSure();
void editEmployee(std::vector<Employee>& employee);

// поиск
void searchForSurName(std::vector<Employee>& employee);
void searchForPost(std::vector<Employee>& employee);
void searchForStartDate(std::vector<Employee>& employee);

// сортировка
void sortWithSurNameDown(std::vector<Employee>& employee);
void sortWithSurNameUp(std::vector<Employee>& employee);

int findSmallestPosition(std::vector<Employee>& employee, int startPosition);
void sortWithPostUp(std::vector<Employee>& employee);

int findBiggestPosition(std::vector<Employee>& employee, int startPosition);
void sortWithPostDown(std::vector<Employee>& employee);

int getNumber(std::vector<Employee>& employee, int index);
void sortWithExperienceUp(std::vector<Employee>& employee);
void sortWithExperienceDown(std::vector<Employee>& employee);

int checkGenderOfEmployee(std::vector<Employee>& employee, const int index);
void searchForEmployeesOfRetirementAge(std::vector<Employee>& employee);
void printEmployeesOfRetirementAge(std::vector<Employee>& employee, std::vector<int> &indexes);

void getExperienceOfEmployees(std::vector<Employee> const& employee);
int ageOfEmployee(std::vector<Employee>& employee, const int index);


void mainMenu(std::vector<Employee>& employee);
void editingMode(std::vector<Employee>& employee);