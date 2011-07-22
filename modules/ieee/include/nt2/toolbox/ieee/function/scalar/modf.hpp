//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_MODF_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_MODF_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/vector.hpp>
#include <nt2/include/functions/trunc.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION(tag::modf_, tag::cpu_,
                      (A0)(A1),
                      (scalar_ < arithmetic_<A0> > )
                      (scalar_ < arithmetic_<A1> > )
                      (scalar_ < arithmetic_<A1> > )
                     )
  {  
    typedef nt2::int32_t result_type;    
    inline int32_t operator()(A0 const& a0,A1 & r1,A1 & r0) const
    {
      r1 = nt2::trunc(a0);
      r0 = a0 - r1;
      return 0; 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(tag::modf_, tag::cpu_,
                      (A0)(A1),
                      (scalar_ < arithmetic_<A0> > )
                      (scalar_ < arithmetic_<A1> > )
                     )
  {  
    typedef A1 result_type;    
    inline A1 operator()(A0 const& a0,A1 & a1) const
    {
      a1 = trunc(a0);
      return a0 - a1;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(tag::modf_, tag::cpu_,
                      (A0),
                      (scalar_ < arithmetic_<A0> > )
                     )
  {
      typedef typename meta::result_of<meta::floating(A0)>::type                 etype;
      typedef boost::fusion::vector<etype, etype>        result_type;
    
    NT2_FUNCTOR_CALL(1)
    {
      result_type res;
      boost::fusion::at_c<0>(res) = nt2::modf(a0, boost::fusion::at_c<1>(res));
      return res;
    }
  };
} }
#endif
