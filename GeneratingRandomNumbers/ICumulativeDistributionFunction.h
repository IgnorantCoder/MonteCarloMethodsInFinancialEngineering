#pragma once

#include <memory>

#include "GeneratingRandomNumbers/Macro.h"

namespace mc {
    class RNDGEN_API ICumulativeDistributionFunction {
    public:
        virtual ~ICumulativeDistributionFunction();

    public:
        double operator()(double x) const;
        std::unique_ptr<const ICumulativeDistributionFunction>
            cloneUnique() const;
        std::shared_ptr<const ICumulativeDistributionFunction>
            cloneShared() const;

    private:
        virtual double callImpl(double x) const = 0;
        virtual std::unique_ptr<const ICumulativeDistributionFunction>
            cloneUniqueImpl() const = 0;
        virtual std::shared_ptr<const ICumulativeDistributionFunction>
            cloneSharedImpl() const = 0;
    };
}