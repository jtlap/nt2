//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_COMPLEX_GENERIC_POW_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_COMPLEX_GENERIC_POW_HPP_INCLUDED
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/sincos.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/seladd.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_real.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/arg.hpp>
#include <nt2/include/functions/logical_not.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/simd/logical.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
                              , (A0)
                            , (generic_< complex_<floating_<A0> > >)
                              (generic_< complex_<floating_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::as_real<result_type>::type rtype;
      result_type tmp = result_type(nt2::log(nt2::abs(a0)), nt2::arg(a0)); 
      tmp = a1*tmp; 
      rtype c, s; 
      sincos(imag(tmp), c, s); 
      return result_type(c, s)*real(tmp); 
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
                              , (A0)(A1)
                              , (generic_< complex_<floating_<A0> > >)
                                (generic_< floating_<A1> >)
                            )
  {
    typedef A0  result_type;
    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_real<result_type>::type rtype;
      result_type tmp = result_type(nt2::log(nt2::abs(a0)), nt2::arg(a0)); 
      tmp = a1*tmp; 
      rtype c, s; 
      sincos(imag(tmp), c, s); 
      return result_type(c, s)*real(tmp); 
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
                              , (A0)(A1)
                              , (generic_< floating_<A0> >)
                                (generic_< complex_<floating_<A1> > >)
                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_real<result_type>::type rtype;
      result_type tmp = result_type(nt2::log(nt2::abs(a0)), nt2::arg(a0)); 
      tmp = a1*tmp; 
      rtype c, s; 
      sincos(imag(tmp), c, s); 
      return result_type(c, s)*real(tmp); 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
                            , (A0)(A1)
                            , (generic_< complex_<floating_<A0> > >)
                              (generic_< imaginary_<floating_<A1> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_real<result_type>::type             rtype; 
      result_type tmp = result_type(nt2::log(nt2::abs(a0)), nt2::arg(a0)); 
      tmp = a1*tmp; 
      rtype c, s; 
      sincos(imag(tmp), c, s); 
      return result_type(c, s)*real(tmp); 
     }
   };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
                            , (A0)(A1)
                            , (generic_< imaginary_<floating_<A0> > >)
                             (generic_< complex_<floating_<A1> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_real<result_type>::type             rtype; 
      result_type tmp = result_type(nt2::log(nt2::abs(a0)), nt2::arg(a0)); 
      tmp = a1*tmp; 
      rtype c, s; 
      sincos(imag(tmp), c, s); 
      return result_type(c, s)*real(tmp); 
     }
   };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
                            , (A0)(A1)
                            , (generic_< imaginary_<floating_<A0> > >)
                              (generic_< floating_<A1> >)
                            )
  {
    typedef meta::as_complex<A1> result_type;
    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_real<result_type>::type             rtype; 
      result_type tmp = result_type(nt2::log(nt2::abs(a0)), nt2::arg(a0)); 
      tmp = a1*tmp; 
      rtype c, s; 
      sincos(imag(tmp), c, s); 
      return result_type(c, s)*real(tmp); 
     }
   };
  
   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
                            , (A0)(A1)
                            ,  (generic_< floating_<A0> >)
                               (generic_< imaginary_<floating_<A1> > >)
                            )
  {
    typedef meta::as_complex<A0> result_type;
    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_real<result_type>::type             rtype;  
      result_type tmp = result_type(nt2::log(nt2::abs(a0)), nt2::arg(a0)); 
      tmp = a1*tmp; 
      rtype c, s; 
      sincos(imag(tmp), c, s); 
      return result_type(c, s)*real(tmp); 
     }
   }; 
} }


#endif
