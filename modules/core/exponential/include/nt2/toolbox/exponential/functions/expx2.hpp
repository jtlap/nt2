//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_EXPX2_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_EXPX2_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup exponential
 * \defgroup exponential_expx2 expx2
 *
 * \par Description
 * exponential of square function: $e^{a_0^2}$
 * \par
 * provisions are made for otaining correct results for large a0
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/expx2.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::expx2_(A0)>::type
 *     expx2(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of expx2
 *
 * \return a value of the same type as the parameter
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag expx2_ of functor expx2
     *        in namespace nt2::tag for toolbox exponential
    **/
    struct expx2_ : ext::elementwise_<expx2_> { typedef ext::elementwise_<expx2_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::expx2_, expx2, 1)
}

#endif

// modified by jt the 25/12/2010
