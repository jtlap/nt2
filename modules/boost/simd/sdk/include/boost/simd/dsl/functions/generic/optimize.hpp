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
#include <boost/simd/sdk/functor/preprocessor/call.hpp>
#include <boost/simd/sdk/functor/preprocessor/dispatch.hpp>
#include <boost/dispatch/meta/identity.hpp>
#include <boost/dispatch/dsl/unpack.hpp>

//==============================================================================
// Recognition of expressions
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_REGISTER_DISPATCH_TO( boost::simd::tag::optimize_, tag::formal_
                            , (A0)
                            , (unspecified_<A0>)
                            , identity
                            )

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::optimize_, tag::formal_
                          , (A0)
                          , (ast_<A0>)
                          )
  {
    typedef dispatch::
            unpack< A0
                  , dispatch::functor< typename proto::tag_of<A0>::type, tag::optimize_ >
                  , typename dispatch::make_functor<tag::optimize_, A0>::type
                  >
    transform;

    typedef typename transform::result_type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0) const
    {
       return transform()(a0);
    }
  };
} } }

#endif
