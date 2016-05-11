#pragma once

#include "Macro.h"

namespace external {
    class EXTERNAL_API Napier {
    public:
        virtual ~Napier();

    public:
        double operator()() const;

    private:
        virtual double callImpl() const = 0;
    };
}