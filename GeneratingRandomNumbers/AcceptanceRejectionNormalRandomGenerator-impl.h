#include "GeneratingRandomNumbers/AcceptanceRejectionNormalRandomGenerator.h"

#include <array>
#include "GeneratingRandomNumbers/IMultiDimensionalUniformGenerator.h"

namespace mc {
    struct AcceptanceRejectionNormalRandomGenerator::Impl {
        Impl(const IMultiDimensionalUniformGenerator<3>& uniform);
        Impl(const Impl& rhs);
        void increment();

        std::unique_ptr<IMultiDimensionalUniformGenerator<3>> _uniform;
        mutable double _x;
    };

    AcceptanceRejectionNormalRandomGenerator::Impl::Impl(
        const IMultiDimensionalUniformGenerator<3>& uniform)
        : _uniform(uniform.cloneUnique()),
        _x(0.0)
    {}

    AcceptanceRejectionNormalRandomGenerator::Impl::Impl(const Impl & rhs)
        : _uniform(rhs._uniform->cloneUnique()),
        _x(rhs._x)
    {
    }

    void AcceptanceRejectionNormalRandomGenerator::Impl::increment()
    {
        std::array<double, 3> rnd = (*this->_uniform)();
        this->_x = -std::log(rnd[0]);

        if (rnd[1] > std::exp(-0.5 * (this->_x - 1.0) * (this->_x - 1.0)))
        {
            this->increment();
        }
        if (std::signbit(rnd[2] - 0.5)) {
            this->_x = (-this->_x);
        }
        return;
    }
}