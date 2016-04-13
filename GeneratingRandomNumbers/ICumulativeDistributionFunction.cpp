#include "ICumulativeDistributionFunction.h"

namespace mc {
    ICumulativeDistributionFunction::~ICumulativeDistributionFunction()
    {
    }

    double ICumulativeDistributionFunction::operator()(double x) const
    {
        return this->callImpl(x);
    }

    std::unique_ptr<const ICumulativeDistributionFunction>
        ICumulativeDistributionFunction::cloneUnique() const
    {
        return this->cloneUniqueImpl();
    }

    std::shared_ptr<const ICumulativeDistributionFunction>
        ICumulativeDistributionFunction::cloneShared() const
    {
        return this->cloneSharedImpl();
    }
}
