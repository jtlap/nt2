//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_EXPO_EXPO_FINALIZATION_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_EXPO_EXPO_FINALIZATION_HPP_INCLUDED

#include <nt2/include/functions/simd/fast_ldexp.hpp>
#include <nt2/include/functions/simd/toint.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/include/functions/simd/is_flint.hpp>
#include <nt2/include/functions/simd/is_gtz.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/round2even.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/include/constants/nbmantissabits.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/two.hpp>

// 4/4/2013 adding "scale" to properly treat denormal use in returns computation
// for float for instance it treats differently  entries roughly between -87.6 and -87.25
// perhaps it will be necessary to check if this function can be accelerated,  using
// only one call to fast_ldexp by precomputing the shift and the multiplicative factor

namespace nt2
{
  namespace details
  {
    template < class A0, class iA0> static
    inline A0 scale(A0 const & y, const iA0& ik)
    {
      return nt2::if_else(gt(ik, -nt2::Nbmantissabits<A0>()),
                          nt2::fast_ldexp(y, ik),
                          nt2::fast_ldexp(y, ik+nt2::Nbmantissabits<A0>())*nt2::Eps<A0>() // denormal case
                         );
    }

    template < class A0, class expo_tag, class speed_tag> struct exp_finalization{};

    template < class A0, class speed_tag> struct exp_finalization < A0, natural_tag, speed_tag>
    {
      static inline A0 finalize(const A0&, const A0& x,
                                const A0& c, const A0 & k,
                                const A0& hi,const A0& lo)
      {
        A0 y =   nt2::oneminus(((lo-(x*c)/(nt2::Two<A0>()-c))-hi));
        return scale(y, nt2::toint(k));
      }
    };

    template < class A0 > struct exp_finalization < A0, two_tag, fast_tag>
    {
      static inline A0 finalize(const A0&, const A0& x,
                                const A0& c, const A0 & k,
                                const A0& ,const A0& )
      {
        A0 y = nt2::oneminus(((-(x*c)/(nt2::Two<A0>()-c))-x));
        return scale(y, nt2::toint(k));
      }
    };

    template < class A0 > struct exp_finalization < A0, two_tag, accu_tag>
    {
      static inline A0 finalize(const A0& a0, const A0& x,
                                const A0& c, const A0 & k,
                                const A0& ,const A0& )
      {
        A0 y = nt2::oneminus(((-(x*c)/(nt2::Two<A0>()-c))-x));
        y = scale(y, nt2::toint(k));
        // adjust for 2^n n flint
        return  nt2::if_else(nt2::logical_and(nt2::is_gtz(a0),
                                              nt2::is_flint(a0)),
                             nt2::round2even(y), y);
      }
    };

    template < class A0 > struct exp_finalization < A0, ten_tag, accu_tag>
    {
      static inline A0 finalize(const A0& a0, const A0&  ,
                                const A0& c , const A0& k,
                                const A0&   , const A0& )
      {
          A0 y = scale(c, toint(k));
          //adjust for 10^n n flint
          return  nt2::if_else(nt2::logical_and(nt2::is_gtz(a0),
                                                nt2::is_flint(a0)),
                               nt2::round2even(y), y);
        }
    };
  }
}

#endif
