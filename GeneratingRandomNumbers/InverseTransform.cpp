#include "GeneratingRandomNumbers/InverseTransform.h"
#include "GeneratingRandomNumbers/InverseTransform-impl.h"

#include "GeneratingRandomNumbers/RandomGenerator.h"

namespace mc {
    InverseTransform::InverseTransform(const InverseTransform & rhs)
        : _impl(std::make_unique<Impl>(
            *rhs._impl->_generator,
            *rhs._impl->_invOfCdf))
    {
    }

    InverseTransform::InverseTransform(
        IUniformRandomNumberGenerator & generator,
        const IInverseOfCdf & invOfCdf)
        : _impl(std::make_unique<Impl>(generator, invOfCdf))
    {
    }

    InverseTransform::~InverseTransform()
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

    RandomGenerator
    makeInverseTransform(
        IUniformRandomNumberGenerator & generator, 
        const IInverseOfCdf & invOfCdf)
    {
        InverseTransform inner(generator, invOfCdf);
        RandomGenerator ret(inner);
        return ret;
    }

    std::shared_ptr<const IGeneralSampling> makeSharedInverseTransform(
        IUniformRandomNumberGenerator & generator,
        const IInverseOfCdf & invOfCdf)
    {
        return std::make_shared<const InverseTransform>(generator, invOfCdf);
    }

    std::unique_ptr<const IGeneralSampling> makeUniqueInverseTransform(
        IUniformRandomNumberGenerator & generator,
        const IInverseOfCdf & invOfCdf)
    {
        return std::make_unique<const InverseTransform>(generator, invOfCdf);
    }
}
