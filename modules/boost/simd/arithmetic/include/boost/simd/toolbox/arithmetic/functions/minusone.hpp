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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_MINUSONE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_MINUSONE_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_minusone minusone
 *
 * \par Description
 * return the entry minus one, saturated in the entry type.
 * minusone(a) is always less or equal to a.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/minusone.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::minusone_(A0)>::type
 *     minusone(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of minusone
 *
 * \return a value of the same type as the parameter
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag minusone_ of functor minusone
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct minusone_ : ext::elementwise_<minusone_> { typedef ext::elementwise_<minusone_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::minusone_, minusone, 1)
} }

#endif

// modified by jt the 25/12/2010
