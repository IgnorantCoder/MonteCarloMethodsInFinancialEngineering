#pragma once

#include "GeneratingRandomNumbers/InverseOfExponentialDistributionCdf.h"
#include "GeneratingRandomNumbers/ExponentialDistributionCdf.h"

namespace mc {
    struct InverseOfExponentialDistributionCdf::Impl {
        Impl(double mean)
            : _mean(mean),
            _original(std::make_unique<const ExponentialDistributionCdf>(mean))
        {}

        double calc(double u) const
        {
            auto&& ret = -this->_mean * std::log(u);
            return std::move(ret);
        }

        double _mean;
        std::unique_ptr<const ICumulativeDistributionFunction> _original;
    };
}