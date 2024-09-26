#include "Question.h"

Question::Question(int correctAnswerid, std::string question, std::vector<std::string> possibleAnswers)
{
    m_correctAnswerid = correctAnswerid;
    m_question = question;
    m_possibleAnswers = possibleAnswers;
}

int Question::GetCorrectAnswerId()
{
    return m_correctAnswerid;
}

Question Question::operator=(Question const& other)
{
    this->m_correctAnswerid = other.m_correctAnswerid;
    this->m_question = other.m_question;
    this->m_possibleAnswers = other.m_possibleAnswers;
    return *this;
}
