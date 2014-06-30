//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_DET_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_DET_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_det det
 *
 * \par Description
 * matrix determinant
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/det.hpp>
 * \endcode
 *
 *
 * \param a the matrix a,  a must be square
 *
 *
 *
**/
//==============================================================================
// trace actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag trace_ of functor trace
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct det_ :  tag::formal_ { typedef tag::formal_ parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::det_, det, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL( tag::det_, det
                                            , (A0 const&)(A1&), 2
                                            )
}

#endif
