#pragma once
#include <ctime>
#include <vector>
#include "IRequestHandler.h"

struct  RequestInfo
{
    unsigned int id;
    time_t recievalTime;
    std::vector<unsigned char> buffer;
};

struct RequestResult;

class IRequestHandler
{
public:
    virtual bool IsRequestRelevant(RequestInfo reqInfo) = 0;
    virtual RequestResult HandleRequest(RequestInfo reqInfo) = 0;
};

struct RequestResult
{
    ~RequestResult() {
    }
    std::vector<unsigned char> response;
    IRequestHandler* newHandler{nullptr};
};