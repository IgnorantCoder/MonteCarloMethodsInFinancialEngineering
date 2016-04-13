#include "IInverseOfCdf.h"

namespace mc {
    IInverseOfCdf::~IInverseOfCdf()
    {
    }

    double IInverseOfCdf::operator()(double u) const
    {
        return this->callImpl(u);
    }

    std::unique_ptr<const IInverseOfCdf> IInverseOfCdf::cloneUnique() const
    {
        return this->cloneUniqueImpl();
    }

    std::shared_ptr<const IInverseOfCdf> IInverseOfCdf::cloneShared() const
    {
        return this->cloneSharedImpl();
    }

    const ICumulativeDistributionFunction & IInverseOfCdf::original() const
    {
        return this->originalImpl();
    }
}
