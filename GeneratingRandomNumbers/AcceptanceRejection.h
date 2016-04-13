#pragma once

#include <memory>

#include "GeneratingRandomNumbers/IGeneralSampling.h"

namespace mc {
    class AcceptanceRejection : public IGeneralSampling {
    public:
        AcceptanceRejection(
            double c,
            const IRandomGenerator& uniformGenerator,
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
}