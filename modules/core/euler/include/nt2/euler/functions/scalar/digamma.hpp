//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SCALAR_DIGAMMA_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SCALAR_DIGAMMA_HPP_INCLUDED

#include <nt2/euler/functions/digamma.hpp>
#include <nt2/euler/functions/details/digamma_kernel.hpp>
#include <nt2/include/constants/digammalargelim.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/scalar/floor.hpp>
#include <nt2/include/functions/scalar/is_greater.hpp>
#include <nt2/include/functions/scalar/is_less.hpp>
#include <nt2/include/functions/scalar/oneminus.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <nt2/include/functions/scalar/selsub.hpp>
#include <nt2/include/functions/scalar/tanpi.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::digamma_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_logical<A0>::type bA0;
      typedef typename meta::scalar_of<A0>::type sA0;
      A0 result = nt2::Zero<A0>();
      A0 x = a0;
      if( a0 <=  result)
      {
        x =  nt2::oneminus(a0);
        result = x - nt2::floor(x);
        result =  nt2::selsub(nt2::gt(result,Half<A0>()),result,nt2::One<A0>());
        if(result) result = nt2::Pi<A0>()/nt2::tanpi(result);
        // we are ready to increment result that was
        // Pi<A0>()/tanpi(remainder) if a0 < 0  and remainder != 0
        // Nan<A0>                   if a0 < 0  and remainder == 0
        // 0                         in any other cases
      }
      if(x > Digammalargelim<A0>())
      { // If we're above the lower-limit for the asymptotic expansion then use it:
        return details::digamma_kernel<A0>::digamma_imp_large(x)+result;
      }
      // If x > 2 reduce to the interval [1,2]:
      bool cond = nt2::gt(x, nt2::Two<A0>());
      A0 r;
      while(cond)
      {
        x      -= nt2::One<A0>();
        result += nt2::rec(x);
        cond = nt2::gt(x, nt2::Two<A0>());
      }
      // If x < 1 use shift to > 1:
      if(nt2::lt(x, nt2::One<A0>()))
      {
        result = -nt2::rec(x);
        x      += nt2::One<A0>();
      }
      return details::digamma_kernel<A0>::digamma_1_2(x)+result;
    }
  };
} }

#endif
