//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_GENERIC_TANH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_GENERIC_TANH_HPP_INCLUDED
#include <nt2/hyperbolic/functions/tanh.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/include/functions/simd/sign.hpp>
#include <nt2/include/functions/simd/expm1.hpp>
#include <nt2/include/functions/simd/is_nez.hpp>
#include <nt2/include/functions/simd/bitofsign.hpp>
#include <nt2/include/functions/simd/bitwise_xor.hpp>
#include <nt2/include/constants/mtwo.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tanh_, tag::cpu_
                            , (A0)
                            , ((generic_<arithmetic_<A0> >))
                            )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::tanh(nt2::tofloat(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tanh_, tag::cpu_
                            , (A0)
                            , ((generic_<floating_<A0> >))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      const A0 x = nt2::abs(a0);
//      if (nt2::all(gt(x,nt2::splat<A0>(1.836840028483855e+01)))) return sign(a0); //TO DO
      const A0 tmp1 = nt2::expm1(-(x+x));
      const A0 tmp2 = -tmp1/(nt2::Two<A0>()+tmp1);
      return nt2::if_else(nt2::is_eqz(a0), a0, nt2::b_xor(tmp2,nt2::bitofsign(a0)));
    }
  };
} }


#endif
