//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_EXPLOG_F_LOG_APPROXIMATION_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_EXPLOG_F_LOG_APPROXIMATION_HPP_INCLUDED

namespace nt2
{
  namespace details
  {
    namespace internal
    {
      template< class A0
              , class Style
              , class base_A0 = typename meta::scalar_of<A0>::type
              >
      struct log_approximation;

      template<class A0,class Style>
      struct log_approximation< A0, Style, float>
      {
        typedef typename meta::as_integer<A0, signed>::type int_type;

        static inline void
        kernel_log(const A0& a0,A0& fe, A0& x,A0& x2, A0& y, const A0&)
        {
          int_type e(fast_frexp(a0, x));
          int_type x_lt_sqrthf = -(Const<float,0x3f3504f3>() > x);
          e += x_lt_sqrthf;
          x += b_and(x, genmask<float>(x_lt_sqrthf))+Const<float,0xbf800000>();
          x2 = sqr(x);
          A0 y1 = fma(Const<float, 0x3d9021bb>() ,x2,Const<float, 0x3def251a>() );
          A0 y2 = fma(Const<float, 0xbdebd1b8>() ,x2,Const<float, 0xbdfe5d4f>() );
          y1 = fma(y1,x2,Const<float, 0x3e11e9bf>() );
          y2 = fma(y2,x2,Const<float, 0xbe2aae50>() );
          y1 = fma(y1,x2,Const<float, 0x3e4cceac>() );
          y2 = fma(y2,x2,Const<float, 0xbe7ffffc>() );
          y1 = fma(y1,x2,Const<float, 0x3eaaaaaa>() );
          y  = fma(x,y2,y1)*x*x2;
          fe = tofloat(e);
       }
      };
    }
  }
}

#endif
