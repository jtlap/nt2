//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_FAST_HYPOT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_FAST_HYPOT_HPP_INCLUDED

#include <boost/simd/include/constants/digits.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/include/constants/eps_related.hpp>

#include <boost/simd/include/functions/sqrt.hpp>
#include <boost/simd/include/functions/sqr.hpp>
#include <boost/simd/include/functions/is_nan.hpp>
#include <boost/simd/include/functions/is_inf.hpp>
#include <boost/simd/include/functions/ldexp.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::fast_hypot_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< arithmetic_<A0> >)(scalar_< arithmetic_<A1> >)
                            )
  {

    typedef typename boost::dispatch::meta::result_of<boost::dispatch::meta::floating(A0,A1)>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef result_type type;
      return boost::simd::fast_hypot(type(a0), type(a1));
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::fast_hypot_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< double_<A0> >)(scalar_< double_<A1> >)
                            )
  {

    typedef typename boost::dispatch::meta::result_of<boost::dispatch::meta::floating(A0,A1)>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename dispatch::meta::as_integer<A0, signed>::type  int_type;
      A0 x =  boost::simd::abs(a0);
      A0 y =  boost::simd::abs(a1);
      if (boost::simd::is_inf(x+y)) return Inf<float>();
      if (boost::simd::is_nan(x+y)) return Nan<float>();
      if (y > x) std::swap(x, y);
      if (x*Eps<A0>() >=  y) return x;
      return x*boost::simd::sqrt(One<A0>()+boost::simd::sqr(y/x));
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::fast_hypot_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< float_<A0> >)(scalar_< float_<A1> >)
                            )
  {

    typedef typename boost::dispatch::meta::result_of<boost::dispatch::meta::floating(A0,A1)>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      // flibc do that in ::fast_hypotf(a0, a1) in asm with no more speed!
      // proper impl as for double is 30% slower
      return result_type(boost::simd::sqrt(boost::simd::sqr(double(a0))+boost::simd::sqr(double(a1))));
    }
  };
} } }


#endif
