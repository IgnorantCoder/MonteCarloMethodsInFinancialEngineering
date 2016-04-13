#include "GeneratingRandomNumbers/simple_linear_congruential_generator.h"
#include "GeneratingRandomNumbers/simple_linear_congruential_generator-impl.h"

namespace mc {
    template<int a, int m>
    inline simple_linear_congruential_generator<a, m>
        ::simple_linear_congruential_generator(int seed)
        : _impl(std::make_unique<Impl>(seed))
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
    inline std::unique_ptr<IRandomGenerator>
    simple_linear_congruential_generator<a, m>::cloneUniqueImpl() const
    {
        return std::make_unique<
            simple_linear_congruential_generator
        >(this->_impl->_x);
    }

    template<int a, int m>
    inline std::shared_ptr<IRandomGenerator> 
    simple_linear_congruential_generator<a, m>::cloneSharedImpl() const
    {
        return std::make_shared<
            simple_linear_congruential_generator
        >(this->_impl->_x);
    }

    template class simple_linear_congruential_generator<6, 11>;
    template class simple_linear_congruential_generator<3, 11>;
}