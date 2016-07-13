#include <cmath>
#include <iostream>
#include <fstream>
#include <random>
#include <numeric>

#include <boost/numeric/ublas/symmetric.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/matrix.hpp>
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
#include "GeneratingRandomNumbers/CorrelationNormalGenerator.h"

#include "GeneratingSamplePaths/BrownianMotion.h"

#include "Utility/Histogram.h"

void UniformDistributionTest();
void ExponentialDistributionTest();
void StdExponentialDistributionTest();
void NormalDistributionTest();
void StdNormalDistributionTest();

void ColeskyFactorizeTest();

void CorrelationNormalGeneratorTest();
void BrawnianBridgeBuilderTest();
void BrownianMotionTest();


int main()
{
    //UniformDistributionTest();
    //ExponentialDistributionTest();
    //StdExponentialDistributionTest();
    //NormalDistributionTest();
    //StdNormalDistributionTest();
    //ColeskyFactorizeTest();
    //CorrelationNormalGeneratorTest();
    BrownianMotionTest();

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
    const auto& result = external::choleskyFactorization(mat);

    std::cout << result->getLowerTriangularMatrix() << std::endl;
    std::cout << result->getUpperTriangularMatrix() << std::endl;
    std::cout <<
        boost::numeric::ublas::prod(
            result->getLowerTriangularMatrix(),
            result->getUpperTriangularMatrix()) << std::endl;
}

void CorrelationNormalGeneratorTest()
{
    constexpr std::size_t N = 2;

    boost::numeric::ublas::vector<double> mu(N);
    mu(0) = 1.5;
    mu(1) = 2.5;

    boost::numeric::ublas::matrix<double> sigma(N, N);
    sigma(0, 0) = 0.81;   sigma(1, 0) = -0.576;
    sigma(0, 1) = -0.576;   sigma(1, 1) = 0.64;

    const auto& gen
        = mc::CorrelationNormalGenerator<N>::makeUnique(mu, sigma);
    std::ofstream ofs("c:/temp/rnd.data");
    for (std::size_t i = 0; i < 10000; ++i) {
        const std::array<double, N>& nums = (*gen)();
        ofs
            << nums[0] << ", "
            << nums[1] << std::endl;
    }
    ofs.close();
}

void BrawnianBridgeBuilderTest()
{
    //mc::BrownianBridgeBuilder builder(
    //    std::make_pair(0.0, 4.0),
    //    std::make_pair(10.0, 4.0),
    //    std::normal_distribution<double>(),
    //    std::mt19937(1));
    //builder.iterate(5);
    //for (std::size_t i = 0; i < builder.size(); ++i) {
    //    std::cout
    //        << builder.getTimeGrid()[i]
    //        << ","
    //        << builder.getValues()[i]
    //        << std::endl;
    //}
}

void BrownianMotionTest()
{
    std::vector<double> timeGrid(12 * 40);
    std::iota(timeGrid.begin(), timeGrid.end(), 0.0);

    const std::size_t simnum = 100;
    std::vector<std::shared_ptr<const mc::IStochasticProcess>> bms;
    for (std::size_t i = 0; i < simnum; ++i) {
        std::shared_ptr<const mc::IStochasticProcess> brownianMotion
            = mc::BrownianMotion::buildByBrownianBridge(timeGrid, 10.0, 8.0);
        bms.push_back(brownianMotion);
    }
    for (std::size_t i = 0; i < timeGrid.size(); ++i) {
        std::cout << timeGrid[i] << ":";
        for (std::size_t j = 0; j < simnum; ++j) {
            std::cout << bms[j]->getValues()[i] << ",";
        }
        std::cout << std::endl;
    }
}

