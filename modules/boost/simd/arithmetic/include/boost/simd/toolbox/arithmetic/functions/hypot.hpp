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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_HYPOT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_HYPOT_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_hypot hypot
 *
 * \par Description
 * computes $(a_0^2 + a_1^2)^{1/2}$
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/hypot.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::hypot_(A0,A0)>::type
 *     hypot(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of hypot
 * \param a1 the second parameter of hypot
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
     * \brief Define the tag hypot_ of functor hypot
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct hypot_ : ext::elementwise_<hypot_> { typedef ext::elementwise_<hypot_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::hypot_, hypot, 2)
} }

#endif

// modified by jt the 25/12/2010
