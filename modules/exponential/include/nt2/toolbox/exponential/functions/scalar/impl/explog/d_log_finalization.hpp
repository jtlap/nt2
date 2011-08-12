//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_EXPLOG_D_LOG_FINALIZATION_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_EXPLOG_D_LOG_FINALIZATION_HPP_INCLUDED

namespace nt2
{
  namespace details
  {
    namespace internal
    {
      template < class A0>
      struct log_finalization< A0, natural_tag, double>
      {
        inline A0 finalize(const A0& fe,const  A0& x,const  A0& x2,const A0& y)
        {
          y = fma(fe, Const<A0, 0xb95e8083>(), y);
          y = fma(Mhalf<A0>(), x2, y);
          A0 z  = x + y;
          return fma(Const<A0, 0x3f318000>(), fe, z);
        }
      };

      template < class A0>
      struct log_finalization< A0, two_tag, double>
      {
        inline A0 finalize(const A0& fe,const  A0& x,const  A0& x2,const A0& y)
        {
          y =  fma(Mhalf<A0>(),x2, y);
          A0 z = fma(x,Const<A0, 0x3ee2a8ed>(),mul(y,Const<A0, 0x3ee2a8ed>()));
          return ((z+y)+x)+fe;
        }
      };

      template < class A0>
      struct log_finalization< A0, ten_tag, double>
      {
        inline A0 finalize(const A0& fe,const  A0& x,const  A0& x2,const A0& y)
        {
          y     =  amul(y, -Half<A0>(), x2);

          // multiply log of fraction by log10(e) and base 2 exponent by log10(2)
          A0 z  = mul(x+y, Const<A0, 0x3a37b152>());//7.00731903251827651129E-4f // log10(e)lo
          z     = amul(z, y, Const<A0, 0x3ede0000>()); //4.3359375E-1f	       // log10(e)hi
          z     = amul(z, x, Const<A0, 0x3ede0000>());
          z     = amul(z, fe, Const<A0, 0x39826a14>());//3.0078125E-1f              // log10(2)hi
          return amul(z, fe, Const<A0, 0x3e9a0000>());//2.48745663981195213739E-4f // log10(2)lo
        }
      };
    }
  }
}


#endif
