//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_SCALAR_DGAMMAINC_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_SCALAR_DGAMMAINC_HPP_INCLUDED

#include <nt2/toolbox/euler/functions/dgammainc.hpp>
#include <nt2/include/functions/scalar/tofloat.hpp>
#include <nt2/include/functions/scalar/exp.hpp>
#include <nt2/include/functions/scalar/log.hpp>
#include <nt2/include/functions/scalar/is_equal.hpp>
#include <nt2/include/functions/scalar/is_eqz.hpp>
#include <nt2/include/functions/scalar/if_zero_else.hpp>
#include <nt2/include/functions/scalar/if_allbits_else.hpp>
#include <nt2/include/functions/scalar/gammaln.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dgammainc_, tag::cpu_
                            , (A0)(A1)
                            , (generic_< arithmetic_<A0> >)
                              (generic_< arithmetic_<A1> >)
                            )
  {
    typedef typename boost::dispatch::meta::as_floating<A0, A1>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::dgammainc(nt2::tofloat(a0), nt2::tofloat(a1));
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dgammainc_, tag::cpu_
                            , (A0)(A1)
                            , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& x, const A1& a) const
    {
      result_type tmp =  nt2::if_zero_else(nt2::is_equal(x, nt2::One<A0>()),
                                           nt2::minusone(a)*nt2::log(x)
                                          );
      tmp =  nt2::if_allbits_else(nt2::is_eqz(a), tmp);
      return nt2::exp(tmp-x-nt2::gammaln(a));
    }
  };
} }

#endif
