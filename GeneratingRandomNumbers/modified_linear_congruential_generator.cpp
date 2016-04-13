#include "GeneratingRandomNumbers/modified_linear_congruential_generator.h"
#include "GeneratingRandomNumbers/modified_linear_congruential_generator-impl.h"

namespace mc {
    template<int a, int m>
    inline modified_linear_congruential_generator<a, m>
        ::modified_linear_congruential_generator(int seed)
        : _impl(std::make_unique<Impl>(seed))
    {
    }

    template<int a, int m>
    inline modified_linear_congruential_generator<a, m>
        ::~modified_linear_congruential_generator()
    {
    }

    template<int a, int m>
    inline double modified_linear_congruential_generator<a, m>::callImpl() const
    {
        this->_impl->iterate();
        return this->_impl->normalize();
    }

    template<int a, int m>
    inline std::unique_ptr<IRandomGenerator> modified_linear_congruential_generator<a, m>::cloneUniqueImpl() const
    {
        return std::make_unique<
            modified_linear_congruential_generator
        >(this->_impl->_x);
    }

    template<int a, int m>
    inline std::shared_ptr<IRandomGenerator> modified_linear_congruential_generator<a, m>::cloneSharedImpl() const
    {
        return std::make_shared<
            modified_linear_congruential_generator
        >(this->_impl->_x);
    }

    //2147483647 = 2^31 - 1
    template class modified_linear_congruential_generator<16807, 2147483647>;
    template class modified_linear_congruential_generator<39373, 2147483647>;
    template class modified_linear_congruential_generator<742938285, 2147483647>;
    template class modified_linear_congruential_generator<950706376, 2147483647>;
    template class modified_linear_congruential_generator<1226874159, 2147483647>;
}