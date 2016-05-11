#pragma once

#include "ExternalWrapper/Pi.h"

namespace external {
    Pi::~Pi()
    {}

    double Pi::operator()() const
    {
        return this->callImpl();
    }
}