#include "GeneratingRandomNumbers/InverseTransformExponentialRandomGenerator.h"
#include "GeneratingRandomNumbers/InverseTransformExponentialRandomGenerator-impl.h"

#include "GeneratingRandomNumbers/modified_linear_congruential_generator.h"
#include "GeneratingRandomNumbers/RandomGenerator.h"

namespace mc {
    InverseTransformExponentialRandomGenerator
        ::InverseTransformExponentialRandomGenerator(
            IUniformRandomNumberGenerator& uniform)
        : _impl(std::make_unique<Impl>(uniform))
    {
    }

    InverseTransformExponentialRandomGenerator
        ::InverseTransformExponentialRandomGenerator(
            const InverseTransformExponentialRandomGenerator & rhs)
        : _impl(std::make_unique<Impl>(*rhs._impl))
    {
    }

    InverseTransformExponentialRandomGenerator
        ::~InverseTransformExponentialRandomGenerator()
    {}

    double InverseTransformExponentialRandomGenerator::callImpl() const
    {
        return (*this->_impl)();
    }

    std::unique_ptr<IExponentialRandomGenerator>
        InverseTransformExponentialRandomGenerator::cloneUniqueImpl() const
    {
        return std::make_unique<InverseTransformExponentialRandomGenerator>(*this);
    }

    std::shared_ptr<IExponentialRandomGenerator>
        InverseTransformExponentialRandomGenerator::cloneSharedImpl() const
    {
        return std::make_shared<InverseTransformExponentialRandomGenerator>(*this);
    }

    RandomGenerator makeInverseTransformExponentialRandomGenerator(int seed)
    {
        auto&& uniform
            = makeUniqueDefaultModifiedLinearCongruentialGenerator(seed);
        InverseTransformExponentialRandomGenerator generator(*uniform);
        RandomGenerator ret(generator);
        return ret;
    }
}