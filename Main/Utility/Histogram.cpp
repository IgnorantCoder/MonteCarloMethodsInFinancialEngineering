#include "Utility/Histogram.h"

#include <algorithm>
#include <cassert>
#include <numeric>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <string>

#include "GeneratingRandomNumbers/RandomGenerator.h"

namespace util {
    Histogram::Histogram(
        std::size_t numOfMaxCount,
        std::size_t numOfInterval,
        const std::string& element)
        : _numOfMaxCount(numOfMaxCount),
        _numOfInterval(numOfInterval),
        _element(element)
    {
    }

    void Histogram::print(
        mc::RandomGenerator & generator,
        std::size_t numOfSim) const
    {
        const auto& sotedRnd
            = this->generate(generator, numOfSim);
        const auto& intervals
            = this->makeInterval(sotedRnd);
        const auto& accumulateCounts
            = this->makeAccumulateCounts(intervals, sotedRnd);
        const auto& counts
            = this->makeCounts(accumulateCounts);
        this->printImpl(intervals, this->normalizeCounts(counts));

        return;
    }

    void Histogram::printImpl(
        const std::vector<std::pair<double, double>>& intervals,
        const std::vector<std::size_t>& counts) const
    {
        assert(intervals.size() == counts.size());
        for (decltype(intervals.size()) i = 0; i < intervals.size(); ++i) {
            this->printImpl(2, intervals[i]);
            this->printImpl( counts[i]);
            std::cout << std::endl;
        }
    }

    void Histogram::printImpl(std::size_t count) const
    {
        for (decltype(count) i = 0; i < count; ++i) {
            std::cout << this->_element;
        }
    }

    void Histogram::printImpl(
        std::size_t precision,
        const std::pair<double, double>& interval) const
    {
        std::cout << "[";
        std::cout << std::fixed << std::setprecision(precision) << interval.first;
        std::cout << ", ";
        std::cout << std::fixed << std::setprecision(precision) << interval.second;
        std::cout << "]";
    }

    std::vector<double> Histogram::generate(
        mc::RandomGenerator & generator,
        std::size_t numOfSim) const
    {
        std::vector<double> rnd;
        rnd.reserve(numOfSim);

        for (decltype(numOfSim) i = 0; i < numOfSim; ++i) {
            rnd.emplace_back(generator());
        }

        std::sort(rnd.begin(), rnd.end());

        return rnd;
    }

    std::vector<std::pair<double, double>>
    Histogram::makeInterval(const std::vector<double>& sorted) const
    {
        const auto& width
            = (sorted.back() - sorted.front()) / this->_numOfInterval;
        std::vector<std::pair<double, double>> ret;
        ret.reserve(_numOfInterval);

        for (decltype(this->_numOfInterval) i = 0; i < _numOfInterval; ++i) {
            ret.emplace_back(
                sorted.front() + i * width,
                sorted.front() + (i + 1) * width);
        }

        return ret;
    }

    std::vector<std::size_t> Histogram::makeAccumulateCounts(
        const std::vector<std::pair<double, double>>& intervals,
        const std::vector<double>& sorted) const
    {
        std::vector<std::size_t> ret;
        ret.reserve(intervals.size());

        for (auto&& interval : intervals) {
            const auto it
                = std::upper_bound(
                    sorted.cbegin(),
                    sorted.cend(),
                    interval.second);
            const auto num
                = std::distance(sorted.cbegin(), it);
            ret.push_back(num);
        }

        return ret;
    }

    std::vector<std::size_t> Histogram::makeCounts(
        const std::vector<std::size_t>& accumulateCounts) const
    {
        std::vector<std::size_t> ret;
        ret.reserve(accumulateCounts.size());
        std::adjacent_difference(
            accumulateCounts.cbegin(),
            accumulateCounts.cend(),
            std::back_inserter(ret));

        return ret;
    }
    
    std::vector<std::size_t> Histogram::normalizeCounts(
        const std::vector<std::size_t>& counts) const
    {
        const auto maxElement
            = *std::max_element(counts.cbegin(), counts.cend());
        const auto coefficient
            = static_cast<double>(this->_numOfMaxCount)
            / static_cast<double>(maxElement);

        std::vector<std::size_t> ret;
        ret.reserve(counts.size());

        std::transform(
            counts.cbegin(),
            counts.cend(),
            std::back_inserter(ret),
            [&coefficient](auto count) { return coefficient * count; });

        return ret;
    }
}