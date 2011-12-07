//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_SIMD_SSE_SSE2_IF_ELSE_ZERO_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_SIMD_SSE_SSE2_IF_ELSE_ZERO_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT 
#include <boost/simd/include/functions/if_else_zero.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/include/functions/bitwise_and.hpp>
#include <boost/simd/include/functions/genmask.hpp>
#include <boost/simd/sdk/simd/logical.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::if_else_zero_, boost::simd::tag::sse2_
                                         , (A0)(A1)
                                         , (boost::mpl::equal_to < boost::simd::meta::cardinal_of<A0>
                                                        , boost::simd::meta::cardinal_of<A1>
                                                        >
                                  )
                                , ((simd_<logical_<A0>,boost::simd::tag::sse_>))
                                  ((simd_<arithmetic_<A1>,boost::simd::tag::sse_>))
                                )
  {
    typedef A1 result_type;
    inline result_type
    operator()(A0 const& a0, A1 const& a1) const
    {
      return bitwise_and(a1, bitwise_cast<A1>(a0));
    }
  };
} } }

#endif
#endif
