//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_EULER_FUNCTION_SIMD_COMMON_DIGAMMA_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTION_SIMD_COMMON_DIGAMMA_HPP_INCLUDED
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/selsub.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/polevl.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/any.hpp>
#include <nt2/include/functions/is_lez.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/nbtrue.hpp>
#include <nt2/include/functions/floor.hpp>
#include <nt2/include/functions/bitwise_ornot.hpp>
#include <nt2/include/functions/bitwise_andnot.hpp>
#include <nt2/include/functions/tanpi.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/toolbox/polynomials/function/scalar/impl/poleval.hpp>
#include <nt2/toolbox/euler/function/scalar/constants.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::digamma_, tag::cpu_,
                          (A0)(X),
                          ((simd_<arithmetic_<A0>,X>))
                         );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::digamma_(tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      return nt2::digamma(tofloat(a0));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::digamma_, tag::cpu_,
                          (A0)(X),
                          ((simd_<real_<A0>,X>))
                         );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::digamma_(tag::simd_<tag::real_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type sA0;
      //
      // This handles reflection of negative arguments, and all our
      // error handling, then forwards to the T-specific approximation.
      //
      A0 result = Zero<A0>();
      A0 x = a0;
      A0 test = is_lez(a0);
      uint32_t nb;
      if( (nb = nbtrue(test)) > 0)
      {
        x = sel(test, oneminus(a0), a0);
        A0 remainder = x - floor(x);
          remainder =  selsub(gt(remainder,Half<A0>()),remainder,One<A0>());
        result = b_and(b_andnot(Pi<A0>()/tanpi(remainder),is_eqz(remainder)), test);
        // we are ready to increment result that was
        // Pi<A0>()/tanpi(remainder) if a0 < 0  and remainder != 0
        // Nan<A0>                   if a0 < 0  and remainder == 0
        // 0                         in any other cases
      }
      A0 r1, r2;
      test = gt(x, Digammalargelim<A0>());
      if((nb = nbtrue(test)))
      { // If we're above the lower-limit for the asymptotic expansion then use it:
        r1 = b_and(digamma_imp_large(x, sA0()), test)+result;
        if (nb >= (uint32_t)meta::cardinal_of<A0>::value) return r1;
      }
      // If x > 2 reduce to the interval [1,2]:
      A0 cond;
      while(any(cond = gt(x, Two<A0>())))
      {
        x      -= b_and(One<A0>(), cond);
        result += b_and(rec(x), cond);
      }
      // If x < 1 use shift to > 1:
      if(any(cond = lt(x, One<A0>())))
      {
        result = sel(cond, -rec(x), result);
        x      += b_and(One<A0>(), cond);
      }
      r2 = b_andnot(digamma_imp_1_2(x, sA0()), test)+result;
      if (nb == 0) return r2;
      return sel(test, r1, r2);
    }
  private:
    template <class A>
    static inline A digamma_imp_1_2(A x, float)
    {
      //
      // Now the approximation, we use the form:
      //
      // digamma(x) = (x - root) * (Y + R(x-1))
      //
      // Where root is the location of the positive root of digamma,
      // Y is a constant, and R is optimised for low nt2::absolute error
      // compared to Y.
      //
      // Maximum Deviation Found:              3.388e-010
      // At float precision, max error found:  2.008725e-008
      //
      typedef typename meta::scalar_of<A>::type sA; 
      static const A Y = splat<A>(0.99558162689208984);
      static const A root = splat<A>(1532632.0 / 1048576);
      static const A root_minor = splat<A>(double(0.3700660185912626595423257213284682051735604e-6L));
      static const boost::array<sA, 4> P = {{    
	0.25479851023250261e0,
	-0.44981331915268368e0,
	-0.43916936919946835e0,
	-0.61041765350579073e-1
	}};
      static const  boost::array<sA, 4> Q = {{
	0.1e1,
	0.15890202430554952e1,
	0.65341249856146947e0,
	0.63851690523355715e-1}}; 
      A g = x - root;
      g -= root_minor;
      x-= One<A>(); 
      A r = eval_poly<4>(x, P)/eval_poly<4>(x, Q);
      A result = fma(g, Y, g * r);
      return result;
    }

    template <class A>
    static inline A digamma_imp_large(A x, float)
    {
      typedef typename meta::scalar_of<A>::type sA; 
      // 9-digit precision for x >= 10:
      static const  boost::array<sA, 3> P = {{
	0.083333333333333333333333333333333333333333333333333L,
	-0.0083333333333333333333333333333333333333333333333333L,
	0.003968253968253968253968253968253968253968253968254L
	}};
      x -= One<A>();
      A result = log(x);
      result += rec(Two<A>()*x);
      A z = rec(sqr(x));
      result -= z * nt2::eval_poly<3>(z, P);
      return result;
    }
    template <class A>
    static inline A digamma_imp_1_2(A x, double)
    {
      //
      // Now the approximation, we use the form:
      //
      // digamma(x) = (x - root) * (Y + R(x-1))
      //
      // Where root is the location of the positive root of digamma,
      // Y is a constant, and R is optimised for low nt2::absolute error
      // compared to Y.
      //
      // Maximum Deviation Found:              3.388e-010
      // At float precision, max error found:  2.008725e-008
      //
      typedef typename meta::scalar_of<A>::type sA; 
      static const A Y = splat<A>(0.99558162689208984);

   static const A root1 = splat<A>(1569415565.0 / 1073741824uL);
   static const A root2 = splat<A>((381566830.0 / 1073741824uL) / 1073741824uL);
   static const A root3 = splat<A>(double(0.9016312093258695918615325266959189453125e-19L));

   static const boost::array<sA, 6> P = {{    
       0.25479851061131551L,
       -0.32555031186804491L,
       -0.65031853770896507L,
       -0.28919126444774784L,
       -0.045251321448739056L,
       -0.0020713321167745952L
     }};
   static const  boost::array<sA, 7> Q = {{
       1L,
       2.0767117023730469L,
       1.4606242909763515L,
       0.43593529692665969L,
       0.054151797245674225L,
       0.0021284987017821144L,
       -0.55789841321675513e-6L
     }};
      A g = x - root1;
      g -= root2;
      g -= root3; 
      x-= One<A>(); 
      A r = eval_poly<6>(x, P)/eval_poly<7>(x, Q);
      A result = fma(g, Y, g * r);
      return result;
    }

    template <class A>
    static inline A digamma_imp_large(A x, double)
    {
      typedef typename meta::scalar_of<A>::type sA; 
      // 9-digit precision for x >= 10:
      static const  boost::array<sA, 8> P = {{
      0.083333333333333333333333333333333333333333333333333L,
      -0.0083333333333333333333333333333333333333333333333333L,
      0.003968253968253968253968253968253968253968253968254L,
      -0.0041666666666666666666666666666666666666666666666667L,
      0.0075757575757575757575757575757575757575757575757576L,
      -0.021092796092796092796092796092796092796092796092796L,
      0.083333333333333333333333333333333333333333333333333L,
      -0.44325980392156862745098039215686274509803921568627L
	}};
      x -= One<A>();
      A result = log(x);
      result += rec(Two<A>()*x);
      A z = rec(sqr(x));
      result -= z * nt2::eval_poly<8>(z, P);
      return result;
    }
  };
} }

#endif
// modified by jt the 05/01/2011
