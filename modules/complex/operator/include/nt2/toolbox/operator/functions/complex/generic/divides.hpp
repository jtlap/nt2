//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTIONS_COMPLEX_GENERIC_DIVIDES_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTIONS_COMPLEX_GENERIC_DIVIDES_HPP_INCLUDED
#include <nt2/toolbox/operator/functions/divides.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/unary_minus.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqr_abs.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/imaginary.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace nt2 { namespace ext
{
  // complex/complex
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::divides_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                              (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      A0 tmp = a0/sqr_abs(a1); 
      return if_else(is_inf(a1), tmp, tmp*conj(a1)); 
    }
  };
  
  // complex/real
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::divides_, tag::cpu_, (A0)(A1)
                            , (generic_< arithmetic_<A0> >)
                              (generic_< complex_< arithmetic_<A1> > >)
                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      A0 tmp = a0/sqr_abs(a1); 
      return if_else(is_inf(a1), tmp, tmp*conj(a1)); 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::divides_, tag::cpu_, (A0)(A1)
                            , (generic_< complex_< arithmetic_<A0> > >)
                              (generic_< arithmetic_<A1> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return result_type(real(a0)/a1, imag(a0)/a1);
    }
  };
  
  // complex/imaginary
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::divides_, tag::cpu_, (A0)(A1)
                            , (generic_< imaginary_< arithmetic_<A0> > >)
                              (generic_< complex_< arithmetic_<A1> > >)
                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      A0 tmp = a0/sqr_abs(a1); 
      return if_else(is_inf(a1), tmp, tmp*conj(a1)); 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::divides_, tag::cpu_, (A0)(A1)
                            , (generic_< complex_< arithmetic_<A0> > >)
                              (generic_< imaginary_< arithmetic_<A1> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return result_type(imag(a0)/imag(a1), -real(a0)/imag(a1));
    }
  };
  
  // imaginary/real
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::divides_, tag::cpu_, (A0)(A1)
                            , (generic_< arithmetic_<A0> >)
                              (generic_< imaginary_< arithmetic_<A1> > >)
                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return result_type(-a0/imag(a1));
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::divides_, tag::cpu_, (A0)(A1)
                            , (generic_< imaginary_< arithmetic_<A0> > >)
                              (generic_< arithmetic_<A1> >)
                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return result_type(imag(a0)/a1);
    }
  };
  
  // imaginary/imaginary
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::divides_, tag::cpu_, (A0)(A1)
                            , (generic_< imaginary_< arithmetic_<A0> > >)
                              (generic_< imaginary_< arithmetic_<A1> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return (imag(a0)/imag(a1));
    }
  };

  // dry/complex
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::divides_, tag::cpu_, (A0)(A1)
                            , (generic_< dry_< arithmetic_<A0> > >)
                              (generic_< complex_< arithmetic_<A1> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type rtype;
    typedef typename meta::as_complex<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return divides(real(a0), a1);
    }
  };
  
  // complex/dry
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::divides_, tag::cpu_, (A0)(A1)
                            , (generic_< complex_< arithmetic_<A0> > > )
                              (generic_< dry_< arithmetic_<A1> > >)
                            )
  {
    typedef typename meta::as_real<A1>::type rtype;
    typedef typename meta::as_complex<A1>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return result_type(real(a0)/real(a1), imag(a0)/real(a1));
    }
  };

  // dry/imaginary
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::divides_, tag::cpu_, (A0)(A1)
                            , (generic_< dry_< arithmetic_<A0> > >)
                              (generic_< imaginary_< arithmetic_<A1> > >)
                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return result_type(-real(a0)/imag(a1));
    }
  };
  
  // imaginary/dry
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::divides_, tag::cpu_, (A0)(A1)
                            , (generic_< imaginary_< arithmetic_<A0> > > )
                              (generic_< dry_< arithmetic_<A1> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return result_type(imag(a0)/real(a1));
    }
  };
  
  // dry/arithmetic
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::divides_, tag::cpu_, (A0)(A1)
                            , (generic_< dry_< arithmetic_<A0> > >)
                              (generic_< arithmetic_<A1> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return result_type(real(a0)/a1);
    }
  };
  
  // arithmetic/dry
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::divides_, tag::cpu_, (A0)(A1)
                            , (generic_< arithmetic_<A0> >)
                              (generic_< dry_< arithmetic_<A1> > >)
                              
                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return result_type(a0/real(a1));
    }
  };  
    
  // dry/dry
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::divides_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > >)
                              (generic_< dry_< arithmetic_<A0> > >)
                              
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return result_type(real(a0)/real(a1));
    }
  };  

} }

#endif
