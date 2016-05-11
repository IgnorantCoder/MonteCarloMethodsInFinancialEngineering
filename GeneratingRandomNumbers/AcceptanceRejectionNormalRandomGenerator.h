#pragma once

#include <memory>

#include "GeneratingRandomNumbers/INormalRandomGenerator.h"
#include "GeneratingRandomNumbers/Macro.h"

namespace mc {
    template <std::size_t N>
    class IMultiDimensionalUniformGenerator;

    class RandomGenerator;

    class AcceptanceRejectionNormalRandomGenerator
        : public INormalRandomGenerator {
    public:
        AcceptanceRejectionNormalRandomGenerator(
            const IMultiDimensionalUniformGenerator<3>& uniform);
        AcceptanceRejectionNormalRandomGenerator(
            const AcceptanceRejectionNormalRandomGenerator& rhs);

    private:
        virtual double callImpl() const override;
        virtual std::unique_ptr<INormalRandomGenerator>
            cloneUniqueImpl() const override;
        virtual std::shared_ptr<INormalRandomGenerator> 
            cloneSharedImpl() const override;

    private:
        struct Impl;
        std::unique_ptr<Impl> _impl;
    };

    RNDGEN_API RandomGenerator
    makeAcceptanceRejectionNormalRandomGenerator(int seed);
}