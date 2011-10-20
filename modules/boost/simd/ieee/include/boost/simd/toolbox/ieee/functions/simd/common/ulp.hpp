//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_ULP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_ULP_HPP_INCLUDED
#include <boost/simd/include/constants/digits.hpp> 
#include <boost/simd/include/constants/infinites.hpp>
#include <boost/simd/include/functions/abs.hpp>
#include <boost/simd/include/functions/predecessor.hpp>
#include <boost/simd/include/functions/successor.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::ulp_, tag::cpu_,
                             (A0)(X),
                             ((simd_<arithmetic_<A0>,X>))
                             )
  {
    typedef A0 result_type; 
    inline result_type operator()(const A0&)const
      {
        return One<A0>();
      }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is floating_
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ulp_, tag::cpu_
                              , (A0)(X)
                              , ((simd_<floating_<A0>,X>))
                              )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
      {
        const A0 x = boost::simd::abs(a0);
        A0 xp = boost::simd::predecessor(x);
        A0 xs = boost::simd::successor(x); 
        return boost::simd::select(boost::simd::is_equal(x, boost::simd::Inf<A0>()),
                                boost::simd::Nan<A0>(), boost::simd::min(x-xp, xs - x));
      }
  };
} } }


#endif
