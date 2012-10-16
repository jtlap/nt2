//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_SSE_SSE2_TOFLOAT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_SSE_SSE2_TOFLOAT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/simd/toolbox/arithmetic/functions/tofloat.hpp>
#include <boost/simd/include/functions/simd/make.hpp>
#include <boost/dispatch/meta/as_floating.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::tofloat_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_<int32_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename dispatch::meta::as_floating<A0>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return _mm_cvtepi32_ps(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::tofloat_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_<uint64_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename dispatch::meta::as_floating<A0>::type  result_type;
    typedef typename meta::scalar_of<result_type>::type     stype;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return boost::simd::make<result_type> ( static_cast<stype>(a0[0])
                                            , static_cast<stype>(a0[1])
                                            );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::tofloat_
                                    , boost::simd::tag::sse2_ , (A0)
                                    , ((simd_<uint32_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename dispatch::meta::as_floating<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<result_type>::type stype;

      return boost::simd::make<result_type> ( static_cast<stype>(a0[0])
                                            , static_cast<stype>(a0[1])
                                            , static_cast<stype>(a0[2])
                                            , static_cast<stype>(a0[3])
                                            );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::tofloat_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_<int64_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename dispatch::meta::as_floating<A0>::type        result_type;
    typedef typename meta::scalar_of<result_type>::type           sftype;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return boost::simd::make<result_type> ( static_cast<sftype>(a0[0])
                                            , static_cast<sftype>(a0[1])
                                            );
    }
  };
} } }

#endif
#endif
