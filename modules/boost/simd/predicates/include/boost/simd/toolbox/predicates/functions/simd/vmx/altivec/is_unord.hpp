//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_SIMD_VMX_ALTIVEC_IS_UNORD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_SIMD_VMX_ALTIVEC_IS_UNORD_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/toolbox/predicates/functions/is_unord.hpp>
#include <boost/simd/include/functions/simd/is_equal.hpp>
#include <boost/simd/include/functions/simd/is_greater.hpp>
#include <boost/simd/include/functions/simd/logical_or.hpp>
#include <boost/simd/include/functions/simd/logical_not.hpp>
#include <boost/simd/include/constants/false.hpp>
#include <boost/simd/sdk/simd/logical.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_unord_, boost::simd::tag::altivec_, (A0)
                            , ((simd_<floating_<A0>, boost::simd::tag::altivec_>))
                              ((simd_<floating_<A0>, boost::simd::tag::altivec_>))
                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
       return logical_not(
         logical_or( is_equal(a0, a1)
                   , logical_or( is_greater(a1, a0)
                               , is_greater(a0, a1)
                               )
                   )
       );
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_unord_, boost::simd::tag::altivec_, (A0)
                            , ((simd_<integer_<A0>, boost::simd::tag::altivec_>))
                              ((simd_<integer_<A0>, boost::simd::tag::altivec_>))
                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const&, A0 const&) const
    {
       return False<result_type>();
    }
  };
} } }

#endif
#endif
