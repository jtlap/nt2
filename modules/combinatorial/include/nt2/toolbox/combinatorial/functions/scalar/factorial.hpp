/*******************************************************************************
 *         Copyright 2003-2011 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_COMBINATORIAL_FUNCTIONS_SCALAR_FACTORIAL_HPP_INCLUDED
#define NT2_TOOLBOX_COMBINATORIAL_FUNCTIONS_SCALAR_FACTORIAL_HPP_INCLUDED
#include <nt2/include/functions/gamma.hpp>
#include <nt2/include/functions/trunc.hpp>
#include <nt2/include/functions/round.hpp>
#include <nt2/include/functions/abss.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::factorial_, tag::cpu_,
		      (A0),
		      (scalar_ < arithmetic_<A0> > )
		      )
  {
    typedef A0  result_type; 
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename boost::dispatch::meta::as_floating<A0>::type ftype;
      typedef typename meta::upgrade<ftype>::type uftype; 
      const ftype r = static_cast<ftype>(nt2::gamma(nt2::trunc(nt2::abss(static_cast<uftype>(a0)))+One<uftype>()));
      return r > Valmax<A0>() ? Inf<A0>() : static_cast<A0>(nt2::round(r)); 
    }
  };
} }
#endif
