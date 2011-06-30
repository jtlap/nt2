//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_SINCOSPI_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_SINCOSPI_HPP_INCLUDED
#include <boost/fusion/tuple.hpp>
#include <nt2/toolbox/trigonometric/function/scalar/impl/trigo.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION(tag::sincospi_, tag::cpu_,
                          (A0),
                          (scalar_ < arithmetic_<A0> > )
                         )
  {
      typedef typename meta::result_of<meta::floating(A0)>::type etype;
      typedef boost::fusion::tuple<etype, etype>           result_type;
    
    NT2_FUNCTOR_CALL(1)
    {
      return sincospi(etype(a0));
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is real_
/////////////////////////////////////////////////////////////////////////////


  NT2_FUNCTOR_IMPLEMENTATION(tag::sincospi_, tag::cpu_,
                          (A0),
                          (scalar_ < real_<A0> > )
                         )
  {
      typedef typename meta::strip<A0>::type           etype;
      typedef boost::fusion::tuple<etype, etype> result_type;
    
    NT2_FUNCTOR_CALL(1)
    {
      result_type res;
      typedef typename meta::result_of<meta::floating(A0)>::type etype;
      impl::trig_base < A0,pi_tag
                      , trig_tag,tag::not_simd_type
                      >::sincosa( a0
                                , boost::fusion::at_c<0>(res)
                                , boost::fusion::at_c<1>(res)
                                );
      return res;
    }
  };
} }
#endif
