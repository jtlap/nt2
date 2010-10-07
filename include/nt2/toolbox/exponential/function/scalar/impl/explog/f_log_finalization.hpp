//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SCALAR_IMPL_EXPLOG_F_LOG_FINALIZATION_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SCALAR_IMPL_EXPLOG_F_LOG_FINALIZATION_HPP_INCLUDED

namespace nt2
{
  namespace details
  {
    namespace internal
    {
      template< class A0
              , class Tag
              , class base_A0 = typename meta::scalar_of<A0>::type
      > struct log_finalization;

      template < class A0>
      struct log_finalization< A0, natural_tag, float>
      {
        inline A0 finalize(const float& fe,
               const  float& x,
               const  float& x2,
               float y)
        {
          y = fma(fe, Const<float,0xb95e8083>(), y);
          y = fma(Mhalf<A0>(), x2, y);
          A0 z  = x + y;
          return fma(Const<float,0x3f318000>(), fe, z);
        }
            };
            template < class A0>
            struct log_finalization< A0, two_tag, float>
            {
        inline A0 finalize(const float& fe,
               const  float& x,
               const  float& x2,
               float y)
        {
          y =  fma(Mhalf<A0>(),x2, y);
          // multiply log of fraction by log2(e)
          A0 z = fma(x,Const<float,0x3ee2a8ed>(),mul(y,Const<float, 0x3ee2a8ed>()));// 0.44269504088896340735992
          return ((z+y)+x)+fe;
        }
      };

      template < class A0>
      struct log_finalization< A0, ten_tag, float>
      {
	inline A0 finalize(const float& fe,
			   const  float& x,
			   const  float& x2,
			   float y)
	{
	  y =  amul(y, -Half<A0>(), x2);
	  // multiply log of fraction by log10(e) and base 2 exponent by log10(2)
	  A0 z = mul(x+y, Const<float,0x3a37b152>());//7.00731903251827651129E-4f // log10(e)lo
	  z = amul(z, y, Const<float,0x3ede0000>()); //4.3359375E-1f	       // log10(e)hi
	  z = amul(z, x, Const<float,0x3ede0000>());
	  z = amul(z, fe, Const<float,0x39826a14>());//3.0078125E-1f              // log10(2)hi
	  return amul(z, fe, Const<float,0x3e9a0000>());//2.48745663981195213739E-4f // log10(2)lo
	}
      };
    }
  }
}

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of f_log_finalization.hpp
// /////////////////////////////////////////////////////////////////////////////
