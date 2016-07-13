#pragma once

#include <vector>
#include <memory>

#include "GeneratingSamplePaths/Macro.h"
#include "GeneratingSamplePaths/IStochasticProcess.h"

namespace mc {
    class BrownianMotion : public IStochasticProcess {
    public:
        static SAMPLEPATHS_API std::shared_ptr<const IStochasticProcess>
        buildByBrownianBridge(
            const std::vector<double>& timeGrid,
            double startValue,
            double endValue);

    public:
        BrownianMotion(
            const std::vector<double>& timeGrid,
            const std::vector<double>& values);

    private:
        const std::vector<double>& getTimeGridImpl() const override;
        const std::vector<double>& getValuesImpl() const override;
        const std::size_t sizeImpl() const override;

    private:
        std::vector<double> _timeGrid;
        std::vector<double> _values;
    };
}

#ifdef INLINE_EXPANTION
#define INLINE inline
#include "GeneratingSamplePaths/BrownianMotion.ipp"
#endif