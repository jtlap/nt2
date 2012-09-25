//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_MTIMES_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_MTIMES_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_mtimes mtimes
 *
 * \par Description
 * Matrix product
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/mtimes.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \param a0 a matrix, vector or scalar
 *
 * \param a1 a matrix, vector or scalar
 *
 * \par Notes
 *   Call the dedicated BLAS/LAPACK routines available on the target (DOT, GEMV, GEMM)
 * \par
 *
**/
//==============================================================================
// mtimes actual class forward declaration
//==============================================================================

namespace nt2
{
  namespace tag
  {
    /*!
     * \brief Define the tag mtimes_ of functor mtimes
     *        in namespace nt2::tag for toolbox algebra
     **/
    struct mtimes_ : ext::unspecified_<mtimes_>
    {
      typedef ext::unspecified_<mtimes_> parent;
    };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mtimes_, mtimes, 2)
}

#endif

