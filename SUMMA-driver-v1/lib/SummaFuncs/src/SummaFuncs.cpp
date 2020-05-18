#include "SummaFuncs.h"
#include "Arduino.h"

SummaFuncs::SummaFuncs() {
    this->client = NULL;
    this->SWDEBUG = true;
}

bool SummaFuncs::SummaDebug() {
    return this->SWDEBUG;
}


