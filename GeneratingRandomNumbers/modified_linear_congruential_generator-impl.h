#pragma once

#include "GeneratingRandomNumbers/modified_linear_congruential_generator.h"

namespace mc {
    template <int a, int m>
    struct modified_linear_congruential_generator<a, m>::Impl {
        Impl(int seed);
        void iterate();
        int calck() const;
        double normalize() const;

        static constexpr int q = m / a;
        static constexpr int r = m % a;
        int _x;
    };

    template <int a, int m>
    inline modified_linear_congruential_generator<a, m>::Impl::Impl(int seed)
        : _x(seed)
    {
    }

    template <int a, int m>
    inline void
    modified_linear_congruential_generator<a, m>::Impl::iterate()
    {
        this->_x = a * (this->_x - this->calck() * q) - this->calck() * r;

        if (this->_x < 0) {
            this->_x = this->_x + m;
            return;
        }
        else {
            this->iterate();
        }

        return;
    }
    
    template <int a, int m>
    inline int modified_linear_congruential_generator<a, m>::Impl::calck() const
    {
        return this->_x / q;
    }

    template <int a, int m>
    inline double
    modified_linear_congruential_generator<a, m>::Impl::normalize() const
    {
        return static_cast<double>(this->_x)
            / static_cast<double>(m);
    }
}