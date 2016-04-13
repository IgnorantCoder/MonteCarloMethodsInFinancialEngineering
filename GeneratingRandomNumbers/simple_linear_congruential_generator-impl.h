#pragma once

#include "GeneratingRandomNumbers/simple_linear_congruential_generator.h"

namespace mc {
    template <int a, int m>
    struct simple_linear_congruential_generator<a, m>::Impl {
        Impl(int seed);
        void iterate( );
        double normalize() const;
        int _x;
    };

    template <int a, int m>
    inline simple_linear_congruential_generator<a, m>::Impl::Impl(int seed)
        : _x(seed)
    {
    }

    template <int a, int m>
    inline void
    simple_linear_congruential_generator<a, m>::Impl::iterate()
    {
        this->_x = (a * this->_x) % m;
        return;
    }

    template <int a, int m>
    inline double
    simple_linear_congruential_generator<a, m>::Impl::normalize() const
    {
        return static_cast<double>(this->_x) 
            / static_cast<double>(m);
    }
}