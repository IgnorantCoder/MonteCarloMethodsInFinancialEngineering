#include "ExternalWrapper/boost/BoostNapier.h"

#include <boost/math/constants/constants.hpp>

namespace external {
    BoostNapier::BoostNapier()
    {
    }

    double BoostNapier::callImpl() const
    {
        return boost::math::constants::e<double>();
    }

    std::unique_ptr<const Napier> makeUniqueBoostNapier()
    {
        return std::make_unique<const BoostNapier>();
    }

    std::shared_ptr<const Napier> makeSharedBoostNapier()
    {
        return std::make_shared<const BoostNapier>();
    }
}
