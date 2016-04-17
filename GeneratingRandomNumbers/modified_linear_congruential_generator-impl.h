#pragma once

#include "GeneratingRandomNumbers/modified_linear_congruential_generator.h"

namespace mc {
    template <int a, int m>
    struct modified_linear_congruential_generator<a, m>::Impl {
        Impl(int seed);
        void iterate();
        double normalize() const;

        static constexpr int _q = m / a;
        static constexpr int _r = m % a;
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
        const int k = this->_x / _q;
        this->_x = a * (this->_x - k * _q) - k * _r;
        this->_x += this->_x < 0 ? m : 0;

        return;
    }
    
    template <int a, int m>
    inline double
    modified_linear_congruential_generator<a, m>::Impl::normalize() const
    {
        return static_cast<double>(this->_x)
            / static_cast<double>(m);
    }
}