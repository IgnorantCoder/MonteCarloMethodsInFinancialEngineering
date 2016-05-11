#pragma once

#include <memory>

#include "ExternalWrapper/Napier.h"

namespace external {
    class BoostNapier : public Napier {
    public:
        BoostNapier();

    public:
        virtual double callImpl() const override;
    };

    EXTERNAL_API std::unique_ptr<const Napier> makeUniqueBoostNapier();
    EXTERNAL_API std::shared_ptr<const Napier> makeSharedBoostNapier();
}