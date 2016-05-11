#pragma once

#include <memory>

#include "GeneratingRandomNumbers/Macro.h"

namespace mc {
    class RNDGEN_API IExponentialRandomGenerator {
    public:
        virtual ~IExponentialRandomGenerator();

    public:
        double operator()() const;
        std::unique_ptr<IExponentialRandomGenerator> cloneUnique() const;
        std::shared_ptr<IExponentialRandomGenerator> cloneShared() const;

    private:
        virtual double callImpl() const = 0;
        virtual std::unique_ptr<IExponentialRandomGenerator>
            cloneUniqueImpl() const = 0;
        virtual std::shared_ptr<IExponentialRandomGenerator>
            cloneSharedImpl() const = 0;
    };
}