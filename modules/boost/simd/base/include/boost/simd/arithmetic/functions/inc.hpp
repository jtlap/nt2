//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_INC_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_INC_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_inc inc
 *
 * \par Description
 * Increments a value by 1.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/inc.hpp>
 * \endcode
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *   meta::call<tag::inc_(A0)>::type
 *   inc(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the first parameter of inc
 *
 * \return a value of the same type as the input
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace boost { namespace simd {
  namespace tag
  {
    /*!
      @brief  inc generic tag

      Represents the inc function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct inc_ : ext::elementwise_<inc_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<inc_> parent;
    };
  }
  /*!
    Increments a value by 1.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = inc(x);
    @endcode

    is equivalent to:

    @code
    T r =  x+T(1);
    @endcode

    @param  a0

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::inc_, inc, 1)
} }

#endif
