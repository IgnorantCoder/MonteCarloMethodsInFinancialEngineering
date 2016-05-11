#pragma once

#include <array>
#include <memory>

namespace mc {
    template <std::size_t N>
    class IMultiDimensionalUniformGenerator {
    public:
        virtual ~IMultiDimensionalUniformGenerator();

    public:
        std::array<double, N> operator()() const;
        std::unique_ptr<IMultiDimensionalUniformGenerator> cloneUnique() const;
        std::shared_ptr<IMultiDimensionalUniformGenerator> cloneShared() const;

    private:
        virtual std::array<double, N> callImpl() const = 0;
        virtual std::unique_ptr<IMultiDimensionalUniformGenerator>
            cloneUniqueImpl() const = 0;
        virtual std::shared_ptr<IMultiDimensionalUniformGenerator>
            cloneSharedImpl() const = 0;
    };

    template<std::size_t N>
    inline IMultiDimensionalUniformGenerator<N>
        ::~IMultiDimensionalUniformGenerator()
    {
    }

    template<std::size_t N>
    inline std::array<double, N>
        IMultiDimensionalUniformGenerator<N>::operator()() const
    {
        return this->callImpl();
    }

    template<std::size_t N>
    inline std::unique_ptr<IMultiDimensionalUniformGenerator<N>>
        IMultiDimensionalUniformGenerator<N>::cloneUnique() const
    {
        return this->cloneUniqueImpl();
    }

    template<std::size_t N>
    inline std::shared_ptr<IMultiDimensionalUniformGenerator<N>>
        IMultiDimensionalUniformGenerator<N>::cloneShared() const
    {
        return this->cloneSharedImpl();
    }


}