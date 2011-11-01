//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_SIMD_COMMON_TYPED_BOOL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_SIMD_COMMON_TYPED_BOOL_HPP_INCLUDED

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::typed_bool_, tag::cpu_, 
                                     (A0)(X), 
                             ((simd_<logical_<A0>,X>))
                             )
  {
    typedef typename A0::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return native_cast<result_type>(a0);
    }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::typed_bool_, tag::cpu_
                             , (A0)(X)
                             , ((simd_< arithmetic_<A0>, X >))
                             )
  {
    typedef A0 result_type;
    inline result_type operator()(const A0& a0) const
    {
      return native_cast<result_type>(is_nez(a0)); 
    }
  };
} } }

#endif
