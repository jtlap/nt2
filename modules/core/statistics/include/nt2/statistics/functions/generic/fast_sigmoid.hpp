//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_GENERIC_FAST_SIGMOID_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_GENERIC_FAST_SIGMOID_HPP_INCLUDED
#include <nt2/statistics/functions/fast_sigmoid.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/is_greater_equal.hpp>
#include <nt2/include/functions/if_else.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( fast_sigmoid_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      A0 _32 = splat<A0>(32);
      A0 oneo_32 =  splat<A0>(1.0/32.0);
      return if_else(nt2::ge(a0, _32)
                    , One<A0>()
                    , nt2::rec(nt2::oneplus(nt2::sqr(nt2::sqr(nt2::sqr(nt2::sqr(nt2::sqr(oneminus(a0*oneo_32)))))))));
    }
  };

} }

#endif
