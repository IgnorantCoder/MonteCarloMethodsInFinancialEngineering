#pragma once

#include <memory>

#include "GeneratingRandomNumbers/IGeneralSampling.h"

namespace mc {
    class IUniformRandomNumberGenerator;
    class IInverseOfCdf;

    class InverseTransform : public IGeneralSampling {
    public:
        InverseTransform(
            IUniformRandomNumberGenerator& generator,
            const IInverseOfCdf& invOfCdf);

    private:
        // Inherited via IGeneralSampling
        virtual double callImpl() const override;
        virtual std::unique_ptr<IGeneralSampling> cloneUniqueImpl() const override;
        virtual std::shared_ptr<IGeneralSampling> cloneSharedImpl() const override;
        virtual const ICumulativeDistributionFunction & distImpl() const override;

    private:
        struct Impl;
        std::unique_ptr<Impl> _impl;
    };
}