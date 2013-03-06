//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_POLYNOM_FUNCTIONS_POLYDER_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOM_FUNCTIONS_POLYDER_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/**
 * @brief Perform polynomial derivative
 *
 *   polyder(p) returns the derivative of the polynomial whose
 *   coefficients are the elements of vector p.
 *
 *   polyder(a,b) returns the derivative of polynomial a*b.
 *
 *   Please use the ratfracder functor to compute the derivative of a/b.
 *
 **/
namespace nt2 { namespace tag
  {
    struct polyder_: ext::elementwise_<polyder_> { typedef ext::elementwise_<polyder_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::polyder_,polyder, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::polyder_,polyder, 2)
}
#endif
