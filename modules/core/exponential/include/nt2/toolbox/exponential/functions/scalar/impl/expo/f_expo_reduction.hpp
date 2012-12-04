//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_EXPO_F_EXPO_REDUCTION_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_EXPO_F_EXPO_REDUCTION_HPP_INCLUDED
#include <nt2/sdk/simd/logical.hpp>
#include <nt2/include/functions/simd/round.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/is_greater_equal.hpp>
#include <nt2/include/functions/simd/is_less_equal.hpp>

namespace nt2
{
  namespace details
  {
    namespace internal
    {
      template< class A0, class Tag
              , class Base_A0 = typename meta::scalar_of<A0>::type
              >
      struct exp_reduction;

      template<class A0> struct exp_reduction <A0,natural_tag,float>
      {
    typedef typename meta::as_logical<A0>::type bA0;
        static inline bA0 isgemaxlog(const A0 & a0)
        {
          return ge(a0,single_constant<A0,0x42b17218>());
        }

        static inline bA0 isleminlog(const A0 & a0)
        {
          return le(a0,single_constant<A0,0xc2b17218>());
        }

        static inline A0 approx(const A0& x)
        {
      typedef typename meta::scalar_of<A0>::type sA0;
          const A0 t =  sqr(x);
          return  x -
                  t*horner<NT2_HORNER_COEFF_T(sA0, 3,
                                            (0x3888d272, 0xbb360954, 0x3e2aaaaa)
                                           )> (t);
        }

        static inline A0 reduce(const A0& a0, A0& hi, A0& lo, A0& x)
        {
          A0 k = round(Invlog_2<A0>()*a0);
          hi = a0-k*single_constant<A0,0x3f318000>();
          lo = k*single_constant<A0,0xb95e8083>();
          x =  hi-lo;
          return k;
        }
      };

      template < class A0 > struct exp_reduction < A0, two_tag, float>
      {
    typedef typename meta::as_logical<A0>::type bA0;
        static inline bA0 isgemaxlog(const A0 & a0)
        {
          return ge(a0,single_constant<A0,0x42fe0000>());
        }

        static inline bA0 isleminlog(const A0 & a0)
        {
          return le(a0,single_constant<A0,0xc2fe0000>());
        }

        static inline A0 approx(const A0& x)
        {
      typedef typename meta::scalar_of<A0>::type sA0;
          const A0 t =  sqr(x);
          return  x
                 - t*horner<NT2_HORNER_COEFF_T( sA0, 3,
                                             (0x3888d272, 0xbb360954, 0x3e2aaaaa)
                                            )> (t);
    }

        static inline A0 reduce(const A0& a0, const A0&, const A0&, A0& x)
        {
          A0 k = round(a0);
          x = (a0 - k)*Log_2<A0>();
          return k;
        }
      };

      template < class A0 > struct exp_reduction < A0, ten_tag, float>
      {
    typedef typename meta::as_logical<A0>::type bA0;
        static inline bA0 isgemaxlog(const A0 & a0)
        {
          return ge(a0,single_constant<A0,0x4218ec59 >());
        }

        static inline bA0 isleminlog(const A0 & a0)
        {
          return le(a0,single_constant<A0, 0xc2179999 >());
        }

        static inline A0 reduce(const A0& a0, A0&, A0&, A0& x)
        {
          A0 k = round(single_constant<A0,0x40549a78>()*a0);
          x = a0-k*single_constant<A0,0x3e9a0000>();
          x -=  k*single_constant<A0,0x39826a13>();
          return k;
        }

        static inline A0 approx(const A0& x)
        {
          const A0 x2 =  sqr(x);
          A0 y1 = madd(single_constant<A0,0x3e5345fd>(), x2,single_constant<A0,0x3f95eceb>());
          A0 y2 = madd(single_constant<A0,0x3f0ac229>(), x2,single_constant<A0,0x400237b4>());
          y1    = madd(y1, x2, single_constant<A0,0x4029a924>());
          y2    = madd(y2, x2, single_constant<A0,0x40135d8e>());
          return oneplus(x*madd(x, y1, y2));
        }
      };
    }
  }
}


#endif
