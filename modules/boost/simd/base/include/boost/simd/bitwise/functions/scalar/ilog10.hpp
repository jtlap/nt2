//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SCALAR_ILOG10_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SCALAR_ILOG10_HPP_INCLUDED

#include <boost/simd/bitwise/functions/ilog10.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/assert.hpp>

#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/sum.hpp>
#include <boost/simd/include/functions/make.hpp>
#include <boost/simd/include/functions/is_greater_equal.hpp>
#include <boost/simd/include/functions/bitwise_cast.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/include/functions/multiplies.hpp>
#endif

namespace boost { namespace simd { namespace ext
{

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ilog10_, tag::cpu_
                            , (A0)
                            , (scalar_< int_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::as_integer<A0, unsigned>::type ui_type;
      BOOST_ASSERT_MSG( a0 > 0, "Logarithm is not defined for zero or negative values." );
      return result_type(ilog10(ui_type(a0)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ilog10_, tag::cpu_
                            , (A0)
                            , (scalar_< uint8_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      int32_t i = a0;
      return
        (i >= 100) ? 2 :
        (i >= 10) ? 1 : 0;
    }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ilog10_, tag::cpu_
                            , (A0)
                            , (scalar_< uint16_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
      typedef native<int32_t,  boost::simd::tag::sse_> v_type;
      v_type t = make<v_type>(10000, 1000, 100, 10);
      return -sum(bitwise_cast<v_type>(a0 >= t));
#else
      return
        (a0 >= 10000) ? 4 :
        (a0 >= 1000) ? 3 :
        (a0 >= 100) ? 2 :
        (a0 >= 10) ? 1 : 0;
#endif
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ilog10_, tag::cpu_
                            , (A0)
                            , (scalar_< uint32_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
      typedef native<int32_t,  boost::simd::tag::sse_> v_type;
      v_type t1 = make<v_type>(10000, 1000, 100, 10);
      v_type t2 = t1*splat<v_type>(10000);
      return (a0 >= 1000000000) ? 9 :
        -(sum(bitwise_cast<v_type>(a0 >= t1))+
          sum(bitwise_cast<v_type>(a0 >= t2)));
#else
      return
        (a0 >= 1000000000) ? 9 :
        (a0 >= 100000000) ? 8 :
        (a0 >= 10000000) ? 7 :
        (a0 >= 1000000) ? 6 :
        (a0 >= 100000) ? 5 :
        (a0 >= 10000) ? 4 :
        (a0 >= 1000) ? 3 :
        (a0 >= 100) ? 2 :
        (a0 >= 10) ? 1 : 0;
#endif
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ilog10_, tag::cpu_
                            , (A0)
                            , (scalar_< uint64_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      uint64_t i = a0;
      return
        (i >= 10000000000000000000ull) ? 19 :
        (i >= 1000000000000000000ull) ? 18 :
        (i >= 100000000000000000ull) ? 17 :
        (i >= 10000000000000000ull) ? 16 :
        (i >= 1000000000000000ull) ? 15 :
        (i >= 100000000000000ull) ? 14 :
        (i >= 10000000000000ull) ? 13 :
        (i >= 1000000000000ull) ? 12:
        (i >= 100000000000ull) ? 11 :
        (i >= 10000000000ull) ? 10 :
        (i >= 1000000000ull) ? 9 :
        (i >= 100000000ull) ? 8 :
        (i >= 10000000ull) ? 7 :
        (i >= 1000000ull) ? 6 :
        (i >= 100000ull) ? 5 :
        (i >= 10000ull) ? 4 :
        (i >= 1000ull) ? 3 :
        (i >= 100ull) ? 2 :
        (i >= 10ull) ? 1 : 0;
    }

  };

} } }

#endif

