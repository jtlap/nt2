//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SIMD_COMMON_FAST_SINCOSPI_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SIMD_COMMON_FAST_SINCOSPI_HPP_INCLUDED
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/toolbox/trigonometric/function/simd/common/impl/trigo.hpp>
/////////////////////////////////////////////////////////////////////////////
// reference based Implementation
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION_IF(tag::fast_sincospi_, tag::cpu_,(A0)(A1),
                             (boost::mpl::equal_to<boost::mpl::sizeof_<A0>, 
  			                           boost::mpl::sizeof_<A1> >), 
                             ( tag::sincospi_
                                          ( simd_<arithmetic_<A0>,X> 
					  , simd_<real_<A1>,X>
				          , simd_<real_<A1>,X>
                                          )
                             ), 
			     (simd_ < arithmetic_<A0> > )
			     (simd_ < real_<A1> > )
			     (simd_ < real_<A1> > )
			     )
  {
    typedef void result_type;    
    inline result_type operator()(A0 const& a0,A1 & a1,A1 & a2) const
    {
      impl::trig_base <A1,pi_tag,fast_tag,
	               tag::simd_type>::sincosa(tofloat(a0),a1,a2); 
    }
  };

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type  is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTOR_IMPLEMENTATION(tag::fast_sincospi_, tag::cpu_,
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
      impl::trig_base < type,pi_tag
        , fast_tag, tag::simd_type
        >::sincosa( a0
                  , boost::fusion::at_c<0>(res)
                  , boost::fusion::at_c<1>(res)
                  );
      return res;
    }
  };
} }
#endif
