namespace mc {
    INLINE IDriftCoefficient::~IDriftCoefficient()
    {
    }

    INLINE double IDriftCoefficient::operator()(double t) const
    {
        return this->callImpl(t);
    }

    INLINE std::shared_ptr<const IDriftCoefficient> 
    IDriftCoefficient::cloneShared() const
    {
        return this->cloneSharedImpl();
    }
}