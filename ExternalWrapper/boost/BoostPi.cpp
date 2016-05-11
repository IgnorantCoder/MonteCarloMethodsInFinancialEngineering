#include "ExternalWrapper/boost/BoostPi.h"

#include <boost/math/constants/constants.hpp>

namespace external {
    BoostPi::BoostPi()
    {
    }

    double BoostPi::callImpl() const
    {
        return boost::math::constants::pi<double>();
    }

    std::unique_ptr<const Pi> makeUniqueBoostPi()
    {
        return std::make_unique<const BoostPi>();
    }
    
    std::shared_ptr<const Pi> makeSharedBoostPi()
    {
        return std::make_shared<const BoostPi>();
    }
}
