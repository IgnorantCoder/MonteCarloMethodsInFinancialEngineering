#pragma once

#include <memory>

#include "GeneratingRandomNumbers/Macro.h"
#include "GeneratingRandomNumbers/ICumulativeDistributionFunction.h"

namespace mc {
    class NormalDistributionCdf : public ICumulativeDistributionFunction {
    public:
        NormalDistributionCdf(double mean, double variance)
            : _mean(mean), _variance(variance)
        {}

    private:
        // Inherited via ICumulativeDistributionFunction
        virtual double callImpl(double x) const override;
        virtual std::unique_ptr<const ICumulativeDistributionFunction>
            cloneUniqueImpl() const override;
        virtual std::shared_ptr<const ICumulativeDistributionFunction>
            cloneSharedImpl() const override;

    private:
        double _mean;
        double _variance;
    };

    RNDGEN_API std::unique_ptr<ICumulativeDistributionFunction>
    makeUniqueNormalDistributionCdf(double mean, double variance);

    RNDGEN_API std::shared_ptr<ICumulativeDistributionFunction>
    makeSharedNormalDistributionCdf(double mean, double variance);

    RNDGEN_API std::unique_ptr<ICumulativeDistributionFunction>
    makeUniqueStandardNormalDistributionCdf();

    RNDGEN_API std::shared_ptr<ICumulativeDistributionFunction>
    makeSharedStandardNormalDistributionCdf();


}