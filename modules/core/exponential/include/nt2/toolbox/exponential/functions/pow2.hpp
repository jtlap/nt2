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
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_POW2_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_POW2_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup exponential
 * \defgroup exponential_pow2 pow2
 *
 * \par Description
 *   base 2 power and scale floating point number.
 *   x = pow2(y) for each element of y is 2 raised to the power y.
 *
 *   x = pow2(f,e) x = f*(2^itrunc(e)).  the result is computed
 *   quickly by simply adding the integer part of e to the floating point exponent of f.
 *   this corresponds to ldexp(f, e)
 *
 *   this function is provided for Matlab compatibility
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/pow2.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0, class A1>
 *     meta::call<tag::pow2_(A0, A1)>::type
 *     pow2(const A0 & a0, const A1 & a1);
 * }
 * \endcode
 *
 *  
**/

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag pow2_ of functor pow2 
     *        in namespace nt2::tag for toolbox exponential
    **/
    struct pow2_ : ext::elementwise_<pow2_> { typedef ext::elementwise_<pow2_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::pow2_, pow2, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::pow2_, pow2, 2)
}

#endif
