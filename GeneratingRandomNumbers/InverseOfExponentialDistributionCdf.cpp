#include "GeneratingRandomNumbers/InverseOfExponentialDistributionCdf.h"
#include "GeneratingRandomNumbers/InverseOfExponentialDistributionCdf-impl.h"

namespace mc {
    InverseOfExponentialDistributionCdf
        ::InverseOfExponentialDistributionCdf(double mean)
        : _impl(std::make_unique<Impl>(mean))
    {
    }

    double InverseOfExponentialDistributionCdf::callImpl(double u) const
    {
        return this->_impl->calc(u);
    }

    std::unique_ptr<const IInverseOfCdf>
    InverseOfExponentialDistributionCdf::cloneUniqueImpl() const
    {
        return std::make_unique<
            const InverseOfExponentialDistributionCdf
        >(this->_impl->_mean);
    }

    std::shared_ptr<const IInverseOfCdf>
    InverseOfExponentialDistributionCdf::cloneSharedImpl() const
    {
        return std::make_shared<
            const InverseOfExponentialDistributionCdf
        >(this->_impl->_mean);
    }
    const ICumulativeDistributionFunction & InverseOfExponentialDistributionCdf::originalImpl() const
    {
        return *this->_impl->_original;
    }
}