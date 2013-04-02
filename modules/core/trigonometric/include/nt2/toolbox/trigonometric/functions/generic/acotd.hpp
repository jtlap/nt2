//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_GENERIC_ACOTD_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_GENERIC_ACOTD_HPP_INCLUDED
#include <nt2/toolbox/trigonometric/functions/acotd.hpp>
#include <nt2/include/functions/simd/atand.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/bitofsign.hpp>
#include <nt2/include/functions/simd/is_inf.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/include/functions/simd/is_nez.hpp>
#include <nt2/include/functions/simd/bitofsign.hpp>
#include <nt2/include/functions/simd/if_else_zero.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/_90.hpp>
#include <nt2/sdk/meta/as_floating.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::acotd_,tag::cpu_
                            , (A0)
                            , ((generic_<floating_<A0> >))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      A0 z = nt2::_90<A0>()-nt2::if_else_zero(nt2::is_nez(a0),nt2::atand(nt2::abs(a0)));
      #ifndef BOOST_SIMD_NO_INFINITIES
      z = nt2::if_zero_else(nt2::is_inf(a0),z);
      #endif
      return nt2::b_or(z, nt2::bitofsign(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::acotd_,tag::cpu_
                            , (A0)
                            , ((generic_<arithmetic_<A0> >))
                            )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::acotd(nt2::tofloat(a0));
    }
  };
} }


#endif
