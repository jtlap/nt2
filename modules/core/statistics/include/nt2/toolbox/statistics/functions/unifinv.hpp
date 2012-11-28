/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
/*!
 * \file
**/
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_UNIFINV_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_UNIFINV_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup statistics
 * \defgroup statistics_unif unifinv
 *
 * \par Description
 * uniform inverse cumulative distribution
 *
 * All inv (inverse distribution functions  can be called with the syntax
 * r = xxxinv(values, param_1, ...,  param_n)
 * the type of values elements determines the type of the output expression elements.
 * uniform distribution has 2 parameters that are the finite bounds (a < b) of the
 * underlying distibution interval [a, b].
 * default is a = 0,  b = 1.
 *
 * differences with matlab
 * when any a >= b the nt2 routine assert,  matlab returns Nan
 *
 * \par
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/unifinv.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::unifinv_(A0)>::type
 *     unifinv(const A0 & a0, const A1 & a = 0, const A2 & b = 1);
 * }
 * \endcode
 *
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag unifinv_ of functor unifinv
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct unifinv_ : ext::elementwise_<unifinv_> { typedef ext::elementwise_<unifinv_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::unifinv_, unifinv, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::unifinv_, unifinv, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::unifinv_, unifinv, 3)
}

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of unifinv.hpp
// /////////////////////////////////////////////////////////////////////////////
