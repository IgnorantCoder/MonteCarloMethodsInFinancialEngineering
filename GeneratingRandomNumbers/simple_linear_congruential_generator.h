#pragma once

#include <memory>

#include "GeneratingRandomNumbers/Macro.h"
#include "GeneratingRandomNumbers/IUniformRandomNumberGenerator.h"

namespace mc {
    class RandomGenerator;

    template <int a, int m>
    class simple_linear_congruential_generator
        : public IUniformRandomNumberGenerator {
    public:
        simple_linear_congruential_generator(int seed);
        simple_linear_congruential_generator(
            const simple_linear_congruential_generator& rhs);
        ~simple_linear_congruential_generator();

    private:
        // Inherited via ILinearCongruentialGenerator
        virtual double callImpl() const override;
        virtual std::unique_ptr<IUniformRandomNumberGenerator>
        cloneUniqueImpl() const override;
        virtual std::shared_ptr<IUniformRandomNumberGenerator>
        cloneSharedImpl() const override;

    private:
        struct Impl;
        std::unique_ptr<Impl> _impl;
    };

    RNDGEN_API RandomGenerator
    makeSimpleLinearCongruentialGenerator(int seed);
}