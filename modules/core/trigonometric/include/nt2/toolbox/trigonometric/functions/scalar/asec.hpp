//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SCALAR_ASEC_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SCALAR_ASEC_HPP_INCLUDED
#include <nt2/toolbox/trigonometric/functions/asec.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/functions/scalar/acsc.hpp>
#include <nt2/include/functions/scalar/is_eqz.hpp>
#include <nt2/include/functions/scalar/is_ltz.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/sqrt.hpp>
#include <nt2/include/functions/scalar/is_equal.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::asec_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
        return nt2::asec(result_type(a0));
      }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::asec_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
	if (is_equal(a0, One<A0>())) return Zero<A0>(); 
	A0 tmp =  (Pio_2<A0>()-nt2::acsc(a0))+  double_constant<A0, 0x3c91a62633145c07ll>(); 
	return tmp;
      }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::asec_, tag::cpu_
                            , (A0)
                            , (scalar_< single_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
	A0 ax =  nt2::abs(a0);
	if (ax <  One<A0>()) return Nan<A0>(); 
	A0 ax1 =  ax-One<A0>(); 
	if (ax1 < 0.001f) {
	  A0 tmp = nt2::sqrt(2*(ax1))*(1-ax1*((5/12.0f)+ax1*((43/160.0f)-ax1*((177/896.0f)+ax1*(2867/18432.0f)))));
	  return (is_ltz(a0)) ? Pi<A0>()-tmp : tmp; 
	}
	if (is_equal(a0, One<A0>())) return Zero<A0>(); 
	A0 tmp =  (Pio_2<A0>()-nt2::acsc(a0));
	return tmp;
      }
  };
} }


#endif
