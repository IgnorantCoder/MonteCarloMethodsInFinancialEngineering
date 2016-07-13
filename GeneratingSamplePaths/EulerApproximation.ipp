#include "GeneratingSamplePaths/IDriftCoefficient.h"
#include "GeneratingSamplePaths/IDiffusionCoefficient.h"

namespace mc {
    EulerApproximation::EulerApproximation(
        const IDriftCoefficient& drift,
        const IDiffusionCoefficient& diffusion)
        : _drift(drift.cloneShared()),
        _diffusion(diffusion.cloneShared())
    {}
}