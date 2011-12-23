//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_CRLIBM_FUNCTIONS_SCALAR_EXPM1_HPP_INCLUDED
#define NT2_TOOLBOX_CRLIBM_FUNCTIONS_SCALAR_EXPM1_HPP_INCLUDED
#include <nt2/sdk/meta/upgrade.hpp>
  extern "C"{
    extern double expm1_rn ( double );
    extern double expm1_rd ( double );
    extern double expm1_rz ( double );
    extern double expm1_ru ( double );
  };
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::crlibm::tag::expm1_<Rounding>, tag::cpu_,
                       (A0)(Rounding),
                       (scalar_<arithmetic_<A0> > )
                      )
  {
    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef result_type   base;
      typedef typename meta::upgrade<base>::type  type;
      return nt2::crlibm::expm1<Rounding>(type(a0));
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////


  NT2_FUNCTOR_IMPLEMENTATION(nt2::crlibm::tag::expm1_<Rounding>, tag::cpu_,
                       (A0)(Rounding),
                       (scalar_<double_<A0> > )
                      )
  {
    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;
    template<class A, class R> struct inner_expm1;
    NT2_CRLIBM_INNER_STRUCT(rn, expm1, rn)
    NT2_CRLIBM_INNER_STRUCT(rd, expm1, rd)
    NT2_CRLIBM_INNER_STRUCT(ru, expm1, ru)
    NT2_CRLIBM_INNER_STRUCT(rz, expm1, rd)
    NT2_FUNCTOR_CALL(1)
      {return inner_expm1<A0,Rounding>::eval(a0, Rounding()); }
  };
} }
#endif
