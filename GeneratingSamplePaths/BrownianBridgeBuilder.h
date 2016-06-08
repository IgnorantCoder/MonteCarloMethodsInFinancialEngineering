#pragma once

#include <cmath>
#include <utility>
#include <vector>
#include <random>

#include "GeneratingSamplePaths/Macro.h"

namespace mc {
    class SAMPLEPATHS_API BrownianBridgeBuilder {
    public:
        BrownianBridgeBuilder(
            const std::pair<double, double>& leftEnd,
            const std::pair<double, double>& rightEnd,
            const std::normal_distribution<double>& dist,
            const std::mt19937& mt);

    public:
        void iterate();
        void iterate(std::size_t n);
        std::size_t size() const;
        const std::vector<double>& getTimeGrid() const;
        const std::vector<double>& getValues() const;

    private:
        std::pair<double, double>
        generate(
            const std::pair<double, double>& leftEnd,
            const std::pair<double, double>& rightEnd);

        void merge(
            const std::vector<double>& newGrid,
            const std::vector<double>& newTimeValues);

    private:
        std::vector<double> _timeGrid;
        std::vector<double> _values;
        mutable std::normal_distribution<double> _dist;
        mutable std::mt19937 _mt;
    };
}