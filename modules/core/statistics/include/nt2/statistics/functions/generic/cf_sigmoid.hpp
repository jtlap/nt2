//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_GENERIC_CF_SIGMOID_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_GENERIC_CF_SIGMOID_HPP_INCLUDED
#include <nt2/statistics/functions/cf_sigmoid.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/bitofsign.hpp>
#include <nt2/include/functions/bitwise_xor.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_greater_equal.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/copysign.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/splat.hpp>

#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/five.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/fifteen.hpp>
#include <nt2/include/constants/six.hpp>

namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( cf_sigmoid_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    // sigmoid is 0.5*tanh(x/2)+0.5
    NT2_FUNCTOR_CALL(1)
    {
      A0 _28 = splat<A0>(28);
      A0 _63 = splat<A0>(63);
      A0 _105= splat<A0>(105);
      A0 _945 = splat<A0>(945);
      A0 oo_30 = splat<A0>(1.0/30.0);
      A0 x = a0*Half<A0>();
      A0 x2 = sqr(x);
      //     A0 z = fma(Half>A0>(), x*(x2+Fifteen<A0>())/fma(Six<A0>(), x2, Fifteen<A0>()), Half<A0>());

      A0 z = fma(oo_30, (x*(fma(x2 + _105, x2, _945))/(fma(x2 + _28, x2,_63))), Half<A0>());
      return if_zero_else(is_ltz(z), if_else(ge(z, One<A0>()), One<A0>(), z));
      // z approximate tanh(abs(x)/2) with the beginning of lambert formula
    }
  };

} }

// q =  105 43 1
// p =  105 8
//  (a*(a^4 + 105*a^2 + 945))/(15*(a^4 + 28*a^2 + 63))
#endif
