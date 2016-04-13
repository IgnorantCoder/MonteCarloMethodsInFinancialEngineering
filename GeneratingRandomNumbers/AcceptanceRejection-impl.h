#pragma once

#include <memory>

#include "GeneratingRandomNumbers/AcceptanceRejection.h"
#include "GeneratingRandomNumbers/ICumulativeDistributionFunction.h"
#include "GeneratingRandomNumbers/IRandomGenerator.h"
#include "GeneratingRandomNumbers/IGeneralSampling.h"

namespace mc {
    struct AcceptanceRejection::Impl {
        Impl(double c,
            const IRandomGenerator& uniformGenerator,
            const IGeneralSampling& samplingGenerator,
            const ICumulativeDistributionFunction& f)
            : _c(c),
            _uniformGenerator(uniformGenerator.cloneUnique()),
            _samplingGenerator(samplingGenerator.cloneUnique()),
            _f(f.cloneUnique())
        {}

        double generate() const
        {
            auto&& x = (*this->_samplingGenerator)();
            auto&& u = (*this->_uniformGenerator)();

            auto&& rhs
                = (*this->_f)(x) / (this->_c * (this->_samplingGenerator->dist())(x));
            if (u <= rhs) {
                return x;
            }

            return generate();
        }

        double _c;
        std::unique_ptr<IRandomGenerator> _uniformGenerator;
        std::unique_ptr<IGeneralSampling> _samplingGenerator;
        std::unique_ptr<const ICumulativeDistributionFunction> _f;
    };
}