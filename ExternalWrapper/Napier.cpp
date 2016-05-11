#pragma once

#include "ExternalWrapper/Napier.h"

namespace external {
    Napier::~Napier()
    {}

    double Napier::operator()() const
    {
        return this->callImpl();
    }
}