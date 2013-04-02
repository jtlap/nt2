//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_GENERIC_ACOT_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_GENERIC_ACOT_HPP_INCLUDED
#include <nt2/toolbox/trigonometric/functions/acot.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/include/functions/simd/atan.hpp>
#include <nt2/include/functions/simd/bitwise_or.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/bitofsign.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::acot_,tag::cpu_
                            , (A0)
                            , ((generic_<arithmetic_<A0> >))
                            )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::acot(nt2::tofloat(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::acot_,tag::cpu_
                            , (A0)
                            , ((generic_<double_<A0> >))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::b_or((nt2::Pio_2<A0>()-nt2::atan(nt2::abs(a0)))+
                       double_constant<A0,0x3c91a62633145c07ll >(),
                       nt2::bitofsign(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::acot_,tag::cpu_
                            , (A0)
                            , ((generic_<single_<A0> >))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::b_or((nt2::Pio_2<A0>()-nt2::atan(nt2::abs(a0))),
                       nt2::bitofsign(a0));;
    }
  };
} }


#endif
