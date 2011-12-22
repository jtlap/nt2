//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_UNALIGNED_LOAD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_UNALIGNED_LOAD_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/toolbox/operator/functions/unaligned_load.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <iterator>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_load_, boost::simd::tag::altivec_
                            , (A0)(A1)(A2)
                            , (iterator_< scalar_< arithmetic_<A0> > >)
                              (scalar_< fundamental_<A1> >)
                              ((target_<simd_<arithmetic_<A2>,boost::simd::tag::altivec_> >))
                            )
  {
    typedef typename A2::type result_type;
    typedef native<boost::simd::uint8_t, boost::simd::tag::altivec_> n_t;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&)const
    {
      static std::size_t sz   = sizeof(typename std::iterator_traits<A0>::value_type);
      static std::size_t card = meta::cardinal_of<result_type>::value;
      result_type MSQ  = {vec_ld(a1*sz  ,a0)};
      result_type LSQ  = {vec_ld((a1*sz)+card*sz-1 ,a0)};
      n_t         mask = {vec_lvsl(a1*sz,a0)};
      result_type that = {vec_perm(MSQ(), LSQ(), mask())};
      return that;
    }
  };
} } }

#endif
#endif /* BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_UNALIGNED_LOAD_HPP_INCLUDED */
