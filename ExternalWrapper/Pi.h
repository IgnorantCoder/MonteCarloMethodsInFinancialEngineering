#pragma once

#include "Macro.h"

namespace external {
    class EXTERNAL_API Pi {
    public:
        virtual ~Pi();

    public:
        double operator()() const;

    private:
        virtual double callImpl() const = 0;
    };
}