//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_SPLAT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_SPLAT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/sdk/simd/category.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::splat_, boost::simd::tag::altivec_, (A0)(A1)
                            , (scalar_< fundamental_<A0> >)
                              ((target_<simd_<arithmetic_<A1>,boost::simd::tag::altivec_> >))
                            )
  {
    typedef typename A1::type result_type;

    BOOST_DISPATCH_CALL(2)
    {
      result_type v;
      v[0] = a0;
      result_type that = {vec_splat(v(), 0)};
      return that;
    }
  };
} } }

#endif
#endif
