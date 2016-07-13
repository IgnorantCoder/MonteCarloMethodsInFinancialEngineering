namespace mc {
    INLINE const std::vector<double>& IStochasticProcess::getTimeGrid() const
	{
		return this->getTimeGridImpl();
	}

    INLINE const std::vector<double>& IStochasticProcess::getValues() const
	{
		return this->getValuesImpl();
	}

    INLINE const std::size_t IStochasticProcess::size() const
	{
		return this->sizeImpl();
	}
}