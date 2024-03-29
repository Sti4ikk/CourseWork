#pragma once
#include "structs.h"
#include <vector>

void secondsSinceLastExecution(int& entryStatus);
void auth(std::vector<Authentication>& authentication, int& tries, int& entryStatus);
long checkHowManyTimeGo(int& entryStatus);
void writeEntryStatus(int& entryStatus);
void writeLanguageInFile(int& languageStatus);

void writingToVectorsFromFileAuth(std::vector<Authentication>& authentication);
void writingToVectorsFromFileEmployee(std::vector<Employee>& employee);
int checkDataOfUser(std::vector<Authentication>& authentication, int& tries, int& entryStatus);
int isLoginAvailable(std::string login, std::vector<Authentication>& authentication);
int confirmPassword(std::string passwordForConfirm, std::string password);
int checkIfLoginInPassword(std::string login, std::string password);

int isPasswordGood(std::string password, std::string login);
void registration(std::vector<Authentication>& authentication);
void printAllEmployee(std::vector<Employee>& employee);
void addNewEmployee(std::vector<Employee>& employee);
void writeInfoOfNewEmployeeInFile(std::vector<Employee>& employee, std::string surName, std::string name, std::string patronymic, std::string gender, std::string dateOfBirthday, std::string departmenrName, std::string post, std::string startDate);
void deleteEmployee(std::vector<Employee>& employee);
int areYouSure();
void editEmployee(std::vector<Employee>& employee);
void writeEmployeeIntoVector(std::vector<Employee>& employee, std::string surName, std::string name, std::string patronymic, std::string gender, std::string dateOfBirthday, std::string departmenrName, std::string post, std::string startDate);

// �����
void searchForSurName(std::vector<Employee>& employee);
void searchForPost(std::vector<Employee>& employee);
void searchForStartDate(std::vector<Employee>& employee);

// ����������
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
void searchForEmployeesOfRetirementAge(std::vector<Employee>& employee, std::vector<int>& indexes);
void printEmployeesOfRetirementAge(std::vector<Employee>& employee, std::vector<int> &indexes);

void getExperienceOfEmployees(std::vector<Employee> const& employee);
int ageOfEmployee(std::vector<Employee>& employee, const int index);


void RusMainMenu(std::vector<Employee>& employee, std::vector<int>& indexes, std::vector<Authentication>& authentication, int& languageStatus);
void editingMode(std::vector<Employee>& employee);

void chooseTypeOfSearch(std::vector<Employee>& employee);
void chooseTypeOfSort(std::vector<Employee>& employee);
int typeOFSorting();
void processsingMode(std::vector<Employee>& employee, std::vector<int>& indexes);
void rusChooseMenuLanguage(std::vector<Employee>& employee, std::vector<int>& indexes, std::vector<Authentication>& authentication, int&languageStatus);
void turnMenuLanguge(int choise, std::vector<Employee>& employee, std::vector<int>& indexes, std::vector<Authentication>& authentication, int& languageStatus);
void writeInToFileAfterDeleteEmployee(std::vector<Employee>& employee);

void rusSettings(std::vector<Employee>& employee, std::vector<int>& indexes, std::vector<Authentication>& authentication, int& languageStatus);

// ���� ������� ����
void EngMainMenu(std::vector<Employee>& employee, std::vector<int>& indexes, std::vector<Authentication>& authentication, int& languageStatus);
void EngChooseTypeOfSort(std::vector<Employee>& employee);
int EngTypeOFSorting();
void EngChooseTypeOfSearch(std::vector<Employee>& employee);
void EngEditingMode(std::vector<Employee>& employee);
void EngProcesssingMode(std::vector<Employee>& employee, std::vector<int>& indexes);
void engChooseMenuLanguage(std::vector<Employee>& employee, std::vector<int>& indexes, std::vector<Authentication>& authentication, int& languageStatus);

// ���� ������� 
void engAddNewEmployee(std::vector<Employee>& employee);
void engDeleteEmployee(std::vector<Employee>& employee);
int engAreYouSure();
void engEditEmployee(std::vector<Employee>& employee);
void engSettings(std::vector<Employee>& employee, std::vector<int>& indexes, std::vector<Authentication>& authentication, int& languageStatus);

int checkInput(); 
int engCheckInput();
//std::string checkInput(std::string variable);