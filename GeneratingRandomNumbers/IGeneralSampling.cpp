#include "GeneratingRandomNumbers/IGeneralSampling.h"

namespace mc {
    double IGeneralSampling::operator()() const
    {
        return this->callImpl();
    }
    const ICumulativeDistributionFunction & IGeneralSampling::dist() const
    {
        return this->distImpl();
    }

    std::unique_ptr<IGeneralSampling> IGeneralSampling::cloneUnique() const
    {
        return this->cloneUniqueImpl();
    }
    std::shared_ptr<IGeneralSampling> IGeneralSampling::cloneShared() const
    {
        return this->cloneSharedImpl();
    }
}