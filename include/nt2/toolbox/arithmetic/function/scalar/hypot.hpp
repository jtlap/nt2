//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_HYPOT_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_HYPOT_HPP_INCLUDED
#include <nt2/sdk/meta/from_bits.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/digits.hpp>

#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/exponent.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/bits.hpp>
#include <nt2/include/functions/ldexp.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for hypot

  /////////////////////////////////////////////////////////////////////////////
  // Compute hypot(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<hypot_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : 
      boost::result_of<meta::floating(A0,A1)>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      A0,
      (3, (float,double, arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(2,  float)
    {
	// flibc do that in ::hypotf(a0, a1) in asm with no more speed!
	// internal is 30% slower
	return nt2::sqrt(nt2::sqr(double(a0))+nt2::sqr(double(a1)));
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2, double)
    {
	// in double ::hypot is very slow
	// 4 times slower than internal
	return internal(a0, a1);
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2, arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type; 
      return nt2::hypot(type(a0), type(a1)); 
    }
  private:
    
    template < class A0>
    static inline A0 internal(const A0& a0, const  A0& a1)
    {
      typedef typename meta::as_integer<A0, signed>::type  int_type;
      A0 x =  abs(a0);
      A0 y =  abs(a1);
      if (nt2::is_inf(x+y)) return Inf<float>();
      if (nt2::is_nan(x+y)) return Nan<float>();
      A0 a =  nt2::max(x, y);
      A0 b =  nt2::min(x, y);
      int_type ea =   nt2::exponent(a);
      int_type eb  =  nt2::exponent(b);
      if (ea-eb > constants<A0>::C0()) return a+b;
      int_type e = Zero<int_type>();
      if (ea > constants<A0>::C1())
	{
	  e = constants<A0>::MC2();
	}
      if (eb < constants<A0>::MC1())
	{
	  
	  e = constants<A0>::C1();
	}
      if (e)
	{
	  a =  nt2::ldexp(a, e);
	  b =  nt2::ldexp(b, e);
	}
      A0 w = a-b;
      if (w > b)
	{
	  A0 t1 = b_and(a, constants<A0>::M1());
	  A0 t2 = a-t1;
	  w  = (t1*t1-(b*(-b)-t2*(a+t1)));
	}
      else
	{
	  A0 y1 = b_and(b, constants<A0>::M1());
	  A0 y2 = b - y1;
	  typedef typename meta::from_bits<A0, unsigned>::type type; 
	  type that = {bits(a)+constants<A0>::C3()}; 
	  A0 t1 = that.value; 
	  A0 t2 = (a+a) - t1;
	  w  = (t1*y1-(w*(-w)-(t1*y2+t2*b)));
	}
      w = nt2::sqrt(w);
      if (e) w = nt2::ldexp(w, -e);
      return w;
    }
    template < class T, class I = typename meta::as_integer<T, signed>::type>
    struct constants;
    template <class I> struct constants<float, I>
    {
      typedef I  int_type;
      static inline int_type C0() { return (30);};
      static inline int_type C1() { return (50);};
      static inline int_type C2() { return (60);};
      static inline int_type MC1(){ return (-50);};
      static inline int_type MC2(){ return (-60);};
      static inline int_type C3() { return (0x00800000);};
      static inline int_type M1() { return (0xfffff000);};
    };
    template <class I> struct constants<double, I>
    {
      typedef I  int_type;
      static inline int_type C0() { return (60);};
      static inline int_type C1() { return (500);};
      static inline int_type C2() { return (600);};
      static inline int_type MC1(){ return (-500);};
      static inline int_type MC2(){ return (-600);};
      static inline int_type C3() { return (0x0010000000000000ll);}
      static inline int_type M1() { return (0xffffffff00000000ll);};
    };
  };
} }


      
#endif
