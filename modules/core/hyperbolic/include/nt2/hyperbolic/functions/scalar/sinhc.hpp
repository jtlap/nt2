//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_SCALAR_SINHC_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_SCALAR_SINHC_HPP_INCLUDED
#include <nt2/hyperbolic/functions/sinhc.hpp>
#include <nt2/hyperbolic/functions/details/sinhc_kernel.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/maxlog.hpp>
#include <nt2/include/constants/log_2.hpp>
#include <nt2/include/functions/scalar/exp.hpp>
#include <nt2/include/functions/scalar/if_else.hpp>
#include <nt2/include/functions/scalar/average.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <boost/simd/sdk/config.hpp>
#ifndef BOOST_SIMD_NO_INFINITIES
#include <nt2/include/constants/inf.hpp>
#endif

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sinhc_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      result_type x = nt2::abs(a0);
      #ifndef BOOST_SIMD_NO_INFINITIES
      if (x == Inf<A0>()) return x;
      #endif
      A0 z = Zero<A0>();
      if( x < One<A0>())
      {
        return details::sinhc_kernel<A0>::compute(sqr(x));
      }
      else
      {
        bool test1 = (x >  Maxlog<A0>()-Log_2<A0>());
        A0 fac = if_else(test1, Half<A0>(), One<A0>());
        A0 tmp = exp(x*fac);
        A0 tmp1 = (Half<A0>()*tmp)/x;
        return if_else(test1, tmp1*tmp, average(tmp, -rec(tmp))/x);
      }
     }
  };

} }


#endif
