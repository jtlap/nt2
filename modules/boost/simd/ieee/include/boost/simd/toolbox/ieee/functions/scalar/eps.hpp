//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_EPS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_EPS_HPP_INCLUDED
#include <boost/simd/include/constants/properties.hpp>
#include <boost/simd/include/constants/digits.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/include/constants/eps_related.hpp>
#include <boost/dispatch/details/ignore_unused.hpp>

#include <boost/simd/include/functions/is_not_finite.hpp>
#include <boost/simd/include/functions/fast_ldexp.hpp>
#include <boost/simd/include/functions/exponent.hpp>
#include <boost/simd/include/functions/abs.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::eps_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {

    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      return One<A0>();
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::eps_, tag::cpu_
                            , (A0)
                            , (scalar_< real_<A0> >)
                            )
  {

    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef std::numeric_limits<A0> lim;
      const A0 a = boost::simd::abs(a0);
      if (is_not_finite(a))
      {
        return result_type(Nan<A0>());
      }
      else if (a < lim::min())
      {
        return Mindenormal<A0>();
      }
      else
      {
        return boost::simd::fast_ldexp(One<A0>(), exponent(a) -lim::digits+1);
      }
    }
  };
} } }


#endif
