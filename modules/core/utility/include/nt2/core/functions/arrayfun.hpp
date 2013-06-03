//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_ARRAYFUN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_ARRAYFUN_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the arrayfun function
 **/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for bsxfun functor
     **/
    struct arrayfun_ : ext::elementwise_<arrayfun_>
    {
      typedef ext::elementwise_<arrayfun_> parent;
    };
  }

  /*!
    @brief Apply element-by-element operation to n expressions

    arrayfun(f,a,b) applies the element-by-element @pfo @c f to expressions
    @c a and @c b.

    The corresponding dimensions of @c a and @c b must be equal to each other.

    @param f Polymorphic Function object to apply
    @param a First expression to process
    @param b Second expression to process
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::arrayfun_, arrayfun, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::arrayfun_, arrayfun, 3)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::arrayfun_, arrayfun, 4)
}

#endif
