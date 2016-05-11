#include "GeneratingRandomNumbers/NormalDistributionCdf.h"

#include "ExternalWrapper/boost/BoostPi.h"

namespace mc {
    double NormalDistributionCdf::callImpl(double x) const
    {
        static auto&& pi
            = (*external::makeUniqueBoostPi())();
        const auto coefficient
            = 1.0 / std::sqrt(0.5 * pi * this->_variance);
        const auto exponent
            = -(x - this->_mean) * (x - this->_mean) / (2.0 * this->_variance);

        return coefficient * std::exp(exponent);
    }

    std::unique_ptr<const ICumulativeDistributionFunction>
    NormalDistributionCdf::cloneUniqueImpl() const
    {
        return std::make_unique<const NormalDistributionCdf>(
            this->_mean,
            this->_variance);
    }

    std::shared_ptr<const ICumulativeDistributionFunction>
    NormalDistributionCdf::cloneSharedImpl() const
    {
        return std::make_shared<const NormalDistributionCdf>(
            this->_mean,
            this->_variance);
    }

    std::unique_ptr<ICumulativeDistributionFunction>
    makeUniqueNormalDistributionCdf(double mean, double variance)
    {
        return std::make_unique<NormalDistributionCdf>(mean, variance);
    }

    std::shared_ptr<ICumulativeDistributionFunction>
    makeSharedNormalDistributionCdf(double mean, double variance)
    {
        return std::make_shared<NormalDistributionCdf>(mean, variance);
    }

    std::unique_ptr<ICumulativeDistributionFunction>
    makeUniqueStandardNormalDistributionCdf()
    {
        return std::make_unique<NormalDistributionCdf>(0.0, 1.0);
    }

    std::shared_ptr<ICumulativeDistributionFunction>
    makeSharedStandardNormalDistributionCdf()
    {
        return std::make_shared<NormalDistributionCdf>(0.0, 1.0);
    }
}
