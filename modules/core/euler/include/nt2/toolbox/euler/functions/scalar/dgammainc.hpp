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
#include <nt2/toolbox/euler/details/math.hpp>
#include <nt2/toolbox/boost_math/functions/gamma_p_derivative.hpp>
#include <nt2/include/functions/scalar/tofloat.hpp>
#include <nt2/include/functions/scalar/exp.hpp>
#include <nt2/include/functions/scalar/log.hpp>
#include <nt2/include/functions/scalar/is_equal.hpp>
#include <nt2/include/functions/scalar/is_eqz.hpp>
#include <nt2/include/functions/scalar/if_zero_else.hpp>
#include <nt2/include/functions/scalar/if_allbits_else.hpp>
#include <nt2/include/functions/scalar/gammaln.hpp>
#include <nt2/include/constants/one.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type is arithmetic_  dgammainc(x, a)/dx
/////////////////////////////////////////////////////////////////////////////
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
      //return nt2::pow(a1, nt2::minusone(a0))*nt2::exp(-a1)/nt2::gamma(a0);
      //boost_math::gamma_p_derivative(a1, a0);
      result_type tmp =  if_zero_else(is_equal(x, One<A0>()), nt2::minusone(a)*nt2::log(x));
      tmp =  if_allbits_else(is_eqz(a), tmp);
//       std::cout << "tmp " << tmp << std::endl;
//       std::cout << "x   " << x  << " a " << a << std::endl;
//       std::cout << "gln " << nt2::gammaln(a)<< std::endl;
//       std::cout <<(tmp-x-nt2::gammaln(a))<< std::endl;
//       std::cout << nt2::exp(tmp-x-nt2::gammaln(a)) << std::endl;
//       std::cout << boost_math::gamma_p_derivative(a, x) << std::endl;
      return nt2::exp(tmp-x-nt2::gammaln(a));
    }
  };
} }

#endif
