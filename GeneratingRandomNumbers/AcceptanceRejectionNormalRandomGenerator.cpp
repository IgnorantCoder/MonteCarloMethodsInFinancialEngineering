#include "GeneratingRandomNumbers/AcceptanceRejectionNormalRandomGenerator.h"
#include "GeneratingRandomNumbers/AcceptanceRejectionNormalRandomGenerator-impl.h"

#include "GeneratingRandomNumbers/MultiDimensionalUniformGenerator.h"
#include "GeneratingRandomNumbers/RandomGenerator.h"

namespace mc {
    AcceptanceRejectionNormalRandomGenerator
        ::AcceptanceRejectionNormalRandomGenerator(
            const IMultiDimensionalUniformGenerator<3>& uniform)
        : _impl(std::make_unique<Impl>(uniform))
    {
    }

    AcceptanceRejectionNormalRandomGenerator
        ::AcceptanceRejectionNormalRandomGenerator(
            const AcceptanceRejectionNormalRandomGenerator & rhs)
        : _impl(std::make_unique<Impl>(*rhs._impl))
    {
    }

    double AcceptanceRejectionNormalRandomGenerator::callImpl() const
    {
        this->_impl->increment();
        return this->_impl->_x;
    }

    std::unique_ptr<INormalRandomGenerator>
        AcceptanceRejectionNormalRandomGenerator::cloneUniqueImpl() const
    {
        return std::make_unique<AcceptanceRejectionNormalRandomGenerator>(*this);
    }

    std::shared_ptr<INormalRandomGenerator> 
        AcceptanceRejectionNormalRandomGenerator::cloneSharedImpl() const
    {
        return std::make_shared<AcceptanceRejectionNormalRandomGenerator>(*this);
    }

    RandomGenerator makeAcceptanceRejectionNormalRandomGenerator(int seed)
    {
        MultiDimensionalUniformGenerator<3> uniform(seed);
        AcceptanceRejectionNormalRandomGenerator generator(uniform);
        RandomGenerator ret(generator);
        return ret;
    }
}