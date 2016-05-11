#pragma once

#include "GeneratingSamplePaths/Macro.h"

namespace mc {
    class SAMPLEPATHS_API IDiffusionCoefficient {
    public:
        virtual ~IDiffusionCoefficient();

    public:
        double operator()(double t) const;

    private:
        virtual double callImpl(double t) const = 0;
    };
}