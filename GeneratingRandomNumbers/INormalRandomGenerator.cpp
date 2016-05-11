#include "GeneratingRandomNumbers/INormalRandomGenerator.h"

namespace mc {
    INormalRandomGenerator::~INormalRandomGenerator()
    {
    }
    double INormalRandomGenerator::operator()() const
    {
        return this->callImpl();
    }

    std::unique_ptr<INormalRandomGenerator> 
        INormalRandomGenerator::cloneUnique() const
    {
        return this->cloneUniqueImpl();
    }

    std::shared_ptr<INormalRandomGenerator> 
        INormalRandomGenerator::cloneShared() const
    {
        return this->cloneSharedImpl();
    }
}