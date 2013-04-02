//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_NBD_ATAN2_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_NBD_ATAN2_HPP_INCLUDED

#include <nt2/toolbox/trigonometric/functions/nbd_atan2.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/atan.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/if_zero_else.hpp>
#include <nt2/include/functions/simd/if_else_zero.hpp>
#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/include/functions/simd/is_inf.hpp>
#include <nt2/include/functions/simd/is_nan.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/copysign.hpp>
#include <nt2/include/functions/simd/signnz.hpp>
#include <nt2/include/functions/simd/is_gtz.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/sdk/meta/as_floating.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::nbd_atan2_, boost::simd::tag::simd_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                              ((simd_<arithmetic_<A0>,X>))
                            )
  {

    typedef typename meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return nt2::nbd_atan2(tofloat(a0), nt2::tofloat(a1));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::nbd_atan2_, boost::simd::tag::simd_
                            , (A0)(X)
                            , ((simd_<uint_<A0>,X>))
                              ((simd_<uint_<A0>,X>))
                            )
  {

    typedef typename meta::as_floating<A0>::type result_type;
    inline result_type operator()(const typename A0::native_type a0_n,
                      const typename A0::native_type a1_n) const
    {
      const A0 a0 = a0_n;
      const A0 a1 = a1_n;
      result_type z = nt2::atan(nt2::tofloat(a0)/nt2::tofloat(a1));
      return nt2::if_zero_else(nt2::is_eqz(a0), z);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::nbd_atan2_, boost::simd::tag::simd_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                              ((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    inline result_type operator()(const typename A0::native_type a0_n,
                                  const typename A0::native_type a1_n) const
    {
      A0 a0 = a0_n;
      A0 a1 = a1_n;
      A0 z = impl::invtrig_base<result_type,radian_tag, tag::simd_type>::kernel_atan(a0/a1);
      z = nt2::if_else(nt2::is_gtz(a1), z, nt2::Pi<A0>()-z)*nt2::signnz(a0);
      return nt2::if_else(nt2::is_eqz(a0), nt2::if_else_zero(nt2::is_ltz(a1), nt2::Pi<A0>()), z);
    }
  };
} }


#endif
