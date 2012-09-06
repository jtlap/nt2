//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_FDLIBM_FUNCTIONS_SCALAR_FREXP_HPP_INCLUDED
#define NT2_TOOLBOX_FDLIBM_FUNCTIONS_SCALAR_FREXP_HPP_INCLUDED
#include <nt2/toolbox/fdlibm/functions/frexp.hpp>
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
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::fdlibm::tag::frexp_, tag::cpu_,
			     (A0)(A1),
                       (scalar_<double_<A0> > )
		       (scalar_<int32_<A1> > )
                      )
  {
    typedef A0 result_type;
    
    inline result_type operator()(A0 const& a0,A1 & a1) const
    {
      return fd_frexp(a0, &a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::fdlibm::tag::frexp_, tag::cpu_,
                       (A0),
                       (scalar_<double_<A0> > )
                      )
  {
    typedef boost::fusion::vector<A0, nt2::int32_t>    result_type;
    
    NT2_FUNCTOR_CALL(1)
    {
      result_type res; 
      boost::fusion::at_c<0>(res) =nt2::fdlibm::frexp(a0, boost::fusion::at_c<1>(res));
      return res; 
    }
  };
} }
#endif
