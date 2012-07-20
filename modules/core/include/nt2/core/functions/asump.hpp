//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_ASUMP_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_ASUMP_HPP_INCLUDED

/*!
  @file
  @brief Define the asump function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the asump functor
    **/
    struct asump_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    @brief Sum of the power of absolute values of table


    Compute the sum of the pth power of the absolute value of all the elements
    of a table along its first non-singleton dimension.

    @par Semantic

    For any table @c t of type @c table<T> and any arithmetic value @c p :

    @code
    table<T> r = asump(t,p);
    @endcode

    is equivalent to:

    @code
    table<T> r = sum(pow_abs(t,p),firstnonsingleton(t));
    @endcode

    @param a0 Table to process
    @param a1 Power at which absolute values are raised

    @return A @nt2 expression representing
            @c sum(pow_abs(a0,a1),firstnonsingleton(a0))
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::asump_, asump, 2)

  /*!
    @brief Sum of power of absolute values of table along a dimension

    Compute the sum of the pth power of absolute value of all the elements of
    a table along a given dimension.

    @par Semantic

    For any table @c t of type @c table<T> and any integer @c n:

    @code
    table<T> r = asump(t,p,n);
    @endcode

    is equivalent to:

    @code
    table<T> r = sum(pow_abs(t,p),n);
    @endcode

    @param a0 Table to process
    @param a1 Power at which absolute values are raised
    @param a2 Dimension along which to process a0

    @return A @nt2 expression representing @c sum(pow_abs(a0,a1),a2)
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::asump_, asump, 3)
}

#endif
