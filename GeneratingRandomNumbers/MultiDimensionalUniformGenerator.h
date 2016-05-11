#pragma once

#include <random>

#include "GeneratingRandomNumbers/IMultiDimensionalUniformGenerator.h"

namespace mc {
    template <std::size_t N>
    class MultiDimensionalUniformGenerator
        : public IMultiDimensionalUniformGenerator<N> {
    public:
        MultiDimensionalUniformGenerator(int seed);

    private:
        MultiDimensionalUniformGenerator(
            const std::uniform_real_distribution<double>& uniform,
            const std::mt19937& mt);

    private:
        virtual std::array<double, N> callImpl() const override;
        virtual std::unique_ptr<IMultiDimensionalUniformGenerator>
            cloneUniqueImpl() const override;
        virtual std::shared_ptr<IMultiDimensionalUniformGenerator>
            cloneSharedImpl() const override;

    private:
        mutable std::uniform_real_distribution<double> _uniform;
        mutable std::mt19937 _mt;
    };

    template<std::size_t N>
    inline MultiDimensionalUniformGenerator<N>::MultiDimensionalUniformGenerator(
        int seed)
        : _uniform(0.0, 1.0),
        _mt(seed)
    {}

    template<std::size_t N>
    inline MultiDimensionalUniformGenerator<N>::MultiDimensionalUniformGenerator(
        const std::uniform_real_distribution<double>& uniform,
        const std::mt19937 & mt)
        : _uniform(uniform), _mt(mt)
    {}

    template<std::size_t N>
    inline std::array<double, N> 
        MultiDimensionalUniformGenerator<N>::callImpl() const
    {
        std::array<double, N>&& rnd = {};
        for (std::size_t i = 0; i < N; ++i) {
            rnd[i] = this->_uniform(this->_mt);
        }

        return std::move(rnd);
    }

    template<std::size_t N>
    inline std::unique_ptr<IMultiDimensionalUniformGenerator<N>>
        MultiDimensionalUniformGenerator<N>::cloneUniqueImpl() const
    {
        struct Impl : public MultiDimensionalUniformGenerator<N>
        {
            Impl(
                const std::uniform_real_distribution<double>& uniform,
                const std::mt19937& mt)
                : MultiDimensionalUniformGenerator<N>(uniform, mt)
            {}
        };
        return std::make_unique<Impl>(
            this->_uniform,
            this->_mt);
    }

    template<std::size_t N>
    inline std::shared_ptr<IMultiDimensionalUniformGenerator<N>>
        MultiDimensionalUniformGenerator<N>::cloneSharedImpl() const
    {
        struct Impl : public MultiDimensionalUniformGenerator<N>
        {
            Impl(
                const std::uniform_real_distribution<double>& uniform,
                const std::mt19937& mt)
                : MultiDimensionalUniformGenerator<N>(uniform, mt)
            {}
        };
        return std::make_shared<Impl>(
            this->_uniform,
            this->_mt);
    }
}