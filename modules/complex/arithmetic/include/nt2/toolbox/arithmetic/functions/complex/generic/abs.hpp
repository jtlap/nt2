//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_ABS_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_ABS_HPP_INCLUDED
#include <nt2/toolbox/arithmetic/functions/abs.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/hypot.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/is_less.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/exponent.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/unary_minus.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::abs_, tag::cpu_, (A0)
                            , (generic_< complex_< floating_<A0> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type       result_type;
    NT2_FUNCTOR_CALL(1)
    {
    typedef typename meta::as_integer<result_type>::type itype; 
      //      return hypot(real(a0),imag(a0));
      result_type r =  nt2::abs(real(a0));
      result_type i =  nt2::abs(imag(a0));
      itype e =  if_else(lt(r, i), exponent(i), exponent(r));
      return ldexp(sqrt(sqr(ldexp(r, -e))+sqr(ldexp(i, -e))), e); 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::abs_, tag::cpu_, (A0)
                            , (generic_< imaginary_< floating_<A0> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::abs(imag(a0)); 
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::abs_, tag::cpu_, (A0)
                            , (generic_< dry_< floating_<A0> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::abs(a0); 
    }
  };  
} }

#endif
