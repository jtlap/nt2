//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SIMD_COMPLEX_GENERIC_EXPM1_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SIMD_COMPLEX_GENERIC_EXPM1_HPP_INCLUDED
#include <nt2/sdk/simd/logical.hpp>
#include <nt2/include/constants/mtwo.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/logical_notand.hpp>
#include <nt2/include/functions/logical_or.hpp>
#include <nt2/include/functions/is_not_equal.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/is_invalid.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expm1_, tag::cpu_
                            , (A0)
                            , ((generic_<complex_<floating_<A0> > >))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type rA0; 
      typedef typename meta::as_logical<rA0>::type bA0; 
      const A0 u =  nt2::exp(a0);
      const bA0 p = logical_or(is_eqz(u),is_invalid(u)); 
      const A0 y1 = minusone(u);
      const bA0 m = logical_notand(p, is_not_equal(u, One<A0>()));
      const A0 y2 = y1*(a0/nt2::log(u));
      return select(p,y1,select(m, y2, a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expm1_, tag::cpu_
                            , (A0)
                            , ((generic_<imaginary_<floating_<A0> > >))
                            )
  {
    typedef typename meta::as_complex<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type rtype;
      // cos(t)-1 + i sin(t) with  t =  imag(a0)
      return result_type(Mtwo<rtype>()*sqr(nt2::sin(imag(a0)*Half<rtype>()), nt2::sin(imag(a0))));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expm1_, tag::cpu_
                            , (A0)
                            , (generic_< dry_<floating_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return result_type(nt2::expm1(real(a0))); 
    }
  };    
} }


#endif
