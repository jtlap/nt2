//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_ASUM2_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_ASUM2_HPP_INCLUDED

/*!
  @file
  @brief Define the asum2 function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the asum2 functor
    **/
    struct asum2_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    @brief Sum of squared absolute value of table

    Compute the sum of the squared absolute value of all the elements of a table
    along its first non-singleton dimension.

    @par Semantic

    For any table @c t of type @c table<T> :

    @code
    table<T> r = asum2(t);
    @endcode

    is equivalent to:

    @code
    table<T> r = sum(sqr_abs(t),firstnonsingleton(t));
    @endcode

    @param a0 Table to process

    @return A @nt2 expression representing
            @c sum(sqr_abs(a0),firstnonsingleton(a0))
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::asum2_, asum2, 1 )

  /*!
    @brief Sum of absolute values of table along a dimension

    Compute the sum of the squared absolute value of all the elements of a table
    along a given dimension.

    @par Semantic

    For any table @c t of type @c table<T> and any integer @c n:

    @code
    table<T> r = asum2(t,n);
    @endcode

    is equivalent to:

    @code
    table<T> r = sum(sqr_abs(t),n);
    @endcode

    @param a0 Table to process
    @param a1 Dimension along which to process a0

    @return A @nt2 expression representing @c sum(sqr_abs(a0),a1)
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::asum2_, asum2, 2 )
}

#endif
