//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_ASEC_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_ASEC_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>

#include <nt2/include/functions/acsc.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/sqrt.hpp>
//#include <nt2/include/functions/log.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::asec_, tag::cpu_,
                      (A0),
                      (arithmetic_<A0>)
                     )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::asec_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
      template<class Sig> struct result;
      template<class This,class A0>
      struct result<This(A0)> : std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
      {
      typedef typename NT2_RETURN_TYPE(1)::type type;
        return nt2::asec(type(a0));
      }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::asec_, tag::cpu_,
                      (A0),
                      (double_<A0>)
                     )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::asec_(tag::double_),
              tag::cpu_, Dummy> : callable
  {
      template<class Sig> struct result;
      template<class This,class A0>
      struct result<This(A0)> : std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
      {
// 	A0 ax =  nt2::abs(a0);
// 	if (ax <  One<A0>()) return Nan<A0>(); 
// 	A0 ax1 =  ax-One<A0>(); 
// 	if (ax1 < 0.01) {
// 	  std::cout << "icitted" << std::endl; 
// 	  return nt2::sqrt(2*log(ax))*(1-ax1/6-3.264474750714559e-01f*sqr(ax1)*ax1); 
// 	}
        //                                  6.123233995736765886130E-17
	if (is_equal(a0, One<A0>())) return Zero<A0>(); 
	A0 tmp =  (Pio_2<A0>()-nt2::acsc(a0))+  double_constant<A0, 0x3c91a62633145c07ll>(); 
	return tmp;
	//        return (Pio_2<A0>()-nt2::acsc(a0))+double_constant<A0, 0x3c91a62633145c07ll>();
      }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::asec_, tag::cpu_,
                      (A0),
                      (float_<A0>)
                     )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::asec_(tag::float_),
              tag::cpu_, Dummy> : callable
  {
      template<class Sig> struct result;
      template<class This,class A0>
      struct result<This(A0)> : std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
      {
	A0 ax =  nt2::abs(a0);
	if (ax <  One<A0>()) return Nan<A0>(); 
	A0 ax1 =  ax-One<A0>(); 
	if (ax1 < 0.001f) {
	  //limit((acos(1/x)/sqrt(2*(x-1))-(1-(5/12)*(x-1)+(43/160)*(x-1)^2-(177/896)*(x-1)^3))/(x-1)^4,x,1) = 2867/18432
	  A0 tmp = nt2::sqrt(2*(ax1))*(1-ax1*((5/12.0f)+ax1*((43/160.0f)-ax1*((177/896.0f)+ax1*(2867/18432.0f)))));
	  return (is_ltz(a0)) ? Pi<A0>()-tmp : tmp; 
	}
	if (is_equal(a0, One<A0>())) return Zero<A0>(); 
	A0 tmp =  (Pio_2<A0>()-nt2::acsc(a0));
	//	if (abs(tmp) < 1.0e-4) tmp -= 4.3711388e-08;
	return tmp;
      }
  };
} }

#endif
// modified by jt the 26/12/2010
