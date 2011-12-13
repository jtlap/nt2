/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_IMPL_TRIGO_D_PIO2_REDUCING_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_IMPL_TRIGO_D_PIO2_REDUCING_HPP_INCLUDED

#include <boost/fusion/tuple.hpp>
#include <nt2/include/functions/toint.hpp>
#include <nt2/include/functions/round2even.hpp>
#include <nt2/include/constants/digits.hpp>
//#include <nt2/toolbox/trigonometric/functions/simd/common/impl/trigo/rem_pio2.hpp>
#include <nt2/include/functions/rem_pio2.hpp>

namespace nt2
{
  namespace details
  {
    namespace internal
    {
      // trigonometric double reduction algorithms in the [-pi/4, pi/4] range for double.
      // this reductions are used in the accurate and fast/common
      // trigonometric functions with different policies

      template<class A0> struct pio2_reducing < A0, tag::simd_type, double>
      {
        typedef typename meta::as_integer<A0, signed>::type int_type;

        static inline int_type noreduction(const A0& x, A0& xr,  A0& xc)
        {
          xr =  x;
          xc = Zero<A0>();
          return Zero<int_type>();
        }
        
        static inline int_type straight_reduction(const A0& x, A0& xr, A0& xc)
        {
          // x has to be in [pi/4, pi/2]
          xc = Zero<A0>();
          xr = x-double_constant<A0,0x3FF921FB54400000ll>();
                    // 6.07710050630396597660e-11
          xr -= double_constant<A0,0x3DD0B4611A600000ll>();
                    // 2.02226624871116645580e-21
          xr -= double_constant<A0,0x3BA3198A2E000000ll>();
          xc = Zero<A0>();
          return One<int_type>();
        }

        static inline int_type cephes_reduction(const A0& x, A0& xr, A0& xc)
        {
                                // 6.36619772367581382433e-01
          A0 xi = round2even(x* double_constant<A0,0x3FE45F306DC9C883ll> ());
                    // 1.57079632673412561417e+00
          xr = x-xi*double_constant<A0,0x3FF921FB54400000ll>();
                    // 6.07710050630396597660e-11
          xr -= xi*double_constant<A0,0x3DD0B4611A600000ll>();
                    // 2.02226624871116645580e-21
          xr -= xi*double_constant<A0,0x3BA3198A2E000000ll>();
          xc = Zero<A0>();
          return toint(xi);
        }

        static inline int_type fdlibm_medium_reduction(const A0& t, A0& xr, A0& xc)
        {
          A0 fn = round2even(t*double_constant<A0,0x3FE45F306DC9C883ll>());
          A0 r  = t-fn*double_constant<A0,0x3FF921FB54400000ll>();
          A0 w  = fn*double_constant<A0,0x3DD0B4611A626331ll>();        /* 1st round good to 85 bit */
          A0 t2 = r;
          w  = fn*double_constant<A0,0x3DD0B4611A600000ll>();
          r  = t2-w;
          w  = fn*double_constant<A0,0x3BA3198A2E037073ll>()-((t2-r)-w);
          t2 = r;                                /* 2nd round will cover all possible cases */
          w  = fn*double_constant<A0,0x3BA3198A2E000000ll>();
          r  = t2-w;
          w  = fn*double_constant<A0,0x397B839A252049C1ll>()-((t2-r)-w);
          xr = r-w;
          xc = (r-xr)-w;
          return  toint(fn);
        }

        static inline int_type fdlibm_big_reduction(const A0& t, A0& xr, A0& xc)
        {
          return nt2::rem_pio2(t, xr, xc);
        }
        
        static inline int_type invalidity_reduction(const A0& t, A0& xr, A0& xc)
        {
          ignore_unused(t);
          ignore_unused(xc); 
          int_type i = Zero<int_type>();
          xr =  Nan<A0>(); 
          return i;
        }
      };
    }
  }
}


#endif

// /////////////////////////////////////////////////////////////////////////////
// End of d_pio2_reducing.hpp
// /////////////////////////////////////////////////////////////////////////////
