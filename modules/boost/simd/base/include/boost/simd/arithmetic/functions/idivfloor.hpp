//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_IDIVFLOOR_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_IDIVFLOOR_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_idivfloor idivfloor
 *
 * \par Description
 * return the \c floor of the operands real divisionin the corresponding integer type
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/idivfloor.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::idivfloor_(A0,A0)>::type
 *     idivfloor(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of idivfloor
 * \param a1 the second parameter of idivfloor
 *
 * \return an integer value
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
      @brief  idivfloor generic tag

      Represents the idivfloor function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct idivfloor_ : ext::elementwise_<idivfloor_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<idivfloor_> parent;
    };
  }
  /*!
    Computes the integer conversion of the truncated division of its parameters.

    @par semantic:
    For any given value @c x,  @c y of type @c T:

    @code
    T r = idivfix(x, y);
    @endcode

    For floating point values the code is equivalent to:

    @code
    as_integer<T> r = toints(floor(x/y));
    @endcode

    If y is null, it returns Valmax (resp. Valmin)
    if x is positive (resp. negative) and 0 if x is null.

    @param  a0
    @param  a1

    @return      a value of the integral type associated to the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::idivfloor_, idivfloor, 2)
} }

#endif


