#pragma once

#include <array>
#include <memory>

namespace mc {
    template<std::size_t N>
    class IMultiDimensionalNormalGenerator {
    public:
        virtual ~IMultiDimensionalNormalGenerator();

    public:
        std::array<double, N> operator()() const;
        std::unique_ptr<IMultiDimensionalNormalGenerator> cloneUnique() const;
        std::shared_ptr<IMultiDimensionalNormalGenerator> cloneShared() const;

    private:
        virtual std::array<double, N> callImpl() const = 0;
        virtual std::unique_ptr<IMultiDimensionalNormalGenerator>
            cloneUniqueImpl() const = 0;
        virtual std::shared_ptr<IMultiDimensionalNormalGenerator>
            cloneSharedImpl() const = 0;
    };

    template<std::size_t N>
    inline IMultiDimensionalNormalGenerator<N>
        ::~IMultiDimensionalNormalGenerator()
    {
    }

    template<std::size_t N>
    inline std::array<double, N>
    IMultiDimensionalNormalGenerator<N>::operator()() const
    {
        return this->callImpl();
    }

    template<std::size_t N>
    inline std::unique_ptr<IMultiDimensionalNormalGenerator<N>>
    IMultiDimensionalNormalGenerator<N>::cloneUnique() const
    {
        return this->cloneUniqueImpl();
    }

    template<std::size_t N>
    inline std::shared_ptr<IMultiDimensionalNormalGenerator<N>>
    IMultiDimensionalNormalGenerator<N>::cloneShared() const
    {
        return this->cloneSharedImpl();
    }
}