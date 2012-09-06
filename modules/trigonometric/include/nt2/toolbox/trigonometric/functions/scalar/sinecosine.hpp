//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SCALAR_SINECOSINE_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SCALAR_SINECOSINE_HPP_INCLUDED
#include <nt2/toolbox/trigonometric/functions/sinecosine.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/toolbox/trigonometric/functions/scalar/impl/trigo.hpp>
/////////////////////////////////////////////////////////////////////////////
// reference based Implementation
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::sinecosine_<mode>, tag::cpu_,
			     (A0)(A1)(mode),
			     (scalar_ < arithmetic_<A0> > )
			     (scalar_ < floating_<A1> > )
			     (scalar_ < floating_<A1> > )
			     )
  {
    typedef nt2::int32_t result_type;    
    inline result_type operator()(A0 const& a0,A1 & a1,A1 & a2) const
    {
      a1 = impl::trig_base <A1,radian_tag,tag::not_simd_type, mode>::sincosa(A1(a0),a2);
      return 0; 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::sinecosine_<mode>, tag::cpu_,
			     (A0)(A1)(mode),
			     (scalar_ < arithmetic_<A0> > )
			     (scalar_ < floating_<A1> > )
			     )
  {
    typedef A1 result_type;    
    inline A1 operator()(A0 const& a0,A1 & a2) const
    {
      return impl::trig_base <A1,radian_tag,tag::not_simd_type, mode>::sincosa(A1(a0),a2);
    }
  };

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type  is floating_
  /////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::sinecosine_<mode>, tag::cpu_,
			     (A0)(mode),
			     (scalar_ < arithmetic_<A0> > )
			     )
  {
    typedef typename boost::dispatch::meta::as_floating<A0>::type etype;
    typedef boost::fusion::tuple<etype, etype>           result_type;
    NT2_FUNCTOR_CALL(1)
      {
	return sinecosine(etype(a0));
      }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type  is floating_
  /////////////////////////////////////////////////////////////////////////////
  
  
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::sinecosine_<mode>, tag::cpu_,
			     (A0)(mode),
			     (scalar_ < floating_<A0> > )
			     )
  {
    typedef boost::fusion::tuple<A0, A0>       result_type;
    NT2_FUNCTOR_CALL(1)
      {
	result_type res;
	boost::fusion::at_c<0>(res) = impl::trig_base < A0,radian_tag
	  ,  tag::not_simd_type, mode
	  >::sincosa(a0, boost::fusion::at_c<1>(res));
        return res;
      }
    };
} }
#endif
