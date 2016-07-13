#pragma once

#include <memory>

#include "GeneratingSamplePaths/Macro.h"

namespace mc {
    class SAMPLEPATHS_API IDriftCoefficient {
    public:
        virtual ~IDriftCoefficient();

    public:
        double operator()(double t) const;
        std::shared_ptr<const IDriftCoefficient> cloneShared() const;

    private:
        virtual double callImpl(double t) const = 0;
        virtual std::shared_ptr<const IDriftCoefficient> cloneSharedImpl() const = 0;
    };
}

#ifdef INLINE_EXPANTION
#define INLINE inline
#include "GeneratingSamplePaths/IDriftCoefficient.ipp"
#endif
