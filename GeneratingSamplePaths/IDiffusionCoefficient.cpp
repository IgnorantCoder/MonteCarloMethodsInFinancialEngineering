#include "GeneratingSamplePaths/IDiffusionCoefficient.h"

namespace mc {
    IDiffusionCoefficient::~IDiffusionCoefficient()
    {
    }

    double IDiffusionCoefficient::operator()(double t) const
    {
        return this->callImpl(t);
    }
}
