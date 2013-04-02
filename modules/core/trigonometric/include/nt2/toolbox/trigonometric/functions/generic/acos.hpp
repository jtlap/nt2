//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_GENERIC_ACOS_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_GENERIC_ACOS_HPP_INCLUDED
#include <nt2/toolbox/trigonometric/functions/acos.hpp>
#include <nt2/toolbox/trigonometric/functions/scalar/impl/invtrig.hpp>
#include <nt2/toolbox/trigonometric/functions/simd/common/impl/invtrig.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/sign.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <boost/simd/sdk/simd/meta/is_native.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::acos_, tag::cpu_
                            , (A0)
                            , (generic_< arithmetic_<A0> >)
                            )
  {

    typedef typename meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::if_nan_else(nt2::gt(nt2::abs(a0), nt2::One<A0>()),
                         nt2::oneminus(nt2::sign(nt2::tofloat(a0)))*nt2::Pio_2<result_type>());
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::acos_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;
    typedef typename boost::simd::meta::is_native<A0>::type       is_native_t;

    NT2_FUNCTOR_CALL(1)
    {
      return impl::invtrig_base<A0,radian_tag,is_native_t>::acos(a0);
    }
  };
} }


#endif
