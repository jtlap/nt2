//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_GENERIC_LIN_SIGMOID_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_GENERIC_LIN_SIGMOID_HPP_INCLUDED
#include <nt2/statistics/functions/lin_sigmoid.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/constants/quarter.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( lin_sigmoid_, tag::cpu_
                              , (A0)
                              , (generic_< floating_<A0> >)
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return min(One<A0>(), max(Zero<A0>(), fma(Quarter<A0>(), a0, Half<A0>())));
    }
  };

} }

#endif
