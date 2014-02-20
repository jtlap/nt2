//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_POW_ABSI_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_POW_ABSI_HPP_INCLUDED
#include <nt2/exponential/functions/pow_absi.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#include <nt2/include/functions/simd/is_odd.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/sqr.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_absi_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_<floating_<A0>,X>))
                              (scalar_< integer_<A1> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      result_type x = a0;
      A1 n = nt2::abs(a1);
      result_type ret = One<result_type>();
      for(A1 t = n; t > 0; t >>= 1)
      {
        if(is_odd(t)) ret*=x;
        x = sqr(x);
      }
      return is_ltz(a1) ? rec(ret) : ret;
    }
  };
} }

#endif
