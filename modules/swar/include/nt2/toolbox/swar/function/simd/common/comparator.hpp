//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_COMMON_COMPARATOR_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_COMMON_COMPARATOR_HPP_INCLUDED
#include <boost/mpl/vector.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/any.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  //TODO A0 == A1
  NT2_FUNCTOR_IMPLEMENTATION(tag::comparator_, tag::cpu_,
                             (A0)(A1)(A2)(X),
                             ((simd_<arithmetic_<A0>,X>))
                             ((simd_<arithmetic_<A1>,X>))
                             ((scalar_<integer_<A2> >))
                            )
  {
    typedef typename meta::strip<A0>::type                       nA0;
    typedef boost::fusion::vector<nA0,nA0,int>           result_type;
    
    NT2_FUNCTOR_CALL(3)
    {
      typedef result_type r_t;
      r_t res;
      if (a2)
	{
	  boost::fusion::at_c<1>(res) =  nt2::min(a0, a1);
	  boost::fusion::at_c<0>(res) =  nt2::max(a0, a1);
	}
      else
	{
	  boost::fusion::at_c<0>(res) =  nt2::min(a0, a1);
	  boost::fusion::at_c<1>(res) =  nt2::max(a0, a1);
	}
      boost::fusion::at_c<2>(res) = nt2::any(a0-boost::fusion::at_c<0>(res)); 
      return res; 
    }
  };
} }
#endif
