#pragma once
#include "IRequestHandler.h"
#include "Game.h"
#include "LoggedUser.h"
#include "GameManager.h"
class RequestHandlerFactory;

class GameRequestHandler : public IRequestHandler
{
public:
	GameRequestHandler(LoggedUser user, Game& game, RequestHandlerFactory& handlerFactory);
	virtual bool isRequestRelevant(RequestInfo reqInfo) override;
	virtual RequestResult handleRequest(RequestInfo reqInfo) override;
private:
	Game& _game;
	LoggedUser _user;
	// GameManager& _gameManager; not needed because we can get access from the factory getter
	RequestHandlerFactory& _handlerFactory;
	RequestResult getQuestion(RequestInfo reqInfo) const;
	RequestResult submitAnswer(RequestInfo reqInfo) const;
	RequestResult getGameResults(RequestInfo reqInfo) const;
	RequestResult leaveGame(RequestInfo reqInfo) const;
};
