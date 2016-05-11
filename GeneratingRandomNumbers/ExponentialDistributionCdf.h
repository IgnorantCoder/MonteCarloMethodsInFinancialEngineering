#pragma once

#include <memory>

#include "GeneratingRandomNumbers/ICumulativeDistributionFunction.h"

namespace mc {
    class ExponentialDistributionCdf : public ICumulativeDistributionFunction {
    public:
        explicit ExponentialDistributionCdf(double mean)
            : _mean(mean)
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
    };
}