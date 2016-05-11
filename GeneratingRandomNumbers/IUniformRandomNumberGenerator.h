#pragma once

#include <memory>

#include "GeneratingRandomNumbers/Macro.h"

namespace mc {
    class RNDGEN_API IUniformRandomNumberGenerator {
    public:
        virtual ~IUniformRandomNumberGenerator();

    public:
        double operator()() const;
        std::unique_ptr<IUniformRandomNumberGenerator> cloneUnique() const;
        std::shared_ptr<IUniformRandomNumberGenerator> cloneShared() const;

    private:
        virtual double callImpl() const = 0;
        virtual std::unique_ptr<IUniformRandomNumberGenerator>
        cloneUniqueImpl() const = 0;
        virtual std::shared_ptr<IUniformRandomNumberGenerator>
        cloneSharedImpl() const = 0;
    };
}