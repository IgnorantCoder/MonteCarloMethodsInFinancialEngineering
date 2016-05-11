#pragma once

#include <vector>
#include <xutility>

namespace mc {
    class RandomGenerator;
}

namespace util {
    class Histogram {
    public:
        Histogram(
            std::size_t numOfMaxCount,
            std::size_t numOfInterval,
            const std::string& element);
        void print(
            mc::RandomGenerator& generator,
            std::size_t numOfSim) const;

    private:
        void printImpl(
            const std::vector<std::pair<double, double>>& iinterval,
            const std::vector<std::size_t>& counts) const;
        void printImpl(std::size_t count) const;
        void printImpl(
            std::size_t precision,
            const std::pair<double, double>& interval) const;

        std::vector<double>
        generate(
            mc::RandomGenerator & generator,
            std::size_t numOfSim) const;
        std::vector<std::pair<double, double>>
        makeInterval(const std::vector<double>& sorted) const;
        std::vector<std::size_t>
        makeAccumulateCounts(
            const std::vector<std::pair<double, double>>& intervals,
            const std::vector<double>& sorted) const;
        std::vector<std::size_t>
        makeCounts(
            const std::vector<std::size_t>& accumulateCounts) const;
        std::vector<std::size_t>
        normalizeCounts(
            const std::vector<std::size_t>& counts) const;

    private:
        std::size_t _numOfMaxCount;
        std::size_t _numOfInterval;
        std::string _element;
    };
}