//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_FUZZY_FUNCTIONS_GENERIC_TOLERANT_TRUNC_HPP_INCLUDED
#define NT2_TOOLBOX_FUZZY_FUNCTIONS_GENERIC_TOLERANT_TRUNC_HPP_INCLUDED
#include <nt2/include/functions/tolerant_floor.hpp>
#include <nt2/include/functions/sign.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tolerant_trunc_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    inline result_type operator()(const A0& a0)
    {
      typedef typename meta::as_logical<result_type>::type ltype; 
      ltype test = is_ltz(a0);
      result_type aa0 = nt2::abs(a0);
      return negif(test, tolerant_floor(aa0));
    }
  };
} }


#endif
