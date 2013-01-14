//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
/*!
 * \file
**/
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_FAST_HYPOT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_FAST_HYPOT_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_fast_hypot fast_hypot
 *
 * \par Description
 * computes $(a_0^2 + a_1^2)^{1/2}$ in a quicker,
 * but sometimes less accurate way than \c hypot
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/fast_hypot.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::fast_hypot_(A0,A0)>::type
 *     fast_hypot(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of fast_hypot
 * \param a1 the second parameter of fast_hypot
 *
 * \return a value of the common type of the parameters
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag fast_hypot_ of functor fast_hypot
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct fast_hypot_ : ext::elementwise_<fast_hypot_> { typedef ext::elementwise_<fast_hypot_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::fast_hypot_, fast_hypot, 2)
} }

#endif

// modified by jt the 25/12/2010
