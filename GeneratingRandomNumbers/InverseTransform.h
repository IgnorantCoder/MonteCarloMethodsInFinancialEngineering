#pragma once

#include <memory>

#include "GeneratingRandomNumbers/Macro.h"
#include "GeneratingRandomNumbers/IGeneralSampling.h"

namespace mc {
    class IUniformRandomNumberGenerator;
    class IInverseOfCdf;
    class RandomGenerator;

    class InverseTransform : public IGeneralSampling {
    public:
        InverseTransform(
            const InverseTransform& rhs);
        InverseTransform(
            IUniformRandomNumberGenerator& generator,
            const IInverseOfCdf& invOfCdf);
        ~InverseTransform();

    private:
        // Inherited via IGeneralSampling
        virtual double callImpl() const override;
        virtual std::unique_ptr<IGeneralSampling>
        cloneUniqueImpl() const override;
        virtual std::shared_ptr<IGeneralSampling>
        cloneSharedImpl() const override;
        virtual const ICumulativeDistributionFunction & distImpl() const override;

    private:
        struct Impl;
        std::unique_ptr<Impl> _impl;
    };

    RNDGEN_API RandomGenerator
    makeInverseTransform(
        IUniformRandomNumberGenerator& generator,
        const IInverseOfCdf& invOfCdf);

    RNDGEN_API std::shared_ptr<const IGeneralSampling>
    makeSharedInverseTransform(
        IUniformRandomNumberGenerator& generator,
        const IInverseOfCdf& invOfCdf);

    RNDGEN_API std::unique_ptr<const IGeneralSampling>
    makeUniqueInverseTransform(
        IUniformRandomNumberGenerator& generator,
        const IInverseOfCdf& invOfCdf);

}