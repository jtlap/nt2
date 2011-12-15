/*******************************************************************************
 *         Copyright 2003-2011 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_IMPL_TRIGO_D_REM_PIO2_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_IMPL_TRIGO_D_REM_PIO2_HPP_INCLUDED



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
        static const uint_32_t N =  meta::cardinal_of<A0>::value;
        typedef rpio2 < sA0, tag::simd_type>                  srpio2; 
        static inline void rem_pio2(const A0& x, int_type &n, A0&xr, A0&xc)
        {
          for(uint_32_t i = 0; i < N; i++){
            sA0 y[2];
            int32_t n1 = srpio2::__ieee754_rem_pio2(x[i], y);
            at<i>(n) =  n1; 
            at<i>(xr) = y[0];
            at<i>(xc) = y[1];
          }
        }
      };         
    }
  }
}


#endif

// /////////////////////////////////////////////////////////////////////////////
// End of d_rem_pio2.hpp<2>
// /////////////////////////////////////////////////////////////////////////////
