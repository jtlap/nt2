//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TRAPZ_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TRAPZ_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup core
 * \defgroup core trapz
 *
 * \par Description
 * Returns the trapz integral of the elements of the SIMD vector
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/trapz.hpp>
 * trapz  Trapezoidal numerical integration.
 *    z = trapz(y) computes an approximation of the integral of y via
 *    the trapezoidal method (with unit spacing).  to compute the integral
 *    for spacing different from one, multiply z by the spacing increment.
 * 
 *    for vectors, trapz(y) is the integral of y. for matrices, trapz(y)
 *    is a row vector with the integral over each column. for n-d
 *    arrays, trapz(y) works across the first non-singleton dimension.
 * 
 *    z = trapz(x,y) computes the integral of y with respect to x using
 *    the trapezoidal method.  x must be a vector and y must a vector of the same
 *    length as the numel of x or an array whose first
 *    non-singleton dimension has  numel(x) elements.  trapz operates along this
 *    dimension.
 * 
 *    z = trapz(x,y,dim) or trapz(y,dim) integrates across dimension dim
 *    of y. the length of x must be the same as size(y,dim)).
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::trapz_(A0)>::type
 *     trapz(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of trapz
 *
 * \return always a scalar value
 *
 * \par Notes
 * \par
 * This is a reduction operation. As such it has not real interest outside
 * SIMD mode.
 * \par
 * Such an operation always has a scalar result which translate a property
 * of the whole SIMD vector.
 * \par
 * If usable and used in scalar mode, it reduces to the operation as acting
 * on a one element vector.
 *
**/


namespace nt2
{
  namespace tag
  {
    struct trapz_ : boost::dispatch::tag::formal_
    {
       typedef boost::dispatch::tag::formal_ parent;
    };
  }

  //============================================================================
  /*!
   * trapz of a table
   *
   * \param xpr  table
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::trapz_       , trapz, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::trapz_       , trapz, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::trapz_       , trapz, 3)
}


#endif
