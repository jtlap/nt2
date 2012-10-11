//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSE2_SORT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSE2_SORT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/simd/toolbox/swar/functions/sort.hpp>
#include <boost/simd/include/functions/simd/min.hpp>
#include <boost/simd/include/functions/simd/max.hpp>
#include <boost/simd/include/functions/simd/minimum.hpp>
#include <boost/simd/include/functions/simd/maximum.hpp>
#include <boost/simd/include/functions/simd/make.hpp>
#include <boost/simd/toolbox/swar/functions/details/shuffle.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::sort_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_ < type32_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      A0 p0  = details::shuffle<2,3,0,1>(a0);
      A0 mn = min(a0,p0);
      A0 mx = max(a0,p0);

      A0 minmax = details::shuffle<0,1,0,1>(mn,mx);
      A0 maxmin = details::shuffle<1,0,1,0>(mn,mx);
      mn = min(minmax,maxmin);
      mx = max(minmax,maxmin);

      return  details::shuffle<0,1,0,1>
              ( A0(details::shuffle<0,2,0,2>(mn))
              , A0(details::shuffle<0,2,0,2>(mx))
              );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::sort_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_ < type64_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return boost::simd::make<A0>(minimum(a0), maximum(a0));
    }
  };
} } }

#endif
#endif
