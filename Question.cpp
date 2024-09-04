#include "Question.h"

Question::Question(int id, std::string question, std::vector<std::string> possibleAnswers)
{
    m_id = m_id;
    m_question = question;
    m_possibleAnswers = possibleAnswers;
}

int Question::getCorrectAnswerId()
{
    return 0;
}

Question Question::operator=(Question const& other)
{
    this->m_id = other.m_id;
    this->m_question = other.m_question;
    this->m_possibleAnswers = other.m_possibleAnswers;
    return *this;
}
