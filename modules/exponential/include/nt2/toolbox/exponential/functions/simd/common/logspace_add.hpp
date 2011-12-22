//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_LOGSPACE_ADD_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_LOGSPACE_ADD_HPP_INCLUDED
#include <nt2/include/functions/logspace_add.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/log1p.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/tofloat.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::logspace_add_, tag::cpu_
                            , (A0)(X)
                            , ((simd_< arithmetic_<A0>, X>))((simd_< arithmetic_<A0>, X >))
                            )
  {
    typedef typename meta::result_of<meta::floating(A0)>::type result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return nt2::logspace_add(tofloat(a0), tofloat(a1));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::logspace_add_, tag::cpu_
                            , (A0)(X)
                            , ((simd_< floating_<A0>, X >))((simd_< floating_<A0>, X >))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      A0 tmp = -nt2::abs(a0-a1); 
      return if_else(is_nan(tmp), a0+a1, nt2::max(a0,a1)+nt2::log1p(nt2::exp(tmp))); 
    }
  };
} }

#endif
