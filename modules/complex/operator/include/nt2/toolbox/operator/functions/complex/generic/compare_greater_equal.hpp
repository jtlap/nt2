//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTIONS_COMPLEX_GENERIC_COMPARE_GREATER_EQUAL_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTIONS_COMPLEX_GENERIC_COMPARE_GREATER_EQUAL_HPP_INCLUDED

#include <nt2/toolbox/operator/functions/compare_greater_equal.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <nt2/include/functions/compare_less.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/imaginary.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/imaginary.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::compare_greater_equal_, tag::cpu_, (A0), 
                                     ((generic_ < complex_< arithmetic_ <A0> > > ))
                                     ((generic_ < complex_< arithmetic_ <A0> > > ))     
                      )
  {
    typedef typename meta::as_real<A0>::type    rA0; 
    typedef typename meta::scalar_of<rA0>::type  sA0; 
    typedef typename meta::as_logical<sA0>::type result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return result_type(!compare_less(a0, a1)); 
    }
  };
} }

#endif
