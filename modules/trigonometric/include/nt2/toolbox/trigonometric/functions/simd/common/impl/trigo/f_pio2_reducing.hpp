/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_IMPL_TRIGO_F_PIO2_REDUCING_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_IMPL_TRIGO_F_PIO2_REDUCING_HPP_INCLUDED

#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/fast_toint.hpp>
#include <nt2/include/functions/round2even.hpp>
#include <nt2/toolbox/arithmetic/include/functions/toint.hpp>
#include <nt2/include/constants/digits.hpp>
//#include <nt2/toolbox/trigonometric/functions/simd/common/impl/trigo/rem_pio2.hpp>
#include <nt2/include/functions/rem_pio2.hpp>

namespace nt2
{
  namespace details
  {
    namespace internal
    {
      // trigonometric float reduction algoritms in the [-pi/4, pi/4] range.
      // this reductions are used in the accurate and fast
      // trigonometric functions with different policies
      //      template < class A0, class base_A0 = typename meta::scalar_of<A0>::type >  struct pio2_reducing{};

      template < class A0>  struct pio2_reducing < A0, tag::simd_type, float>
      {
        typedef typename meta::as_integer<A0, signed>::type int_type;
        typedef typename meta::scalar_of<int_type>::type   sint_type;

        static inline int_type noreduction(const A0& x, A0& xr,  A0& xc)
        {
          //  std::cout << " no reduction "  << std::endl; 
          // x has to be in [0, pi/4]
          xr =  x;
          xc = Zero<A0>();
          return Zero<int_type>();
        }

        static inline int_type straight_reduction(const A0& x, A0& xr, A0& xc)
        {
          //  std::cout << " straight reduction "  << std::endl; 
          // x has to be in [pi/4, pi/2]
          xr = x-single_constant<A0,0x3fc90f80>();
          xr -= single_constant<A0,0x37354400 >();
          xr -= single_constant<A0,0x2e85a300>();
          xc = Zero<A0>();
          return One<int_type>();
        }

        static inline int_type cephes_reduction(const A0& x, A0& xr, A0& xc)
        {
          //  std::cout << " cephes reduction "  << std::endl; 
          //          A0 xi = round2even(x* Const<A0,invpio2>());
          int_type n = fast_toint(x* single_constant<A0,0x3f22f984>()+Half<A0>());
          A0 xi =  tofloat(n);
          xr = x-xi*single_constant<A0,0x3fc90f80>();
          xr -= xi*single_constant<A0,0x37354400 >();
          xr -= xi*single_constant<A0,0x2e85a300>();
          xc = Zero<A0>();
          return n;
        }

        static inline int_type fdlibm_medium_reduction(const A0& t, A0& xr, A0& xc)
        {
          A0 fn = round2even(t*single_constant<A0,0x3f22f984>());
          A0 r  = t-fn*single_constant<A0,0x3fc90f80>();
          A0 w  = fn*single_constant<A0,0x37354443>();        /* 1st round good to 40 bit */
          A0 t2 = r;
          w  = fn*single_constant<A0,0x37354400>();
          r  = t2-w;
          w  = fn*single_constant<A0,0x2e85a308>()-((t2-r)-w);
          t2 = r;                                /* 2nd round will cover all possible cases */
          w  = fn*single_constant<A0,0x2e85a300>();
          r  = t2-w;
          w  = fn*single_constant<A0,0x248d3132>()-((t2-r)-w);
          xr = r-w;
          xc = (r-xr)-w;
          return  toint(fn);
        }

        static inline int_type fdlibm_big_reduction(const A0& t, A0& xr, A0& xc)
        {
          return nt2::rem_pio2(t, xr, xc);
//           int_type i;
//           rpio2<A0, tag::simd_type>::rem_pio2(t, i, xr, xc);
//           return i;
        }

        static inline int_type invalidity_reduction(const A0& t, A0& xr, A0& /*xc*/)
        {
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
// End of f_pio2_reducing.hpp
// /////////////////////////////////////////////////////////////////////////////
