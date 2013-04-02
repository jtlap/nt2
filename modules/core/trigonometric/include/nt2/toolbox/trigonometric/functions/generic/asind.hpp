//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_GENERIC_ASIND_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_GENERIC_ASIND_HPP_INCLUDED
#include <nt2/toolbox/trigonometric/functions/asind.hpp>
#include <nt2/include/functions/simd/asin.hpp>
#include <nt2/include/functions/simd/indeg.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/sign.hpp>
#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/include/constants/_90.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/sdk/meta/as_floating.hpp>


namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::asind_,tag::cpu_
                            , (A0)
                            , ((generic_<arithmetic_<A0> >))
                            )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::if_nan_else(nt2::gt(nt2::abs(a0), nt2::One<A0>()),
                              nt2::sign(nt2::tofloat(a0))*nt2::_90<result_type>());
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::asind_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::indeg(nt2::asin(nt2::tofloat(a0)));
    }
  };
} }


#endif
