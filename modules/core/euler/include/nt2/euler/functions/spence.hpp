//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SPENCE_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SPENCE_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief spence generic tag

     Represents the spence function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct spence_ : ext::elementwise_<spence_> { typedef ext::elementwise_<spence_> parent; };
  }
  /*!
    Computes the spence function or dilogarithm


    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = spence(x);
    @endcode

    Computes \f$\mathop{\mbox{Li}_2}(x)=\int_1^{x} \frac{\log t}{t-1}\mbox{d}t\f$

    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::spence_, spence, 1)
}

#endif

