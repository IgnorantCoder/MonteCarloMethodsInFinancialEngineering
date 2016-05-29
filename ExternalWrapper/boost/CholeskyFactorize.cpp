#include "ExternalWrapper/boost/CholeskyFactorize.h"

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/symmetric.hpp>

#define BOOST_NUMERIC_BINDINGS_USE_CLAPACK
#include <boost/numeric/bindings/lapack/posv.hpp>
#include <boost/numeric/bindings/traits/ublas_matrix.hpp>
#undef  BOOST_NUMERIC_BINDINGS_USE_CLAPACK


namespace external {
    CholeskyFactorizeResult::CholeskyFactorizeResult(
        boost::numeric::ublas::triangular_matrix<double>&& triangularMatrix)
        : _lowerTriangularMatrix(),
        _upperTriangularMatrix()
    {
        _lowerTriangularMatrix
            = std::make_unique<const lower_triangle_matrix_type>(
                std::move(triangularMatrix));
        _upperTriangularMatrix
            = std::make_unique<const upper_triangle_matrix_type>(
                boost::numeric::ublas::trans(*this->_lowerTriangularMatrix));
    }

    auto CholeskyFactorizeResult::getLowerTriangularMatrixImpl() const
        -> const lower_triangle_matrix_type&
    {
        return *this->_lowerTriangularMatrix;
    }

    auto CholeskyFactorizeResult::getUpperTriangularMatrixImpl() const
        -> const upper_triangle_matrix_type&
    {
        return *this->_upperTriangularMatrix;
    }

    std::unique_ptr<const ICholeskyFactorizeResult>
    choleskyFactorization(
        const boost::numeric::ublas::symmetric_matrix<double>& matrix)
    {
        boost::numeric::ublas::matrix<
            double,
            boost::numeric::ublas::column_major> columnMajorMatrix(
                matrix.size1(),
                matrix.size2());
        columnMajorMatrix.assign(matrix);

        const auto info
            = boost::numeric::bindings::lapack::potrf('L', columnMajorMatrix);
        
        boost::numeric::ublas::triangular_matrix<double>&& tmp
            = boost::numeric::ublas::triangular_adaptor<
                boost::numeric::ublas::matrix<
                double,
                boost::numeric::ublas::column_major>>(columnMajorMatrix);
        auto&& result
            = std::make_unique<const CholeskyFactorizeResult>(std::move(tmp));

        return std::move(result);
    }
}