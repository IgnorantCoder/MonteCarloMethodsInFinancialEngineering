#include <cmath>
#include <iostream>
#include <random>

#include "ExternalWrapper/boost/BoostPi.h"
#include "ExternalWrapper/boost/BoostNapier.h"
#include "Utility/Histogram.h"
#include "GeneratingRandomNumbers/AcceptanceRejection.h"
#include "GeneratingRandomNumbers/InverseOfExponentialDistributionCdf.h"
#include "GeneratingRandomNumbers/InverseTransform.h"
#include "GeneratingRandomNumbers/modified_linear_congruential_generator.h"
#include "GeneratingRandomNumbers/NormalDistributionCdf.h"
#include "GeneratingRandomNumbers/RandomGenerator.h"
#include "GeneratingRandomNumbers/AcceptanceRejectionNormalRandomGenerator.h"
#include "GeneratingRandomNumbers/InverseTransformExponentialRandomGenerator.h"

int main()
{
    util::Histogram histogram(50, 20, "*");
    
    {
        std::cout << "//////////////////////////////////////////////////" << std::endl;
        std::cout << "// Uniform distribution"                            << std::endl;
        std::cout << "//////////////////////////////////////////////////" << std::endl;
        auto&& generator
            = mc::makeModifiedLinearCongruentialGenerator(1);
        histogram.print(generator, 100000);
    }

    {
        std::cout << "//////////////////////////////////////////////////" << std::endl;
        std::cout << "// Exponential distribution"                        << std::endl;
        std::cout << "//////////////////////////////////////////////////" << std::endl;
        auto&& generator
            = mc::makeInverseTransformExponentialRandomGenerator(1);
        histogram.print(generator, 100000);
    }

    {
        std::cout << "//////////////////////////////////////////////////" << std::endl;
        std::cout << "// Std Exponential distribution"                    << std::endl;
        std::cout << "//////////////////////////////////////////////////" << std::endl;
        struct NormalRandom {
            NormalRandom() : _exponential(1.0), _mt(1) {}
            double operator()() const { return _exponential(_mt); }
            mutable std::exponential_distribution<> _exponential;
            mutable std::mt19937 _mt;
        } inner;

        mc::RandomGenerator generator(inner);
        histogram.print(generator, 1000000);
    }

    {
        std::cout << "//////////////////////////////////////////////////" << std::endl;
        std::cout << "// Normal distribution"                             << std::endl;
        std::cout << "//////////////////////////////////////////////////" << std::endl;
        auto&& generator
            = mc::makeAcceptanceRejectionNormalRandomGenerator(1);
        histogram.print(generator, 100000);
    }

    {
        std::cout << "//////////////////////////////////////////////////" << std::endl;
        std::cout << "// Std Normal distribution"                         << std::endl;
        std::cout << "//////////////////////////////////////////////////" << std::endl;
        struct NormalRandom {
            NormalRandom() : _normal(0.0, 1.0), _mt(1) {}
            double operator()() const { return _normal(_mt); }
            mutable std::normal_distribution<> _normal;
            mutable std::mt19937 _mt;
        } inner;

        mc::RandomGenerator generator(inner);
        histogram.print(generator, 1000000);
    }

    return 0;
}