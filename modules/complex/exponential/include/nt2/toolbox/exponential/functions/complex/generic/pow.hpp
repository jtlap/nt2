//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_POWONENTIAL_FUNCTIONS_COMPLEX_GENERIC_POW_HPP_INCLUDED
#define NT2_TOOLBOX_POWONENTIAL_FUNCTIONS_COMPLEX_GENERIC_POW_HPP_INCLUDED
#include <nt2/toolbox/powonential/functions/pow.hpp>
#include <nt2/toolbox/powonential/functions/sincos.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
                            , (A0)
                            , (generic_< complex_<floating_<A0> > >)
                              (generic_< complex_<floating_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type rtype;
      rtype r =  nt2::abs(a0);
      rtype i = arg(a0);
      ltype test =  is_real(a0);
      rtype rho =  nt2::log(r);
      rtype theta =  seladd(logical_not(test), i*real(a1), rho*imag(a1));
      rho = if_else(is_real(a0), pow(r, real(a1)),  exp (rho *real(a1) - i * imag(a1)));
      rtype c, s; 
      sincos(theta, c, s)
      return result_type(c, s)*rho; 
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
                              , (A0)(A1)
                              , (generic_< complex_<floating_<A0> > >)
                                (generic_< arithmetic_<floating_<A1> > >)
                            )
  {
    typedef A0  result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type rtype;
      rtype rho = pow(nt2::abs(a0), a1);
      rtype theta = arg(a0)*a1;
      sincos(theta, c, s)
      return result_type(c, s)*rho; 
 
    }
  };
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
//                               , (A0)(A1)
//                               , (generic_< arithmetic_<floating_<A1> > >)
//                                 (generic_< complex_<floating_<A0> > >)
//                             )
//   {
//     typedef A0  result_type;
//     NT2_FUNCTOR_CALL(1)
//     {
//       typedef typename meta::as_real<A0>::type rtype;
//       rtype rho = pow(nt2::abs(a0), real(a1));
//       rtype theta = arg(a0)*real(a1)+imag(a1)*nt2::log(rho);
//       sincos(theta, c, s)
//       return result_type(c, s)*rho; 
 
//     }
//   };

//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
//                             , (A0)
//                             , (generic_< complex_<floating_<A0> > >)
//                             , (generic_< imaginary_<floating_<A0> > >)
//                             )
//   {
//     typedef typename meta::as_real<A0>::type             rtype; 
//     typedef typename meta::as_complex<rtype>::type result_type;
//     NT2_FUNCTOR_CALL(1)
//     {
//       typedef typename meta::as_real<A0>::type rtype;
//       rtype r =  nt2::abs(a0);
//       rtype i = arg(a0);
//       ltype test =  is_real(a0);
//       rtype rho =  nt2::log(r);
//       rtype theta =  seladd(logical_not(test), i*real(a1), rho*imag(a1));
//       rho = if_else(is_real(a0), pow(r, real(a1)),  exp (rho *real(a1) - i * imag(a1)));
//       rtype c, s; 
//       sincos(theta, c, s)
//       return result_type(c, s)*rho; 
 
//     }
//   };  
} }


#endif
