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
/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION(tag::modf_, tag::cpu_,
                      (A0),
                      (fundamental_<A0>)
                     )
  {
      typedef typename meta::strip<A0>::type            etype;
      typedef boost::fusion::vector<etype, etype>        result_type;
    
    NT2_FUNCTOR_CALL(1)
    {
      typename NT2_RETURN_TYPE(1)::type res;
      boost::fusion::at_c<1>(res) = trunc(a0);
      boost::fusion::at_c<0>(res)= a0 - boost::fusion::at_c<1>(res);
      return res;
    }
  };
} }
#endif
