//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOM_FUNCTIONS_DECONV_HPP_INCLUDED
#define NT2_POLYNOM_FUNCTIONS_DECONV_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
// tie(p, q) = deconv(a, b)
// This compute the deconvolution of a polynomial a by a polynomial b
// i.e. division returning quotent and remainder,
// such that a = polyadd(conv(a, q), r)
// The polynomials are supposed to be given by an array of elements
// in decreasing degrees order

namespace nt2 { namespace tag
  {
    struct deconv_ : ext::tieable_<deconv_> { typedef ext::tieable_<deconv_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::deconv_, deconv, 2)
}

#endif
