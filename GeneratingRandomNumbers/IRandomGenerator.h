#pragma once

#include <memory>

namespace mc {
    class IRandomGenerator {
    public:
        virtual ~IRandomGenerator();

    public:
        double operator()() const;
        std::unique_ptr<IRandomGenerator> cloneUnique() const;
        std::shared_ptr<IRandomGenerator> cloneShared() const;

    private:
        virtual double callImpl() const = 0;
        virtual std::unique_ptr<IRandomGenerator> cloneUniqueImpl() const = 0;
        virtual std::shared_ptr<IRandomGenerator> cloneSharedImpl() const = 0;
    };
}