#ifndef SummaFuncs_h
#define SummaFuncs_h

#include <Arduino.h>
#include "IPAddress.h"
#include "Client.h"
#include "Stream.h"


class SummaFuncs : public Print {
private:
    Client* client;
    bool SWDEBUG;

public:
    SummaFuncs();
    SummaFuncs(Client& client);

    bool SummaDebug();


}