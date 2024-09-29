#include "GameRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"

const unsigned int GET_QUESTION_REQUEST_CODE = 30;
const unsigned int SUBMIT_ANSWER_REQUEST_CODE = 31;
const unsigned int GET_GAMES_RESULT_REQUEST_CODE = 32;
const unsigned int LEAVE_GAME_REQUEST_CODE = 33;

GameRequestHandler::GameRequestHandler(LoggedUser user, Game& game, RequestHandlerFactory& handlerFactory)
    : m_user(user.getUsername()), m_game(game), m_handlerFactory(handlerFactory)
{
}

bool GameRequestHandler::IsRequestRelevant(RequestInfo reqInfo)
{
    std::cout << ctime(&reqInfo.recievalTime) << "\n";
    return reqInfo.id == GET_QUESTION_REQUEST_CODE
        || reqInfo.id == SUBMIT_ANSWER_REQUEST_CODE
        || reqInfo.id == GET_GAMES_RESULT_REQUEST_CODE
        || reqInfo.id == LEAVE_GAME_REQUEST_CODE;
}

RequestResult GameRequestHandler::HandleRequest(RequestInfo reqInfo)
{
    try
    {
        switch (reqInfo.id)
        {
        case GET_QUESTION_REQUEST_CODE:
            return GetQuestion(reqInfo);
        case SUBMIT_ANSWER_REQUEST_CODE:
            return SubmitAnswer(reqInfo);
        case GET_GAMES_RESULT_REQUEST_CODE:
            return GetGameResults(reqInfo);
        case LEAVE_GAME_REQUEST_CODE:
            return LeaveGame(reqInfo);
        }
    }
    catch (...)
    {
        ErrorResponse er = { "Error in server db from game handler" };
        std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(er);
        return { bufferToSend, nullptr };
    }
}

RequestResult GameRequestHandler::GetQuestion(RequestInfo reqInfo) const
{
    Question currentQuestion = m_game.getQuestionForUser(m_user); 
    GetQuestionResponse gq;
    gq.question = currentQuestion.getQuestion();
    for (int i = 0; i < currentQuestion.getPossibleAnswers().size(); i++)
        gq.answers[i + 1] = currentQuestion.getPossibleAnswers()[i];
    gq.status = gq.answers.size() > 0 ? 1 : 0;
    std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(gq);
    return { bufferToSend, m_handlerFactory.createGameRequestHandler(m_user, m_game) };
}

RequestResult GameRequestHandler::SubmitAnswer(RequestInfo reqInfo) const
{
    int correctAnswerId = m_game.submitAnswer(m_user, reqInfo.id, reqInfo.recievalTime);
    SubmitAnswerResponse su;
    su.correctAnswerId = correctAnswerId;
    std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(su);
    return { bufferToSend, m_handlerFactory.createGameRequestHandler(m_user, m_game) };
}

RequestResult GameRequestHandler::GetGameResults(RequestInfo reqInfo) const
{
    GetGameResultsResponse gr;
    std::map<LoggedUser, GameData> res = m_game.getGameResults();
    for (auto it = res.begin(); it != res.end(); it++)
    {
        PlayerResults pr;
        pr.username = it->first.getUsername();
        pr.averageAnswerTime = it->second.averangeAnswerTime;
        pr.correctAnswerCount = it->second.correctAnswerCount;
        pr.wrongAnswerCount = it->second.wrongAnswerCount;
        gr.results.push_back(pr);
    }
   
    bool isFinished = m_game.gameIsFinished();
    if (isFinished)
    {
        gr.status = 1;
        std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(gr);
        return { bufferToSend, m_handlerFactory.createMenuRequestHandler(m_user) }; //maybe go back to room
    }
    gr.status = 0;
    gr.results = std::vector<PlayerResults>();
    std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(gr);
    return { bufferToSend, m_handlerFactory.createGameRequestHandler(m_user, m_game) };
}

RequestResult GameRequestHandler::LeaveGame(RequestInfo reqInfo) const
{
    int successRemovefromGame = m_game.removePlayer(m_user);
    if (successRemovefromGame == 0)
    {
        int successRemovefromRoom = m_handlerFactory.getRoomManager().getRoom(m_game.getId()).removeUser(m_user);
        if (successRemovefromRoom == 0)
        {
            std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(LeaveGameResponse());
            return { bufferToSend, m_handlerFactory.createMenuRequestHandler(m_user)}; 
        }
    }
    throw(std::exception("error remove user from game"));
}


