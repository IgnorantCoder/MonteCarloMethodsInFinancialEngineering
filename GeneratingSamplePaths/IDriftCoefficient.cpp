#include "GeneratingSamplePaths/IDriftCoefficient.h"

namespace mc {
    IDriftCoefficient::~IDriftCoefficient()
    {
    }

    double IDriftCoefficient::operator()(double t) const
    {
        return this->callImpl(t);
    }
}
