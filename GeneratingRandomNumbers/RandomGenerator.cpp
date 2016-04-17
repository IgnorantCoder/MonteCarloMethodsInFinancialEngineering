#include "GeneratingRandomNumbers/RandomGenerator.h"

namespace mc {
    double RandomGenerator::operator()() const
    {
        return _holder->call();
    }
}