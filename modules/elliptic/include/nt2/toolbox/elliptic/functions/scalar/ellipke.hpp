//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ELLIPTIC_FUNCTIONS_SCALAR_ELLIPKE_HPP_INCLUDED
#define NT2_TOOLBOX_ELLIPTIC_FUNCTIONS_SCALAR_ELLIPKE_HPP_INCLUDED
#include <boost/fusion/tuple.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/is_greater.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/toolbox/trigonometric/constants.hpp>
#include <nt2/include/constants/real.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::ellipke_, tag::cpu_,
			     (A0),
			     (scalar_<arithmetic_<A0> > )
			     )
  {
    typedef typename meta::result_of<meta::floating(A0)>::type etype;
    typedef boost::fusion::tuple<etype, etype>           result_type;
    
    NT2_FUNCTOR_CALL(1)
      {
	return ellipke(etype(a0), Eps<etype>()); 
      }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::ellipke_, tag::cpu_,
			     (A0)(A1),
			     (scalar_<arithmetic_<A0> >)
			     (scalar_<arithmetic_<A1> >)
			     )
  {
    typedef typename meta::strip<A0>::type           etype;
    typedef boost::fusion::tuple<etype, etype> result_type;
    
    NT2_FUNCTOR_CALL(2)
      {
	typedef typename meta::result_of<meta::floating(A0)>::type type;
	return ellipke(type(a0), type(a1)); 
      }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is real_
  /////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::ellipke_, tag::cpu_,
			     (A0)(A1),
			     (scalar_<real_<A0> >)
			     (scalar_<real_<A1> >)
			     )
  {
    typedef typename meta::strip<A0>::type           etype;
    typedef boost::fusion::tuple<etype, etype> result_type;
    
    NT2_FUNCTOR_CALL(2)
      {
	result_type res;
	nt2::ellipke(a0, a1, boost::fusion::at_c<0>(res), boost::fusion::at_c<1>(res)); 
	return res; 
      }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // reference based Implementations 1 input
  /////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTOR_IMPLEMENTATION(  nt2::tag::ellipke_, tag::cpu_,
			       (A0)(A1), 
			       (scalar_<arithmetic_<A0> >)
			       (scalar_<real_<A1> >)
			       (scalar_<real_<A1> >)
			       )
  {
    typedef void result_type;    
    inline result_type operator()(A0 const& a0,A1 & a1,A1 & a2) const
      {
	nt2::ellipke(a0,Eps<A1>(),a1,a2); 
      }
  }; 
  
  /////////////////////////////////////////////////////////////////////////////
  // reference based Implementations 2 inputs
  /////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTOR_IMPLEMENTATION(  nt2::tag::ellipke_, tag::cpu_,(A0)(A1)(A2), 
			       (scalar_<arithmetic_<A0> >)
			       (scalar_<real_<A1> >)
			       (scalar_<real_<A2> >)
			       (scalar_<real_<A2> >)
			       )
  {
    typedef void result_type;    
    inline result_type operator()(A0 const& a0,A1 const& a1, A2 & a2,A2 & a3) const
      {
	if (is_ltz(a0) || gt(a0, One<A0>()))
	  {
	    a2 = Nan<A2>();
	    a3 = Nan<A2>();
	    return; 
	  }
	A2 m = a0; 
	A2 aa0 = One<A2>();;
	A2 bb0 = sqrt(oneminus(m));
	A2 s0 = m;
	int32_t i1 = 0;
	A2 mm = 1;
	A2 aa1; 
	while (mm > a1) {
	  aa1 = average(aa0, bb0);
	  A2 bb1 = nt2::sqrt(aa0*bb0);
	  A2 cc1 = nt2::average(aa0, -bb0);
	  i1++; 
	  mm = nt2::ldexp(sqr(cc1), i1); 
	  s0 += mm;
	  aa0 = aa1;
	  bb0 = bb1;
	};
	if (is_equal(m, One<A2>()))
	  {
	    a2 = Inf<A2>();
	    a3 = One<A2>();
	  }
	else
	  {
	    a2 = nt2::Pio_2<A2>()/aa1;
	    a3 = a2*(One<A2>()-s0*Half<A2>());
	  }
      }
  };
  
} }
#endif
