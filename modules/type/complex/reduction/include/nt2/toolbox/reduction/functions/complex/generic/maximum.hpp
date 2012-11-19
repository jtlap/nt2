//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTIONS_COMPLEX_GENERIC_MAXIMUM_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTIONS_COMPLEX_GENERIC_MAXIMUM_HPP_INCLUDED

#include <nt2/toolbox/reduction/functions/maximum.hpp>
#include <nt2/include/functions/inbtrue.hpp>
#include <nt2/include/functions/posmax.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/arg.hpp>
#include <nt2/include/functions/at_i.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_imaginary.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>
#include <nt2/sdk/meta/as_logical.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::maximum_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type rtype;
    typedef typename meta::scalar_of<rtype>::type stype;
    typedef typename meta::as_complex<stype>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_logical<rtype>::type ltype;
      rtype absa0 = nt2::abs(a0);
      nt2::int32_t tmp = posmax(absa0);
      ltype test = eq(absa0, absa0[tmp]);
      if (inbtrue(test) > 1)
        {
          rtype z = if_else(test, arg(a0), Minf<rtype>());
          return nt2::at_i(a0, posmax(z));
        }
      return nt2::at_i(a0, tmp);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::maximum_, tag::cpu_, (A0)
                            , (generic_< imaginary_< arithmetic_<A0> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type rtype;
    typedef typename meta::scalar_of<rtype>::type stype;
    typedef typename meta::as_imaginary<stype>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return a0[posmax(nt2::abs(a0))];
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::maximum_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type rtype;
    typedef typename meta::scalar_of<rtype>::type stype;
    typedef typename meta::as_dry<stype>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return a0[posmax(nt2::abs(a0))];
    }
  };

} }

#endif
