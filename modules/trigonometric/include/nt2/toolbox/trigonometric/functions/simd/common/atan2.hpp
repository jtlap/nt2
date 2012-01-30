//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_ATAN2_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_ATAN2_HPP_INCLUDED

#include <nt2/toolbox/trigonometric/functions/atan2.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/atan.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/if_allbits_else.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/logical_and.hpp>
#include <nt2/include/functions/copysign.hpp>
#include <nt2/include/functions/signnz.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/sdk/meta/as_floating.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::atan2_, boost::simd::tag::simd_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))((simd_<arithmetic_<A0>,X>))
                            )
  {

    typedef typename meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return nt2::atan2(tofloat(a0), tofloat(a1));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::atan2_, boost::simd::tag::simd_
                            , (A0)(X)
                            , ((simd_<uint_<A0>,X>))((simd_<uint_<A0>,X>))
                            )
  {

    typedef typename meta::as_floating<A0>::type result_type;
    inline result_type operator()(const typename A0::native_type a0_n,
                      const typename A0::native_type a1_n) const
    {
      const A0 a0 = {a0_n};
      const A0 a1 = {a1_n};
      result_type z = atan(tofloat(a0)/tofloat(a1));  
      return sel(is_eqz(a0), Zero<result_type>(), z);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::atan2_, boost::simd::tag::simd_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    inline result_type operator()(const typename A0::native_type a0_n,
                      const typename A0::native_type a1_n) const
    {
      A0 a0 = {a0_n};
      A0 a1 = {a1_n};
      typedef typename meta::as_logical<A0>::type lA0; 
      lA0 test = logical_and(is_inf(a0), is_inf(a1));
      a0 = if_else(test, copysign(One<A0>(), a0), a0);
      a1 = if_else(test, copysign(One<A0>(), a1), a1); 
      A0 z = {impl::invtrig_base<result_type,radian_tag, tag::simd_type>::kernel_atan(a0/a1)}; 
      //A0 z = atan(abs(a0/a1));  // case a1 > 0,  a0 > 0
      z = sel(is_gtz(a1), z, Pi<A0>()-z)*signnz(a0);
      return if_nan_else(logical_or(is_nan(a0), is_nan(a1)),
                         sel(is_eqz(a0),
                             sel(is_ltz(a1), Pi<A0>(), Zero<A0>()),
                             z)
                         );
    }
  };
} }


#endif
