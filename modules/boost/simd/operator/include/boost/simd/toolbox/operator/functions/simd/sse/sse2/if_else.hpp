//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_SSE2_IF_ELSE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_SSE2_IF_ELSE_HPP_INCLUDED
#include <boost/simd/toolbox/operator/functions/if_else.hpp>
#include <boost/simd/include/functions/bitwise_select.hpp>
#include <boost/simd/include/functions/is_nez.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::if_else_, boost::simd::tag::sse2_, (A0)(A1)
                            , ((simd_< logical_<A0>, boost::simd::tag::sse_ >))
                              ((simd_< arithmetic_<A1>, boost::simd::tag::sse_ >))
                              ((simd_< arithmetic_<A1>, boost::simd::tag::sse_ >))
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A1&a2) const
    {
      return bitwise_select(bitwise_cast<A1>(a0), a1, a2);
    }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::if_else_, boost::simd::tag::sse2_, (A0)(A1)
                            , ((simd_< arithmetic_<A0>, boost::simd::tag::sse_ >))
                              ((simd_< arithmetic_<A1>, boost::simd::tag::sse_ >))
                              ((simd_< arithmetic_<A1>, boost::simd::tag::sse_ >))
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A1&a2) const
    {
      return  bitwise_select( genmask(a0), a1, a2 );
    }
  };  
} } }

#endif
