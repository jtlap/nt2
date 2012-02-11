//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_DSL_FUNCTIONS_GENERIC_EVALUATE_HPP_INCLUDED
#define BOOST_SIMD_DSL_FUNCTIONS_GENERIC_EVALUATE_HPP_INCLUDED

#include <boost/simd/dsl/functions/evaluate.hpp>
#include <boost/simd/include/functions/optimize.hpp>
#include <boost/simd/include/functions/schedule.hpp>
#include <boost/simd/include/functions/compile.hpp>

#include <boost/simd/sdk/functor/hierarchy.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::evaluate_, tag::formal_
                            , (A0)
                            , (ast_<A0>)
                            )
  {
    typedef typename dispatch::meta::call<tag::optimize_(A0 const&)>::type optimized;
    typedef typename dispatch::meta::call<tag::compile_(A0 const&)>::type  compiled;
    typedef typename dispatch::meta::call<tag::schedule_(optimized, compiled)>::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0) const
    {
      return schedule(optimize(a0), compile(a0));
    }
  };
} } }

#endif
