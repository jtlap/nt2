//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_ASEC_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_ASEC_HPP_INCLUDED
#include <nt2/toolbox/trigonometric/functions/asec.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/include/functions/simd/acsc.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/constants/pio_2.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::asec_, boost::simd::tag::simd_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::asec(nt2::tofloat(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::asec_, boost::simd::tag::simd_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return (nt2::Pio_2<A0>()-nt2::acsc(a0));
    }
  };
} }


#endif
