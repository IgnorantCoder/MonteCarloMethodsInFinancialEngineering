#pragma once

#include <vector>

#include "GeneratingSamplePaths/Macro.h"

namespace mc {
    class SAMPLEPATHS_API IStochasticProcess {
    public:
        const std::vector<double>& getTimeGrid() const;
        const std::vector<double>& getValues() const;
        const std::size_t size() const;

    private:
        virtual const std::vector<double>& getTimeGridImpl() const = 0;
        virtual const std::vector<double>& getValuesImpl() const = 0;
        virtual const std::size_t sizeImpl() const = 0;
    };
}

#ifdef INLINE_EXPANTION
#define INLINE inline
#include "GeneratingSamplePaths/IStochasticProcess.ipp"
#endif
