//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_GENERIC_SIGMOID_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_GENERIC_SIGMOID_HPP_INCLUDED
#include <nt2/statistics/functions/sigmoid.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/uminus.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( sigmoid_, tag::cpu_
                              , (A0)
                              , (generic_< floating_<A0> >)
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1) { return nt2::rec(nt2::oneplus(nt2::exp(-a0))); }
  };

} }

#endif
