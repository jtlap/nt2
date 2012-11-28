/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_GENERIC_UNIFINV_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_GENERIC_UNIFINV_HPP_INCLUDED
#include <nt2/toolbox/statistics/functions/unifinv.hpp>
#include <nt2/include/functions/tsxfun.hpp>
#include <nt2/include/functions/is_gez.hpp>
#include <nt2/include/functions/is_lez.hpp>
#include <nt2/include/functions/is_nle.hpp>
#include <nt2/include/functions/is_ngt.hpp>
#include <nt2/include/functions/is_greater_equal.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/is_less_equal.hpp>
#include <nt2/include/functions/if_allbits_else.hpp>
#include <nt2/include/functions/if_else_zero.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/logical_and.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2 { namespace ext
{


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifinv_, tag::cpu_
                              , (A0)
                              , (generic_< floating_<A0> >)
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
      {
        return if_else(logical_and(is_gez(a0), le(a0, One<A0>())), a0, Nan<A0> ());
      }
  };

 NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifinv_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                              (generic_< floating_<A2> >)
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(3)
      {
        BOOST_AUTO_TPL(z, a2-a1);
        BOOST_ASSERT_MSG(nt2::globalall(is_gtz(z)), "b(s) must be strictly greater than a(s)");
        BOOST_AUTO_TPL(z1, if_allbits_else(logical_or(gt(a0, a2), lt(a0, a1)), z));
        return fma(a0, z1, a1);
      }
  };

} }
#endif
