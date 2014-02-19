//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SCALAR_LOG1P_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SCALAR_LOG1P_HPP_INCLUDED

#include <nt2/exponential/functions/log1p.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/config/enforce_precision.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/log.hpp>
#include <nt2/include/functions/scalar/minusone.hpp>
#include <nt2/include/functions/scalar/oneplus.hpp>

#ifndef BOOST_SIMD_NO_INFINITIES
#include <nt2/include/constants/inf.hpp>
#endif

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log1p_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      boost::simd::config::enforce_precision<A0> enforcer;

      if (nt2::abs(a0) < Eps<A0>()) return a0;
      if (Mone<A0>() > a0)   return Nan<A0>();
      #ifndef BOOST_SIMD_NO_INFINITIES
      if (a0 == Inf<A0>())   return Inf<A0>();
      #endif
      result_type u = oneplus(a0);
      result_type uu = u;
      result_type t =(minusone(uu)-a0);
      result_type v = u;
      result_type r =nt2::log(v);
      if (t)
        return r*(a0/minusone(v)); //-t/u; /* cancels errors with IEEE arithmetic */
      else
        return r;
    }
  };
} }

#endif
