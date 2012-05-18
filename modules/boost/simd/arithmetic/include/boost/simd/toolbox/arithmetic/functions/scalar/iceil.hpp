//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_ICEIL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_ICEIL_HPP_INCLUDED
#include <boost/simd/toolbox/arithmetic/functions/iceil.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/functions/scalar/ceil.hpp>
#include <boost/simd/include/functions/scalar/is_nan.hpp>
#include <boost/simd/include/functions/scalar/is_inf.hpp>
#include <boost/simd/include/functions/scalar/is_ltz.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/valmax.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::iceil_, tag::cpu_, (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1) { return a0; }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::iceil_, tag::cpu_, (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {
    typedef typename dispatch::meta::as_integer<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      if (boost::simd::is_inf(a0))
      {
        if (boost::simd::is_ltz(a0))
        return boost::simd::Valmin<result_type>();
        else
        return  boost::simd::Valmax<result_type>();
      }

      if (boost::simd::is_nan(a0)) return Zero<result_type>();

      return result_type(boost::simd::ceil(a0));
    }
  };
} } }

#endif
