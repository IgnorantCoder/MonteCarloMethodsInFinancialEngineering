#include "GeneratingRandomNumbers/IRandomGenerator.h"

namespace mc {
    IRandomGenerator::~IRandomGenerator()
    {
    }

    double IRandomGenerator::operator()() const
    {
        return this->callImpl();
    }

    std::unique_ptr<IRandomGenerator> IRandomGenerator::cloneUnique() const
    {
        return this->cloneUniqueImpl();
    }

    std::shared_ptr<IRandomGenerator> IRandomGenerator::cloneShared() const
    {
        return this->cloneSharedImpl();
    }
}