//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Averageributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_AVERAGE_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_AVERAGE_HPP_INCLUDED
#include <nt2/toolbox/arithmetic/functions/average.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/hypot.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::average_, tag::cpu_, (A0)(A1)
                            , (generic_< complex_ < arithmetic_<A0> > > )
                              (generic_< complex_ < arithmetic_<A1> > > )
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return result_type(average(real(a0), real(a1)),average(imag(a0), imag(a1))) ; 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::average_, tag::cpu_, (A0)(A1)
                            , (generic_< dry_ < arithmetic_<A0> > > )
                              (generic_< dry_ < arithmetic_<A1> > > )
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return result_type(average(real(a0), real(a1))) ; 
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::average_, tag::cpu_, (A0)(A1)
                            , (generic_< imaginary_< arithmetic_<A0> > >)
                              (generic_< complex_< arithmetic_<A1> > >)
                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_real<A1>::type rA1;
      return result_type(real(a1)*Half<rA1>(),average(imag(a0), imag(a1))) ; 
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::average_, tag::cpu_, (A0)(A1)
                            ,  (generic_< complex_< arithmetic_<A0> > >)
                               (generic_< imaginary_< arithmetic_<A1> > >)
                             
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_real<A0>::type rA0;
      return result_type(real(a0)*Half<rA0>(),average(imag(a0), imag(a1))) ; 
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::average_, tag::cpu_, (A0)(A1)
                            ,  (generic_< imaginary_< arithmetic_<A0> > >)
                               (generic_< imaginary_< arithmetic_<A1> > >)
                             
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return result_type(average(imag(a0), imag(a1))); 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::average_, tag::cpu_, (A0)(A1)
                            ,  (generic_< arithmetic_<A0> >)
                               (generic_< imaginary_< arithmetic_<A1> > >)
                             
                            )
  {
    typedef typename meta::as_complex<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return result_type(a0, imag(a1))*Half<A0>() ; 
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::average_, tag::cpu_, (A0)(A1)
                            ,  (generic_< dry_ < arithmetic_<A0> > > )
                               (generic_< imaginary_< arithmetic_<A1> > >)
                             
                            )
  {
    typedef typename meta::as_complex<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_real<A0>::type rtype;
      return result_type(real(a0), imag(a1))*Half<rtype>() ; 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::average_, tag::cpu_, (A0)(A1)
                            ,  (generic_< imaginary_< arithmetic_<A0> > >)
                               (generic_< arithmetic_<A1> >)
                             
                            )
  {
    typedef typename meta::as_complex<A1>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return result_type(a1, imag(a0))*Half<A1>() ; 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::average_, tag::cpu_, (A0)(A1)
                            ,  (generic_< imaginary_< arithmetic_<A0> > >)
                               (generic_< dry_ < arithmetic_<A1> > >)
                             
                            )
  {
    typedef typename meta::as_complex<A1>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return result_type(real(a1), imag(a0))*Half<A1>() ; 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::average_, tag::cpu_, (A0)(A1)
                            ,  (generic_< arithmetic_<A0> >)
                               (generic_< complex_< arithmetic_<A1> > >)
                             
                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return result_type(average(real(a0), real(a1)),imag(a1)*Half<A0>()) ; 
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::average_, tag::cpu_, (A0)(A1)
                            ,  (generic_< dry_ < arithmetic_<A0> > >)
                               (generic_< complex_< arithmetic_<A1> > >)
                             
                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(2)
    {
     typedef typename meta::as_real<A0>::type rtype;
       return result_type(average(real(a0), real(a1)),imag(a1)*Half<rtype>()) ; 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::average_, tag::cpu_, (A0)(A1)
                            ,  (generic_< complex_< arithmetic_<A0> > >)
                               (generic_< arithmetic_<A1> >)
                             
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return result_type(average(real(a0), real(a1)),imag(a0)*Half<A1>()) ; 
    }
  };  

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::average_, tag::cpu_, (A0)(A1)
                            ,  (generic_< complex_< arithmetic_<A0> > >)
                               (generic_< dry_ < arithmetic_<A1> > >)
                             
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_real<A1>::type rtype;
      return result_type(average(real(a0), real(a1)),imag(a0)*Half<rtype>()) ; 
    }
  };
} }

#endif
