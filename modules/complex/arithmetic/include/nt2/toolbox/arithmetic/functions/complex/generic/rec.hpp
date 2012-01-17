//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_REC_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_REC_HPP_INCLUDED
#include <nt2/toolbox/arithmetic/functions/rec.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/is_finite.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/unary_minus.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqr_abs.hpp>
#include <nt2/include/functions/copysign.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/imaginary.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/meta/as_integer.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rec_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<result_type>::type rtype; 
      typedef typename meta::as_integer<rtype>::type itype; 
      rtype rr =  nt2::abs(real(a0));
      rtype ii =  nt2::abs(imag(a0));
      itype e =  -if_else(lt(rr, ii), exponent(ii), exponent(rr));
      A0 aa0 =  nt2::ldexp(a0, e); 
      rtype denom =  sqr_abs(aa0);
      A0 num = conj(aa0);
      A0 r =  ldexp(num/denom, e);
      if (all(is_finite(r))) return r; 
      r = if_else(is_eqz(denom), result_type(copysign(Inf<rtype>(), real(a0)), Zero<rtype>()), r);
      r = if_else(is_inf(a0),    result_type(rec(copysign(denom, real(a0))), Zero<rtype>()), r);
      return r;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rec_, tag::cpu_, (A0)
                            , (generic_< imaginary_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return result_type(-nt2::rec(imag(a0))); 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rec_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return result_type(nt2::rec(real(a0))); 
    }
  };
  
} }

#endif
