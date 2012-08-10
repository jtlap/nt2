//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SIMD_TRANSFORM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SIMD_TRANSFORM_HPP_INCLUDED
#ifndef BOOST_SIMD_NO_SIMD

#include <nt2/core/functions/transform.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/scalar/numel.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/fusion/include/pop_front.hpp>
#include <cstdio>

namespace nt2 { namespace ext
{
  //============================================================================
  // Global nD element-wise transform
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::transform_, boost::simd::tag::simd_
                            , (A0)(A1)
                            , (ast_<A0>)
                              (ast_<A1>)
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
    {
      nt2::transform(a0,a1,0,nt2::numel(a0));
    }
  };

  //============================================================================
  // Partial nD element-wise transform with offset/size
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::transform_, boost::simd::tag::simd_
                            , (A0)(A1)(A2)(A3)
                            , (ast_<A0>)
                              (ast_<A1>)
                              (scalar_< integer_<A2> >)
                              (scalar_< integer_<A3> >)
                            )
  {
    typedef void result_type;

    typedef typename A0::value_type stype;
    typedef boost::simd::native<stype, BOOST_SIMD_DEFAULT_EXTENSION> target_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1& a1, A2 p, A3 sz) const
    {
      static const std::size_t N = boost::simd::meta
                                        ::cardinal_of<target_type>::value;

      std::size_t aligned_sz  = sz & ~(N-1);
      std::size_t it          = p;

      for(std::size_t m=it+aligned_sz; it != m; it+=N)
        nt2::run( a0, it, nt2::run(a1, it, meta::as_<target_type>()) );

      for(std::size_t m=it+(sz-aligned_sz); it != m; ++it)
        nt2::run( a0, it, nt2::run(a1, it, meta::as_<stype>()) );
    }
  };
} }

#endif
#endif
