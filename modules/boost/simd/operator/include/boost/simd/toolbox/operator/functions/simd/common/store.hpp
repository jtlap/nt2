//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_STORE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_STORE_HPP_INCLUDED

#include <boost/simd/toolbox/operator/functions/store.hpp>
#include <boost/simd/include/functions/simd/unaligned_store.hpp>
#include <boost/simd/toolbox/operator/functions/simd/common/details/details_load_store.hpp>
#include <boost/simd/sdk/meta/iterate.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd { namespace ext
{
  // regular store
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::store_ , tag::cpu_
                            , (A0)(A1)(A2)(X)
                            , ((simd_< unspecified_<A0>, X >))
                              (iterator_< unspecified_<A1> >)
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef typename dispatch::meta::
            call<tag::unaligned_store_(A0 const&, A1 const&, A2 const&)>::type
    result_type;
    BOOST_SIMD_FUNCTOR_CALL(3)
    {
      BOOST_ASSERT_MSG
      ( boost::simd::is_aligned(a1,BOOST_SIMD_CONFIG_ALIGNMENT)
     && boost::simd::is_aligned(a1+a2,BOOST_SIMD_CONFIG_ALIGNMENT)
      , "Unaligned memory location. You tried to store with a pointer that"
        " is not aligned on the simd vector size.");
      return unaligned_store(a0, a1, a2);
    }
  };

  // scatter
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::store_, tag::cpu_
                            , (A0)(A1)(A2)(X)(Y)
                            , (mpl::equal_to< boost::simd::meta::cardinal_of<A0>
                                            , boost::simd::meta::cardinal_of<A2>
                                            >
                              )
                            , ((simd_< unspecified_<A0>, X >))
                              (iterator_< unspecified_<A1>  >)
                              ((simd_< integer_<A2>, Y >))
                            )
  {
    typedef typename dispatch::meta::
            call<tag::unaligned_store_(A0 const&, A1 const&, A2 const&)>::type
    result_type;
    BOOST_SIMD_FUNCTOR_CALL(3)
    {
      BOOST_ASSERT_MSG
      ( boost::simd::is_aligned(a1,BOOST_SIMD_CONFIG_ALIGNMENT)
      , "Unaligned memory location. You tried to store with a pointer that"
        " is not aligned on the simd vector size.");
      return unaligned_store(a0, a1, a2);
    }
  };

  // fusion sequence
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::store_, tag::cpu_
                                   , (A0)(A1)(A2)(X)
                                   , ((simd_< fusion_sequence_<A0>, X >))
                                     (fusion_sequence_<A1>)
                                     (generic_< integer_<A2> >)
                                   )
  {
    typedef A0 result_type;

    inline result_type operator()(const A0& a0, const A1& a1, const A2& a2) const
    {
      static const int N = fusion::result_of::size<A1>::type::value;
      meta::iterate<N>( details::storer< boost::simd::tag::store_
                                       , A0
                                       , A1
                                       , A2
                                       >(a0, a1, a2)
                      );
      return a0;
    }
  };

} } }

#endif
