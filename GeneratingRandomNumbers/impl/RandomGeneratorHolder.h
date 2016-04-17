#pragma once

namespace mc {
    namespace impl {
        struct RandomGeneratorHolder {
            virtual double call() const = 0;
        };

        template <typename T>
        struct RandomGeneratorHolderImpl : public RandomGeneratorHolder {
            RandomGeneratorHolderImpl(const T& inner);
            virtual double call() const override;

            T _inner;
        };

        template<typename T>
        inline RandomGeneratorHolderImpl<T>::RandomGeneratorHolderImpl(const T & inner)
            : _inner(inner)
        {
        }

        template<typename T>
        inline double RandomGeneratorHolderImpl<T>::call() const
        {
            return (this->_inner)();
        }
    }
}