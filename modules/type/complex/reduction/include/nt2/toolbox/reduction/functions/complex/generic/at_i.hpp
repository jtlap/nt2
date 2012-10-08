//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTIONS_COMPLEX_GENERIC_AT_I_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTIONS_COMPLEX_GENERIC_AT_I_HPP_INCLUDED

#include <nt2/toolbox/reduction/functions/at_i.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/posmax.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/arg.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_imaginary.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::at_i_, tag::cpu_, (A0)(A1)
                                     , (generic_< complex_< arithmetic_<A0> > >)
                                     ((scalar_<integer_<A1> >))
                                     )
  {
    typedef typename meta::as_real<A0>::type rtype;
    typedef typename meta::scalar_of<rtype>::type stype;
    typedef typename meta::as_complex<stype>::type result_type;
    NT2_FUNCTOR_CALL(2)
      {
        return result_type(nt2::real(a0)[a1], nt2::imag(a0)[a1]);
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::at_i_, tag::cpu_, (A0)(A1)
                                     , (generic_< imaginary_< arithmetic_<A0> > >)
                                     ((scalar_<integer_<A1> >))
                                     )
  {
    typedef typename meta::as_real<A0>::type rtype;
    typedef typename meta::scalar_of<rtype>::type stype;
    typedef typename meta::as_imaginary<stype>::type result_type;
    NT2_FUNCTOR_CALL(2)
      {
        return a0[a1];
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::at_i_, tag::cpu_, (A0)(A1)
                                     , (generic_< dry_< arithmetic_<A0> > >)
                                     ((scalar_<integer_<A1> >))
                                     )
  {
    typedef typename meta::as_real<A0>::type rtype;
    typedef typename meta::scalar_of<rtype>::type stype;
    typedef typename meta::as_dry<stype>::type result_type;
    NT2_FUNCTOR_CALL(2)
      {
        return result_type(nt2::real(a0)[a1]);
      }
  };

} }

#endif
