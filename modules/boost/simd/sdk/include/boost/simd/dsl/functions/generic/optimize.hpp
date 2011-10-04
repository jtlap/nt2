//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_DSL_FUNCTIONS_GENERIC_OPTIMIZE_HPP_INCLUDED
#define BOOST_SIMD_DSL_FUNCTIONS_GENERIC_OPTIMIZE_HPP_INCLUDED

#include <boost/simd/dsl/functions/optimize.hpp>
#include <boost/simd/sdk/functor/hierarchy.hpp>
#include <boost/simd/sdk/functor/preprocessor/dispatch.hpp>
#include <boost/dispatch/meta/identity.hpp>

//==============================================================================
// Recognition of expressions (no-op by default)
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_REGISTER_DISPATCH_TO( boost::simd::tag::optimize_, tag::formal_
                          , (A0)
                          , (unspecified_<A0>)
                          , identity
                          )
} } }

#endif
