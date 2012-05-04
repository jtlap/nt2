//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_SIMD_COMMON_FAST_GAMMA_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_SIMD_COMMON_FAST_GAMMA_HPP_INCLUDED
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/negif.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_nan.hpp>
#include <nt2/include/functions/simd/any.hpp>
#include <nt2/include/functions/simd/nbtrue.hpp>
#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/toolbox/euler/constants/fastgammalargelim.hpp>
#include <nt2/include/functions/simd/sinpi.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fast_gamma_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return fast_gamma(tofloat(a0));
    }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is floating_
  /////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::fast_gamma_, tag::cpu_,
                             (A0)(X),
                             ((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type; 
    NT2_FUNCTOR_CALL(1)
      {
        typedef typename meta::as_logical<A0>::type bA0; 
        A0 sgngam = One<A0>(); //positive
        A0 r =  Nan<A0>(), r2=  Nan<A0>();
        A0 q =  nt2::abs(a0);
        A0 x = a0;
        bA0 test0 = gt(q, Fastgammalargelim<A0>());
        uint32_t nb = 0;
        if ((nb = (nbtrue(test0) > 0)))
          {
            bA0 negative = is_ltz(a0);
            A0 s =  stirling(q);
            uint32_t nb1 = 0;
            A0 r1 = {{}};
            if ((nb1 = (nbtrue(negative) > 0)))
              {
                A0 p = floor(q);
                //              A0 test1 = is_equal(p, q); //must return Nan<A0>();
                sgngam = negif(is_even(p), sgngam);
                A0 z = q - p;
                bA0 test2 = lt(z, Half<A0>() );
                p = seladd(test2, p, One<A0>());
                z = sel(test2, q - p, z);
                z = q*sinpi(z);
                //              A0 test3 = is_eqz(z);
                z =  nt2::abs(z);
                r1 = sgngam*Pi<A0>()/(z * s );
                if (nb1 >= meta::cardinal_of<A0>::value) return r1;
              }
            r2 = sel(negative, r1, s);
          }
        if (nb >= meta::cardinal_of<A0>::value) return r2;
        A0 y2 =  other(test0, x); // computation result if ~test0
        r = sel(test0, r2, y2);
        return if_nan_else(is_nan(a0), r); 
        
      }    
  private :
    template < class bAA0, class AA0 >
      static inline AA0 other(const bAA0& test, const AA0& xx)
      {
        typedef typename meta::scalar_of<AA0>::type sA0; 
        static boost::array<sA0, 7> P = {{
            sA0(1.60119522476751861407E-4),
            sA0(1.19135147006586384913E-3),
            sA0(1.04213797561761569935E-2),
            sA0(4.76367800457137231464E-2),
            sA0(2.07448227648435975150E-1),
            sA0(4.94214826801497100753E-1),
            sA0(9.99999999999999996796E-1)
          }};
        static boost::array<sA0, 8>  Q = {{
            sA0(-2.31581873324120129819E-5),
            sA0(5.39605580493303397842E-4),
            sA0(-4.45641913851797240494E-3),
            sA0(1.18139785222060435552E-2),
            sA0(3.58236398605498653373E-2),
            sA0(-2.34591795718243348568E-1),
            sA0(7.14304917030273074085E-2),
            sA0(1.00000000000000000320E0)
          }};
        AA0 x =  sel(test, Five<A0>()/Two<A0>(), xx);
        AA0 z = One<A0>();
        bAA0 test1;
        while( nt2::any(test1 = ge(x,Three<A0>())) )
          {
            x = seladd(test1, x, Mone<A0>());
            z = sel(   test1, z*x, z);
          }
        bAA0 test2;
        while( nt2::any(test2 = is_ltz(x)) )
          {
            z = sel(   test2, z/x, z);
            x = seladd(test2, x, One<A0>());
          }
        while( nt2::any(test1 =lt(x,Two<A0>())) )
          {
            z = sel(   test1, z/x, z);
            x = seladd(test1, x, One<A0>());
          }
        x -= Two<A0>();
        AA0 p = polevl(x,P);
        AA0 q = polevl(x,Q);
        return z*p/q;        
      }
  };
} }

#endif
