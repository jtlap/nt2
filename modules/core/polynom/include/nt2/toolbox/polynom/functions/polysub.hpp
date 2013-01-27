//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_POLYNOM_FUNCTIONS_POLYSUB_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOM_FUNCTIONS_POLYSUB_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
// polysub(a, b)
// This compute the sum of two polynomials.
// The polynomials are supposed to be given by an array of elements
// in decreasing degrees order

namespace nt2 { namespace tag
  {
    struct polysub_ : ext::elementwise_<polysub_> { typedef ext::elementwise_<polysub_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::polysub_, polysub, 2)
}

#endif
