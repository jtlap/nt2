//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_HYPOT_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_HYPOT_HPP_INCLUDED
#include <nt2/sdk/meta/from_bits.hpp>
#include <nt2/include/constants/infinites.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/digits.hpp>

#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/exponent.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/bits.hpp>
#include <nt2/include/functions/ldexp.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is fundamental_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{

  template < class T, class I = typename meta::as_integer<T, signed>::type>
  struct hypot_constants;

  template <class I> struct hypot_constants<float, I>
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

  template <class I> struct hypot_constants<double, I>
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

 NT2_FUNCTOR_IMPLEMENTATION(tag::hypot_, tag::cpu_,
                       (A0)(A1),
                       (scalar_<fundamental_<A0> >)(scalar_<fundamental_<A1> >)
                      )
 {
   typedef typename meta::result_of<meta::floating(A0,A1)>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      typedef result_type ftype;
      return internal(ftype(a0), ftype(a1)); 
    }
  private:

    static inline float internal(const float& a0, const  float& a1)
      {
	// flibc do that in ::hypotf(a0, a1) in asm with no more speed!
	// internal is 30% slower
	return float(nt2::sqrt(nt2::sqr(double(a0))+nt2::sqr(double(a1))));	
      }
    
    template < class AA0>
    static inline AA0  internal(const AA0& a0, const  AA0& a1)
    {
      // in double ::hypot is very slow and is 4 times slower than internal
      // this routine in float (with float constants) is 30% slower than 
      // the straightforward preceding overload for floats
      // The float constants are provided in order to modify
      // the algorithm if a architecture gived different speed results
      typedef typename meta::as_integer<AA0, signed>::type  int_type;
      AA0 x =  nt2::abs(a0);
      AA0 y =  nt2::abs(a1);
      if (nt2::is_inf(x+y)) return Inf<AA0>();
      if (nt2::is_nan(x+y)) return Nan<AA0>();
      AA0 a =  nt2::max(x, y);
      AA0 b =  nt2::min(x, y);
      int_type ea =   nt2::exponent(a);
      int_type eb  =  nt2::exponent(b);
      if (ea-eb > hypot_constants<AA0>::C0()) return a+b;
      int_type e = Zero<int_type>();
      if (ea > hypot_constants<AA0>::C1())
      {
        e = hypot_constants<AA0>::MC2();
      }
      if (eb < hypot_constants<AA0>::MC1())
      {

        e = hypot_constants<AA0>::C1();
      }
      if (e)
      {
        a =  nt2::ldexp(a, e);
        b =  nt2::ldexp(b, e);
      }
      AA0 w = a-b;
      if (w > b)
      {
        AA0 t1 = b_and(a, hypot_constants<AA0>::M1());
        AA0 t2 = a-t1;
        w  = (t1*t1-(b*(-b)-t2*(a+t1)));
      }
      else
      {
        AA0 y1 = b_and(b, hypot_constants<AA0>::M1());
        AA0 y2 = b - y1;
        typedef typename meta::from_bits<AA0, unsigned>::type type;
        type that = {bits(a)+hypot_constants<AA0>::C3()};
        AA0 t1 = that.value;
        AA0 t2 = (a+a) - t1;
        w  = (t1*y1-(w*(-w)-(t1*y2+t2*b)));
      }
      w = nt2::sqrt(w);
      if (e) w = nt2::ldexp(w, -e);
      return w;
    }
  };

} }

#endif
