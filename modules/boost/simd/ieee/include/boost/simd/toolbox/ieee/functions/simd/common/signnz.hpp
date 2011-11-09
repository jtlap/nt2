//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_SIGNNZ_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_SIGNNZ_HPP_INCLUDED
#include <boost/simd/include/constants/digits.hpp>
#include <boost/simd/include/functions/is_ltz.hpp>
#include <boost/simd/include/functions/is_gez.hpp>
#include <boost/simd/include/functions/is_gtz.hpp>
#include <boost/simd/include/functions/is_nan.hpp>
#include <boost/simd/include/functions/is_positive.hpp>
#include <boost/simd/include/functions/seladd.hpp>
#include <boost/simd/include/functions/if_nan_else.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/one.hpp>  
#include <iostream>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::signnz_, tag::cpu_,
                         (A0)(X),
                         ((simd_<integer_<A0>,X>))
                        )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      return typed_bool(is_ltz(a0))-typed_bool(is_gez(a0)); // here True is -1 False 0 !
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::signnz_, tag::cpu_,
                         (A0)(X),
                         ((simd_<unsigned_<A0>,X>))
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


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::signnz_, tag::cpu_,
                         (A0)(X),
                         ((simd_<floating_<A0>,X>))
                        )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      //      return seladd(is_nan(a0), seladd(is_positive(a0), Mone<A0>(),Two<A0>()), a0);
      std::cout << "icitte" << std::endl; 
      return if_nan_else(is_nan(a0), select(is_negative(a0), Mone<A0>(), One<A0>())); 
    }
  };
} } }
#endif
