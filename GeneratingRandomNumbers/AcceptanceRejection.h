#pragma once

#include <memory>

#include "GeneratingRandomNumbers/Macro.h"
#include "GeneratingRandomNumbers/IGeneralSampling.h"

namespace mc {
    class IUniformRandomNumberGenerator;
    class IGeneralSampling;
    class ICumulativeDistributionFunction;
    class RandomGenerator;

    class AcceptanceRejection : public IGeneralSampling {
    public:
        AcceptanceRejection(const AcceptanceRejection& rhs);
        AcceptanceRejection(
            double c,
            const IUniformRandomNumberGenerator& uniformGenerator,
            const IGeneralSampling& samplingGenerator,
            const ICumulativeDistributionFunction& f);

    private:
        // Inherited via IGeneralSampling
        virtual double callImpl() const override;
        virtual const ICumulativeDistributionFunction & distImpl() const override;
        virtual std::unique_ptr<IGeneralSampling> cloneUniqueImpl() const override;
        virtual std::shared_ptr<IGeneralSampling> cloneSharedImpl() const override;

    private:
        struct Impl;
        std::unique_ptr<Impl> _impl;
    };

    RNDGEN_API RandomGenerator
    makeAcceptanceRejection(
        double c,
        const IUniformRandomNumberGenerator& uniformGenerator,
        const IGeneralSampling& samplingGenerator,
        const ICumulativeDistributionFunction& f);
}