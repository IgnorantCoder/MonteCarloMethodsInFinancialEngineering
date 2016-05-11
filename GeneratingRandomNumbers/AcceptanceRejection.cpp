#include "GeneratingRandomNumbers/AcceptanceRejection.h"
#include "GeneratingRandomNumbers/AcceptanceRejection-impl.h"

#include "GeneratingRandomNumbers/RandomGenerator.h"

namespace mc {
    AcceptanceRejection::AcceptanceRejection(const AcceptanceRejection & rhs)
        : _impl(std::make_unique<Impl>(
            rhs._impl->_c,
            *rhs._impl->_uniformGenerator,
            *rhs._impl->_samplingGenerator,
            *rhs._impl->_f))
    {
    }

    AcceptanceRejection::AcceptanceRejection(
        double c, 
        const IUniformRandomNumberGenerator & uniformGenerator,
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

    RandomGenerator makeAcceptanceRejection(
        double c,
        const IUniformRandomNumberGenerator & uniformGenerator,
        const IGeneralSampling & samplingGenerator,
        const ICumulativeDistributionFunction & f)
    {
        AcceptanceRejection inner(c, uniformGenerator, samplingGenerator, f);
        RandomGenerator ret(inner);
        return ret;
    }
}

