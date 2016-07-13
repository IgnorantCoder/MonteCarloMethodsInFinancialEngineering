namespace mc {
    INLINE IDiffusionCoefficient::~IDiffusionCoefficient()
    {
    }

    INLINE double IDiffusionCoefficient::operator()(double t) const
    {
        return this->callImpl(t);
    }

    INLINE std::shared_ptr<const IDiffusionCoefficient>
        IDiffusionCoefficient::cloneShared() const
    {
        return this->cloneSharedImpl();
    }
}