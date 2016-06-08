#pragma once

#include <cassert>
#include <memory>
#include <random>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

#include "ExternalWrapper/boost/CholeskyFactorize.h"
#include "ExternalWrapper/ICholeskyFactorizeResult.h"
#include "GeneratingRandomNumbers/IMultiDimensionalNormalGenerator.h"

namespace mc {
    template <std::size_t N>
    class CorrelationNormalGenerator
        : public IMultiDimensionalNormalGenerator<N> {
    public:
        static std::unique_ptr<IMultiDimensionalNormalGenerator<N>> makeUnique(
            const boost::numeric::ublas::matrix<double>& sigma,
            int seed = 1);
        static std::unique_ptr<IMultiDimensionalNormalGenerator<N>> makeUnique(
            const boost::numeric::ublas::vector<double>& mu,
            const boost::numeric::ublas::matrix<double>& sigma,
            int seed = 1);

    private:
        CorrelationNormalGenerator(
            const boost::numeric::ublas::vector<double>& mu,
            const boost::numeric::ublas::matrix<double>& a,
            const std::normal_distribution<double>& dist,
            const std::mt19937& mt);

    private:
        virtual std::array<double, N> callImpl() const override;
        virtual std::unique_ptr<IMultiDimensionalNormalGenerator>
            cloneUniqueImpl() const override;
        virtual std::shared_ptr<IMultiDimensionalNormalGenerator>
            cloneSharedImpl() const override;

    private:
        boost::numeric::ublas::vector<double> _mu;
        boost::numeric::ublas::matrix<double> _a;
        mutable std::normal_distribution<double> _dist;
        mutable std::mt19937 _mt;
    };

    template<std::size_t N>
    inline std::unique_ptr<IMultiDimensionalNormalGenerator<N>>
    CorrelationNormalGenerator<N>::makeUnique(
        const boost::numeric::ublas::matrix<double>& sigma,
        int seed)
    {
        const boost::numeric::ublas::zero_vector<double> zero(N);
        return CorrelationNormalGenerator<N>::makeUnique(
            zero,
            sigma,
            seed);
    }

    template<std::size_t N>
    inline std::unique_ptr<IMultiDimensionalNormalGenerator<N>>
    CorrelationNormalGenerator<N>::makeUnique(
        const boost::numeric::ublas::vector<double>& mu,
        const boost::numeric::ublas::matrix<double>& sigma,
        int seed)
    {
        struct Impl : public CorrelationNormalGenerator {
            Impl(
                const boost::numeric::ublas::vector<double>& mu,
                const boost::numeric::ublas::matrix<double>& a,
                const std::normal_distribution<double>& dist,
                const std::mt19937& mt)
                : CorrelationNormalGenerator(mu, a, dist, mt)
            {}
        };

        return std::make_unique<Impl>(
            mu,
            external::choleskyFactorization(sigma)->getLowerTriangularMatrix(),
            std::normal_distribution<double>(0.0, 1.0),
            std::mt19937(seed));
    }

    template<std::size_t N>
    inline CorrelationNormalGenerator<N>::CorrelationNormalGenerator(
        const boost::numeric::ublas::vector<double>& mu,
        const boost::numeric::ublas::matrix<double>& a,
        const std::normal_distribution<double>& dist,
        const std::mt19937& mt)
        : _mu(mu), _a(a), _dist(dist), _mt(mt)
    {
        assert(N == a.size1());
        assert(N == a.size2());
        assert(N == mu.size());
    }

    template<std::size_t N>
    inline std::array<double, N>
    CorrelationNormalGenerator<N>::callImpl() const
    {
        boost::numeric::ublas::vector<double> z(N);
        for (std::size_t i = 0; i < N; ++i) {
            z(i) = this->_dist(this->_mt);
        }

        const auto& az
            = boost::numeric::ublas::prod(_a, z);
        const auto& x
            = _mu + az;

        std::array<double, N>&& ret = {};
        std::copy(x.cbegin(), x.cend(), ret.begin());

        return std::move(ret);
    }

    template<std::size_t N>
    inline std::unique_ptr<IMultiDimensionalNormalGenerator<N>>
    CorrelationNormalGenerator<N>::cloneUniqueImpl() const
    {
        struct Impl : public CorrelationNormalGenerator {
            Impl(
                const boost::numeric::ublas::vector<double>& mu,
                const boost::numeric::ublas::matrix<double>& a,
                const std::normal_distribution<double>& dist,
                const std::mt19937& mt)
                : CorrelationNormalGenerator(mu, a, dist, mt)
            {}
        };

        return std::make_unique<Impl>(
            this->_mu,
            this->_a,
            this->_dist,
            this->_mt);
    }

    template<std::size_t N>
    inline std::shared_ptr<IMultiDimensionalNormalGenerator<N>>
    CorrelationNormalGenerator<N>::cloneSharedImpl() const
    {
        struct Impl : public CorrelationNormalGenerator {
            Impl(
                const boost::numeric::ublas::vector<double>& mu,
                const boost::numeric::ublas::matrix<double>& a,
                const std::normal_distribution<double>& dist,
                const std::mt19937& mt)
                : CorrelationNormalGenerator(mu, a, dist, mt)
            {}
        };

        return std::make_shared<Impl>(
            this->_mu,
            this->_a,
            this->_dist,
            this->_mt);
    }
}