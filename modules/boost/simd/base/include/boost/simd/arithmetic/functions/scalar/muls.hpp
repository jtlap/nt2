//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_MULS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_MULS_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/muls.hpp>
#include <boost/simd/include/functions/scalar/genmask.hpp>
#include <boost/simd/include/functions/scalar/abs.hpp>
#include <boost/simd/include/functions/scalar/bitofsign.hpp>
#include <boost/simd/include/functions/scalar/bitwise_xor.hpp>
#include <boost/simd/include/functions/scalar/saturate.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/dispatch/meta/upgrade.hpp>
#include <boost/dispatch/meta/as_unsigned.hpp>
#
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::muls_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)(scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return a0*a1;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::muls_, tag::cpu_
                            , (A0)
                            , (scalar_< unsigned_<A0> >)(scalar_< unsigned_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::upgrade<A0>::type utype;
      utype res = utype(a0)*utype(a1);
      return static_cast<A0>(res) | genmask(static_cast<A0>(res >> sizeof(A0)*CHAR_BIT));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::muls_, tag::cpu_
                            , (A0)
                            , (scalar_< integer_<A0> >)(scalar_< integer_<A0> >)
                            )
  {

    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::upgrade<A0>::type uptype;
      return A0(saturate<A0>(static_cast<uptype>(a0)*static_cast<uptype>(a1)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::muls_, tag::cpu_
                                   , (A0)
                                   , (scalar_< int32_<A0> >)(scalar_< int32_<A0> >)
                                   )
  {

    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::as_unsigned<A0>::type untype;
      typedef typename dispatch::meta::upgrade<A0>::type utype;

      utype res = utype(a0)*utype(a1);
      untype res2 = (untype(a0 ^ a1) >> (sizeof(A0)*CHAR_BIT-1)) + Valmax<A0>();

      A0 hi = (res >> sizeof(A0)*CHAR_BIT);
      A0 lo = res;

      if(hi != (lo >> (sizeof(A0)*CHAR_BIT-1)))
        res = res2;

      return res;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::muls_, tag::cpu_
                            , (A0)
                            , (scalar_< uint64_<A0> >)(scalar_< uint64_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      if (a1 == 0 || a0 == 0) return Zero<A0>();
      if (a1 >= a0)
      {
        A0 z = Valmax<A0>()/a1;
        if (z < a0)
          return  Valmax<A0>();
        else
          return a0*a1;
      }
      else
        return muls(a1, a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::muls_, tag::cpu_
                            , (A0)
                            , (scalar_< int64_<A0> >)(scalar_< int64_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      if (a1 == 0 || a0 == 0) return Zero<result_type>();
      typedef typename dispatch::meta::as_unsigned<result_type>::type untype;
      result_type sign =  b_xor(bitofsign(a0), bitofsign(a1));
      untype aa0 = boost::simd::abs(a0);
      untype aa1 = boost::simd::abs(a1);
      if (aa1 >= aa0)
      {
        untype z = Valmax<result_type>()/aa1;
        if (z < aa0)
          return sign ? Valmin<result_type>():Valmax<result_type>();
        else
          return a0*a1;
      }
      else
        return muls(a1, a0);
    }
  };
} } }

#endif
