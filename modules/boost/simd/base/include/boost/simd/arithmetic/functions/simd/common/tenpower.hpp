//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_TENPOWER_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_TENPOWER_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/tenpower.hpp>
#include <boost/simd/include/functions/simd/abs.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/is_odd.hpp>
#include <boost/simd/include/functions/simd/is_ltz.hpp>
#include <boost/simd/include/functions/simd/shift_right.hpp>
#include <boost/simd/include/functions/simd/multiplies.hpp>
#include <boost/simd/include/functions/simd/any.hpp>
#include <boost/simd/include/functions/simd/abs.hpp>
#include <boost/simd/include/functions/simd/sqr.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/ten.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT( tenpower_, tag::cpu_
                          , (A0)(X)
                          , ((simd_<int_<A0>,X>))
                          )
  {
    typedef typename dispatch::meta::as_floating<A0>::type result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type result = One<result_type>();
      result_type base = Ten<result_type>();
      A0 exp = boost::simd::abs(a0);
      while(any(exp))
      {
        result *= if_else(is_odd(exp), base, One<result_type>());
        exp >>= 1;
        base = sqr(base);
      }
      return if_else(is_ltz(a0), rec(result), result);
    }
  };

  BOOST_DISPATCH_IMPLEMENT( tenpower_, tag::cpu_
                          , (A0)(X)
                          , ((simd_<uint_<A0>,X>))
                          )
  {
    typedef typename dispatch::meta::as_floating<A0>::type result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type result = One<result_type>();
      result_type base = Ten<result_type>();
      A0 exp = a0;
      while(any(exp))
      {
        result *= if_else(is_odd(exp), base, One<result_type>());
        exp >>= 1;
        base = sqr(base);
      }
      return result;
    }
  };

} } }


#endif
