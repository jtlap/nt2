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
      int32_t i = a0;
      return
        (i >= 10000) ? 4 :
        (i >= 1000) ? 3 :
        (i >= 100) ? 2 :
        (i >= 10) ? 1 : 0;
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
      int32_t i = a0;
      return
        (i >= 1000000000) ? 9 :
        (i >= 100000000) ? 8 :
        (i >= 10000000) ? 7 :
        (i >= 1000000) ? 6 :
        (i >= 100000) ? 5 :
        (i >= 10000) ? 4 :
        (i >= 1000) ? 3 :
        (i >= 100) ? 2 :
        (i >= 10) ? 1 : 0;
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

