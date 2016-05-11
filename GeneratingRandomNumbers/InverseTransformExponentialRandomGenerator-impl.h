#pragma once

#include <memory>

#include "GeneratingRandomNumbers/IUniformRandomNumberGenerator.h"
#include "GeneratingRandomNumbers/IInverseOfCdf.h"
#include "GeneratingRandomNumbers/InverseTransform.h"
#include "GeneratingRandomNumbers/InverseOfExponentialDistributionCdf.h"


namespace mc {
    struct InverseTransformExponentialRandomGenerator::Impl {
        Impl(IUniformRandomNumberGenerator& uniform)
            : _generator(
                uniform,
                InverseOfExponentialDistributionCdf(1.0))
        {}

        double operator()()
        {
            return _generator();
        }
        
        InverseTransform _generator;
    };
}