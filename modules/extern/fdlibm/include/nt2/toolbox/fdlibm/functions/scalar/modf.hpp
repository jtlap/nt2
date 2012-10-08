//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_FDLIBM_FUNCTIONS_SCALAR_MODF_HPP_INCLUDED
#define NT2_TOOLBOX_FDLIBM_FUNCTIONS_SCALAR_MODF_HPP_INCLUDED
#include <nt2/toolbox/fdlibm/functions/modf.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/vector.hpp>
#include <nt2/sdk/meta/strip.hpp>
  extern "C"{
    extern double fd_modf ( double,double* );
  }
/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is double_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::fdlibm::tag::modf_, tag::cpu_,
                      (A0),
                      (scalar_<double_<A0> > )
	              (scalar_<double_<A0> > )		     
                     )
  {
    typedef A0       result_type;
    
    inline result_type operator()(A0 const& a0,A0 & a1) const
    {      
      return ::fd_modf(a0, &a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::fdlibm::tag::modf_, tag::cpu_,
                      (A0),
                      (scalar_<double_<A0> > )
                     )
  {
    typedef boost::fusion::vector<A0, A0>        result_type;
    NT2_FUNCTOR_CALL(1)
    {      
      result_type res;
      boost::fusion::at_c<0>(res) = nt2::fdlibm::modf(a0, boost::fusion::at_c<1>(res));
      return res;
    }
  };
} }
#endif
