#pragma once

#include <memory>
#include <vector>

#include "GeneratingSamplePaths/fwd.h"

namespace mc {
    class EulerApproximation {
    public:
        EulerApproximation(
            const IDriftCoefficient& drift,
            const IDiffusionCoefficient& diffusion);

    public:
        std::vector<double> generatedBy(
            const std::vector<double>& timeGrid) const;

    private:
        std::vector<double> generateRandom(std::size_t size) const;
        std::vector<double> calculateTimeDiff(
            const std::vector<double>& timeGrid) const;
        std::vector<double> calculateMu(
            const std::vector<double>& timeGrid) const;
        std::vector<double> calculateSigma(
            const std::vector<double>& timeGrid) const;


    private:
        std::shared_ptr<const IDriftCoefficient> _drift;
        std::shared_ptr<const IDiffusionCoefficient> _diffusion;
    };
}

#ifdef INLINE_EXPANTION
#define INLINE inline
#include "GeneratingSamplePaths/EulerApproximation.ipp"
#endif