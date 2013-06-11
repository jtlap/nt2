//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_COMMON_STORE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_COMMON_STORE_HPP_INCLUDED

#include <boost/simd/memory/functions/store.hpp>
#include <boost/simd/memory/functions/details/store.hpp>
#include <boost/simd/sdk/meta/iterate.hpp>
#include <boost/simd/include/functions/simd/insert.hpp>
#include <boost/simd/include/functions/simd/extract.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/pointee.hpp>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY - SIMD store without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::store_
                                    , tag::cpu_
                                    , (A0)(A1)(X)
                                    , ((simd_< unspecified_<A0>, X >))
                                      (iterator_<unspecified_<A1> >)
                                    )
  {
    typedef void result_type;
    typedef typename boost::pointee<A1>::type stype;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, A1 a1) const
    {
      for(std::size_t i=0; i!=meta::cardinal_of<A0>::value; ++i)
        a1[i] = static_cast<stype>(a0[i]);
    }
  };

  /// INTERNAL ONLY - SIMD store via scalar emulation with offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::store_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)(X)
                                    , ((simd_< unspecified_<A0>, X >))
                                      (iterator_< unspecified_<A1> >)
                                      (scalar_< integer_<A2> >)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type
    operator()(const A0& a0, A1 a1, A2 a2) const
    {
      boost::simd::store(a0,a1+a2);
    }
  };

  /// INTERNAL ONLY - SIMD scatter store via scalar emulation
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::store_
                                      , tag::cpu_
                                      , (A0)(A1)(A2)(X)(Y)
                                      , (mpl::equal_to
                                            < boost::simd::meta::cardinal_of<A0>
                                            , boost::simd::meta::cardinal_of<A2>
                                            >
                                        )
                                      , ((simd_< unspecified_<A0>, X >))
                                        (iterator_< scalar_< unspecified_<A1> > >)
                                        ((simd_< integer_<A2>, Y >))
                                      )
  {
    typedef void result_type;
    typedef typename boost::pointee<A1>::type stype;

    BOOST_FORCEINLINE result_type
    operator()(const A0& a0, A1 a1, A2 const& a2) const
    {
      for(std::size_t i=0; i<meta::cardinal_of<A0>::value; ++i)
        a1[a2[i]] = static_cast<stype>(a0[i]);
    }
  };

  /// INTERNAL ONLY - SIMD store for Fusion Sequence with offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::store_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)(X)
                                    , ((simd_< fusion_sequence_<A0>, X >))
                                      (fusion_sequence_<A1>)
                                      (generic_< integer_<A2> >)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type
    operator()(const A0& a0, const A1& a1, const A2& a2) const
    {
      static const int N = fusion::result_of::size<A1>::type::value;
      meta::iterate<N>( details::storer< boost::simd::
                                         tag::store_(A0, A1, A2)
                                       >(a0, a1, a2)
                      );
    }
  };

  /// INTERNAL ONLY - SIMD store for Fusion Sequence without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::store_
                                    , tag::cpu_
                                    , (A0)(A1)(X)
                                    , ((simd_< fusion_sequence_<A0>, X >))
                                      (fusion_sequence_<A1>)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1& a1) const
    {
      static const int N = fusion::result_of::size<A1>::type::value;
      meta::iterate<N>( details::storer< boost::simd::
                                         tag::store_(A0, A1)
                                       >(a0, a1)
                      );
    }
  };
} } }

#endif
