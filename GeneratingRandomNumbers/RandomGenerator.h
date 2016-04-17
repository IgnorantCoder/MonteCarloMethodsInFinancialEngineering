#pragma once

#include <memory>

#include "GeneratingRandomNumbers/Macro.h"
#include "GeneratingRandomNumbers/impl/RandomGeneratorHolder.h"

namespace mc {
    class RNDGEN_API RandomGenerator {
    public:
        template <typename T>
        RandomGenerator(const T& inner);

        double operator()() const;

    private:
        std::unique_ptr<impl::RandomGeneratorHolder> _holder;
    };

    template<typename T>
    inline RandomGenerator::RandomGenerator(const T & inner)
        : _holder(std::make_unique<impl::RandomGeneratorHolderImpl<T>>(inner))
    {
    }

}
