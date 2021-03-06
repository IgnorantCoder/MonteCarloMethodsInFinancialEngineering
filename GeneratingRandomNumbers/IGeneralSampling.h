#pragma once

#include <memory>

#include "GeneratingRandomNumbers/Macro.h"

namespace mc {
    class ICumulativeDistributionFunction;

    class RNDGEN_API IGeneralSampling {
    public:
        double operator()() const;
        const ICumulativeDistributionFunction& dist() const;
        std::unique_ptr<IGeneralSampling> cloneUnique() const;
        std::shared_ptr<IGeneralSampling> cloneShared() const;

    private:
        virtual double callImpl() const = 0;
        virtual const ICumulativeDistributionFunction& distImpl() const = 0;
        virtual std::unique_ptr<IGeneralSampling> cloneUniqueImpl() const = 0;
        virtual std::shared_ptr<IGeneralSampling> cloneSharedImpl() const = 0;
    };
}