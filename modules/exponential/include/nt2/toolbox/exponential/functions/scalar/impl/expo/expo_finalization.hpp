//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_EXPO_EXPO_FINALIZATION_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_EXPO_EXPO_FINALIZATION_HPP_INCLUDED
#include <nt2/include/functions/fast_ldexp.hpp>
#include <nt2/include/functions/fast_toint.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_flint.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/genmask.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/round2even.hpp>
#include <nt2/include/functions/logical_and.hpp>

namespace nt2
{
  namespace details
  {
    namespace internal
    {
      template < class A0, class expo_tag, class speed_tag> struct exp_finalization{};

      template < class A0, class speed_tag> struct exp_finalization < A0, natural_tag, speed_tag>
      {
        static inline A0 finalize(const A0&, const A0& x,
                                  const A0& c, const A0 & k,
                                  const A0& hi,const A0& lo)
        {
          A0 y =   oneminus(((lo-(x*c)/(Two<A0>()-c))-hi));
          return fast_ldexp(y, fast_toint(k));
        }
      };
      template < class A0 > struct exp_finalization < A0, two_tag, fast_tag>
      {
        static inline A0 finalize(const A0&, const A0& x,
                                  const A0& c, const A0 & k,
                                  const A0& ,const A0& )
        {
          A0 y = oneminus(((-(x*c)/(Two<A0>()-c))-x));
          return fast_ldexp(y, fast_toint(k));
        }
      };
      template < class A0 > struct exp_finalization < A0, two_tag, accu_tag>
      {
        static inline A0 finalize(const A0& a0, const A0& x,
                                  const A0& c, const A0 & k,
                                  const A0& ,const A0& )
        {
          A0 y = oneminus(((-(x*c)/(Two<A0>()-c))-x));
          y = fast_ldexp(y, fast_toint(k));
          // adjust for 2^n n flint
          return  select(logical_and(is_gtz(a0), is_flint(a0)),  round2even(y), y);
        }
      };

      template < class A0 > struct exp_finalization < A0, ten_tag, accu_tag>
      {
        static inline A0 finalize(const A0& a0, const A0&  ,
                                  const A0& c , const A0& k,
                                  const A0&   , const A0& )
        {
          A0 y = fast_ldexp(c, fast_toint(k));
          //adjust for 10^n n flint
          return  if_else(l_and(is_gtz(a0), is_flint(a0)),  round2even(y), y);
        }
      };

    }
  }
}


#endif
