//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_BESSEL_FUNCTIONS_SCALAR_YNI_HPP_INCLUDED
#define NT2_TOOLBOX_BESSEL_FUNCTIONS_SCALAR_YNI_HPP_INCLUDED
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/cos.hpp>
#include <nt2/include/functions/cospi.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/y0.hpp>
#include <nt2/include/functions/y1.hpp>

#include <nt2/toolbox/bessel/details/math.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::yni_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)(scalar_< arithmetic_<A1> >)
                            )
  {
    typedef typename boost::dispatch::meta::as_floating<A0,A1>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::yni(a0, result_type(a1));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is double
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::yni_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)(scalar_< double_<A1> >)
                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      if (is_inf(a1)) return Zero<result_type>(); 
      if (is_eqz(a1)) return Minf<result_type>(); 
    #ifdef NT2_TOOLBOX_BESSEL_HAS__YN
      return ::_yn(a0, a1);
    #elif defined(NT2_TOOLBOX_BESSEL_HAS_YN)
      return ::yn(a0, a1);
    #else
      #error yn not supported
    #endif
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is float
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::yni_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)(scalar_< single_<A1> >)
                            )
  {

    typedef typename meta::strip<A1>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      typedef A1 result_type;
      if (is_ltz(a1)||is_nan(a1)) return Nan<result_type>();
      if (is_inf(a1)) return Zero<result_type>(); 
      if (is_eqz(a1)) return Minf<result_type>(); 
      result_type x = a1;
      const int32_t n1 = nt2::abs(a0);
      result_type sign = (a0<0)?nt2::cospi(n1):1;
      if( n1 == 0 ) return( sign * nt2::y0(x) );
      if( n1 == 1 ) return( sign * nt2::y1(x) );
      //      result_type an1 = n1;
      /* forward recurrence on n */

      result_type anm2 = nt2::y0(x);
      result_type anm1 = nt2::y1(x);
      int32_t k = 1;
      result_type r = k << 1;
      result_type xinv = rec(x);
      result_type an;
      do
      {
        an = r*anm1*xinv-anm2;
        anm2 = anm1;
        anm1 = an;
        r +=Two<result_type>();
        ++k;
      }
      while( k < n1 );
      return sign*an;
      //     return ::ynf(a0, a1);
    }
  };
} }


#endif
