//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_LOAD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_LOAD_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
////////////////////////////////////////////////////////////////////////////////
// load for AVX SIMD types
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/toolbox/operator/functions/load.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/dispatch/meta/mpl.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::load_ , boost::simd::tag::avx_
                            , (A0)(A1)(A2)
                            , (iterator_< scalar_< double_<A0> > >)
                              (scalar_< fundamental_<A1> >)
                              ((target_< simd_< double_<A2>, boost::simd::tag::avx_ > >))
                            )
  {
    typedef typename A2::type result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&)const
    {
      BOOST_ASSERT_MSG
      ( boost::simd::memory::is_aligned(a0+a1,sizeof(result_type))
      , "load has been called on a pointer which alignment is not "
        "compatible with current SIMD extension."
      );

      return _mm256_load_pd(a0+a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::load_ , boost::simd::tag::avx_
                            , (A0)(A1)(A2)
                            , (iterator_< scalar_< single_<A0> > >)
                              (scalar_< fundamental_<A1> >)
                              ((target_< simd_< single_<A2>, boost::simd::tag::avx_ > >))
                            )
  {
    typedef typename A2::type result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&)const
    {
      BOOST_ASSERT_MSG
      ( boost::simd::memory::is_aligned(a0+a1,sizeof(result_type))
      , "load has been called on a pointer which alignment is not "
        "compatible with current SIMD extension."
      );

      return _mm256_load_ps(a0+a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::load_ , boost::simd::tag::avx_
                            , (A0)(A1)(A2)
                            , (iterator_< scalar_< integer_<A0> > >)
                              (scalar_< fundamental_<A1> >)
                              ((target_< simd_< integer_<A2>, boost::simd::tag::avx_ > >))
                            )
  {
    typedef typename A2::type result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&)const
    {
      BOOST_ASSERT_MSG
      ( boost::simd::memory::is_aligned(a0+a1,sizeof(result_type))
      , "load has been called on a pointer which alignment is not "
        "compatible with current SIMD extension."
      );

      return _mm256_load_si256(reinterpret_cast<__m256i const*>(a0+a1));
    }
  };

} } }


#include <boost/simd/toolbox/operator/functions/simd/sse/avx/details/load_offset.hpp>

#endif
#endif
