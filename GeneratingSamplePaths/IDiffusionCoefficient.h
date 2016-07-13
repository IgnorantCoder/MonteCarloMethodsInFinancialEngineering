#pragma once

#include <memory>

#include "GeneratingSamplePaths/Macro.h"

namespace mc {
    class SAMPLEPATHS_API IDiffusionCoefficient {
    public:
        virtual ~IDiffusionCoefficient();

    public:
        double operator()(double t) const;
        std::shared_ptr<const IDiffusionCoefficient> cloneShared() const;

    private:
        virtual double callImpl(double t) const = 0;
        virtual std::shared_ptr<const IDiffusionCoefficient> cloneSharedImpl() const = 0;
    };
}

#ifdef INLINE_EXPANTION
#define INLINE inline
#include "GeneratingSamplePaths/IDiffusionCoefficient.ipp"
#endif