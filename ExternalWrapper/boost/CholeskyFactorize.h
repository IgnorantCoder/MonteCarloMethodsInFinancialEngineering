#pragma once

#include <memory>

#include <boost/numeric/ublas/fwd.hpp>

#include "ExternalWrapper/Macro.h"
#include "ExternalWrapper/ICholeskyFactorizeResult.h"

namespace external {
    class CholeskyFactorizeResult
         : public ICholeskyFactorizeResult {
    public:
        using lower_triangle_matrix_type
            = boost::numeric::ublas::triangular_matrix<double>;
        using upper_triangle_matrix_type
            = boost::numeric::ublas::triangular_matrix<
                double,
                boost::numeric::ublas::upper>;

    public:
        CholeskyFactorizeResult(
            boost::numeric::ublas::triangular_matrix<double>&& triangularMatrix);

    private:
        virtual const lower_triangle_matrix_type&
        getLowerTriangularMatrixImpl() const override;
        virtual const upper_triangle_matrix_type&
        getUpperTriangularMatrixImpl() const override;

    private:
        std::unique_ptr<const lower_triangle_matrix_type> _lowerTriangularMatrix;
        std::unique_ptr<const upper_triangle_matrix_type> _upperTriangularMatrix;
    };

    EXTERNAL_API std::unique_ptr<const ICholeskyFactorizeResult>
    choleskyFactorization(
        const boost::numeric::ublas::symmetric_matrix<double>& matrix);
}