//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_ACOSPI_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_ACOSPI_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 {
  namespace tag
  {
   /*!
     @brief acospi generic tag

     Represents the acospi function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct acospi_ : ext::elementwise_<acospi_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<acospi_> parent;
    };
  }
  /*!
    inverse cosine in \f$\pi\f$ multiples.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = acospi(x);
    @endcode

    Returns the arc @c r in the interval
    \f$[0, 1[\f$ such that <tt>cospi(r) == x</tt>.
    If @c x is outside \f$[-1, 1[\f$ the result is Nan.

    @see @funcref{acosd}, @funcref{acos}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::acospi_, acospi, 1)
}

#endif
