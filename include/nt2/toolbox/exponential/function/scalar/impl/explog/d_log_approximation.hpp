/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_NUMERIC_FUNCTION_DETAILS_SCALAR_IMPL_EXPLOG_D_LOG_APPROXIMATION_HPP_INCLUDED
#define NT2_CORE_NUMERIC_FUNCTION_DETAILS_SCALAR_IMPL_EXPLOG_D_LOG_APPROXIMATION_HPP_INCLUDED

namespace nt2
{
  namespace details
  {
    namespace internal
    {
      template < class A0, class Style> 
      struct log_approximation< A0, Style, double>
      {
	typedef typename meta::as_integer<A0, signed>::type int_type;	
	typedef typename meta::scalar_of<A0>::type            s_type;

	static inline void kernel_log(const  A0& a0,
				      A0& dk,
				      A0& hfsq,
				      A0& s,
				      A0& R,
				      A0& f)
	{
	  A0 x;
	  int_type k;
	  bf::tie(x, k) = fast_frexp(a0);
	  const int_type x_lt_sqrthf = -isgt(Sqrt_2o_2<A0>(), x);
	  k += x_lt_sqrthf;
	  f = minusone(x+b_and(x, genmask<A0>(x_lt_sqrthf)));
	  dk = tofloat(k);
	  s = f/add(Two<A0>(),f);
	  A0 z = sqr(s);
	  A0 w = sqr(z);
	  A0 t1= w*horner<NT2_HORNER_COEFF_T(A0, 3,
					   (0x3fc39a09d078c69fll, 
					    0x3fcc71c51d8e78afll,
					    0x3fd999999997fa04ll)
					   )> (w);
          A0 t2= z*horner<NT2_HORNER_COEFF_T(A0, 4,
					 (0x3fc2f112df3e5244ll,
					  0x3fc7466496cb03dell,
					  0x3fd2492494229359ll,
					  0x3fe5555555555593ll)
					   )> (w);
           R = t2+t1;
           hfsq = mul(Half<A0>(), sqr(f));
	}
      }; 
    }
  }
}


#endif

// /////////////////////////////////////////////////////////////////////////////
// End of d_log_approximation.hpp
// /////////////////////////////////////////////////////////////////////////////
