#pragma once

#include "ExternalWrapper/Macro.h"

#include <boost/numeric/ublas/fwd.hpp>

namespace external {
    class EXTERNAL_API ICholeskyFactorizeResult {
    public:
        using lower_triangle_matrix_type
            = boost::numeric::ublas::triangular_matrix<double>;
        using upper_triangle_matrix_type
            = boost::numeric::ublas::triangular_matrix<
            double,
            boost::numeric::ublas::upper>;

    public:
        const lower_triangle_matrix_type& getLowerTriangularMatrix() const;
        const upper_triangle_matrix_type& getUpperTriangularMatrix() const;

    private:
        virtual const lower_triangle_matrix_type&
        getLowerTriangularMatrixImpl() const = 0;

        virtual const upper_triangle_matrix_type&
        getUpperTriangularMatrixImpl() const = 0;

    };
}