//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_COMMON_ILOG10_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_COMMON_ILOG10_HPP_INCLUDED

#include <boost/simd/bitwise/functions/ilog10.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/splat.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/if_else_zero.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/three.hpp>
#include <boost/simd/include/constants/four.hpp>
#include <boost/simd/include/constants/five.hpp>
#include <boost/simd/include/constants/six.hpp>
#include <boost/simd/include/constants/seven.hpp>
#include <boost/simd/include/constants/eight.hpp>
#include <boost/simd/include/constants/nine.hpp>
#include <boost/simd/include/constants/ten.hpp>
#include <boost/simd/include/constants/eleven.hpp>
#include <boost/simd/include/constants/twelve.hpp>
#include <boost/simd/include/constants/twenty.hpp>
#include <boost/simd/include/constants/hundred.hpp>
#include <boost/simd/include/constants/thousand.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd { namespace ext
{

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ilog10_, tag::cpu_
                                   , (A0)(X)
                                   , ((simd_< int_<A0>,X >))
                                   )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::as_integer<A0, unsigned>::type ui_type;
      BOOST_ASSERT_MSG( assert_all(a0 > 0), "Logarithm is not defined for zero or negative values." );
      return bitwise_cast<result_type>(ilog10(bitwise_cast<ui_type>(a0)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ilog10_, tag::cpu_
                            , (A0)(X)
                            , ((simd_< uint8_<A0>,X >))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return
        if_else(a0 >= Hundred<A0>(), Two<result_type>(),
                if_else_zero((a0 >= Ten<A0>()), One<result_type>()
                            )
               );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ilog10_, tag::cpu_
                            , (A0)(X)
                            , ((simd_< uint16_<A0>,X >))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return
        if_else(a0 >= splat<A0>(10000), Four<result_type>(),
                if_else(a0 >= Thousand<A0>(), Three<result_type>(),
                        if_else(a0 >= Hundred<A0>(), Two<result_type>(),
                                if_else_zero((a0 >= Ten<A0>()) , One<result_type>()
                                            )
                               )
                       )
               );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ilog10_, tag::cpu_
                            , (A0)(X)
                            , ((simd_< uint32_<A0>,X >))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return
        if_else(a0 >= splat<A0>(1000000000), Nine<result_type>(),
                if_else(a0 >= splat<A0>(100000000), Eight<result_type>(),
                        if_else(a0 >= splat<A0>(10000000), Seven<result_type>(),
                                if_else(a0 >= splat<A0>(1000000), Six<result_type>(),
                                        if_else(a0 >= splat<A0>(100000), Five<result_type>(),
                                                if_else(a0 >= splat<A0>(10000), Four<result_type>(),
                                                        if_else(a0 >= Thousand<A0>(), Three<result_type>(),
                                                                if_else(a0 >= Hundred<A0>(), Two<result_type>(),
                                                                        if_else_zero((a0 >= Ten<A0>()) , One<result_type>()
                                                                                    )
                                                                       )
                                                               )
                                                       )
                                               )
                                       )
                               )
                       )
               );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ilog10_, tag::cpu_
                            , (A0)(X)
                            , ((simd_< uint64_<A0>,X >))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return
        if_else(a0 >= splat<A0>(1000000000000000000ull), splat<result_type>(18),
                if_else(a0 >= splat<A0>(100000000000000000ull), splat<result_type>(17),
                        if_else(a0 >= splat<A0>(10000000000000000ull), splat<result_type>(16),
                                if_else(a0 >= splat<A0>(1000000000000000ull), splat<result_type>(15),
                                        if_else(a0 >= splat<A0>(100000000000000ull), splat<result_type>(14),
                                                if_else(a0 >= splat<A0>(10000000000000ull), splat<result_type>(13),
                                                        if_else(a0 >= splat<A0>(1000000000000ull), Twelve<result_type>(),
                                                                if_else(a0 >= splat<A0>(100000000000ull), Eleven<result_type>(),
                                                                        if_else(a0 >= splat<A0>(10000000000ull), Ten<result_type>(),
                                                                                if_else(a0 >= splat<A0>(1000000000ull), Nine<result_type>(),
                                                                                        if_else(a0 >= splat<A0>(100000000ull), Eight<result_type>(),
                                                                                                if_else(a0 >= splat<A0>(10000000ul), Seven<result_type>(),
                                                                                                        if_else(a0 >= splat<A0>(1000000ull), Six<result_type>(),
                                                                                                                if_else(a0 >= splat<A0>(100000ull), Five<result_type>(),
                                                                                                                        if_else(a0 >= splat<A0>(10000ull), Four<result_type>(),
                                                                                                                                if_else(a0 >= Thousand<A0>(), Three<result_type>(),
                                                                                                                                        if_else(a0 >= Hundred<A0>(), Two<result_type>(),
                                                                                                                                                if_else_zero((a0 >= Ten<A0>()) , One<result_type>()
                                                                                                                                                            )
                                                                                                                                               )
                                                                                                                                       )
                                                                                                                               )
                                                                                                                       )
                                                                                                               )
                                                                                                       )
                                                                                               )

                                                                                       )
                                                                               )
                                                                       )
                                                               )
                                                       )
                                               )
                                       )
                               )
                       )
               );
    }

  };
} } }


#endif
