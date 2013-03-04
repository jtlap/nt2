//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_POLYNOM_FUNCTIONS_DEGREE_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOM_FUNCTIONS_DEGREE_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/**
 * @brief Perform polynomial format reduction
 *
 *   degree(p) returns the degree of the input polynomial.
 *   null polynomial has degree -1
 *   non null constant polynomial has degree 0
 *
 *
 **/
namespace nt2 { namespace tag
  {
    struct degree_: ext::elementwise_<degree_> { typedef ext::elementwise_<degree_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::degree_,degree, 1)
}
#endif
