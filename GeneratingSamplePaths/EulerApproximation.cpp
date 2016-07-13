#include "GeneratingSamplePaths/EulerApproximation.h"

#include <algorithm>
#include <numeric>
#include <random>
#include <vector>
#include <iterator>
#include <functional>

#include "GeneratingSamplePaths/IDriftCoefficient.h"
#include "GeneratingSamplePaths/IDiffusionCoefficient.h"

namespace {
    std::vector<double> calculateDriftTerm(
        const std::vector<double>& delta,
        const std::vector<double>& mu)
    {
        std::vector<double>&& ret = {};
        ret.reserve(delta.size());

        std::transform(
            delta.cbegin(),
            delta.cend(),
            mu.cbegin(),
            std::back_inserter(ret),
            std::multiplies<double>());

        return std::move(ret);
    }

    std::vector<double> calculateDiffusionTerm(
        const std::vector<double>& delta,
        const std::vector<double>& sigma,
        const std::vector<double>& rnd)
    {
        std::vector<double>&& coeff = {};
        coeff.reserve(delta.size());
        std::transform(
            sigma.cbegin(),
            sigma.cend(),
            delta.cbegin(),
            std::back_inserter(coeff),
            [](double s, double d) {return s * std::sqrt(d);});

        std::vector<double>&& ret = {};
        ret.reserve(delta.size());
        std::transform(
            coeff.cbegin(),
            coeff.cend(),
            rnd.cbegin(),
            std::back_inserter(ret),
            std::multiplies<double>());

        return std::move(ret);
    }

    std::vector<double> calculateIndependentIncrement(
        const std::vector<double>& driftTerm,
        const std::vector<double>& diffusionTerm)
    {
        std::vector<double>&& ret = {};
        ret.reserve(driftTerm.size());

        std::transform(
            driftTerm.cbegin(),
            driftTerm.cend(),
            diffusionTerm.cbegin(),
            std::back_inserter(ret),
            std::multiplies<double>());

        return std::move(ret);
    }
}

namespace mc {
    std::vector<double>
    EulerApproximation::generatedBy(const std::vector<double>& timeGrid) const
    {
        const std::vector<double>& rnd
            = this->generateRandom(timeGrid.size() - 1);
        const std::vector<double>& delta
            = this->calculateTimeDiff(timeGrid);
        const std::vector<double>& mu
            = this->calculateMu(timeGrid);
        const std::vector<double>& sigma
            = this->calculateSigma(timeGrid);

        const std::vector<double>& drift
            = calculateDriftTerm(delta, mu);
        const std::vector<double>& diffusion
            = calculateDiffusionTerm(delta, sigma, rnd);

        const std::vector<double>& independetIncrement
            = calculateIndependentIncrement(drift, diffusion);

        double x = 0;
        std::vector<double>&& ret = {x};
        ret.reserve(timeGrid.size());

        for (auto&& inc : independetIncrement) {
            x += inc;
            ret.emplace_back(x);
        }

        return std::move(ret);
    }

    std::vector<double> EulerApproximation::generateRandom(std::size_t size) const
    {
        std::normal_distribution<double> normal;
        constexpr int seed = 1;
        std::mt19937 mt(seed);

        auto&& gen = [&normal, &mt]() {
            return normal(mt);
        };

        std::vector<double> ret(size);
        std::generate(ret.begin(), ret.end(), gen);

        return ret;
    }

    std::vector<double> EulerApproximation::calculateTimeDiff(
        const std::vector<double>& timeGrid) const
    {
        std::vector<double>&& delta = {};
        delta.reserve(timeGrid.size() - 1);
        std::adjacent_difference(
            timeGrid.cbegin(),
            timeGrid.cend(),
            std::back_inserter(delta));

        return std::move(delta);
    }

    std::vector<double> EulerApproximation::calculateMu(
        const std::vector<double>& timeGrid) const
    {
        std::vector<double>&& mu = {};
        mu.reserve(timeGrid.size() - 1);
        std::transform(
            timeGrid.cbegin(),
            std::prev(timeGrid.cend()),
            std::back_inserter(mu),
            [this](double t) {return (*this->_drift)(t);});

        return std::move(mu);
    }

    std::vector<double> EulerApproximation::calculateSigma(
        const std::vector<double>& timeGrid) const
    {
        std::vector<double>&& sigma = {};
        sigma.reserve(timeGrid.size() - 1);
        std::transform(
            timeGrid.cbegin(),
            std::prev(timeGrid.cend()),
            std::back_inserter(sigma),
            [this](double t) {return (*this->_diffusion)(t);});

        return std::move(sigma);
    }
}

#ifndef INLINE_EXPANTION
#define INLINE
#include "GeneratingSamplePaths/EulerApproximation.ipp"
#endif