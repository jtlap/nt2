//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTION_SIMD_SSE_SSE2_IS_NOT_EQUAL_TO_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTION_SIMD_SSE_SSE2_IS_NOT_EQUAL_TO_HPP_INCLUDED

#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/simd/sdk/meta/downgrade.hpp>
#include <boost/simd/include/functions/complement.hpp>
#include <boost/simd/include/functions/is_equal.hpp>
#include <boost/simd/include/functions/bitwise_or.hpp>
#include <boost/simd/include/functions/minus.hpp>
#include <boost/simd/include/constants/digits.hpp>
#include <iostream>
namespace boost { namespace dispatch
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::is_not_equal_, tag::cpu_
                            , (A0)
                            , ((simd_<double_<A0>,tag::sse_>))
                              ((simd_<double_<A0>,tag::sse_>))
                            )
  {
    typedef A0 result_type;

    BOOST_DISPATCH_FUNCTOR_CALL_REPEAT(2)
    {
      A0 that = { _mm_cmpneq_pd(a0,a1) };
      return that;
    }
  };

  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::is_not_equal_, tag::cpu_
                            , (A0)
                            , ((simd_<float_<A0>,tag::sse_>))
                              ((simd_<float_<A0>,tag::sse_>))
                            )
  {
    typedef A0 result_type;

    BOOST_DISPATCH_FUNCTOR_CALL_REPEAT(2)
    {
      A0 that = { _mm_cmpneq_ps(a0,a1) };
      return that;
    }
  };

  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::is_not_equal_, tag::cpu_
                            , (A0)
                            , ((simd_<integer_<A0>,tag::sse_>))
                              ((simd_<integer_<A0>,tag::sse_>))
                            )
  {
    typedef A0 result_type;

    BOOST_DISPATCH_FUNCTOR_CALL_REPEAT(2)
    {
      A0 that = boost::simd::complement(boost::simd::eq(a0,a1));
      return that;
    }
  };

  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::is_not_equal_, tag::cpu_
                            , (A0)
                            , ((simd_<ints64_<A0>,tag::sse_>))
                              ((simd_<ints64_<A0>,tag::sse_>))
                            )
  {
    typedef A0 result_type;

    BOOST_DISPATCH_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::downgrade<A0, unsigned>::type  type;
      type tmp      = { a0 - a1 };
      type tmp2     = { _mm_shuffle_epi32(tmp, _MM_SHUFFLE(2, 3, 0, 1)) };
      tmp           = boost::simd::neq(tmp,Zero<type>());
      A0   that     = { tmp | tmp2 };
      return that;
    }
  };
} }

#endif
