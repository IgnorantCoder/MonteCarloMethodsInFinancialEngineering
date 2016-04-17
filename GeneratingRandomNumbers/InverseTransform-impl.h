#pragma once

#include <memory>

#include "GeneratingRandomNumbers/InverseTransform.h"
#include "GeneratingRandomNumbers/IInverseOfCdf.h"
#include "GeneratingRandomNumbers/IUniformRandomNumberGenerator.h"

namespace mc {
    struct InverseTransform::Impl {
        Impl(
            IUniformRandomNumberGenerator& generator,
            const IInverseOfCdf& invOfCdf)
            : _generator(generator.cloneUnique()),
            _invOfCdf(invOfCdf.cloneUnique())
        {}

        double generate() const
        {
            auto&& u = (*this->_generator)();
            return (*this->_invOfCdf)(u);
        }

        std::unique_ptr<IUniformRandomNumberGenerator> _generator;
        std::unique_ptr<const IInverseOfCdf> _invOfCdf;
    };
}