#pragma once

#include <memory>

#include "GeneratingRandomNumbers/Macro.h"
#include "GeneratingRandomNumbers/IUniformRandomNumberGenerator.h"

namespace mc {
    class RandomGenerator;

    template <int a, int m>
    class modified_linear_congruential_generator
        : public IUniformRandomNumberGenerator {
    public:
        modified_linear_congruential_generator(int seed);
        modified_linear_congruential_generator(
            const modified_linear_congruential_generator& rhs);
        ~modified_linear_congruential_generator();

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

    RNDGEN_API std::unique_ptr<IUniformRandomNumberGenerator>
    makeUniqueDefaultModifiedLinearCongruentialGenerator(int seed);

    RNDGEN_API std::shared_ptr<IUniformRandomNumberGenerator>
    makeSharedDefaultModifiedLinearCongruentialGenerator(int seed);

    RNDGEN_API RandomGenerator
    makeModifiedLinearCongruentialGenerator(int seed);
}