#pragma once

#include <memory>

#include "GeneratingRandomNumbers/InverseTransform.h"
#include "GeneratingRandomNumbers/IInverseOfCdf.h"
#include "GeneratingRandomNumbers/IRandomGenerator.h"

namespace mc {
    struct InverseTransform::Impl {
        Impl(
            IRandomGenerator& generator,
            const IInverseOfCdf& invOfCdf)
            : _generator(generator.cloneUnique()),
            _invOfCdf(invOfCdf.cloneUnique())
        {}

        double generate() const
        {
            auto&& u = (*this->_generator)();
            return (*this->_invOfCdf)(u);
        }

        std::unique_ptr<IRandomGenerator> _generator;
        std::unique_ptr<const IInverseOfCdf> _invOfCdf;
    };
}