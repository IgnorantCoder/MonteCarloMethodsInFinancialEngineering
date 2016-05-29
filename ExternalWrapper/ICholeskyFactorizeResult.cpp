#include "ExternalWrapper/ICholeskyFactorizeResult.h"

namespace external {
    const ICholeskyFactorizeResult::lower_triangle_matrix_type&
    ICholeskyFactorizeResult::getLowerTriangularMatrix() const
    {
        return this->getLowerTriangularMatrixImpl();
    }

    const ICholeskyFactorizeResult::upper_triangle_matrix_type&
    ICholeskyFactorizeResult::getUpperTriangularMatrix() const
    {
        return this->getUpperTriangularMatrixImpl();
    }

}

