//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_FDLIBM_FUNCTION_SCALAR_FREXP_HPP_INCLUDED
#define NT2_TOOLBOX_FDLIBM_FUNCTION_SCALAR_FREXP_HPP_INCLUDED
#include <nt2/sdk/meta/upgrade.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
  extern "C"{
    extern double fd_frexp ( double,int* );
  }
/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION(fdlibm::tag::frexp_, tag::cpu_,
                       (A0),
                       (scalar_ < double_<A0> > )
                      )
  {
      typedef typename meta::strip<A0>::type         f_type;
      typedef typename meta::as_integer<A0>::type    i_type; 
      typedef boost::fusion::vector<f_type, i_type>    result_type;
    
    NT2_FUNCTOR_CALL(1)
    {
      typedef result_type rtype;
      rtype res; 
      int r1t;
      boost::fusion::at_c<0>(res) = fd_frexp(a0, &r1t);
      boost::fusion::at_c<1>(res) = r1t;
      return res;
    }
  };
} }
#endif
