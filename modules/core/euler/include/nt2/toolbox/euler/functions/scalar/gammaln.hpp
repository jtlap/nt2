//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_SCALAR_GAMMALN_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_SCALAR_GAMMALN_HPP_INCLUDED

#include <nt2/toolbox/euler/functions/gammaln.hpp>
#include <boost/simd/sdk/math.hpp>
#include <nt2/include/functions/scalar/is_eqz.hpp>
#include <nt2/include/functions/scalar/is_invalid.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <nt2/sdk/error/policies.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/zero.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gammaln_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      if ((a0 == nt2::Inf<A0>()) || nt2::is_eqz(a0) ) return nt2::Inf<A0>();
      if ((a0 < nt2::Zero<A0>()) || nt2::is_invalid(a0)) return nt2::Nan<A0>();
    #ifdef BOOST_SIMD_HAS_LGAMMA
      return ::lgamma(a0);
    #else
      return boost::math::lgamma(a0, nt2_policy());
    #endif
    }
  };

#ifdef BOOST_SIMD_HAS_LGAMMAF
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gammaln_, tag::cpu_
                            , (A0)
                            , (scalar_< single_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      if ((a0 == nt2::Inf<A0>()) || nt2::is_eqz(a0) ) return nt2::Inf<A0>();
      if ((a0 < nt2::Zero<A0>()) || nt2::is_invalid(a0)) return nt2::Nan<A0>();
      return ::lgammaf(a0);
    }
  };
#endif

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gammaln_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {
    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::gammaln(result_type(a0));
    }
  };
} }


#endif
