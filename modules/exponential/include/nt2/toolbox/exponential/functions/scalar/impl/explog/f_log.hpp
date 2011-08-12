//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_EXPLOG_F_LOG_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_EXPLOG_F_LOG_HPP_INCLUDED
#include <nt2/core/numeric/functions/sqr.hpp>
#include <nt2/core/numeric/functions/tofloat.hpp>
#include <nt2/core/numeric/functions/is_nan.hpp>
#include <nt2/core/numeric/functions/is_ltz.hpp>
#include <nt2/core/numeric/functions/is_eqz.hpp>
#include <nt2/core/numeric/functions/fast_frexp.hpp>
#include <nt2/core/numeric/functions/genmask.hpp>
#include <nt2/core/numeric/functions/amul.hpp>

namespace nt2
{
  namespace details
  {
    namespace internal
    {
      //////////////////////////////////////////////////////////////////////////////
      // math log functions
      //////////////////////////////////////////////////////////////////////////////

      inline void kernel_log(const float& a0,
			     float& fe,
			     float& x,
			     float& x2,
			     float& y)
      {
        typedef float A0;
        typedef meta::as_integer<A0, signed>::type int_type;
        int_type e;
        boost::fusion::tie(x, e) = fast_frexp(a0);
        int_type x_lt_sqrthf = -(Const<float, 0x3f3504f3>() > x);
        e += x_lt_sqrthf;
        //     if (x_lt_sqrthf) x+= x;
        //     x += Const<float, 0xbf800000>();
        x += b_and(x, genmask<float>(x_lt_sqrthf))+Const<float,0xbf800000>();
        x2 = sqr(x);
        A0 y1 = fma(Const<float, 0x3d9021bb>() ,x2,Const<float, 0x3def251a>() );
        A0 y2 = fma(Const<float, 0xbdebd1b8>() ,x2,Const<float, 0xbdfe5d4f>() );
        y1 = fma(y1,x2,Const<float, 0x3e11e9bf>() );
        y2 = fma(y2,x2,Const<float, 0xbe2aae50>() );
        y1 = fma(y1,x2,Const<float, 0x3e4cceac>() );
        y2 = fma(y2,x2,Const<float, 0xbe7ffffc>() );
        y1 = fma(y1,x2,Const<float, 0x3eaaaaaa>() );
        y = fma(x,y2,y1)*x*x2;
        fe = tofloat(e);
      }

      inline float log(const float& a0)
      {
        typedef float A0;
        if (a0 == Inf<A0>()) return a0;
        if (iseqz(a0)) return Minf<A0>();
        if (nt2::is_nan(a0)||is_ltz(a0)) return Nan<A0>();
        float x, fe, x2, y;
        kernel_log(a0, fe, x, x2, y);
        y = fma(fe, Const<float, 0xb95e8083>(), y);
        y = fma(Mhalf<A0>(), x2, y);
        A0 z  = x + y;
        return fma(Const<float, 0x3f318000>(), fe, z);
      }

      inline float log2(const float& a0)
      {
        typedef float A0;
        if (a0 == Inf<A0>()) return a0;
        if (iseqz(a0)) return Minf<A0>();
        if (nt2::is_nan(a0)||is_ltz(a0)) return Nan<A0>();
        A0 x, fe, x2, y;
        kernel_log(a0, fe, x, x2, y);
        y =  fma(Mhalf<A0>(),x2, y);
        // multiply log of fraction by log2(e)
        A0 z = fma( x
                  , Const<float, 0x3ee2a8ed>()
                  , mul(y,Const<float, 0x3ee2a8ed>())// 0.44269504088896340735992
                  );
        return ((z+y)+x)+fe;
      }

      inline float log10(const float& a0)
      {
        typedef float A0;
        if (a0 == Inf<A0>()) return a0;
        if (iseqz(a0)) return Minf<A0>();
        if (nt2::is_nan(a0)||isltz(a0)) return Nan<A0>();
        A0 x, fe, x2, y;
        kernel_log(a0, fe, x, x2, y);
        y =  amul(y, -Half<A0>(), x2);
        // multiply log of fraction by log10(e) and base 2 exponent by log10(2)
        A0 z = mul(x+y, Const<float, 0x3a37b152>());//7.00731903251827651129E-4f // log10(e)lo
        z = amul(z, y, Const<float, 0x3ede0000>()); //4.3359375E-1f	       // log10(e)hi
        z = amul(z, x, Const<float, 0x3ede0000>());
        z = amul(z, fe, Const<float, 0x39826a14>());//3.0078125E-1f              // log10(2)hi
        return amul(z, fe, Const<float, 0x3e9a0000 >());//2.48745663981195213739E-4f // log10(2)lo
      }
    }
  }
}


#endif
