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
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_CAUINV_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_CAUINV_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup statistics
 * \defgroup statistics_cau cauinv
 *
 * \par Description
 * cauchy inverse of cumulative distribution
 *
 * All inv (inverse cumulative distribution functions  can be called with the syntax
 * r = xxxinv(values, param_1, ...,  param_n)
 * the type of values elements determines the type of the output expression elements.
 * values outside of [0 1] return Nan
 * cauchy has 2 parameters: median and scale
 * defaults are 0 and 1 respectively
 * \par
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/cauinv.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::cauinv_(A0)>::type
 *     cauinv(const A0 & a0, const A1 & median = 0, const A2 & scale = 1);
 * }
 * \endcode
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag cauinv_ of functor cauinv
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct cauinv_ : ext::elementwise_<cauinv_> { typedef ext::elementwise_<cauinv_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::cauinv_, cauinv, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::cauinv_, cauinv, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::cauinv_, cauinv, 3)
}

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of cauinv.hpp
// /////////////////////////////////////////////////////////////////////////////
