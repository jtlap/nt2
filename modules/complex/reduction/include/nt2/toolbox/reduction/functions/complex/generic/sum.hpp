//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTIONS_COMPLEX_GENERIC_SUM_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTIONS_COMPLEX_GENERIC_SUM_HPP_INCLUDED
#include <nt2/toolbox/reduction/functions/sum.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_imaginary.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sum_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type rtype;
    typedef typename meta::scalar_of<rtype>::type stype;
    typedef typename meta::as_complex<stype>::type result_type; 
    NT2_FUNCTOR_CALL(1)
    {
      return result_type(sum(real(a0)), sum(imag(a0)));  
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sum_, tag::cpu_, (A0)
                            , (generic_< imaginary_< arithmetic_<A0> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type rtype;
    typedef typename meta::scalar_of<rtype>::type stype;
    typedef typename meta::as_imaginary<stype>::type result_type; 
    NT2_FUNCTOR_CALL(1)
    {
      return result_type(nt2::sum(imag(a0))); 
    }
  };
  
} }

#endif
