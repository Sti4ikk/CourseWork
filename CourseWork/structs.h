#pragma once
#include "enums.h"
#include <string>

// Информация о сотрудниках предприятия
struct Employee
{
	std::string surName;
	std::string name;
	std::string patronymic;
	std::string gender;
	std::string dateOfBirthday;
	std::string departmentName;
	Post post;
	std::string startDate;
};

// данные для аутентификации
struct Authentication
{
	std::string login;
	std::string password;
};