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
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_CUMTRAPZ_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_CUMTRAPZ_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/simd/toolbox/operator/functions/multiplies.hpp>
#include <boost/simd/toolbox/constant/constants/one.hpp>


/*!
 * \ingroup boost_simd_swar
 * \defgroup boost_simd_swar_cumtrapz cumtrapz
 *
 * \par Description
 * compute the cumulate trapz of the vector elements using the abscissae differences
 * is they are given
 *  z = cumtrapz(y) computes an approximation of the cumulative
 *  integral of y via the trapezoidal method (with unit spacing).  to
 *  compute the integral for spacing different from one, multiply z by
 *  the spacing incrementor use cumtrapz(dx, y) where dx is the abscisae
 *  constant and SCALAR increment.
 *
 *  for vectors, cumtrapz(y) is a vector containing the cumulative
 *  integral of y. for matrices, cumtrapz(y) is a matrix the same size as
 *  x with the cumulative integral over each column. for n-d arrays,
 *  cumtrapz(y) works along the first non-singleton dimension.
 *
 *  z = cumtrapz(x,y) computes the cumulative integral of y with respect
 *  to x using trapezoidal integration.  x and y must be vectors of the
 *  same length, or x must be a column vector and y an array whose first
 *  non-singleton dimension is length(x).  cumtrapz operates across this
 *  dimension.
 *  if x is scalar the increment is considered constant and of value x.
 *  (A 1x1 matrix expression is not a scalar)
 *
 *  z = cumtrapz(x,y,dim) or cumtrapz(y,dim) integrates along dimension
 *  dim of y. the length of x must be the same as size(y,dim)).
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/cumtrapz.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::cumtrapz_(A0)>::type
 *     cumtrapz(const A0 & x, const A1 & y, const A2 & dim);
 * }
 * \endcode
 *
 *
**/

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag cumtrapz_ of functor cumtrapz
     *        in namespace boost::simd::tag for toolbox boost.simd.swar
    **/
    struct cumtrapz_ : tag::formal_
    {
      typedef tag::formal_ parent;
    };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::cumtrapz_, cumtrapz, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::cumtrapz_, cumtrapz, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::cumtrapz_, cumtrapz, 3)
} }

#endif

// modified by jt the 25/12/2010
