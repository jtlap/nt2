//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_DSL_FUNCTIONS_GENERIC_COMPILE_HPP_INCLUDED
#define BOOST_SIMD_DSL_FUNCTIONS_GENERIC_COMPILE_HPP_INCLUDED

#include <boost/simd/dsl/functions/compile.hpp>
#include <boost/simd/include/functions/run.hpp>
#include <boost/simd/sdk/functor/hierarchy.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::compile_, tag::formal_
                            , (A0)
                            , (unspecified_<A0>)
                            )
  {
    typedef dispatch::functor<tag::run_> result_type;
    
    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(A0 const&) const
    {
      return result_type();
    }
  };
} } }

#endif
