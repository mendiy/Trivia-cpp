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
    virtual bool IsRequestRelevant(RequestInfo reqInfo) override;
    virtual RequestResult HandleRequest(RequestInfo reqInfo) override;
private:
    Game& m_game;
    LoggedUser m_user;
    // GameManager& _gameManager; found in the uml, but not needed because we can get access from the factory getter
    RequestHandlerFactory& m_handlerFactory;
    RequestResult GetQuestion(RequestInfo reqInfo) const;
    RequestResult SubmitAnswer(RequestInfo reqInfo) const;
    RequestResult GetGameResults(RequestInfo reqInfo) const;
    RequestResult LeaveGame(RequestInfo reqInfo) const;
};
