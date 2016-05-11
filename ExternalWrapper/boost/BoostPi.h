#pragma once

#include <memory>

#include "ExternalWrapper/Pi.h"

namespace external {
    class BoostPi : public Pi {
    public:
        BoostPi();

    public:
        virtual double callImpl() const override;
    };

    EXTERNAL_API std::unique_ptr<const Pi> makeUniqueBoostPi();
    EXTERNAL_API std::shared_ptr<const Pi> makeSharedBoostPi();
}