//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_LOGS_D_LOG_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_LOGS_D_LOG_HPP_INCLUDED

#include <boost/fusion/include/vector_tie.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/is_nan.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/fast_frexp.hpp>
#include <nt2/include/functions/simd/genmask.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/minusone.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/constants/real.hpp>

namespace nt2
{
  namespace details
  {
    namespace internal
    {
      //////////////////////////////////////////////////////////////////////////////
      // math log functions
      //////////////////////////////////////////////////////////////////////////////

      template < class A0 > 
      struct logarithm< A0, tag::not_simd_type, double>
      {
	static inline void kernel_log(const A0& a0,
				      A0& dk,
				      A0& hfsq,
				      A0& s,
				      A0& R,
				      A0& f)
	{
	  typedef typename meta::as_integer<A0, signed>::type int_type;
	  typedef typename meta::scalar_of<A0>::type               sA0;
	  A0 x;
	  int_type k;
	  boost::fusion::vector_tie(x, k) = fast_frexp(a0);
	  //	  fast_frexp(a0, x, k);
	  const int_type x_lt_sqrthf = is_greater(Sqrt_2o_2<A0>(), x)?Mone<int_type>():Zero<int_type>();
	  k += x_lt_sqrthf;
	  f = minusone(x+b_and(x, genmask(x_lt_sqrthf)));
	  dk = tofloat(k);
	  s = f/add(Two<A0>(),f);
	  A0 z = sqr(s);
	  A0 w = sqr(z);
	  A0 t1= w*horner<NT2_HORNER_COEFF_T(sA0, 3,
					 (0x3fc39a09d078c69fll, 
					  0x3fcc71c51d8e78afll,
					  0x3fd999999997fa04ll)
					 )> (w);
	  A0 t2= z*horner<NT2_HORNER_COEFF_T(sA0, 4,
				       (0x3fc2f112df3e5244ll,
					0x3fc7466496cb03dell,
					0x3fd2492494229359ll,
					0x3fe5555555555593ll)
			)> (w);
	  R = t2+t1;
	  hfsq = mul(Half<A0>(), sqr(f));
	}
	
	static inline A0 log(const A0& a0)
	{
	  // ln(2)hi  =  6.93147180369123816490e-01  or  0x3fe62e42fee00000
	  // ln(2)lo  =  1.90821492927058770002e-10  or  0x3dea39ef35793c76
	  if (a0 == Inf<A0>()) return a0;
	  if (is_eqz(a0)) return Minf<A0>();
	  if (nt2::is_nan(a0)||is_ltz(a0)) return Nan<A0>();
	  A0 dk, hfsq, s, R, f;
	  kernel_log(a0, dk, hfsq, s, R, f);
	  return  mul(dk, double_constant<A0, 0x3fe62e42fee00000ll>())-
	    ((hfsq-(s*(hfsq+R)+mul(dk,double_constant<A0, 0x3dea39ef35793c76ll>())))-f);
	}
	static inline A0 log2(const A0& a0)
	{
	  if (a0 == Inf<A0>()) return a0;
	  if (is_eqz(a0)) return Minf<A0>();
	  if (nt2::is_nan(a0)||is_ltz(a0)) return Nan<A0>();
	  A0 dk, hfsq, s, R, f;
	  kernel_log(a0, dk, hfsq, s, R, f);
	  return -(hfsq-(s*(hfsq+R))-f)*Invlog_2<A0>()+dk;
	}
	
	static inline A0 log10(const A0& a0)
	{
	  if (a0 == Inf<A0>()) return a0;
	  if (is_eqz(a0)) return Minf<A0>();
	  if (nt2::is_nan(a0)||is_ltz(a0)) return Nan<A0>();
	  A0 dk, hfsq, s, R, f;
	  kernel_log(a0, dk, hfsq, s, R, f);
	  return -(hfsq-(s*(hfsq+R))-f)*Invlog_10<A0>()+dk*Log_2olog_10<A0>();
	}
      }; 
    }
  }
}


#endif
