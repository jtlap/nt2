//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_SIMD_VMX_ALTIVEC_IS_GREATER_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_SIMD_VMX_ALTIVEC_IS_GREATER_EQUAL_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/toolbox/predicates/functions/is_greater_equal.hpp>
#include <boost/simd/include/functions/simd/logical_not.hpp>
#include <boost/simd/sdk/simd/logical.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_greater_equal_, boost::simd::tag::altivec_, (A0)
                            , ((simd_<floating_<A0>, boost::simd::tag::altivec_>))
                              ((simd_<floating_<A0>, boost::simd::tag::altivec_>))
                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      result_type that = vec_cmpge(a0(),a1());
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_greater_equal_, boost::simd::tag::altivec_, (A0)
                            , ((simd_<integer_<A0>, boost::simd::tag::altivec_>))
                              ((simd_<integer_<A0>, boost::simd::tag::altivec_>))
                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      result_type lt = vec_cmplt(a0(),a1());
      return !lt;
    }
  };
} } }

#endif
#endif
