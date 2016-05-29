#include <cmath>
#include <iostream>
#include <random>

#include <boost/numeric/ublas/symmetric.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/io.hpp>

#include "ExternalWrapper/boost/BoostPi.h"
#include "ExternalWrapper/boost/BoostNapier.h"
#include "ExternalWrapper/boost/CholeskyFactorize.h"

#include "GeneratingRandomNumbers/AcceptanceRejection.h"
#include "GeneratingRandomNumbers/InverseOfExponentialDistributionCdf.h"
#include "GeneratingRandomNumbers/InverseTransform.h"
#include "GeneratingRandomNumbers/modified_linear_congruential_generator.h"
#include "GeneratingRandomNumbers/NormalDistributionCdf.h"
#include "GeneratingRandomNumbers/RandomGenerator.h"
#include "GeneratingRandomNumbers/AcceptanceRejectionNormalRandomGenerator.h"
#include "GeneratingRandomNumbers/InverseTransformExponentialRandomGenerator.h"

#include "Utility/Histogram.h"

void UniformDistributionTest();
void ExponentialDistributionTest();
void StdExponentialDistributionTest();
void NormalDistributionTest();
void StdNormalDistributionTest();

void ColeskyFactorizeTest();

int main()
{
    //UniformDistributionTest();
    //ExponentialDistributionTest();
    //StdExponentialDistributionTest();
    //NormalDistributionTest();
    //StdNormalDistributionTest();
    ColeskyFactorizeTest();

    return 0;
}

void UniformDistributionTest()
{
    util::Histogram histogram(50, 20, "*");
    std::cout << "//////////////////////////////////////////////////" << std::endl;
    std::cout << "// Uniform distribution" << std::endl;
    std::cout << "//////////////////////////////////////////////////" << std::endl;
    auto&& generator
        = mc::makeModifiedLinearCongruentialGenerator(1);
    histogram.print(generator, 100000);
}

void ExponentialDistributionTest()
{
    util::Histogram histogram(50, 20, "*");
    std::cout << "//////////////////////////////////////////////////" << std::endl;
    std::cout << "// Exponential distribution" << std::endl;
    std::cout << "//////////////////////////////////////////////////" << std::endl;
    auto&& generator
        = mc::makeInverseTransformExponentialRandomGenerator(1);
    histogram.print(generator, 100000);
}

void StdExponentialDistributionTest()
{
    util::Histogram histogram(50, 20, "*");
    std::cout << "//////////////////////////////////////////////////" << std::endl;
    std::cout << "// Std Exponential distribution" << std::endl;
    std::cout << "//////////////////////////////////////////////////" << std::endl;

    std::exponential_distribution<> d(1.0);
    std::mt19937 e(1);
    mc::RandomGenerator gen([&]() {return d(e);});
    histogram.print(gen, 1000000);
}

void NormalDistributionTest()
{
    util::Histogram histogram(50, 20, "*");
    std::cout << "//////////////////////////////////////////////////" << std::endl;
    std::cout << "// Normal distribution" << std::endl;
    std::cout << "//////////////////////////////////////////////////" << std::endl;
    auto&& generator
        = mc::makeAcceptanceRejectionNormalRandomGenerator(1);
    histogram.print(generator, 100000);
}

void StdNormalDistributionTest()
{
    util::Histogram histogram(50, 20, "*");
    std::cout << "//////////////////////////////////////////////////" << std::endl;
    std::cout << "// Std Normal distribution" << std::endl;
    std::cout << "//////////////////////////////////////////////////" << std::endl;

    std::normal_distribution<> d(0.0, 1.0); //standard normal
    std::mt19937 e(1);
    mc::RandomGenerator gen([&](){return d(e);});
    histogram.print(gen, 1000000);
}

void ColeskyFactorizeTest()
{
    boost::numeric::ublas::symmetric_matrix<double> mat(3);
    mat(0, 0) =  4; //mat(0, 1) = -1;   mat(0, 2) =  1;
    mat(1, 0) = -1;   mat(1, 1) =  4; //mat(1, 2) = -1;
    mat(2, 0) =  1;   mat(2, 1) = -1;   mat(2, 2) =  4;
    std::cout << mat << std::endl;
    auto&& result = external::choleskyFactorization(mat);

    std::cout << result->getLowerTriangularMatrix() << std::endl;
    std::cout <<
        boost::numeric::ublas::prod(
            result->getLowerTriangularMatrix(),
            result->getUpperTriangularMatrix()) << std::endl;
}