#include <iostream>

#include "GeneratingRandomNumbers/RandomGenerator.h"
#include "GeneratingRandomNumbers/simple_linear_congruential_generator.h"
#include "GeneratingRandomNumbers/modified_linear_congruential_generator.h"

int main()
{
    {
        mc::RandomGenerator generator
            = mc::makeSimpleLinearCongruentialGenerator(1);
        for (std::size_t i = 0; i < 1000; ++i) {
            std::cout << generator() << std::endl;
        }
    }

    {
        mc::RandomGenerator generator
            = mc::makeModifiedLinearCongruentialGenerator(1);
        for (std::size_t i = 0; i < 1000000; ++i) {
            std::cout << generator() << std::endl;
        }
    }
    
    return 0;
}