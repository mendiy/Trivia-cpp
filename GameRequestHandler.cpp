#include "GameRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"

#define GET_QUESTION_REQUEST_CODE 30
#define SUBMIT_ANSWER_REQUEST_CODE 31
#define GET_GAMES_RESULT_REQUEST_CODE 32
#define LEAVE_GAME_REQUEST_CODE 33

GameRequestHandler::GameRequestHandler(LoggedUser user, Game game, RequestHandlerFactory& handlerFactory)
	: _user(user.getUsername()), _game(game), _handlerFactory(handlerFactory)
{
}

bool GameRequestHandler::isRequestRelevant(RequestInfo reqInfo)
{
	std::cout << ctime(&reqInfo.recievalTime) << "\n";
	return reqInfo.id == GET_QUESTION_REQUEST_CODE
		|| reqInfo.id == SUBMIT_ANSWER_REQUEST_CODE
		|| reqInfo.id == GET_GAMES_RESULT_REQUEST_CODE
		|| reqInfo.id == LEAVE_GAME_REQUEST_CODE;
}

RequestResult GameRequestHandler::handleRequest(RequestInfo reqInfo)
{
    try
    {
        switch (reqInfo.id)
        {
        case GET_QUESTION_REQUEST_CODE:
            return getQuestion(reqInfo);
        case SUBMIT_ANSWER_REQUEST_CODE:
            return submitAnswer(reqInfo);
        case GET_GAMES_RESULT_REQUEST_CODE:
            return getGameResults(reqInfo);
        case LEAVE_GAME_REQUEST_CODE:
            return leaveGame(reqInfo);
        }
    }
    catch (...)
    {
        ErrorResponse er = { "Error in server db from game handler" };
        std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(er);
        return { bufferToSend, nullptr };
    }
}

RequestResult GameRequestHandler::getQuestion(RequestInfo reqInfo) const
{
    Question currentQuestion = _game.getQuestionForUser(_user); 
    GetQuestionResponse gq;
    gq.question = currentQuestion.getQuestion();
    for (int i = 0; i < currentQuestion.getPossibleAnswers().size(); i++)
        gq.answers[i + 1] = currentQuestion.getPossibleAnswers()[i];
    gq.status = gq.answers.size() > 0 ? 1 : 0;
    std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(gq);
    return { bufferToSend, _handlerFactory.createGameRequestHandler(_user, _game) };
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo reqInfo) const
{
    int correctAnswerId = _game.submitAnswer(_user, reqInfo.id, reqInfo.recievalTime); //TODO check time type and change to reference
    SubmitAnswerResponse su;
    su.correctAnswerId = correctAnswerId;
    std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(su);
    return { bufferToSend, _handlerFactory.createGameRequestHandler(_user, _game) };
}

RequestResult GameRequestHandler::getGameResults(RequestInfo reqInfo) const
{
    GetGameResultsResponse gr;
    std::map<LoggedUser, GameData> res = _game.getGameResults();
    for (auto it = res.begin(); it != res.end(); it++)
    {
        PlayerResults pr;
        pr.username = it->first.getUsername();
        pr.averageAnswerTime = it->second.averangeAnswerTime;
        pr.correctAnswerCount = it->second.correctAnswerCount;
        pr.wrongAnswerCount = it->second.wrongAnswerCount;
        gr.results.push_back(pr);
    }
    // TODO check if game ended and change status accordingly
    gr.status = 1;
    std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(gr);
    if(gr.status == 1)
        return { bufferToSend, _handlerFactory.createMenuRequestHandler(_user) }; //TODO maybe go back to room
    return { bufferToSend, _handlerFactory.createGameRequestHandler(_user, _game) };
}

RequestResult GameRequestHandler::leaveGame(RequestInfo reqInfo) const
{
    int successRemovefromGame = _game.removePlayer(_user);
    if (successRemovefromGame == 0)
    {
        int successRemovefromRoom = _handlerFactory.getRoomManager().getRoom(_game.getId()).removeUser(_user);
        if (successRemovefromRoom == 0)
        {
            std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(LeaveGameResponse());
            return { bufferToSend, _handlerFactory.createMenuRequestHandler(_user)}; 
        }
    }
    throw(std::exception("error remove user from game"));
}


