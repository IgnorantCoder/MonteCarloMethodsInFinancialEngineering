#pragma once

#include <memory>

namespace mc {
    class ICumulativeDistributionFunction;

    class IInverseOfCdf {
    public:
        virtual ~IInverseOfCdf();

    public:
        double operator()(double u) const;
        std::unique_ptr<const IInverseOfCdf> cloneUnique() const;
        std::shared_ptr<const IInverseOfCdf> cloneShared() const;
        const ICumulativeDistributionFunction& original() const;

    private:
        virtual double callImpl(double u) const = 0;
        virtual std::unique_ptr<const IInverseOfCdf> cloneUniqueImpl() const = 0;
        virtual std::shared_ptr<const IInverseOfCdf> cloneSharedImpl() const = 0;
        virtual const ICumulativeDistributionFunction& originalImpl() const = 0;
    };
}