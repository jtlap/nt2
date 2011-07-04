//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_MODF_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_MODF_HPP_INCLUDED
#include <boost/fusion/tuple.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/trunc.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/vector.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
    NT2_FUNCTOR_IMPLEMENTATION_IF( tag::modf_, tag::cpu_, (A0)(A1)(A2)(X)
				  ,( boost::mpl::and_ <
				     boost::is_same<A0,A1>, 
				     boost::is_same<A0,A2>
				     >
				  )
                                , ( tag::modf_
				    ( simd_<arithmetic_<A0>,X> 
				      , simd_<arithmetic_<A1>,X>
				      , simd_<arithmetic_<A2>,X>  
				      )
				    )
			    , ((simd_< arithmetic_<A0>, X>))
			      ((simd_< arithmetic_<A1>, X>))    
			      ((simd_< arithmetic_<A2>, X>))
                            )
  {
    typedef void result_type;
    inline void operator()(A0 const& a0,A1 & r0,A2 & r1) const
      {
	r1 = nt2::trunc(a0);
	r0 = a0-r1;    
      }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION_IF( tag::modf_, tag::cpu_, (A0)(A1)(X)
				  ,(boost::is_same<A0,A1>)
                                , ( tag::modf_
				    ( simd_<arithmetic_<A0>,X> 
				      , simd_<arithmetic_<A1>,X>
				      )
				    )
			    , ((simd_< arithmetic_<A0>, X>))
			      ((simd_< arithmetic_<A1>, X>))    
                            )
  {
    typedef A0 result_type;
    inline void operator()(A0 const& a0,A1 & r1) const
      {
	r1 = nt2::trunc(a0);
	return a0-r1;    
      }
  };

    
  NT2_FUNCTOR_IMPLEMENTATION(tag::modf_, tag::cpu_,
                       (A0)(X),
                       ((simd_<arithmetic_<A0>,X>))
                      )
  {
      typedef typename meta::strip<A0>::type                A00;
      typedef boost::fusion::vector<A00, A00>       result_type;
    
    NT2_FUNCTOR_CALL_REPEAT(1)
    {
      result_type res;
      nt2::modf(a0,boost::fusion::at_c<0>(res),boost::fusion::at_c<1>(res));
      return res;
    }
  };
} }
#endif
