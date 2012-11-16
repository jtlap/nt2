//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_AVX_SHUFFLE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_AVX_SHUFFLE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
#include <boost/simd/toolbox/swar/functions/shuffle.hpp>
#include <boost/simd/toolbox/swar/functions/details/shuffle.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd
{
  namespace ext
  {
    BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shuffle_
                                      , boost::simd::tag::avx_
                                      , (A0)(P)
                                      , ((simd_ < type64_<A0>
                                                , boost::simd::tag::avx_
                                                >
                                        ))
                                        (target_< unspecified_<P> >)
                                      )
    {
      
    };

   BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shuffle_
                                      , boost::simd::tag::avx_
                                      , (A0)(P)
                                      , ((simd_ < type32_<A0>
                                                , boost::simd::tag::avx_
                                                >
                                        ))
                                        (target_< unspecified_<P> >)
                                      )
    {
 
    };

    BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shuffle_
                                      , boost::simd::tag::avx_
                                      , (A0)(P)
                                      , ((simd_ < type64_<A0>
                                                , boost::simd::tag::avx_
                                                >
                                        ))
                                        ((simd_ < type64_<A0>
                                                , boost::simd::tag::avx_
                                                >
                                        ))
                                        (target_< unspecified_<P> >)
                                      )
    {
  
    };

    BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shuffle_
                                      , boost::simd::tag::avx_
                                      , (A0)(P)
                                      , ((simd_ < type32_<A0>
                                                , boost::simd::tag::avx_
                                                >
                                        ))
                                        ((simd_ < type32_<A0>
                                                , boost::simd::tag::avx_
                                                >
                                        ))
                                        (target_< unspecified_<P> >)
                                      )
    {
     
    };
  }
} }

#endif
#endif
