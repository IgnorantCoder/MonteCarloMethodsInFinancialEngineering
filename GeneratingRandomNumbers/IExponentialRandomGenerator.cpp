#include "GeneratingRandomNumbers/IExponentialRandomGenerator.h"

namespace mc {
    IExponentialRandomGenerator::~IExponentialRandomGenerator()
    {
    }
    double IExponentialRandomGenerator::operator()() const
    {
        return this->callImpl();
    }

    std::unique_ptr<IExponentialRandomGenerator>
        IExponentialRandomGenerator::cloneUnique() const
    {
        return this->cloneUniqueImpl();
    }

    std::shared_ptr<IExponentialRandomGenerator>
        IExponentialRandomGenerator::cloneShared() const
    {
        return this->cloneSharedImpl();
    }
}