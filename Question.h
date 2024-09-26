#pragma once
#include <iostream>
#include <vector>
class Question
{
public:
    Question() : m_correctAnswerid(-1) {};
    Question(int correctAnswerid , std::string m_question, std::vector<std::string> m_possibleAnswers);
    ~Question() {};
    std::string GetQuestion() { return m_question; };
    std::vector<std::string> GetPossibleAnswers() { return m_possibleAnswers; };
    int GetCorrectAnswerId();
    Question operator=(Question const& other);
private:
    int  m_correctAnswerid;
    std::string m_question;
    std::vector<std::string> m_possibleAnswers;
};