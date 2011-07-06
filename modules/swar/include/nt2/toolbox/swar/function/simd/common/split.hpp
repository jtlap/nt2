//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_COMMON_SPLIT_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_COMMON_SPLIT_HPP_INCLUDED
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/include/functions/load.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <boost/fusion/tuple.hpp>
namespace nt2 { namespace meta
{
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is upgradeable
  /////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTOR_IMPLEMENTATION_IF( tag::split_, tag::cpu_,
				 (A0)(A1)(X),
				 (boost::mpl::and_ <
				    boost::mpl::not_< boost::is_same<A0, typename meta::upgrade<A0>::type> >,
				    boost::is_same<A1, typename meta::upgrade<A0>::type>
				  > 
                                 ), 
                                 (tag::split_(simd_<arithmetic_<A0>,X>,
					      simd_<arithmetic_<A1>,X>,
					      simd_<arithmetic_<A1>,X>
					      )
				  ),
                                 ((simd_<arithmetic_<A0>,X>))
				 ((simd_<arithmetic_<A1>,X>))
		                 ((simd_<arithmetic_<A1>,X>))
                                )
  {
    typedef int result_type;    
    inline result_type operator()(A0 const& a0,A1 & a1, A1 & a2) const
      {
	static const int size_2 = meta::cardinal_of<A0>::value/2;
	typedef typename meta::scalar_of<A1>::type sA1; 
	NT2_ALIGNED_TYPE(sA1) tmp1[size_2];
	NT2_ALIGNED_TYPE(sA1) tmp2[size_2];
	for(int i = 0; i != size_2; ++i){
	  tmp1[i] = a0[i];
	  tmp2[i] = a0[i+size_2];
	}
	a1 = load<A1>(&tmp1[0], 0); 
	a2 = load<A1>(&tmp2[0], 0); 
	return 0; 
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION_IF( tag::split_, tag::cpu_,
				 (A0)(X),
				 (boost::mpl::not_< boost::is_same<A0, typename meta::upgrade<A0>::type> >),
				 (tag::split_(simd_<arithmetic_<A0>,X>)),
				 ((simd_<arithmetic_<A0>,X>))
				 )
  {
    typedef typename meta::upgrade<A0>::type rtype;
    typedef boost::fusion::tuple<rtype, rtype> result_type;
    
    NT2_FUNCTOR_CALL_REPEAT(1)
    {
      result_type res;
      nt2::split(a0,  boost::fusion::at_c<0>(res),  boost::fusion::at_c<1>(res));
      return res; 
    }
  };
} }

#endif
