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
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_EXPONENTBITS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_EXPONENTBITS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_ieee
 * \defgroup boost_simd_ieee_exponentbits exponentbits
 *
 * \par Description
 * Returns the exponent bits of the floating input as an integer value.
 * the other bits (sign and mantissa) are just masked.
 * \par
 * The sign \f$ \pm \f$, exponent e and mantissa m of a floating point entry a are related by
 * \f$a = \pm m\times 2^e\f$, with m between zero and one
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/exponentbits.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::exponentbits_(A0)>::type
 *     exponentbits(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of exponentbits
 *
 * \return an integer value
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag exponentbits_ of functor exponentbits
     *        in namespace boost::simd::tag for toolbox boost.simd.ieee
    **/
    struct exponentbits_ : ext::elementwise_<exponentbits_> { typedef ext::elementwise_<exponentbits_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::exponentbits_, exponentbits, 1)
} }

#endif

// modified by jt the 25/12/2010
