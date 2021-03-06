#pragma once

#include <memory>

#include "GeneratingRandomNumbers/Macro.h"
#include "GeneratingRandomNumbers/IInverseOfCdf.h"

namespace mc {
    class InverseOfExponentialDistributionCdf
        : public IInverseOfCdf {
    public:
        InverseOfExponentialDistributionCdf(
            const InverseOfExponentialDistributionCdf& rhs);
        InverseOfExponentialDistributionCdf(double mean);
        ~InverseOfExponentialDistributionCdf();

    private:
        // Inherited via IInverseOfCdf
        virtual double callImpl(double u) const override;
        virtual std::unique_ptr<const IInverseOfCdf> cloneUniqueImpl() const override;
        virtual std::shared_ptr<const IInverseOfCdf> cloneSharedImpl() const override;
        virtual const ICumulativeDistributionFunction & originalImpl() const override;

    private:
        struct Impl;
        std::unique_ptr<Impl> _impl;
    };

    RNDGEN_API std::shared_ptr<const IInverseOfCdf>
    makeSharedInverseOfExponentialDistributionCdf(double mean);

    RNDGEN_API std::unique_ptr<const IInverseOfCdf>
    makeUniqueInverseOfExponentialDistributionCdf(double mean);

}