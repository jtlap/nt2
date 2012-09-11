//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_FDLIBM_FUNCTIONS_SCALAR_FINITE_HPP_INCLUDED
#define NT2_TOOLBOX_FDLIBM_FUNCTIONS_SCALAR_FINITE_HPP_INCLUDED
#include <nt2/toolbox/fdlibm/functions/finite.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/simd/logical.hpp>

extern "C" { extern bool fd_finite ( double ); }

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::fdlibm::tag::finite_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef result_type base;
      typedef typename meta::upgrade<base>::type  type;
      return result_type(nt2::fdlibm::finite(type(a0)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::fdlibm::tag::finite_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
      { return result_type(::fd_finite(a0)); }
  };
} }


#endif
