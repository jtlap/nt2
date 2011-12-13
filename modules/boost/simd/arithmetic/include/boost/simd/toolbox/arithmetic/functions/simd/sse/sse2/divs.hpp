//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_SSE_SSE2_DIVS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_SSE_SSE2_DIVS_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/simd/toolbox/arithmetic/functions/divs.hpp>
#include <boost/simd/include/functions/group.hpp>
#include <boost/simd/include/functions/split.hpp>
#include <boost/dispatch/meta/upgrade.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divs_, boost::simd::tag::sse2_, (A0)
                            , ((simd_<ints8_<A0>,boost::simd::tag::sse_>))
                              ((simd_<ints8_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::upgrade<A0>::type ivtype;
      ivtype a0l, a0h, a1l, a1h;
      split(a0, a0l, a0h);
      split(a1, a1l, a1h);
      return group( boost::simd::divs(a0l, a1l)
                  , boost::simd::divs(a0h, a1h)
                  );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divs_, boost::simd::tag::sse2_, (A0)
                            , ((simd_<ints16_<A0>,boost::simd::tag::sse_>))
                              ((simd_<ints16_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::upgrade<A0>::type ivtype;
      ivtype a0l, a0h, a1l, a1h;
      split(a0, a0l, a0h);
      split(a1, a1l, a1h);
      return group( boost::simd::divs(a0l, a1l)
                  , boost::simd::divs(a0h, a1h)
                  );
    }
  };
} } }

#endif
#endif
