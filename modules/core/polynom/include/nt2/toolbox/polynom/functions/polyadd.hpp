//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_POLYNOM_FUNCTIONS_POLYADD_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOM_FUNCTIONS_POLYADD_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
// polyadd(a, b)
// This compute the sum of two polynomials.
// The polynomials are supposed to be given by an array of elements
// in decreasing degrees order

namespace nt2 { namespace tag
  {
    struct polyadd_ : ext::elementwise_<polyadd_> { typedef ext::elementwise_<polyadd_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::polyadd_, polyadd, 2)
}

#endif
