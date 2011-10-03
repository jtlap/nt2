//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_DSL_FUNCTIONS_PACK_EVALUATE_HPP_INCLUDED
#define BOOST_SIMD_DSL_FUNCTIONS_PACK_EVALUATE_HPP_INCLUDED

#include <boost/simd/dsl/functions/evaluate.hpp>
#include <boost/simd/include/functions/terminal.hpp>
#include <boost/simd/sdk/simd/pack/forward.hpp>
#include <boost/simd/sdk/functor/hierarchy.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>
#include <boost/dispatch/dsl/compute.hpp>
#include <boost/dispatch/dsl/semantic_of.hpp>

//==============================================================================
// Evaluation of simd native pack
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::evaluate_, tag::formal_
                            , (A0)(Tag)
                            , ((expr_< unspecified_<A0>, boost::simd::domain, Tag >))
                            )
  {
    typedef typename dispatch::meta::semantic_of<A0>::type result_type;
    
    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(A0 const& a0) const
    {
      return dispatch::meta::compute<BOOST_SIMD_DEFAULT_SITE>()(a0);
    }
  };
} } }

#endif
