//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TRI1L_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TRI1L_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief tri1l generic tag

      Represents the tri1l function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct tri1l_ : ext::elementwise_<tri1l_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<tri1l_> parent;
    };
  }

  /*!
    @brief Apply a 1-lower-triangular masking to an expression

    Apply a mask on an expression that evaluates to 0 everywhere except on the
    lower triangular part of @c a0 and 1 on the diagonal.

    @param a0 Expression to mask.
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::tri1l_, tri1l, 1)


  /*!
    @brief Apply an offset 1-lower-triangular masking to an expression

    Apply a mask on an expression that evaluates to 0 everywhere except on the
    lower triangular part of @c a0 and @c a1 subdiagonal and 1 on the diagonal.

    @param a0 Expression to mask.
    @param a1 Diagonal offset to the mask.
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::tri1l_, tri1l, 2)
}

#endif
