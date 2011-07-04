//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SIMD_COMMON_FAST_SINCOS_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SIMD_COMMON_FAST_SINCOS_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/sdk/meta/strip.hpp>
 #include <nt2/toolbox/trigonometric/function/simd/common/impl/trigo.hpp>
/////////////////////////////////////////////////////////////////////////////
// reference based Implementation
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION_IF(tag::fast_sincos_, tag::cpu_,(A0)(A1)(X),
				(boost::mpl::equal_to<meta::cardinal_of<A0>, 
			                	 meta::cardinal_of<A1>
				        >
				), 
                                ( tag::fast_sincos_
				  ( simd_<arithmetic_<A0>,X> 
				    , simd_<real_<A1>,X>
				    , simd_<real_<A1>,X>
				    )
				  ), 
				((simd_ < arithmetic_<A0>,X > ))
				((simd_ < real_<A1>,X > ))
				((simd_ < real_<A1>,X > ))
			     )
  {
    typedef int result_type;    
    inline result_type operator()(A0 const& a0,A1 & a1,A1 & a2) const
    {
      impl::trig_base <A1,radian_tag,fast_tag,
	               tag::simd_type>::sincosa(tofloat(a0),a1,a2); 
    }
  };

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type  is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTOR_IMPLEMENTATION(tag::fast_sincos_, tag::cpu_,
                              (A0)(X),
                              ((simd_<arithmetic_<A0>,X>))
                             )
  {
      typedef typename meta::as_real<A0>::type  rtype;
      typedef boost::fusion::tuple<rtype, rtype> result_type;
    
    NT2_FUNCTOR_CALL_REPEAT(1)
    {
      typedef result_type rtype;
      rtype res;
      typedef typename  boost::fusion::result_of::value_at_c<rtype,0>::type type;
      impl::trig_base < type,radian_tag
                      , fast_tag, tag::simd_type
      >::sincosa( tofloat(a0)
                , boost::fusion::at_c<0>(res)
                , boost::fusion::at_c<1>(res)
                );
      return res;
    }
  };
} }
#endif
