/*******************************************************************************
 *         Copyright 2003-2011 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_IMPL_TRIGO_REM_PIO2_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_IMPL_TRIGO_REM_PIO2_HPP_INCLUDED
#include <nt2/toolbox/trigonometric/functions/scalar/impl/trigo/f_rem_pio2.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
namespace nt2
{
  namespace details
  {
    namespace internal
    {
      
      template < class A0 > struct rpio2 < A0, tag::simd_type> 
      {
        typedef typename meta::as_integer<A0, signed>::type int_type;
        typedef typename meta::scalar_of<A0>::type               sA0;
        typedef typename meta::scalar_of<int_type>::type        isA0;
        static const uint32_t N =  meta::cardinal_of<A0>::value;
        typedef rpio2 < sA0, tag::not_simd_type>              srpio2; 
        static inline void rem_pio2(const A0& x, int_type &n, A0&xr, A0&xc)
        {
          NT2_ALIGNED_TYPE(sA0) xr1[meta::cardinal_of<A0>::value];
          NT2_ALIGNED_TYPE(sA0) xc1[meta::cardinal_of<A0>::value];
          NT2_ALIGNED_TYPE(isA0) n1[meta::cardinal_of<A0>::value];
           for(uint32_t i = 0; i < N; i++){
            sA0 xr0, xc0;
            isA0 n0; 
              srpio2::rem_pio2(x[i], n0, xr0, xc0); //n1[i], xr1[i], xc[i]);
            n1[i] = n0;
            xr1[i] = xr0;
            xc1[i] = xc0;
           }
          xr = nt2::load<A0>(&xr1[0], 0);
          xc = nt2::load<A0>(&xc1[0], 0);  
          n = nt2::load<int_type>(&n1[0], 0);

        }
      };         
    }
  }
}


#endif

// /////////////////////////////////////////////////////////////////////////////
// End of d_rem_pio2.hpp<2>
// /////////////////////////////////////////////////////////////////////////////
