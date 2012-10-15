//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SCALAR_UNALIGNED_LOAD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SCALAR_UNALIGNED_LOAD_HPP_INCLUDED

#include <boost/simd/toolbox/operator/functions/unaligned_load.hpp>
#include <boost/simd/toolbox/operator/functions/simd/common/details/details_load_store.hpp>
#include <boost/simd/sdk/meta/iterate.hpp>
#include <boost/dispatch/meta/mpl.hpp>
#include <boost/simd/sdk/memory/details/category.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>

namespace boost { namespace simd { namespace ext
{
//==============================================================================
// unaligned_load_ without offset
//==============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_load_ , tag::cpu_
                            , (A0)(A1)(A2)
                            , (iterator_< unspecified_<A0> >)
                              (scalar_< fundamental_<A1> >)
                              (target_< unspecified_<A2> >)
                            )
  {
    typedef typename A2::type result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&) const
    {
      A0 that = a0;
      std::advance(that,a1);
      return *that;
    }
  };

//==============================================================================
// unaligned_load_ with offset
//==============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(  boost::simd::tag::unaligned_load_ , tag::cpu_
                            , (A0)(A1)(A2)(A3)
                            , (iterator_< unspecified_<A0> >)
                              (scalar_< fundamental_<A1> >)
                              (target_< unspecified_<A2> >)
                              (mpl_integral_< scalar_< integer_<A3> > >)
                            )
  {
    typedef typename A2::type result_type;
    inline result_type operator()(const A0& a0, const A1& a1,
                                  const A2&, const A3&) const
    {
      A0 that = a0;
      std::advance(that,a1+A3::value);
      return *that;
    }
  };

  // fusion sequence
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_load_, tag::cpu_
                                   , (A0)(A1)(A2)
                                   , (fusion_sequence_<A0>)
                                     (generic_< integer_<A1> >)
                                     ((target_< fusion_sequence_<A2> >))
                                   )
  {
    typedef typename A2::type result_type;

    inline result_type operator()(const A0& a0, const A1& a1, const A2&) const
    { 
      static const int N = fusion::result_of::size<A0>::type::value;
      result_type that;
      meta::iterate<N>( details::loader< boost::simd::tag::unaligned_load_
                                       , A0
                                       , A1
                                       , result_type
                                       >(a0, a1, that)
                      );
      return that;
    }
  };

} } }

#endif
