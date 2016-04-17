#include "GeneratingRandomNumbers/simple_linear_congruential_generator.h"
#include "GeneratingRandomNumbers/simple_linear_congruential_generator-impl.h"

#include "GeneratingRandomNumbers/RandomGenerator.h"

namespace mc {
    template<int a, int m>
    inline simple_linear_congruential_generator<a, m>
        ::simple_linear_congruential_generator(int seed)
        : _impl(std::make_unique<Impl>(seed))
    {
    }

    template<int a, int m>
    inline simple_linear_congruential_generator<a, m>
        ::simple_linear_congruential_generator(
            const simple_linear_congruential_generator& rhs)
        : _impl(std::make_unique<Impl>(rhs._impl->_x))
    {
    }

    template<int a, int m>
    inline simple_linear_congruential_generator<a, m>
        ::~simple_linear_congruential_generator()
    {
    }

    template<int a, int m>
    inline double simple_linear_congruential_generator<a, m>::callImpl() const
    {
        this->_impl->iterate();
        return this->_impl->normalize();
    }

    template<int a, int m>
    inline std::unique_ptr<IUniformRandomNumberGenerator>
    simple_linear_congruential_generator<a, m>::cloneUniqueImpl() const
    {
        return std::make_unique<
            simple_linear_congruential_generator
        >(this->_impl->_x);
    }

    template<int a, int m>
    inline std::shared_ptr<IUniformRandomNumberGenerator>
    simple_linear_congruential_generator<a, m>::cloneSharedImpl() const
    {
        return std::make_shared<
            simple_linear_congruential_generator
        >(this->_impl->_x);
    }

    template class simple_linear_congruential_generator<6, 11>;

    RandomGenerator 
    makeSimpleLinearCongruentialGenerator(int seed)
    {
        simple_linear_congruential_generator<6, 11> inner(seed);
        RandomGenerator ret(inner);
        return ret;
    }
}