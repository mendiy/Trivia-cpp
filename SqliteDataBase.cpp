#include "SqliteDataBase.h"
#include <exception>
#include <iostream>
#include <string>
#include "sqlite3.h"
#include "LoggedUser.h"
#include "IDatabase.h"
#include "Question.h"


//static std::string user;

static int userCallback(void* isExists, int argc, char** argv, char** azColName) {
	int i;
	if (argc > 0 && argv[0])
	{
		*(bool*)isExists = (*argv[0] == '1');
	}

	return 0;
}
static int questionsCallback(void* questionList, int argc, char** argv, char** azColName) {
	std::list<Question>* questions = static_cast<std::list<Question>*>(questionList);
	std::vector<std::string> ans;
	int id = 0;
	std::string q;

	for (int i = 0; i < argc; i++) {
		if (strcmp(azColName[i], "CORRECT") == 0) {
			id = std::stoi(argv[i]);
		}
		else if (strcmp(azColName[i], "QUESTION") == 0) {
			q = argv[i];
		}
		else {
			ans.push_back(argv[i]);
		}
	}
	questions->push_back(Question(id, q, ans));

	return 0;
}


SqliteDataBase::SqliteDataBase()
{
	db = nullptr;

	if (open() == false)
	{
		throw "Failed to open DB";
	}
	std::string userTable = "CREATE TABLE IF NOT EXISTS USERS ("
		"USERNAME TEXT NOT NULL PRIMARY KEY,"
		"PASSWORD TEXT NOT NULL,"
		"EMAIL TEXT NOT NULL); ";
	char* errMessage = nullptr;
	int res = sqlite3_exec(db, userTable.c_str(), nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
		std::cout << "Failed to open User Table\n";

	std::string questionTable = "CREATE TABLE IF NOT EXISTS QUESTIONS ("
		"ID INTEGER NOT NULL PRIMARY KEY,"
		"QUESTION TEXT NOT NULL,"
		"A TEXT NOT NULL,"
		"B TEXT NOT NULL,"
		"C TEXT NOT NULL,"
		"D TEXT NOT NULL,"
		"CORRECT INTEGER NOT NULL);";
	errMessage = nullptr;
	res = sqlite3_exec(db, questionTable.c_str(), nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
		std::cout << "Failed to open Question Table\n";

	std::string statisticTable = "CREATE TABLE IF NOT EXISTS STATISTICS ("
		"USERNAME TEXT NOT NULL,"
		"GAME_ID INTEGER NOT NULL,"
		"CORRECT_ANSWERS INTEGER NOT NULL,"
		"TOTAL_TIME REAL NOT NULL,"
		"TOTAL_QUESTIONS INTEGER NOT NULL,"
		"UNCORRECT_ANSWERS INTEGER NOT NULL,"
		"SCORE INTEGER NOT NULL,"
		"PRIMARY KEY (USERNAME, GAME_ID));";
	errMessage = nullptr;
	res = sqlite3_exec(db, statisticTable.c_str(), nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
		std::cout << "Failed to open Statistic Table\n";

	//std::string insertQuestions = R"(
	//	INSERT INTO QUESTIONS (ID, QUESTION, A, B, C, D, CORRECT) VALUES
	//	(1, 'What is the capital of France?', 'Paris', 'London', 'Rome', 'Berlin', 1),
	//	(2, 'What is 2 + 2?', '3', '4', '5', '6', 2),
	//	(3, 'Which planet is known as the Red Planet?', 'Earth', 'Mars', 'Jupiter', 'Venus', 2),
	//	(4, 'What is the largest ocean on Earth?', 'Atlantic', 'Pacific', 'Indian', 'Arctic', 2),
	//	(5, 'Who wrote "Hamlet"?', 'Charles Dickens', 'William Shakespeare', 'Mark Twain', 'Jane Austen', 2),
	//	(6, 'What is the chemical symbol for water?', 'H2O', 'CO2', 'O2', 'H2', 1),
	//	(7, 'What is the fastest land animal?', 'Cheetah', 'Lion', 'Horse', 'Elephant', 1),
	//	(8, 'Which country is known as the Land of the Rising Sun?', 'China', 'Japan', 'South Korea', 'Thailand', 2),
	//	(9, 'What is the square root of 64?', '6', '7', '8', '9', 3),
	//	(10, 'Which language is primarily spoken in Brazil?', 'Spanish', 'Portuguese', 'French', 'English', 2);
	//	)";
	/*res = sqlite3_exec(db, insertQuestions.c_str(), nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
		std::cout << "Failed to insert questions: " << errMessage << "\n";
	else
		std::cout << "Questions inserted successfully.\n";*/

	/*std::string insertQuery = "INSERT INTO STATISTICS (USERNAME, GAME_ID, CORRECT_ANSWERS, TOTAL_TIME, TOTAL_QUESTIONS, UNCORRECT_ANSWERS, SCORE) VALUES"
		"('user1', 1, 8, 96.5, 10, 2, 80),"
		"('user2', 2, 7, 105.3, 10, 3, 70),"
		"('user3', 3, 9, 99.0, 10, 1, 90),"
		"('user4', 4, 6, 78.2, 10, 4, 60),"
		"('user5', 5, 8, 112.7, 10, 2, 80),"
		"('user6', 6, 7, 87.5, 10, 3, 70),"
		"('user7', 7, 9, 90.1, 10, 1, 90),"
		"('user8', 8, 6, 81.4, 10, 4, 60),"
		"('user9', 9, 8, 116.2, 10, 2, 80),"
		"('user10', 10, 7, 80.5, 10, 3, 70),"
		"('user1', 11, 9, 117.3, 10, 1, 90),"
		"('user2', 12, 6, 84.6, 10, 4, 60),"
		"('user3', 13, 8, 120.0, 10, 2, 80),"
		"('user4', 14, 7, 77.9, 10, 3, 70),"
		"('user5', 15, 9, 112.5, 10, 1, 90),"
		"('user6', 16, 6, 81.0, 10, 4, 60),"
		"('user7', 17, 8, 116.8, 10, 2, 80),"
		"('user8', 18, 7, 80.3, 10, 3, 70),"
		"('user9', 19, 9, 117.0, 10, 1, 90),"
		"('user10', 20, 6, 84.0, 10, 4, 60),"
		"('user1', 21, 8, 119.5, 10, 2, 80),"
		"('user2', 22, 7, 106.7, 10, 3, 70),"
		"('user3', 23, 9, 99.3, 10, 1, 90),"
		"('user4', 24, 6, 78.1, 10, 4, 60),"
		"('user5', 25, 8, 112.9, 10, 2, 80);";*/
	/*res = sqlite3_exec(db, insertQuery.c_str(), nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
		std::cout << "Failed to insert Query: " << errMessage << "\n";
	else
		std::cout << "Query inserted successfully.\n";*/

	//getQuestions(5);
	std::cout << "DB Created!" << std::endl;
}

SqliteDataBase::~SqliteDataBase()
{
	
}
void SqliteDataBase::printQuestions(std::list<Question> questionList)
{
	for (auto it = questionList.begin(); it != questionList.end(); it++)
	{
		std::cout << "question " << it->getQuestion() << "\n";
	}
}

bool SqliteDataBase::open()
{

	std::string dbFileName = "Trivia_DB";
	int res = sqlite3_open(dbFileName.c_str(), &db);
	if (res != SQLITE_OK)
	{
		db = nullptr;
		std::cout << "Failed to open DB" << std::endl;
		return false;
	}
	return true;
}

bool SqliteDataBase::close()
{
	return false;
}

bool SqliteDataBase::doesUserExist(std::string username)
{
	char* zErrMsg = 0;
	bool isExists = false;
	std::string sql = "SELECT EXISTS(SELECT 1 from USERS WHER USERNAME = '" + username + "');";

	/* Execute SQL statement */
	int rc = sqlite3_exec(db, sql.c_str(), nullptr, &isExists, &zErrMsg);

	if (rc != SQLITE_OK) {
		std::cerr << zErrMsg << "\n";
		sqlite3_free(zErrMsg);
		return false;
	}
	
	std::cout << "user selected\n";
	
	sqlite3_close(db);
	
	return isExists;
}

bool SqliteDataBase::doesPasswordMatch(std::string username, std::string password)
{
	char* zErrMsg = 0;
	bool isMatch = false;
	std::string sql = "SELECT EXISTS(SELECT 1 from USERS WHERE USERNAME = '" + username + "' AND PASSWORD = '" + password + "');";

	/* Execute SQL statement */
	int rc = sqlite3_exec(db, sql.c_str(), userCallback, &isMatch, &zErrMsg);

	if (rc != SQLITE_OK) {
		std::cerr << zErrMsg << "\n";
		sqlite3_free(zErrMsg);
		return false;
	}

	std::cout << "password match!\t" << isMatch << "\n";

	sqlite3_close(db);

	return isMatch;
}

bool SqliteDataBase::addNewUser(std::string username, std::string password, std::string email)
{
	char* zErrMsg = 0;
	std::cout << "from add new user: " << username << ", " << password << ", " << email << "\n";
	std::string sql = "INSERT INTO USERS (USERNAME, PASSWORD, EMAIL) "  \
		"VALUES ('" + username + "', '" + password + "', '" + email + "'); ";
	std::cout << "query: " << sql << "\n";
	/* Execute SQL statement */
	int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &zErrMsg);

	if (rc != SQLITE_OK) {
		std::cerr << zErrMsg << "\n";
		sqlite3_free(zErrMsg);
		return false;
	}
	
	std::cout << "user created successfully\n";
	
	sqlite3_close(db);
	return true;
}

std::list<Question> SqliteDataBase::getQuestions(int amount)
{
	std::list<Question> questionsList;
	char* zErrMsg = 0;
	Question q;
	std::string sql = "SELECT * from QUESTIONS LIMIT " + std::to_string(amount) + ";";

	/* Execute SQL statement */
	int rc = sqlite3_exec(db, sql.c_str(), questionsCallback, &questionsList, &zErrMsg);

	if (rc != SQLITE_OK) {
		std::cerr << zErrMsg << "\n";
		sqlite3_free(zErrMsg);
	}
	sqlite3_close(db);

	//this->printQuestions(questionsList);
	return questionsList;
}

float SqliteDataBase::getPlayerAverageAnswerTime(std::string time)
{
	return 0.0f;
}

int SqliteDataBase::getNumOfCorrectAnswers(std::string)
{
	return 0;
}

int SqliteDataBase::getNumOfTotalAnswers(std::string)
{
	return 0;
}

int SqliteDataBase::getNumOfPlayerGames(std::string)
{
	return 0;
}

int SqliteDataBase::getPlayerScore(std::string)
{
	return 0;
}

int SqliteDataBase::getHighScores()
{
	return 0;
}
