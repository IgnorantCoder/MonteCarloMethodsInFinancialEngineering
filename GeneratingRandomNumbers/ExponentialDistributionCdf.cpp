#include "ExponentialDistributionCdf.h"

namespace mc {
    double ExponentialDistributionCdf::callImpl(double x) const
    {
        return 1 - std::exp(- x / this->_mean);
    }

    std::unique_ptr<const ICumulativeDistributionFunction> 
    ExponentialDistributionCdf::cloneUniqueImpl() const
    {
        return std::make_unique<const ExponentialDistributionCdf>(this->_mean);
    }

    std::shared_ptr<const ICumulativeDistributionFunction> mc::ExponentialDistributionCdf::cloneSharedImpl() const
    {
        return std::make_shared<const ExponentialDistributionCdf>(this->_mean);
    }
}
