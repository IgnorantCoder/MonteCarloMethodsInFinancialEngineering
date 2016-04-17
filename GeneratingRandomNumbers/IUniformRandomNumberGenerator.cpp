#include "GeneratingRandomNumbers/IUniformRandomNumberGenerator.h"

namespace mc {
    IUniformRandomNumberGenerator::~IUniformRandomNumberGenerator()
    {
    }

    double IUniformRandomNumberGenerator::operator()() const
    {
        return this->callImpl();
    }

    std::unique_ptr<IUniformRandomNumberGenerator>
    IUniformRandomNumberGenerator::cloneUnique() const
    {
        return this->cloneUniqueImpl();
    }

    std::shared_ptr<IUniformRandomNumberGenerator>
    IUniformRandomNumberGenerator::cloneShared() const
    {
        return this->cloneSharedImpl();
    }
}
