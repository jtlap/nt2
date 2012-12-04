//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_LOAD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_LOAD_HPP_INCLUDED

#include <boost/simd/toolbox/operator/functions/load.hpp>
#include <boost/simd/include/functions/simd/unaligned_load.hpp>
#include <boost/simd/toolbox/operator/functions/simd/common/details/details_load_store.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/sdk/meta/iterate.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd { namespace ext
{
  // regular load
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::load_, tag::cpu_
                            , (A0)(A1)(A2)(X)
                            , (iterator_<unspecified_<A0> >)
                              (scalar_< fundamental_<A1> >)
                              ((target_< simd_< unspecified_<A2>, X > >))
                            )
  {
    typedef typename dispatch::meta::
            call<tag::unaligned_load_(A0 const&, A1 const&, A2 const&)>::type
    result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&) const
    {
      BOOST_ASSERT_MSG
      ( boost::simd::memory::is_aligned(a0,BOOST_SIMD_CONFIG_ALIGNMENT)
     && boost::simd::memory::is_aligned(a0+a1,BOOST_SIMD_CONFIG_ALIGNMENT)
      , "Unaligned memory location. You tried to load with a pointer that"
        " is not aligned on the simd vector size.");
      return unaligned_load<typename A2::type>(a0, a1);
    }
  };

  // shifted load
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::load_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(X)
                            , (iterator_<unspecified_<A0> >)
                              (scalar_< fundamental_<A1> >)
                              ((target_< simd_< unspecified_<A2>, X > >))
                              (mpl_integral_< scalar_< integer_<A3> > >)
                            )
  {
    typedef typename dispatch::meta::
            call<tag::unaligned_load_(A0 const&, A1 const&, A2 const&, A3 const&)>::type
    result_type;
    inline result_type operator()(const A0& a0, const A1& a1,
                                  const A2&, const A3&) const
    {
      BOOST_ASSERT_MSG
      ( boost::simd::memory::is_aligned(a0,BOOST_SIMD_CONFIG_ALIGNMENT)
     && boost::simd::memory::is_aligned(a0+a1,BOOST_SIMD_CONFIG_ALIGNMENT)
      , "Unaligned memory location. You tried to load with a pointer that"
        "is not aligned on the simd vector size.");
      return unaligned_load<typename A2::type, A3::value>(a0, a1);
    }
  };

  // gather
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::load_, tag::cpu_
                            , (A0)(A1)(A2)(X)(Y)
                            , (mpl::equal_to< boost::simd::meta::cardinal_of<A1>
                                            , boost::simd::meta::cardinal_of<typename A2::type>
                                            >
                              )
                            , (iterator_< unspecified_<A0> >)
                              ((simd_< integer_<A1>, X >))
                              ((target_< simd_< unspecified_<A2>, Y > >))
                            )
  {
    typedef typename dispatch::meta::
            call<tag::unaligned_load_(A0 const&, A1 const&, A2 const&)>::type
    result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&) const
    {
      BOOST_ASSERT_MSG
      ( boost::simd::memory::is_aligned(a0,BOOST_SIMD_CONFIG_ALIGNMENT)
      , "Unaligned memory location. You tried to load with a pointer that"
        "is not aligned on the simd vector size.");
      return unaligned_load<typename A2::type>(a0, a1);
    }
  };

  // logical
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::load_, tag::cpu_
                            , (A0)(A1)(A2)(X)
                            , (iterator_<scalar_< logical_<A0> > >)
                              (scalar_< fundamental_<A1> >)
                              ((target_< simd_< logical_<A2>, X > >))
                            )
  {
    typedef typename A2::type result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&) const
    {
      BOOST_ASSERT_MSG
      ( boost::simd::memory::is_aligned(a0,BOOST_SIMD_CONFIG_ALIGNMENT)
      , "Unaligned memory location. You tried to load with a pointer that"
        "is not aligned on the simd vector size.");
      return unaligned_load<typename A2::type>(a0, a1);
    }
  };

  // fusion sequence
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::load_, tag::cpu_
                                   , (A0)(A1)(A2)(X)
                                   , (fusion_sequence_<A0>)
                                     (generic_< integer_<A1> >)
                                     ((target_< simd_< fusion_sequence_<A2>, X > >))
                                   )
  {
    typedef typename A2::type result_type;

    inline result_type operator()(const A0& a0, const A1& a1, const A2&) const
    {
      static const int N = fusion::result_of::size<A0>::type::value;
      result_type that;
      meta::iterate<N>( details::loader< boost::simd::tag::load_
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
