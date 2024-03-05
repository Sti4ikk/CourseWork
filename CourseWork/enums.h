#pragma once

// должности предприятия
enum class Post
{
	JUNIOR = 1,
	MIDDLE,
	SENIOR,
	TEAM_LEADER,
	PROJECT_MANAGER,
	DIRECTOR_OF_DEPARTMENT,
	DEPUTY_GENERAL_DIRECTOR,
	GENERAL_DIRECTOR,
};

enum class AuthOrRegistr
{
	AUTH = 1,
	REGISTER,
};

enum Main_Menu
{
	EDITING_MODE = 1,
	PROCESSING_MODE,
	SETTINGS,
	EXIT,
};

enum EditingMode
{
	CHECKING = 1,
	ADDING,
	EDITING,
	DELETING,
	BACK,
};



enum Menu_Branches
{
	SORTING,
	SEARCH,
	INDIVIDUAL_TASK,
	GET_BACK,
};