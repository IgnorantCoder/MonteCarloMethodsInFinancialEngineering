#pragma once

#include <memory>

#include "GeneratingRandomNumbers/Macro.h"

namespace mc {
    class RNDGEN_API INormalRandomGenerator {
    public:
        virtual ~INormalRandomGenerator();

    public:
        double operator()() const;
        std::unique_ptr<INormalRandomGenerator> cloneUnique() const;
        std::shared_ptr<INormalRandomGenerator> cloneShared() const;

    private:
        virtual double callImpl() const = 0;
        virtual std::unique_ptr<INormalRandomGenerator>
            cloneUniqueImpl() const = 0;
        virtual std::shared_ptr<INormalRandomGenerator>
            cloneSharedImpl() const = 0;
    };
}