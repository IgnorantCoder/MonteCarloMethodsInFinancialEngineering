#include "GeneratingRandomNumbers/AcceptanceRejection.h"
#include "GeneratingRandomNumbers/AcceptanceRejection-impl.h"

namespace mc {
    AcceptanceRejection::AcceptanceRejection(
        double c, 
        const IRandomGenerator & uniformGenerator,
        const IGeneralSampling & samplingGenerator,
        const ICumulativeDistributionFunction & f)
        : _impl(std::make_unique<Impl>(c, uniformGenerator, samplingGenerator, f))
    {
    }

    double AcceptanceRejection::callImpl() const
    {
        return this->_impl->generate();
    }

    const ICumulativeDistributionFunction & AcceptanceRejection::distImpl() const
    {
        return this->_impl->_samplingGenerator->dist();
    }

    std::unique_ptr<IGeneralSampling> AcceptanceRejection::cloneUniqueImpl() const
    {
        return std::make_unique<
            AcceptanceRejection
        >(this->_impl->_c,
            *this->_impl->_uniformGenerator,
            *this->_impl->_samplingGenerator,
            *this->_impl->_f);
    }

    std::shared_ptr<IGeneralSampling> AcceptanceRejection::cloneSharedImpl() const
    {
        return std::make_shared<
            AcceptanceRejection
        >(this->_impl->_c,
            *this->_impl->_uniformGenerator,
            *this->_impl->_samplingGenerator,
            *this->_impl->_f);
    }
}

