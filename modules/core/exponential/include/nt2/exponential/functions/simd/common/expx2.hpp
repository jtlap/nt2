//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_EXPX2_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_EXPX2_HPP_INCLUDED

#include <nt2/exponential/functions/expx2.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/floor.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/is_inf.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/maxlog.hpp>
#include <nt2/sdk/meta/as_floating.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expx2_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {

    typedef typename meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::expx2(nt2::tofloat(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expx2_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      A0 x =  nt2::abs(a0);
      // Represent x as an exact multiple of 1/32 plus a residual.
      A0 m = Expx2c1<A0>() * nt2::floor(Expx2c2<A0>() * x + nt2::Half<A0>());
      x -= m;
      // x**2 = m**2 + 2mf + f**2
      A0 u = nt2::sqr(m);
      A0 u1 = nt2::Two<A0>()*m*x + nt2::sqr(x);
      // u is exact, u1 is small.
      return nt2::if_else(is_inf(a0),
                          nt2::Inf<A0>(),
                          nt2::if_else(nt2::gt(u+u1, nt2::Maxlog<A0>()),
                                       nt2::Inf<A0>(),
                                       nt2::exp(u)*nt2::exp(u1)
                                      )
                         );
    }
  };
} }


#endif
