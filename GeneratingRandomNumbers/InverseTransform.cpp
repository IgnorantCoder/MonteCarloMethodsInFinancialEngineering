#include "GeneratingRandomNumbers/InverseTransform.h"
#include "GeneratingRandomNumbers/InverseTransform-impl.h"

namespace mc {
    InverseTransform::InverseTransform(
        IRandomGenerator & generator,
        const IInverseOfCdf & invOfCdf)
        : _impl(std::make_unique<Impl>(generator, invOfCdf))
    {
    }

    double InverseTransform::callImpl() const
    {
        return this->_impl->generate();
    }

    std::unique_ptr<IGeneralSampling> InverseTransform::cloneUniqueImpl() const
    {
        return std::make_unique<InverseTransform>(
            *this->_impl->_generator,
            *this->_impl->_invOfCdf);
    }

    std::shared_ptr<IGeneralSampling> InverseTransform::cloneSharedImpl() const
    {
        return std::make_shared<InverseTransform>(
            *this->_impl->_generator,
            *this->_impl->_invOfCdf);
    }

    const ICumulativeDistributionFunction & InverseTransform::distImpl() const
    {
        return this->_impl->_invOfCdf->original();
    }
}
