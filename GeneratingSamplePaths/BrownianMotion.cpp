#include "GeneratingSamplePaths/BrownianMotion.h"

#include <algorithm>
#include <numeric>
#include <iterator>
#include <set>
#include <xutility>
#include <random>
#include <functional>

namespace {
    std::size_t half(std::size_t n)
    {
        return n >> 1;
    }

    auto makeCalculator(
        const std::vector<double>& timeGrid,
        const std::vector<double>& values,
        const std::function<double()>& normal)
        -> std::function<double(std::size_t, std::size_t l, std::size_t u)>
    {
        return [&timeGrid, &values, &normal](
            std::size_t i, std::size_t l, std::size_t u)
            {
                const double t = timeGrid[i];
                const double tl = timeGrid[l];
                const double tu = timeGrid[u];
                const double vl = values[l];
                const double vu = values[u];

                const double mu = ((tu - t) * vl + (t - tl) * vu) / (tu - tl);
                const double sigma = std::sqrt((t - tl) * (tu - t) / (tu - tl));

                return mu + sigma * normal();
            };
    }

    std::set<std::size_t> targetset(const std::set<std::size_t>& marked)
    {
        std::set<std::size_t> candidate;
        std::transform(
            marked.cbegin(),
            std::prev(marked.cend()),
            std::next(marked.cbegin()),
            std::inserter(candidate, candidate.begin()),
            [](std::size_t l, std::size_t u) {return half(l + u);});
        std::set<std::size_t> target;
        std::set_difference(
            candidate.cbegin(),
            candidate.cend(),
            marked.cbegin(),
            marked.cend(),
            std::inserter(target, target.begin()));

        return target;
    }

    void buildByBrownianBridge(
        std::vector<double>& values,
        const std::vector<double>& timeGrid,
        const std::function<double()>& normal,
        std::set<std::size_t>& marked)
    {
        const std::set<std::size_t> target = targetset(marked);
        if (target.empty()) {
            return;
        }

        const auto calculator
            = makeCalculator(timeGrid, values, normal);
        const auto filler
            = [&values, &calculator, &marked](std::size_t i) {
            const std::size_t l = *std::prev(marked.lower_bound(i));
            const std::size_t u = *marked.lower_bound(i);
                values[i] = calculator(i, l, u);
                return i;
            };
        std::transform(
            target.cbegin(),
            target.cend(),
            std::inserter(marked, marked.begin()),
            filler);

        return buildByBrownianBridge(values, timeGrid, normal, marked);
    }
}

namespace mc {
    std::shared_ptr<const IStochasticProcess>
    BrownianMotion::buildByBrownianBridge(
        const std::vector<double>& timeGrid,
        double startValue,
        double endValue)
    {
        std::vector<double> values(timeGrid.size());
        values.front() = startValue;
        values.back() = endValue;

        std::set<std::size_t> marked = { 0, values.size() - 1 };

        std::random_device rnd;
        std::mt19937 engine(rnd());
        std::normal_distribution<double> dist(0.0, 1.0);

        ::buildByBrownianBridge(
                values, 
                timeGrid,
                [&engine, &dist]() {return dist(engine);},
                marked);

        return std::make_shared<const BrownianMotion>(timeGrid, values);
    }
}

#ifndef INLINE_EXPANTION
#define INLINE
#include "GeneratingSamplePaths/BrownianMotion.ipp"
#endif
