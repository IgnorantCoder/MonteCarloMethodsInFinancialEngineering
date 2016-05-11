#pragma once

#include <memory>

#include "GeneratingRandomNumbers/IExponentialRandomGenerator.h"
#include "GeneratingRandomNumbers/Macro.h"

namespace mc {
    class IUniformRandomNumberGenerator;

    class RandomGenerator;

    class InverseTransformExponentialRandomGenerator
        : public IExponentialRandomGenerator {
    public:
        InverseTransformExponentialRandomGenerator(
            IUniformRandomNumberGenerator& uniform);
        InverseTransformExponentialRandomGenerator(
            const InverseTransformExponentialRandomGenerator& rhs);
        ~InverseTransformExponentialRandomGenerator();

    private:
        virtual double callImpl() const override;
        virtual std::unique_ptr<IExponentialRandomGenerator>
            cloneUniqueImpl() const override;
        virtual std::shared_ptr<IExponentialRandomGenerator>
            cloneSharedImpl() const override;

    private:
        struct Impl;
        std::unique_ptr<Impl> _impl;
    };

    RNDGEN_API RandomGenerator
    makeInverseTransformExponentialRandomGenerator(int seed);
}