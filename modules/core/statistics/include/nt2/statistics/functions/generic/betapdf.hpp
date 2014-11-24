//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_GENERIC_BETAPDF_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_GENERIC_BETAPDF_HPP_INCLUDED
#include <nt2/statistics/functions/betapdf.hpp>
#include <nt2/include/functions/beta.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/logical_or.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/all.hpp>
#include <nt2/include/functions/gt.hpp>
#include <nt2/include/functions/is_lez.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::betapdf_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                              (generic_< floating_<A2> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(3)
      {
        BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gtz(a1)), "a parameter must be positive");
        BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gtz(a2)), "b parameter must be positive");
        return nt2::if_zero_else(logical_or(nt2::is_lez(a0), nt2::gt(a0, One<A0>())),
                                 (nt2::pow(a0, minusone(a1))*nt2::pow(oneminus(a0), minusone(a2)))/beta(a1, a2));
      }
  };

} }

#endif
