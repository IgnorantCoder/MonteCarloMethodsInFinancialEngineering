namespace mc {
    INLINE BrownianMotion::BrownianMotion(
        const std::vector<double>& timeGrid,
        const std::vector<double>& values)
        : _timeGrid(timeGrid),
        _values(values)
    {
    }

    INLINE const std::vector<double>& BrownianMotion::getTimeGridImpl() const
    {
        return _timeGrid;
    }

    INLINE const std::vector<double>& BrownianMotion::getValuesImpl() const
    {
        return _values;
    }
    INLINE const std::size_t BrownianMotion::sizeImpl() const
    {
        return _timeGrid.size();
    }
}
