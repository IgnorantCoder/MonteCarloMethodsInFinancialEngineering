#pragma once

#include <memory>

#include "GeneratingRandomNumbers/ILinearCongruentialGenerator.h"

namespace mc {
    template <int a, int m>
    class simple_linear_congruential_generator
        : public ILinearCongruentialGenerator {
    public:
        simple_linear_congruential_generator(int seed);
        ~simple_linear_congruential_generator();

    private:
        // Inherited via ILinearCongruentialGenerator
        virtual double callImpl() const override;
        virtual std::unique_ptr<IRandomGenerator> cloneUniqueImpl() const override;
        virtual std::shared_ptr<IRandomGenerator> cloneSharedImpl() const override;

    private:
        struct Impl;
        std::unique_ptr<Impl> _impl;
    };
}