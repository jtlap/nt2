//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_HYPOT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_HYPOT_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
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
      @brief  hypot generic tag

      Represents the hypot function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct hypot_ : ext::elementwise_<hypot_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<hypot_> parent;
    };
  }
  /*!
    Computes  computes $(a_0^2 + a_1^2)^{1/2}$

    @par semantic:
    For any given value @c x,  @c y of type @c T:

    @code
    as_floating<T> r = hypot(x, y);
    @endcode

    For floating point values the code is equivalent to:

    @code
    as_floating<T> r = sqrt(sqr(x)+sqr(y));
    @endcode

    Provision are made to avoid overflow and to compute
    @c hypot accurately.
    If these considerations can be put aside use
    @c fast_hypot.

    @param  a0
    @param  a1

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::hypot_, hypot, 2)
} }

#endif


