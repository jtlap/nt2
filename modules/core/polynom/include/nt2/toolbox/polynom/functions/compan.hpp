//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_POLYNOM_FUNCTIONS_COMPAN_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOM_FUNCTIONS_COMPAN_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/**
 * @brief companion matrix of a polynomial
 *
 *   compan(p) returns the compan of the input polynomial.
 *   null polynomial has compan -1
 *   non null constant polynomial has compan 0
 *
 *
 **/
namespace nt2 { namespace tag
  {
    struct compan_: ext::elementwise_<compan_> { typedef ext::elementwise_<compan_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::compan_,compan, 1)
}
#endif
