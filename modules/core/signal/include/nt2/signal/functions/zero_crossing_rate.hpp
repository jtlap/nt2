//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SIGNAL_FUNCTIONS_ZERO_CROSSING_RATE_HPP_INCLUDED
#define NT2_SIGNAL_FUNCTIONS_ZERO_CROSSING_RATE_HPP_INCLUDED
#include <nt2/include/functor.hpp>
/*!
 * \ingroup core
 * \defgroup core zero_crossing_rate
 *
 * \par Description
 * Returns the zero_crossing_rate of the elements of the SIMD vector
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/zero_crossing_rate.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0, class A1>
 *     meta::call<tag::zero_crossing_rate_(A0, A1)>::type
 *     zero_crossing_rate(const A0 & a0, const A1& n);
 * }
 * \endcode
 *
**/


namespace nt2
{
  namespace tag
  {
    struct zero_crossing_rate_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  //============================================================================
  /*!
   * rate of sign changes along a signal
   *
   * \param xpr  table
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::zero_crossing_rate_, zero_crossing_rate, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::zero_crossing_rate_, zcr, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::zero_crossing_rate_, zero_crossing_rate, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::zero_crossing_rate_, zcr, 2)
}

#endif
