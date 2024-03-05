#pragma once
#include "enums.h"
#include <string>

// ���������� � ����������� �����������
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

// ������ ��� ��������������
struct Authentication
{
	std::string login;
	std::string password;
};