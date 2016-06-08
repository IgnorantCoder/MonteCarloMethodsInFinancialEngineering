#include "GeneratingSamplePaths/BrownianBridgeBuilder.h"

namespace {
    bool isOdd(std::size_t n)
    {
        return n & 0x1;
    }

    bool isEven(std::size_t n)
    {
        return !isOdd(n);
    }

    std::size_t half(std::size_t n)
    {
        return n >> 1;
    }
}

namespace mc {
    BrownianBridgeBuilder::BrownianBridgeBuilder(
        const std::pair<double, double>& leftEnd,
        const std::pair<double, double>& rightEnd,
        const std::normal_distribution<double>& dist, 
        const std::mt19937& mt)
        : _timeGrid(2),
        _values(2),
        _dist(dist),
        _mt(mt)
    {
        _timeGrid.front() = leftEnd.first;
        _timeGrid.back() = rightEnd.first;
        _values.front() = leftEnd.second;
        _values.back() = rightEnd.second;

    }

    void BrownianBridgeBuilder::iterate()
    {
        std::vector<double> newTimeGrid;
        newTimeGrid.reserve(_timeGrid.size() - 1);

        std::vector<double> newValues;
        newValues.reserve(_values.size() - 1);

        for (std::size_t i = 0; i < _timeGrid.size() - 1; ++i) {
            const auto& newPoint
                = this->generate(
                    std::make_pair(_timeGrid[i], _values[i]),
                    std::make_pair(_timeGrid[i + 1], _values[i + 1]));
            newTimeGrid.emplace_back(newPoint.first);
            newValues.emplace_back(newPoint.second);
        }

        this->merge(newTimeGrid, newValues);
        return;
    }

    void BrownianBridgeBuilder::iterate(std::size_t n)
    {
        if (n == 0) {
            return;
        }
        this->iterate();
        return this->iterate(n - 1);
    }

    std::size_t BrownianBridgeBuilder::size() const
    {
        return _timeGrid.size();
    }

    const std::vector<double>& BrownianBridgeBuilder::getTimeGrid() const
    {
        return this->_timeGrid;
    }

    const std::vector<double>& BrownianBridgeBuilder::getValues() const
    {
        return this->_values;
    }

    std::pair<double, double> BrownianBridgeBuilder::generate(
        const std::pair<double, double>& leftEnd,
        const std::pair<double, double>& rightEnd)
    {
        const double x
            = 0.5 * (leftEnd.first + rightEnd.first);
        const double a
            = ((rightEnd.first - x) * leftEnd.second
                + (x - leftEnd.first) * rightEnd.second)
            / (rightEnd.first - leftEnd.first);
        const double b
            = std::sqrt(
            (x - leftEnd.first)
                * (rightEnd.first - x)
                / (rightEnd.first - leftEnd.first));
        return std::make_pair(x, a + b * _dist(_mt));
    }

    void BrownianBridgeBuilder::merge(
        const std::vector<double>& newTimeGrid,
        const std::vector<double>& newValues)
    {
        std::vector<double> timeGrid(_timeGrid.size() + newTimeGrid.size());
        std::vector<double> values(_values.size() + newValues.size());

        for (std::size_t i = 0; i < timeGrid.size() ; ++i) {
            if (isEven(i)) {
                timeGrid[i] = _timeGrid[half(i)];
                values[i] = _values[half(i)];
            }

            if (isOdd(i)) {
                timeGrid[i] = newTimeGrid[half(i)];
                values[i] = newValues[half(i)];
            }
            
        }

        _timeGrid = timeGrid;
        _values = values;
    }
}
