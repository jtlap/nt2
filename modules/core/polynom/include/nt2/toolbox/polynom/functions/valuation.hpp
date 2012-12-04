//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_POLYNOM_FUNCTIONS_VALUATION_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOM_FUNCTIONS_VALUATION_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/**
 * @brief Perform polynomial format reduction
 *
 *   valuation(p) returns the valuation of the input polynomial.
 *   null polynomial has valuation -1
 *   non null constant polynomial has valuation 0
 *
 **/
namespace nt2 { namespace tag
  {
    struct valuation_: ext::elementwise_<valuation_> { typedef ext::elementwise_<valuation_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::valuation_,valuation, 1)
}
#endif
