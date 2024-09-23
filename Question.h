#pragma once
#include <iostream>
#include <vector>
class Question
{
public:
	Question() :m_id(-1) {};
	Question(int m_id, std::string m_question, std::vector<std::string> m_possibleAnswers);
	~Question() {};
	std::string getQuestion() { return m_question; };
	std::vector<std::string> getPossibleAnswers() { return m_possibleAnswers; };
	int getCorrectAnswerId();
	Question operator=(Question const& other);
private:
	int m_id;
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
};